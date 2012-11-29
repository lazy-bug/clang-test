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

#ifndef DECLTOSTRING_HPP
#define	DECLTOSTRING_HPP

#include <clang/AST/DeclVisitor.h>
#include "llvm/Support/raw_ostream.h"
#include <clang/AST/PrettyPrinter.h>
#include <llvm/ADT/SmallVector.h>
#include <clang/Basic/Specifiers.h>
#include <clang/Basic/Module.h>

class DeclToString : public clang::DeclVisitor<DeclToString> {
    llvm::raw_ostream &Out;
    clang::PrintingPolicy Policy;
    unsigned Indentation;
    bool PrintInstantiation;

    llvm::raw_ostream& Indent() {
        return Indent(Indentation);
    }
    
    llvm::raw_ostream& Indent(unsigned Indentation);
    void ProcessDeclGroup(llvm::SmallVectorImpl<clang::Decl*>& Decls);

    void Print(clang::AccessSpecifier AS);

public:

    DeclToString(llvm::raw_ostream &Out, const clang::PrintingPolicy &Policy,
            unsigned Indentation = 0, bool PrintInstantiation = false)
    : Out(Out), Policy(Policy), Indentation(Indentation),
    PrintInstantiation(PrintInstantiation) {
    }

    void VisitDeclContext(clang::DeclContext *DC, bool Indent = true);

    void VisitTranslationUnitDecl(clang::TranslationUnitDecl *D);
    void VisitTypedefDecl(clang::TypedefDecl *D);
    void VisitTypeAliasDecl(clang::TypeAliasDecl *D);
    void VisitEnumDecl(clang::EnumDecl *D);
    void VisitRecordDecl(clang::RecordDecl *D);
    void VisitEnumConstantDecl(clang::EnumConstantDecl *D);
    void VisitFunctionDecl(clang::FunctionDecl *D);
    void VisitFieldDecl(clang::FieldDecl *D);
    void VisitVarDecl(clang::VarDecl *D);
    void VisitLabelDecl(clang::LabelDecl *D);
    void VisitParmVarDecl(clang::ParmVarDecl *D);
    void VisitFileScopeAsmDecl(clang::FileScopeAsmDecl *D);
    void VisitImportDecl(clang::ImportDecl *D);
    void VisitStaticAssertDecl(clang::StaticAssertDecl *D);
    void VisitNamespaceDecl(clang::NamespaceDecl *D);
    void VisitUsingDirectiveDecl(clang::UsingDirectiveDecl *D);
    void VisitNamespaceAliasDecl(clang::NamespaceAliasDecl *D);
    void VisitCXXRecordDecl(clang::CXXRecordDecl *D);
    void VisitLinkageSpecDecl(clang::LinkageSpecDecl *D);
    void VisitTemplateDecl(const clang::TemplateDecl *D);
    void VisitFunctionTemplateDecl(clang::FunctionTemplateDecl *D);
    void VisitClassTemplateDecl(clang::ClassTemplateDecl *D);
    void VisitObjCMethodDecl(clang::ObjCMethodDecl *D);
    void VisitObjCImplementationDecl(clang::ObjCImplementationDecl *D);
    void VisitObjCInterfaceDecl(clang::ObjCInterfaceDecl *D);
    void VisitObjCProtocolDecl(clang::ObjCProtocolDecl *D);
    void VisitObjCCategoryImplDecl(clang::ObjCCategoryImplDecl *D);
    void VisitObjCCategoryDecl(clang::ObjCCategoryDecl *D);
    void VisitObjCCompatibleAliasDecl(clang::ObjCCompatibleAliasDecl *D);
    void VisitObjCPropertyDecl(clang::ObjCPropertyDecl *D);
    void VisitObjCPropertyImplDecl(clang::ObjCPropertyImplDecl *D);
    void VisitUnresolvedUsingTypenameDecl(clang::UnresolvedUsingTypenameDecl *D);
    void VisitUnresolvedUsingValueDecl(clang::UnresolvedUsingValueDecl *D);
    void VisitUsingDecl(clang::UsingDecl *D);
    void VisitUsingShadowDecl(clang::UsingShadowDecl *D);

    void PrintTemplateParameters(const clang::TemplateParameterList *Params,
            const clang::TemplateArgumentList *Args);
    void prettyPrintAttributes(clang::Decl *D);
};


#endif	/* DECLTOSTRING_HPP */

