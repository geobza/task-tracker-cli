# currently works on macOS, make sure to include prereq in README.md
# plan: work in windows (wsl) and linux 
# edit: just needs to be known at compile time, look into downloadin
FILE := include/json.hpp
FILE_URL := https://raw.githubusercontent.com/nlohmann/json/refs/heads/develop/single_include/nlohmann/json.hpp 

CXX := g++
CXXFLAGS := -std=c++11 -Wall -I$(shell brew --prefix nlohmann-json)/include
SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

$(FILE):
	@echo "Downloading $(FILE)..."
	curl -L -o $(FILE) $(FILE_URL)

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $^

clean:
	rm -f main $(OBJECTS)
