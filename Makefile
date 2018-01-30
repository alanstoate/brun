SRC_DIR := ./src
INC_DIR := ./include
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
CPPFLAGS := -lstdc++fs -lncurses 
CXXFLAGS := -std=c++17

all:
	g++ -I $(INC_DIR) $(SRC_FILES) $(CPPFLAGS) $(CXXFLAGS) -o brun
