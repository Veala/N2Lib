TARGET = test_N2Variables_2
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

win32:INCLUDEPATH += d:/N2/N2/src/include \
                     d:/N2/N2/export/common \

win32:LIBS += d:/N2/build-N2-Desktop_Qt_5_4_2_MinGW_32bit-Release/release/libN2.a

SOURCES += \
    test_N2Variables_2.cpp

include(deployment.pri)
qtcAddDeployment()

