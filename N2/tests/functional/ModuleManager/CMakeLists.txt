cmake_minimum_required(VERSION 2.8)

set(NAME_PRJ_FT_VARS test_ModuleManager)
project(${NAME_PRJ_FT_VARS})


#set(LIBRARIES	n2vm)

#message(STATUS $LIBRARY_OUTPUT_DIRECTORY)

set(HEADERS_TST_1_FILES ../../Testing.h						
						stdafx.h
						targetver.h
						
)

set(SOURCE_TST_1_FILES 	stdafx.cpp
						ModuleManager.cpp
#						../../../src/N2Module.cpp
#						../../../src/N2ModulesManager.cpp
#						../../../src/N2ModuleExternal.cpp
#						../../../src/N2System.cpp
#						../../../src/N2Register.cpp
#						../../../src/N2ControlObject.cpp
#						../../../src/N2Control.cpp
#						../../../src/N2Log.cpp
)			


add_executable(${NAME_PRJ_FT_VARS} ${HEADERS_TST_1_FILES} ${SOURCE_TST_1_FILES})	
target_link_libraries(${NAME_PRJ_FT_VARS} ${LIBRARIES})


