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

all:    aoc02-1 aoc02-2

aoc02-1: aoc02-1.o
	@echo "Building ... aoc02-1"
	@$(CXX) $(CXXFLAGS) aoc02-1.o -o aoc02-1 $(LDFLAGS)

aoc02-2: aoc02-2.o
	@echo "Building ... aoc02-2"
	@$(CXX) $(CXXFLAGS) aoc02-2.o -o aoc02-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc02-1 aoc02-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

