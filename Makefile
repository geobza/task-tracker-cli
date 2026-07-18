# currently works on macOS, make sure to include prereq in README.md
# plan: work in windows (wsl) and linux
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I$(shell brew --prefix nlohmann-json)/include
SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $^

clean:
	rm -f main $(OBJECTS)
