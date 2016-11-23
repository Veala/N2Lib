cmake_minimum_required(VERSION 2.8)

set (PROJECTNAME TinyXML_lib)
project (${PROJECTNAME})

set(LIBRARY_OUTPUT_DIRECTORY export/out/)


set(HEADER_LIB_TINY_XML	
				tinyxml/source/tinystr.h
				tinyxml/source/tinyxml.h
)

set(SOURCE_LIB_TINY_XML	
				tinyxml/source/tinyxmlparser.cpp
				tinyxml/source/tinyxmlerror.cpp
				tinyxml/source/tinyxml.cpp
				tinyxml/source/tinystr.cpp				
)

add_library(tinyxml STATIC ${HEADER_LIB_TINY_XML} ${SOURCE_LIB_TINY_XML}  )	#

