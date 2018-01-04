TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/nmea-tests.cpp \
    src/position.cpp \
    src/utilities.cpp

HEADERS += \
    headers/parseNMEA.h \
    headers/position.h \
    headers/types.h \
    headers/utilities.h

INCLUDEPATH += headers/

LIBS += -lboost_unit_test_framework
