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

all:    aoc08-1 aoc08-2

aoc08-1: aoc08-1.o
	@echo "Building ... aoc08-1"
	@$(CXX) $(CXXFLAGS) aoc08-1.o -o aoc08-1 $(LDFLAGS)

aoc08-2: aoc08-2.o
	@echo "Building ... aoc08-2"
	@$(CXX) $(CXXFLAGS) aoc08-2.o -o aoc08-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc08-1 aoc08-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

