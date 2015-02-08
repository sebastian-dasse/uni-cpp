TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += /usr/local/lib/boost_1_57_0
LIBS += ~/boost/lib/libboost_system.a \
    ~/boost/lib/libboost_regex.a

LIBS += -pthread

SOURCES += main.cpp \
    web_crawler.cpp

include(deployment.pri)
qtcAddDeployment()

