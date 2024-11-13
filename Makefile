# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Rule to compile any .cpp file
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean rule
clean:
	rm -f $(wildcard *.o) $(wildcard $(basename $(wildcard *.cpp)))

.PHONY: clean
