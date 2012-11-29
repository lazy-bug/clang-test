#include <clang/Frontend/CompilerInstance.h>

#include "testvisitor.hpp"
#include "DeclToString.hpp"

clang::ASTConsumer *OutlineBuilderAction::CreateASTConsumer(clang::CompilerInstance &compInstance, llvm::StringRef filename) {
    compInstance.getDiagnostics().setClient(new clang::IgnoringDiagConsumer(), true);
    return new OutlineBuilderConsumer(filename.str());
}

OutlineBuilderConsumer::OutlineBuilderConsumer(const std::string& filename) : filename(filename) {
}

void OutlineBuilderConsumer::HandleTranslationUnit(clang::ASTContext &ctxt) {
    OutlineBuildingVisitor Visitor(&ctxt, filename);
    Visitor.TraverseDecl(ctxt.getTranslationUnitDecl());
    std::stringstream sout;
    char sep = ' ';
    std::map<std::string, std::string>:: iterator it = Visitor.filenames.begin();
    sout << "{\"files\" : [";
    while (it != Visitor.filenames.end()) {
        sout << sep << "{\"fileid\" : \"" <<  it->second << "\", \"filepath\" : \"" << it->first << "\"}";
        sep = ',';
        it++;
    }
    sout << "], \"Decls\" : [";
    sout << Visitor.ss.str();
    sout << "]}";
    
    std::cout << sout.str() << std::endl;
}

//bool OutlineBuildingVisitor::VisitCXXMethodDecl(CXXMethodDecl* methodDecl) {
//    return VisitFunctionDecl(methodDecl);
//}

bool OutlineBuildingVisitor::shouldVisit(const FullSourceLoc& loc) {
    if (!ctxt->getSourceManager().isFromMainFile(loc))
        return false;
    return true;
}

bool OutlineBuildingVisitor::VisitFunctionDecl(FunctionDecl* methodDecl) {
    // {"t" : "F", "a" : "", "n" : "name", "fr", "file1", "l" : 200, "c" : 21}
    std::string name;
    std::string type = "M";
    size_t line = 0, col = 0;
    std::string filename = "";
    std::string attr = "";
    
    const FullSourceLoc& loc = ctxt->getFullLoc(methodDecl->getLocation());
    if (!shouldVisit(loc)) return true;
    
    switch (methodDecl->getAccess()) {
        case clang::AS_none:
        case clang::AS_private:
            attr += "-";
            break;
        case clang::AS_protected:
            attr += "*";
            break;
        case clang::AS_public:
            attr = "+";
            break;
    }
    std::string tname;
    llvm::raw_string_ostream out(tname);
    clang::PrintingPolicy pp = ctxt->getPrintingPolicy();
    pp.TerseOutput = 1;
    pp.SuppressScope = 1;
    pp.SuppressInitializers = 1;
    DeclToString declToString(out, pp);
    declToString.VisitFunctionDecl(methodDecl);
    if (methodDecl->isPure()) attr += "P";
    getLocationFromFullSourceLoc(loc, filename, line, col);
    name = out.str();
    if (methodDecl->isTemplateDecl()) attr += "T";
    ss << sep << "{\"t\" : \"" << type << "\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str()
            << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"a\" : \"" << attr << "\"}" << std::endl;
    sep = ", ";

    return true;
}


bool OutlineBuildingVisitor::TraverseCXXRecordDecl(CXXRecordDecl* recordDecl) {
    // {"t" : "C", "a" : "", "n" : "name", "fr", "file1", "l" : 200, "c" : 21, "ch" : [{},{}]}
    std::string name = "*";
    std::string type = "";
    size_t line = 0, col = 0;
    std::string filename = "";
    std::string attr = "";
    
    const FullSourceLoc& loc = ctxt->getFullLoc(recordDecl->getLocation());

    if (!shouldVisit(loc)) return true;
    
    if (!recordDecl->isCompleteDefinition())
        return true;
    if (recordDecl->isLocalClass())
        return true;

    switch (recordDecl->getTagKind()) {
        case clang::TTK_Class:
            type = "C";
            break;
        case clang::TTK_Enum:
            type = "E";
            break;
        case clang::TTK_Interface:
            type = "I";
            break;
        case clang::TTK_Struct:
            type = "S";
            break;
        case clang::TTK_Union:
            type = "U";
            break;
    }
    switch (recordDecl->getAccess()) {
        case clang::AS_none:
        case clang::AS_private:
            attr += "-";
            break;
        case clang::AS_protected:
            attr += "*";
            break;
        case clang::AS_public:
            attr = "+";
            break;
    }
    getLocationFromFullSourceLoc(loc, filename, line, col);

    name = recordDecl->getNameAsString();

    if (recordDecl->isAnonymousStructOrUnion()) attr += "A";
    if (recordDecl->isPolymorphic()) attr += "P";
    if (recordDecl->isTemplateDecl()) attr += "T";

    ss << sep << "{\"t\" : \"" << type << "\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str()
            << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"a\" : \"" << attr << "\", \"ch\" : [" << std::endl;
    sep = "";
    Base::TraverseCXXRecordDecl(recordDecl);
    ss << "]}" << std::endl;
    sep = ", ";
    return true;
}

bool OutlineBuildingVisitor::TraverseNamespaceDecl(NamespaceDecl* namespaceDecl) {
    // {"t" : "N", "n" : "*", "fr": "file1", "l" : 200, "c" : 21, "ch" : [{},{},{}]}
    std::string name = "*"; // constant for anonymous
    size_t line = 0, col = 0;
    std::string filename = "";
    const FullSourceLoc& loc = ctxt->getFullLoc(namespaceDecl->getLocation());
    
    if (!shouldVisit(loc)) return true;
    
    if (!namespaceDecl->isAnonymousNamespace()) {
        name = namespaceDecl->getNameAsString();
    }
    getLocationFromFullSourceLoc(loc, filename, line, col);
    ss << sep << "{\"t\" : \"N\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str()
            << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"ch\" : [" << std::endl;
    sep = "";
    Base::TraverseNamespaceDecl(namespaceDecl);
    ss << "]}" << std::endl;
    sep = ", ";
    return true;
}

void OutlineBuildingVisitor::getLocationFromFullSourceLoc(const FullSourceLoc& sourceLoc, std::string& filename, size_t& line, size_t& col) {
    if (sourceLoc.isValid()) {
        line = sourceLoc.getSpellingLineNumber();
        col = sourceLoc.getSpellingColumnNumber();

        filename = ctxt->getSourceManager().getFilename(sourceLoc);

        std::map<std::string, std::string>::iterator it = filenames.find(filename);
        if (it != filenames.end()) {
            filename = it->second;
        } else {
            fileno++;
            std::stringstream file;
            file << "file" << fileno;
            filenames[filename] = file.str();
            filename = file.str();
        }
    }
}

void ClangToolRunner::runTool() {
    tool.run(clang::tooling::newFrontendActionFactory<OutlineBuilderAction > ());
}
