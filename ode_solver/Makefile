# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wpedantic -fsanitize=address -g -Iinclude
LDFLAGS = -fsanitize=address

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
OUT_DIR = output

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/simulation

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Clean everything including output
cleanall: clean
	rm -rf $(OUT_DIR)/*

# Run the program (example - modify arguments as needed)
run: all | $(OUT_DIR)
	./$(TARGET) lorenz single adaptive 0. 0.005 10000 16. 4. 45. -13. -12. 52. 

# Phony targets
.PHONY: all clean cleanall run

# Dependencies (headers)
$(OBJ_DIR)/main.o: $(INC_DIR)/state.h $(INC_DIR)/rk4.h $(INC_DIR)/systems.h $(INC_DIR)/plotter.h $(INC_DIR)/config.h
$(OBJ_DIR)/state.o: $(INC_DIR)/state.h
$(OBJ_DIR)/rk4.o: $(INC_DIR)/rk4.h $(INC_DIR)/state.h
$(OBJ_DIR)/systems.o: $(INC_DIR)/systems.h $(INC_DIR)/state.h $(INC_DIR)/config.h
$(OBJ_DIR)/plotter.o: $(INC_DIR)/plotter.h $(INC_DIR)/state.h
