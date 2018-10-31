CXX := g++
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra -Werror -Wno-format-zero-length -pedantic -Isrc
LDFLAGS = -ldl -lpthread

APP_DIR := .
COMM_DIR := src
OBJ_DIR := obj

APP_FILES := $(wildcard $(APP_DIR)/*.cpp)
COMM_FILES := $(wildcard $(COMM_DIR)/*.cpp)

APP_OBJS := $(patsubst $(APP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(APP_FILES))
COMM_OBJS := $(patsubst $(COMM_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(COMM_FILES))

all: mkdir pool-test

mkdir:
	mkdir -p $(OBJ_DIR) 

pool-test: $(APP_OBJS) $(COMM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(COMM_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJ_DIR)/*.o
	rmdir $(OBJ_DIR)
	rm pool-test

.PHONY: clean
