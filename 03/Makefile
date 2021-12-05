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

all:    aoc03-1 aoc03-2

aoc03-1: aoc03-1.o
	@echo "Building ... aoc03-1"
	@$(CXX) $(CXXFLAGS) aoc03-1.o -o aoc03-1 $(LDFLAGS)

aoc03-2: aoc03-2.o
	@echo "Building ... aoc03-2"
	@$(CXX) $(CXXFLAGS) aoc03-2.o -o aoc03-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc03-1 aoc03-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

