## AI WAS USED TO WRITE THIS FILE !!

# Compiler & Flags
CXX          := clang++
CXXFLAGS     := -std=c++20 -O3 -Wall -Wextra -Wpedantic -Iinclude
DEBUG_FLAGS  := -std=c++20 -g -O0 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -Iinclude

# Directories
SRC_DIR      := src
INC_DIR      := include
OBJ_DIR      := build
BIN_DIR      := bin

# Files
SRCS         := $(wildcard $(SRC_DIR)/*.cpp)
OBJS         := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET       := $(BIN_DIR)/simple2d

# Phony targets (targets that do not represent actual files)
.PHONY: all clean debug run help

# Default target: build the release executable
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $@"

# Compile each .cpp file into an object file .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they do not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Debug build with AddressSanitizer & UndefinedBehaviorSanitizer
debug: CXXFLAGS := $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "Debug build with ASan and UBSan complete."

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) output/*
	@echo "Cleaned build and output files."

# Quick help menu
help:
	@echo "Available make targets:"
	@echo "  make        - Compile release binary (with -O3 optimizations)"
	@echo "  make debug  - Compile with debug symbols and sanitizers (ASan/UBSan)"
	@echo "  make run    - Build and execute the simulation"
	@echo "  make clean  - Remove all compiled objects, binaries, and outputs"
