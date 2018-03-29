TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    headers/earth.h \
    headers/geometry.h \
    headers/logs.h \
    headers/position.h \
    headers/route.h \
    headers/track.h \
    headers/types.h \
    headers/xmlparser.h

SOURCES += \
    src/earth.cpp \
    src/gpx-tests.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/gpx-tests/name.cpp \
    src/gpx-tests/totalLength-t0068955.cpp


INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx-tests

LIBS += -lboost_unit_test_framework

macx {

QMAKE_CFLAGS += -std=c++11 -stdlib=libc++

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

LIBS += -L"/usr/local/Cellar/boost/1.66.0/lib" -lboost_random

INCLUDEPATH += "/usr/local/Cellar/boost/1.66.0/include"


}
