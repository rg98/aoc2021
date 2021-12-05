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

all:    aoc04-1 aoc04-2

aoc04-1: aoc04-1.o
	@echo "Building ... aoc04-1"
	@$(CXX) $(CXXFLAGS) aoc04-1.o -o aoc04-1 $(LDFLAGS)

aoc04-2: aoc04-2.o
	@echo "Building ... aoc04-2"
	@$(CXX) $(CXXFLAGS) aoc04-2.o -o aoc04-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc04-1 aoc04-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

