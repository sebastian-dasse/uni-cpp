TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    test_generic_fix_point.cpp \
    fix_point.tpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point.hpp

