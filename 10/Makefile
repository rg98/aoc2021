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

all:    aoc10-1 aoc10-1-2 aoc10-2 aoc10-2-2

aoc10-1: aoc10-1.o
	@echo "Building ... aoc10-1"
	@$(CXX) $(CXXFLAGS) aoc10-1.o -o aoc10-1 $(LDFLAGS)

aoc10-1-2: aoc10-1-2.o
	@echo "Building ... aoc10-1-2"
	@$(CXX) $(CXXFLAGS) aoc10-1-2.o -o aoc10-1-2 $(LDFLAGS)

aoc10-2: aoc10-2.o
	@echo "Building ... aoc10-2"
	@$(CXX) $(CXXFLAGS) aoc10-2.o -o aoc10-2 $(LDFLAGS)

aoc10-2-2: aoc10-2-2.o
	@echo "Building ... aoc10-2-2"
	@$(CXX) $(CXXFLAGS) aoc10-2-2.o -o aoc10-2-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc10-1 aoc10-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

