#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/testvisitor.o \
	${OBJECTDIR}/DeclToString.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/local/lib/libclang.a /usr/local/lib/libclangAnalysis.a /usr/local/lib/libclangARCMigrate.a /usr/local/lib/libclangAST.a /usr/local/lib/libclangASTMatchers.a /usr/local/lib/libclangBasic.a /usr/local/lib/libclangCodeGen.a /usr/local/lib/libclangDriver.a /usr/local/lib/libclangEdit.a /usr/local/lib/libclangFrontend.a /usr/local/lib/libclangFrontendTool.a /usr/local/lib/libclangLex.a /usr/local/lib/libclangParse.a /usr/local/lib/libclangRewriteCore.a /usr/local/lib/libclangRewriteFrontend.a /usr/local/lib/libclangSema.a /usr/local/lib/libclangSerialization.a /usr/local/lib/libclangStaticAnalyzerCheckers.a /usr/local/lib/libclangStaticAnalyzerCore.a /usr/local/lib/libclangStaticAnalyzerFrontend.a /usr/local/lib/libclangTooling.a -lc++ -lc -lm -lstdc++.6 -lLLVMAnalysis -lLLVMArchive -lLLVMARMAsmParser -lLLVMARMAsmPrinter -lLLVMARMCodeGen -lLLVMARMDesc -lLLVMARMDisassembler -lLLVMARMInfo -lLLVMAsmParser -lLLVMAsmPrinter -lLLVMBitReader -lLLVMBitWriter -lLLVMCodeGen -lLLVMCore -lLLVMCppBackendCodeGen -lLLVMCppBackendInfo -lLLVMDebugInfo -lLLVMExecutionEngine -lLLVMHexagonAsmPrinter -lLLVMHexagonCodeGen -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMInstCombine -lLLVMInstrumentation -lLLVMInterpreter -lLLVMipa -lLLVMipo -lLLVMJIT -lLLVMLinker -lLLVMMBlazeAsmParser -lLLVMMBlazeAsmPrinter -lLLVMMBlazeCodeGen -lLLVMMBlazeDesc -lLLVMMBlazeDisassembler -lLLVMMBlazeInfo -lLLVMMC -lLLVMMCDisassembler -lLLVMMCJIT -lLLVMMCParser -lLLVMMipsAsmParser -lLLVMMipsAsmPrinter -lLLVMMipsCodeGen -lLLVMMipsDesc -lLLVMMipsDisassembler -lLLVMMipsInfo -lLLVMMSP430AsmPrinter -lLLVMMSP430CodeGen -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMNVPTXAsmPrinter -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMObject -lLLVMPowerPCAsmPrinter -lLLVMPowerPCCodeGen -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMRuntimeDyld -lLLVMScalarOpts -lLLVMSelectionDAG -lLLVMSparcCodeGen -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMSupport -lLLVMTableGen -lLLVMTarget -lLLVMTransformUtils -lLLVMVectorize -lLLVMX86AsmParser -lLLVMX86AsmPrinter -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Disassembler -lLLVMX86Info -lLLVMX86Utils -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lclang -lclangAST

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclang.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangAnalysis.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangARCMigrate.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangAST.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangASTMatchers.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangBasic.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangCodeGen.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangDriver.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangEdit.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangFrontend.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangFrontendTool.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangLex.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangParse.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangRewriteCore.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangRewriteFrontend.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangSema.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangSerialization.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangStaticAnalyzerCheckers.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangStaticAnalyzerCore.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangStaticAnalyzerFrontend.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: /usr/local/lib/libclangTooling.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest -Wl,-S ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/testvisitor.o: nbproject/Makefile-${CND_CONF}.mk testvisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -fno-rtti -MMD -MP -MF $@.d -o ${OBJECTDIR}/testvisitor.o testvisitor.cpp

${OBJECTDIR}/DeclToString.o: nbproject/Makefile-${CND_CONF}.mk DeclToString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -fno-rtti -MMD -MP -MF $@.d -o ${OBJECTDIR}/DeclToString.o DeclToString.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangtest

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
