CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS   = src_cpp/solver.cpp src_cpp/analytical.cpp main.cpp src_cpp/option.cpp

# permet de verifier si ça compile
all: pricer 

# permet de comme avant compiler
pricer : src_cpp/solver.cpp src_cpp/analytical.cpp src_cpp/option.cpp main.cpp 
	$(CXX) $(CXXFLAGS) src_cpp/solver.cpp src_cpp/option.cpp src_cpp/analytical.cpp main.cpp -o pricer

# permet de compiler et d'executer
run : pricer 
	./pricer

clean: # supprime la precedente compilation 
	rm -f pricer 
