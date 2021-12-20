#
# Makefile for aoc2021
#
# © Ralph Ganszky 12/2021
#

CXX           = clang++

CXXFLAGS      = -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls \
		-fsanitize=address -fsanitize-address-use-after-scope \
                -std=c++17 -Wall 

LDFLAGS       = 

SRCS          = $(wildcard *.cpp)

DEPENDFILE    = .depend

OBJS          = $(SRCS:.cpp=.o)

all:    aoc20-1 aoc20-2

aoc20-1: aoc20-1.o
	@echo "Building ... aoc20-1"
	@$(CXX) $(CXXFLAGS) aoc20-1.o -o aoc20-1 $(LDFLAGS)

aoc20-2: aoc20-2.o
	@echo "Building ... aoc20-2"
	@$(CXX) $(CXXFLAGS) aoc20-2.o -o aoc20-2 $(LDFLAGS)

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > $(DEPENDFILE)

clean:
	rm -f aoc20-1 aoc20-2  $(OBJS) core perf.data*

-include $(DEPENDFILE)

