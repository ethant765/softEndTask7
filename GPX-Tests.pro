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
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/gpx-tests/netHeightGain_n0689061.cpp \
    src/gpx-tests/name.cpp \
    src/gpx-tests/travellingTime-N0696066.cpp \
    src/gpx-tests/maxlattestsn0690641.cpp \
    src/gpx-tests/maxLongTests_N0669298.cpp \
    src/gpx-tests/n0650950_numPos_Tests.cpp \
    src/gpx-tests/N0680192.cpp \
    src/gpx-tests/n0671966_mingrad.cpp \
    src/gpx-tests/N0643498_Max_Latitude.cpp \
    src/gpx-tests/totalHeightGain-N0720387.cpp \
    src/gpx-tests/max_elevation_n0689529.cpp \
    src/gpx-tests/n0688119_Route_maxGradient.cpp \
    src/gpx-tests/minElevation_N0699610.cpp \
    src/gpx-tests/N0682255_MinLAtitude.cpp \
    src/gpx-tests/TestMinElev-N0719715.cpp \
    src/gpx-tests/TotalTime-N0688008-Tests.cpp \
    src/gpx-tests/TestMinElev-N0719715.cpp \
    src/gpx-tests/n0673230_totalheightgain.cpp \
    src/gpx-tests/minLatTests_N0720717.cpp \
    src/gpx-tests/numPositionsTests_n0719388.cpp \
    src/gpx-tests/maxElevation-n0686300.cpp

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx-tests

LIBS += -lboost_unit_test_framework
