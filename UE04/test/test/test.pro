TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += /usr/local/lib/boost_1_57_0/

#LIBS += /home/sebastian/boost/lib/libboost_system.a

SOURCES += \
    main.cpp

include(deployment.pri)
qtcAddDeployment()

