# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
EXECUTABLE = surety_bond_system

# Default target
all: $(OBJ_DIR) $(EXECUTABLE)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild