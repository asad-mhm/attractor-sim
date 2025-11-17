# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/AttractorSim

# SFML configuration
# Try to detect SFML installation
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS - typically installed via Homebrew
    SFML_INCLUDE = -I/opt/homebrew/include -I/usr/local/include
    SFML_LIB = -L/opt/homebrew/lib -L/usr/local/lib
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
else
    # Linux - typically in standard locations
    SFML_INCLUDE = 
    SFML_LIB = 
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
endif

# Include paths
INCLUDES = -I$(INCLUDE_DIR) $(SFML_INCLUDE)

# Linker flags
LDFLAGS += $(SFML_LIB) $(SFML_LIBS)

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Clean and rebuild
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make run      - Build and run the program"
	@echo "  make help     - Show this help message"
	@echo ""
	@echo "Note: Make sure SFML is installed and accessible."
	@echo "  macOS: brew install sfml"
	@echo "  Linux: sudo apt-get install libsfml-dev"

.PHONY: all clean rebuild run help

