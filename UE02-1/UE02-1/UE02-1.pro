TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test_fix_point_collection.cpp \
    fix_point_collection.cpp

include(deployment.pri)
qtcAddDeployment()

