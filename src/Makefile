INCLUDEDIR = ../headers

vpath %.h $(INCLUDEDIR)

CXXFLAGS = -std=c++11 -I $(INCLUDEDIR) -Wall -Wfatal-errors
OBJECTS = position.o utilities.o parseNMEA.o
EXECS = nmea-tests

################################################################################

.PHONY: all
all : $(EXECS)

################################################################################

nmea-tests : nmea-tests.cpp $(OBJECTS)
	g++ $(CXXFLAGS) $^ -lboost_unit_test_framework -o $@

################################################################################

parseNMEA.o : %.o : %.cpp %.h position.h types.h utilities.h
	g++ $(CXXFLAGS) -c $< -o $@

position.o : %.o : %.cpp %.h types.h utilities.h
	g++ $(CXXFLAGS) -c $< -o $@

utilities.o : %.o : %.cpp %.h types.h
	g++ $(CXXFLAGS) -c $< -o $@

################################################################################

.PHONY: clean
clean :
	rm -f $(OBJECTS) $(EXECS)

################################################################################
