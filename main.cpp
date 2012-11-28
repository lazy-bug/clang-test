#include <iostream>
#include <string>
#include <sstream>
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Type.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Frontend/ASTUnit.h>
#include <map>

using namespace clang;

class OutlineBuildingVisitor : public clang::RecursiveASTVisitor<OutlineBuildingVisitor> {
public:
    typedef clang::RecursiveASTVisitor<OutlineBuildingVisitor> BaseClass;
    explicit OutlineBuildingVisitor(ASTContext *Context)
    : Context(Context), ss(""), sep(""), fileno(0) {
    }
    
    bool VisitCXXMethodDecl(CXXMethodDecl* D) {
        return VisitFunctionDecl(D);
    }
    
    bool VisitFunctionDecl(FunctionDecl* methodDecl) {
        // {"t" : "F", "a" : "", "n" : "name", "fr", "file1", "l" : 200, "c" : 21}
        std::string name = "*";
        std::string type = "M";
        size_t line = 0, col = 0;
        std::string filename = "";
        std::string attr = "";

        switch (methodDecl->getAccess()) {
            case clang::AS_none:
            case clang::AS_private:
                attr += "-"; break;
            case clang::AS_protected:
                attr += "*"; break;
            case clang::AS_public:
                attr = "+"; break;
        }
        
        if (methodDecl->isPure()) attr += "P";
        
        getLocationFromFullSourceLoc(Context->getFullLoc(methodDecl->getLocation()), filename, line, col);
        name = methodDecl->getNameAsString();
        if (methodDecl->isTemplateDecl()) attr += "T";
        ss << sep << "{\"t\" : \"" << type << "\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str() 
                << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"a\" : \"" << attr << "\"}" << std::endl;
        sep = ", ";
        
        return true;
    }
    
    bool TraverseCXXRecordDecl(CXXRecordDecl* recordDecl) {
        // {"t" : "C", "a" : "", "n" : "name", "fr", "file1", "l" : 200, "c" : 21, "ch" : [{},{}]}
        std::string name = "*";
        std::string type = "";
        size_t line = 0, col = 0;
        std::string filename = "";
        std::string attr = "";
        
        if (!recordDecl->isCompleteDefinition()) 
            return true;
        if (recordDecl->isLocalClass())
            return true;
        
        switch (recordDecl->getTagKind()) {
            case clang::TTK_Class: type = "C"; break;
            case clang::TTK_Enum: type = "E"; break;
            case clang::TTK_Interface: type = "I"; break;
            case clang::TTK_Struct: type = "S"; break;
            case clang::TTK_Union: type = "U"; break;
        }
        switch (recordDecl->getAccess()) {
            case clang::AS_none:
            case clang::AS_private:
                attr += "-"; break;
            case clang::AS_protected:
                attr += "*"; break;
            case clang::AS_public:
                attr = "+"; break;
        }
        getLocationFromFullSourceLoc(Context->getFullLoc(recordDecl->getLocation()), filename, line, col);
        
        name = recordDecl->getNameAsString();
        
        if (recordDecl->isAnonymousStructOrUnion()) attr += "A";
        if (recordDecl->isPolymorphic()) attr += "P";
        if (recordDecl->isTemplateDecl()) attr += "T";
        
        ss << sep << "{\"t\" : \"" << type << "\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str() 
                << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"a\" : \"" << attr << "\", \"ch\" : [";
        sep = "";
        BaseClass::TraverseCXXRecordDecl(recordDecl);
        ss << "]}" << std::endl;
        sep = ", ";
        return true;
    }
    
    bool TraverseNamespaceDecl(NamespaceDecl* namespaceDecl) {
        // {"t" : "N", "n" : "*", "fr": "file1", "l" : 200, "c" : 21, "ch" : [{},{},{}]}
        std::string name = "*"; // constant for anonymous
        size_t line = 0, col = 0;
        std::string filename = "";
        if (!namespaceDecl->isAnonymousNamespace()) {
            name = namespaceDecl->getNameAsString();
        } 
        getLocationFromFullSourceLoc(Context->getFullLoc(namespaceDecl->getLocation()), filename, line, col);
        ss << sep << "{\"t\" : \"N\", \"n\" : \"" << name.c_str() << "\", \"fr\" : \"" << filename.c_str() 
                << "\", \"l\" : " << line << ", \"c\" : " << col << ", \"ch\" : [";
        sep = "";
        BaseClass::TraverseNamespaceDecl(namespaceDecl);
        ss << "]}" << std::endl;
        sep = ", ";
        return true;
    }
    
    bool getLocationFromFullSourceLoc(const FullSourceLoc& sourceLoc, std::string& filename, size_t& line, size_t& col) {
        if (sourceLoc.isValid()) {
            line = sourceLoc.getSpellingLineNumber();
            col = sourceLoc.getSpellingColumnNumber();
            
            filename = Context->getSourceManager().getFilename(sourceLoc);
            
            std::map<std::string, std::string>::iterator it = filenames.find(filename);
            if (it != filenames.end()) {
                filename = it->second;
            } else {
                fileno++;
                std::stringstream file; file << "file" << fileno;
                filenames[filename] = file.str();
                filename = file.str();
            }
        }
    }
    std::stringstream ss;
private:
    std::string sep;
    ASTContext* Context;
    std::map<std::string, std::string> filenames;
    size_t fileno;
};

class OutlineBuilderConsumer : public clang::ASTConsumer {
public:

    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
        OutlineBuildingVisitor Visitor(&Context);
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        std::cout << Visitor.ss.str() << std::endl;
        
    }
private:

};

class OutlineBuilderAction : public clang::ASTFrontendAction {
public:
    virtual clang::ASTConsumer *CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
        return new OutlineBuilderConsumer;
    }
};

int main(int argc, const char * const *argv) {
    std::string err;
    std::vector<const char*> Argv;

    clang::tooling::JSONCompilationDatabase* cdb = clang::tooling::JSONCompilationDatabase::loadFromFile("/tmp/poco144/compile_commands.json", err);

    if (cdb != NULL) {
        std::vector<std::string> files;
        files.push_back("/Users/RamneekHanda/Downloads/poco-1.4.4/Foundation/src/ArchiveStrategy.cpp");
        clang::tooling::ClangTool tool(*cdb, files);
        
        tool.run(clang::tooling::newFrontendActionFactory<OutlineBuilderAction > ());
    } else {
        std::cout << "cdb is null" << "- " << err;
    }

    return 0;
}

