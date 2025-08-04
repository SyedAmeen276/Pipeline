# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -pthread -Iinclude
SRC_DIR = src
OBJ_DIR = obj
EXEC = stream_pipeline

# Find all cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean

all: $(EXEC)

# Link all object files into the final binary
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if missing
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)
