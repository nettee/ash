CXX = g++

CXXFILES = $(shell find src/ -name "*.cc")
OBJECTS = $(CXXFILES:.cc=.o)
CXXFLAGS = -std=c++11 -ggdb -Wall

ash: $(OBJECTS)
	$(CXX) -o ash $(OBJECTS) -lreadline

.PHONY: clean
clean:
	-rm ash $(OBJECTS) 


