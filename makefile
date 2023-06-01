CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: programa

programa: main.cpp funkcijos.cpp
	$(CXX) $(CXXFLAGS) -o programa main.cpp funkcijos.cpp && ./programa

clean:
	rm -f programa
