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

all:    aoc01-1 aoc01-2

aoc01-1: aoc01-1.o
	@echo "Building ... aoc01-1"
	@$(CXX) $(CXXFLAGS) aoc01-1.o -o aoc01-1 $(LDFLAGS)

aoc01-2: aoc01-2.o
	@echo "Building ... aoc01-2"
	@$(CXX) $(CXXFLAGS) aoc01-2.o -o aoc01-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc01-1 aoc01-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

