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

all:    aoc06-1 aoc06-2

aoc06-1: aoc06-1.o
	@echo "Building ... aoc06-1"
	@$(CXX) $(CXXFLAGS) aoc06-1.o -o aoc06-1 $(LDFLAGS)

aoc06-2: aoc06-2.o
	@echo "Building ... aoc06-2"
	@$(CXX) $(CXXFLAGS) aoc06-2.o -o aoc06-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc06-1 aoc06-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

