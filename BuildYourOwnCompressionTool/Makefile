CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRCS)) # Exclude main.cpp
OBJS = $(SRCS_NO_MAIN:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)    # Object files excluding main.o
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/cmpress
TEST_TARGET = $(BIN_DIR)/tests

# Build the main executable
$(TARGET): $(OBJS) $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile test files to object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Build and run tests
test: $(TEST_OBJ_FILES) $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_TARGET) -lgtest_main -lgtest $(LDFLAGS)
	$(TEST_TARGET)

.PHONY: clean test
