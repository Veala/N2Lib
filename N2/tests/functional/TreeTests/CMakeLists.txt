cmake_minimum_required(VERSION 2.8)

set(NAME_PRJ test_TreeNode)
project(${NAME_PRJ})


#set(LIBRARIES	n2vm)

#message(STATUS $LIBRARY_OUTPUT_DIRECTORY)

set(HEADERS_TST_1_FILES ../../Testing.h						
						stdafx.h
						targetver.h
						
)

set(SOURCE_TST_1_FILES 	stdafx.cpp
						TreeTests.cpp
						../../../export/common/user/SciurusProjectNode2014.cpp
						../../../export/common/user/HelperSciurusProjectNode2014.cpp
						../../../src/N2Register.cpp
						../../../src/N2Phelper.cpp
						../../../src/N2Log.cpp
)			


add_executable(${NAME_PRJ} ${HEADERS_TST_1_FILES} ${SOURCE_TST_1_FILES})	
#target_link_libraries(${NAME_PRJ} ${LIBRARIES})


