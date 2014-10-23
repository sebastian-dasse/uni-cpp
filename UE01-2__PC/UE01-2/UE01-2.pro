TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    fix_point.cpp \
    test_fix_point_oo.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point.h

