cmake_minimum_required(VERSION 2.8)

set (PROJECTNAME NucisNucleo)
project (${PROJECTNAME})
set (SCIURUS 0)
set (UNICODE 0)

include_directories("src//include//")	
include_directories("..//src//")	
include_directories("export/common/")	

set(WRK_DIR src//)

set(LIBRARY_OUTPUT_DIRECTORY export/out/)

message(STATUS ${LIBRARY_OUTPUT_DIRECTORY})
message(STATUS WRK_DIR=${WRK_DIR})

set(HEADER_LIB_N2VM	export/common/configuration.h
				export/common/IControl.h
				export/common/ILauncher.h
				export/common/isolator.h
				export/common/ITreeNode.h
				export/common/N2Base.h
				export/common/N2BaseSerialize.h
				export/common/N2Commands.h
				export/common/N2ConcreteXMLParser.h
				export/common/N2ControlObject.h
				export/common/N2Defines.h
				export/common/N2Dissection.h
				export/common/N2Environment.h
				export/common/N2LiveObjectsPolicy.h
				export/common/N2Log.h
				export/common/N2Misc.h
				export/common/N2Module.h
				export/common/N2ModulesManager.h
				export/common/N2Parser.h
				export/common/N2RealParser.h
				export/common/N2ProjectNode.h
				export/common/N2RapidXMLParser.h
				export/common/N2Register.h
				export/common/N2Serializer.h
				export/common/N2Standart2014ProjectNode.h
				export/common/N2TinyXMLParser.h
				export/common/N2TreeNode.h
				export/common/N2Variable.h
				export/common/N2XMLF.h
				export/common/tuner.h
				export/common/N2Paths.h
				#export/common/user_node.h
				src/include/N2AllOperatingState.h
				src/include/N2Control.h
				src/include/N2DllSharedAccess.h
				src/include/N2HelpParserStandart2014Project.h
				src/include/N2LinuxSharedAccess.h
				src/include/N2Modules.h
				src/include/N2OperatingState.h
				src/include/N2Order.h
				src/include/N2ParserExternal.h
				src/include/N2Phelper.h
				src/include/N2Processor.h
				src/include/N2SharedAccess.h
				src/include/N2SharedAccessWorker.h
				src/include/N2VariablesManager.h
				# xml-парсеры
				utils/tinyxml/source/tinystr.h
				utils/tinyxml/source/tinyxml.h
)

set(SOURCE_LIB_N2VM	src/N2AllOperatingState.cpp 
				src/N2Control.cpp 
				src/N2ControlObject.cpp
				src/N2DllSharedAccess.cpp
				src/N2HelpParserStandartProject.cpp
				src/N2Module.cpp
				src/N2ModuleExternal.cpp
				src/N2ModulesManager.cpp
				src/N2OperatingState.cpp
				src/N2Order.cpp
				src/N2Processor.cpp
				src/N2RapidXMLParser.cpp
				src/N2Register.cpp
				src/N2StandartProjectNode.cpp
				src/N2System.cpp
				src/N2TinyXMLParser.cpp
				src/N2Base.cpp
				src/N2Variable.cpp
				src/N2Log.cpp
				src/N2Dissection.cpp
				src/N2Phelper.cpp
				src/N2VariablesManager.cpp
				src/N2Environment.cpp
				utils/tinyxml/source/tinyxmlparser.cpp
				utils/tinyxml/source/tinyxmlerror.cpp
				utils/tinyxml/source/tinyxml.cpp
				utils/tinyxml/source/tinystr.cpp	
				
)

if(SCIURUS)
	set(SOURCE_LIB_N2VM_FOR_SCIURUS	export/common/user/HelperSciurusProjectNode2014.cpp
									export/common/user/SciurusProjectNode2014.cpp		
									export/common/user/SciurusDiss1.cpp	
	)
endif()				

#message(STATUS SOURCE_LIB=${SOURCE_LIB})
#set(SRC_COMPILE ${WRK_DIR}${SOURCE_LIB} )



add_library(n2vm STATIC ${HEADER_LIB_N2VM} ${SOURCE_LIB_N2VM} ${SOURCE_LIB_N2VM_FOR_SCIURUS} )	# Создание статической библиотеки с именем n2vm




############
add_subdirectory (utils)
add_subdirectory (tests)
