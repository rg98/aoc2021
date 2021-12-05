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

all:    aoc05-1 aoc05-2

aoc05-1: aoc05-1.o
	@echo "Building ... aoc05-1"
	@$(CXX) $(CXXFLAGS) aoc05-1.o -o aoc05-1 $(LDFLAGS)

aoc05-2: aoc05-2.o
	@echo "Building ... aoc05-2"
	@$(CXX) $(CXXFLAGS) aoc05-2.o -o aoc05-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc05-1 aoc05-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

