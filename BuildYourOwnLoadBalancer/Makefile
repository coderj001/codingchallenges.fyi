CXX = g++
CXXFLAGS = -Wall -std=c++20 -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

OBJS = $(SRCS_NO_MAIN:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/test_%.o)

TARGET = $(BIN_DIR)/loadbalancer
TEST_TARGET = $(BIN_DIR)/tests

# Main target
$(TARGET): $(OBJS) $(MAIN_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build object files from source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build object files from test files
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Test target
test: $(OBJS) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_TARGET) -lgtest -lgtest_main $(LDFLAGS)
	$(TEST_TARGET)

#Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Default target
build: $(TARGET)

.PHONY: clean test build
