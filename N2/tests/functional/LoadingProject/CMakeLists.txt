cmake_minimum_required(VERSION 2.8)

set(NAME_PRJ_FT_VARS test_LoadingProject)
project(${NAME_PRJ_FT_VARS})


set(LIBRARY_XML_PARSER	tinyxml)

#message(STATUS $LIBRARY_OUTPUT_DIRECTORY)

set(HEADERS_TST_1_FILES ../../Testing.h						
						stdafx.h
						targetver.h
						
)

set(SOURCE_TST_1_FILES 	stdafx.cpp
						LoadingProject.cpp
						../../../src/N2TinyXMLParser.cpp
)			


add_executable(${NAME_PRJ_FT_VARS} ${HEADERS_TST_1_FILES} ${SOURCE_TST_1_FILES})	
target_link_libraries(${NAME_PRJ_FT_VARS} ${LIBRARY_XML_PARSER})


