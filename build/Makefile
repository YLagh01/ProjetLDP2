# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -pedantic

# Allegro libraries
ALLEGRO_FLAGS := $(shell pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --cflags --libs)

# Source files
SRC_DIR    = ../src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Output binary
TARGET := arkanoid

# Default target
all: $(TARGET)

# Linking and compiling all sources into the final binary
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(ALLEGRO_FLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
