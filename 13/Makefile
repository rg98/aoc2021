#
# Makefile for aoc2021
#
# © Ralph Ganszky 12/2021
#

CXX           = clang++

CXXFLAGS      = -g -Os -fno-omit-frame-pointer -fno-optimize-sibling-calls \
                -std=c++17 -Wall 

LDFLAGS       = 

SRCS          = $(wildcard *.cpp)

DEPENDFILE    = .depend

OBJS          = $(SRCS:.cpp=.o)

all:    aoc13-1 aoc13-2

aoc13-1: aoc13-1.o
	@echo "Building ... aoc13-1"
	@$(CXX) $(CXXFLAGS) aoc13-1.o -o aoc13-1 $(LDFLAGS)

aoc13-2: aoc13-2.o
	@echo "Building ... aoc13-2"
	@$(CXX) $(CXXFLAGS) aoc13-2.o -o aoc13-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc13-1 aoc13-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

