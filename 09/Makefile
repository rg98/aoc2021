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

all:    aoc09-1 aoc09-2

aoc09-1: aoc09-1.o
	@echo "Building ... aoc09-1"
	@$(CXX) $(CXXFLAGS) aoc09-1.o -o aoc09-1 $(LDFLAGS)

aoc09-2: aoc09-2.o
	@echo "Building ... aoc09-2"
	@$(CXX) $(CXXFLAGS) aoc09-2.o -o aoc09-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc09-1 aoc09-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

