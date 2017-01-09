cmake_minimum_required(VERSION 2.8)

set(NAME_PRJ_FT_VARS test_MemoryAllocation)
project(${NAME_PRJ_FT_VARS})


#set(LIBRARIES	n2vm)

#message(STATUS $LIBRARY_OUTPUT_DIRECTORY)

set(HEADERS_TST_1_FILES ../../Testing.h						
						stdafx.h
						targetver.h
						
)

set(SOURCE_TST_1_FILES 	stdafx.cpp
						MemoryAllocationAndControl.cpp
)			


add_executable(${NAME_PRJ_FT_VARS} ${HEADERS_TST_1_FILES} ${SOURCE_TST_1_FILES})	
#target_link_libraries(${NAME_PRJ_FT_VARS} ${LIBRARIES})


