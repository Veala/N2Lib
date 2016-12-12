#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T12:57:20
#
#-------------------------------------------------

#QT       -= core gui

#TARGET = N2
#TEMPLATE = lib
#CONFIG += staticlib c++11
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += no_lflags_merge

win32:INCLUDEPATH += d:/N2/N2/src/include \
                     d:/N2/N2/export/common \
                     d:/N2/N2/utils/tinyxml \

#win32:LIBS += d:/N2/N2/utils/tinyxml/lib/tinyxml.lib \
#              d:/N2/N2/utils/tinyxml/lib/tinyxmld.lib \

SOURCES += \
    main.cpp \
    src/N2AllOperatingState.cpp \
    src/N2Base.cpp \
    src/N2Control.cpp \
    src/N2ControlObject.cpp \
    src/N2Dissection.cpp \
    src/N2DllSharedAccess.cpp \
    src/N2Environment.cpp \
    src/N2HelpParserStandartProject.cpp \
    src/N2Log.cpp \
    src/N2Module.cpp \
    src/N2ModuleExternal.cpp \
    src/N2ModulesManager.cpp \
    src/N2OperatingState.cpp \
    src/N2Order.cpp \
    src/N2Phelper.cpp \
    src/N2Processor.cpp \
    src/N2RapidXMLParser.cpp \
    src/N2Register.cpp \
    src/N2StandartProjectNode.cpp \
    src/N2System.cpp \
    src/N2TinyXMLParser.cpp \
    #src/N2Types.cpp \
    src/N2Variable.cpp \
    src/N2VariablesManager.cpp \
    utils/tinyxml/source/tinystr.cpp \
    utils/tinyxml/source/tinyxml.cpp \
    utils/tinyxml/source/tinyxmlerror.cpp \
    utils/tinyxml/source/tinyxmlparser.cpp \
    #utils/tinyxml/source/xmltest.cpp \

HEADERS += \
    export/common/configuration.h \
    export/common/IControl.h \
    export/common/ILauncher.h \
    export/common/isolator.h \
    export/common/ITreeNode.h \
    export/common/N2Base.h \
    export/common/N2BaseSerialize.h \
    export/common/N2Commands.h \
    export/common/N2ConcreteXMLParser.h \
    export/common/N2ControlObject.h \
    export/common/N2Defines.h \
    export/common/N2Dissection.h \
    export/common/N2Environment.h \
    export/common/N2LiveObjectsPolicy.h \
    export/common/N2Log.h \
    export/common/N2Misc.h \
    export/common/N2Module.h \
    export/common/N2ModulesManager.h \
    export/common/N2Parser.h \
    export/common/N2ParserXML.h \
    export/common/N2Paths.h \
    export/common/N2ProjectNode.h \
    export/common/N2ProjectSpecInfo.h \
    export/common/N2RapidXMLParser.h \
    export/common/N2RealParser.h \
    export/common/N2Register.h \
    export/common/N2Serializer.h \
    export/common/N2Standart2014ProjectNode.h \
    export/common/N2TinyXMLParser.h \
    export/common/N2TreeNode.h \
    #export/common/N2Types.h \
    export/common/N2Variable.h \
    export/common/N2XMLF.h \
    export/common/tuner.h \
    export/common/user_node.h \
    src/include/N2AllOperatingState.h \
    src/include/N2Control.h \
    src/include/N2DllSharedAccess.h \
    src/include/N2HelpParserStandart2014Project.h \
    src/include/N2LinuxSharedAccess.h \
    src/include/N2Modules.h \
    src/include/N2OperatingState.h \
    src/include/N2Order.h \
    src/include/N2ParserExternal.h \
    src/include/N2Phelper.h \
    src/include/N2Processor.h \
    src/include/N2SharedAccess.h \
    src/include/N2SharedAccessWorker.h \
    src/include/N2VariablesManager.h \
    utils/tinyxml/source/tinystr.h \
    utils/tinyxml/source/tinystr.h \
    utils/tinyxml/source/tinyxml.h \
