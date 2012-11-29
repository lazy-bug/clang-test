/**
 *
 *      ___                       ___     
 *     /\  \          ___        /\  \    
 *    /::\  \        /\  \      /::\  \   
 *   /:/\:\  \       \:\  \    /:/\ \  \  
 *  /:/  \:\  \      /::\__\  _\:\~\ \  \ 
 * /:/__/ \:\__\  __/:/\/__/ /\ \:\ \ \__\
 * \:\  \  \/__/ /\/:/  /    \:\ \:\ \/__/
 *  \:\  \       \::/__/      \:\ \:\__\  
 *   \:\  \       \:\__\       \:\/:/  /  
 *    \:\__\       \/__/        \::/  /   
 *     \/__/                     \/__/    
 *
 * CIS - Clang Indexing Service is a Project Manager & Source code indexing service
 * created so as to simplify the indexing of C/C++ based source code which use
 * standardized build mechanisms.
 * 
 **/

#ifndef TESTVISITOR_HPP
#define	TESTVISITOR_HPP

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
    typedef clang::RecursiveASTVisitor<OutlineBuildingVisitor> Base;

    explicit OutlineBuildingVisitor(ASTContext *ctxt, std::string& filename)
    : ctxt(ctxt), ss(""), sep(""), fileno(0), mainfilename(filename), fEntryPtr(ctxt->getSourceManager().getFileManager().getFile(filename.c_str(), false, false)) {
    }

    //bool VisitCXXMethodDecl(CXXMethodDecl* methodDecl);

    bool VisitFunctionDecl(FunctionDecl* methodDecl);

    bool TraverseCXXRecordDecl(CXXRecordDecl* recordDecl);

    bool TraverseNamespaceDecl(NamespaceDecl* namespaceDecl);

    void getLocationFromFullSourceLoc(const FullSourceLoc& sourceLoc, std::string& filename, size_t& line, size_t& col);

    std::stringstream ss;
    std::map<std::string, std::string> filenames;
private:
    bool shouldVisit(const FullSourceLoc& loc);
    std::string getParamsAsStr(FunctionDecl* functionDecl);
    
    std::string sep;
    ASTContext* ctxt;
    size_t fileno;
    std::string mainfilename;
    const FileEntry* fEntryPtr;
};

class OutlineBuilderConsumer : public clang::ASTConsumer {
public:
    OutlineBuilderConsumer(const std::string& filename);
    void HandleTranslationUnit(clang::ASTContext &ctxt);
private:
    std::string filename;
};

class OutlineBuilderAction : public clang::ASTFrontendAction {
public:
    clang::ASTConsumer *CreateASTConsumer(
            clang::CompilerInstance &compInstance, llvm::StringRef filename);
};

class ClangToolRunner {
    clang::tooling::ClangTool& tool;
public:

    ClangToolRunner(clang::tooling::ClangTool& tool) : tool(tool) {
    }
    void runTool();
};
#endif	/* TESTVISITOR_HPP */

