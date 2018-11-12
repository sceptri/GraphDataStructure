TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        src/sources/main.cpp \
    src/sources/graphstructure.cpp

HEADERS += \
    src/headers/datastructures.h \
    src/headers/graphstructure.h

INCLUDEPATH += src/headers/ \
