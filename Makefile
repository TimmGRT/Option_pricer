CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude

SRCS   = main.cpp src_cpp/option.cpp src_cpp/solver.cpp src_cpp/european_option.cpp src_cpp/asian_option.cpp
TARGET = pricer

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS) $(wildcard include/*.hpp)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
