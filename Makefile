# currently works on macOS, make sure to include prereq in README.md
# plan: work in windows (wsl) and linux
# edit: just needs to be known at compile time, look into downloadin
#FILE := include/json.hpp
#FILE_URL := https://raw.githubusercontent.com/nlohmann/json/refs/heads/develop/single_include/nlohmann/json.hpp

CXX := g++
CXXFLAGS := -std=c++11 -Wall -Iinclude
SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

JSON_HEADER := include/nlohmann/json.hpp
JSON_URL := https://raw.githubusercontent.com/nlohmann/json/refs/heads/develop/single_include/nlohmann/json.hpp

all: $(JSON_HEADER) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS)

$(JSON_HEADER):
	@echo "Downloading nlohmann/json.hpp..."
	@mkdir -p include/nlohmann
	curl -L -o $(JSON_HEADER) $(JSON_URL)

clean:
	rm -f main $(OBJECTS)


distclean: clean
	rm -rf include
