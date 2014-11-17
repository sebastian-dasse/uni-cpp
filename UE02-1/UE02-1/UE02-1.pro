TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    test_fix_point_collection.cpp \
    fix_point_collection.cpp \
    fix_point.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point_collection.h \
    fix_point.h

