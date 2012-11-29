#include "testvisitor.hpp"

int main(int argc, const char * const *argv)
{
    std::string err;
    std::vector<const char*> Argv;

    clang::tooling::JSONCompilationDatabase* cdb = clang::tooling::JSONCompilationDatabase::loadFromFile("/tmp/poco144/compile_commands.json", err);
    
    if (cdb != NULL) {
        std::vector<std::string> files;
        files.push_back("/Users/RamneekHanda/Downloads/poco-1.4.4/Foundation/src/ArchiveStrategy.cpp");
        clang::tooling::ClangTool tool(*cdb, cdb->getAllFiles()[1]);
        ClangToolRunner toolRunner(tool);
        toolRunner.runTool();
    } else {
        std::cout << "cdb is null" << "- " << err;
    }

    return 0;
}

