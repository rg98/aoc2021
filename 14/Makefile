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

all:    aoc14-1 aoc14-2

aoc14-1: aoc14-1.o
	@echo "Building ... aoc14-1"
	@$(CXX) $(CXXFLAGS) aoc14-1.o -o aoc14-1 $(LDFLAGS)

aoc14-2: aoc14-2.o
	@echo "Building ... aoc14-2"
	@$(CXX) $(CXXFLAGS) aoc14-2.o -o aoc14-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc14-1 aoc14-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

