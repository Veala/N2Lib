cmake_minimum_required(VERSION 2.8)

set(NAME_PRJ test_N2OperatingState)
project(${NAME_PRJ})

include_directories(../../../export/common)	
include_directories(../../../src/include)	

set(LIBRARIES	n2vm)

set(SOURCE_FILES test_N2OperatingState.cpp)			


add_executable(${NAME_PRJ} ${HEADERS_TST_FILES} ${SOURCE_FILES})	
target_link_libraries(${NAME_PRJ} ${LIBRARIES})

