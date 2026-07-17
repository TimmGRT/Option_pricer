CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS   = src_cpp/solver.cpp src_cpp/european_option.cpp main.cpp src_cpp/option.cpp src_cpp/asian_option.cpp src_cpp/asian_option.cpp

# permet de verifier si ça compile
all: pricer 

# permet de comme avant compiler
pricer : src_cpp/solver.cpp src_cpp/european_option.cpp src_cpp/option.cpp main.cpp src_cpp/asian_option.cpp
	$(CXX) $(CXXFLAGS) src_cpp/solver.cpp src_cpp/option.cpp src_cpp/european_option.cpp main.cpp src_cpp/asian_option.cpp -o pricer

# permet de compiler et d'executer
run : pricer 
	./pricer

clean: # supprime la precedente compilation 
	rm -f pricer 
