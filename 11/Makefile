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

all:    aoc11-1 aoc11-2

aoc11-1: aoc11-1.o
	@echo "Building ... aoc11-1"
	@$(CXX) $(CXXFLAGS) aoc11-1.o -o aoc11-1 $(LDFLAGS)

aoc11-2: aoc11-2.o
	@echo "Building ... aoc11-2"
	@$(CXX) $(CXXFLAGS) aoc11-2.o -o aoc11-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc11-1 aoc11-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

