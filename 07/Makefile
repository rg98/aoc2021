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

all:    aoc07-1 aoc07-2

aoc07-1: aoc07-1.o
	@echo "Building ... aoc07-1"
	@$(CXX) $(CXXFLAGS) aoc07-1.o -o aoc07-1 $(LDFLAGS)

aoc07-2: aoc07-2.o
	@echo "Building ... aoc07-2"
	@$(CXX) $(CXXFLAGS) aoc07-2.o -o aoc07-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc07-1 aoc07-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

