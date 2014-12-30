TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS += -pthread

SOURCES += main.cpp \
    fix_point.tpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fix_point.hpp

