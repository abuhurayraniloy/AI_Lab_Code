# Set the compiler
CXX = clang++
# Set the compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

# Get the names of all the C++ files in the directory
CPPSRC ?= $(wildcard *.cpp)
EXECUTABLE = $(patsubst %.cpp,%,$(CPPSRC))

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): %.cpp
    $(CXX) $(CXXFLAGS) -o $@ $<

run_%: %
    ./$<

clean:
    rm -f $(EXECUTABLE)

.PHONY: all clean
