# ============================================
# CodeRush Makefile
# Build system for C Racing Education Game
# 
# Integrator: Rinrada Dejsuwannachai (68070503490)
# Date: December 2025
# ============================================
# Makefile for CodeRush Project
# Integrates work from Person 1-5

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows
    RM = del /Q
    RM_DIR = rmdir /S /Q
    TARGET = CodeRush.exe
    CLEAN_CMD = del /Q *.o $(DATA_DIR)\*.o $(GAME_DIR)\*.o $(INPUT_DIR)\*.o $(UI_DIR)\*.o $(SAVE_DIR)\*.o $(TARGET) 2>nul || echo Clean complete
else
    # Linux/macOS
    RM = rm -f
    RM_DIR = rm -rf
    TARGET = CodeRush
    CLEAN_CMD = rm -f $(OBJS) $(TARGET) $(DATA_DIR)/*.o $(GAME_DIR)/*.o $(INPUT_DIR)/*.o $(UI_DIR)/*.o $(SAVE_DIR)/*.o
endif

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g3
LDFLAGS = -lm

# Directories
DATA_DIR = data
GAME_DIR = game
INPUT_DIR = input
UI_DIR = ui
SAVE_DIR = save

# Source files
DATA_SRC = $(DATA_DIR)/question.c
GAME_SRC = $(GAME_DIR)/game.c
INPUT_SRC = $(INPUT_DIR)/input.c
UI_SRC = $(UI_DIR)/ui.c $(UI_DIR)/graphics.c $(UI_DIR)/animation.c
SAVE_SRC = $(SAVE_DIR)/save.c
MAIN_SRC = main.c

# Object files
DATA_OBJ = $(DATA_DIR)/question.o
GAME_OBJ = $(GAME_DIR)/game.o
INPUT_OBJ = $(INPUT_DIR)/input.o
UI_OBJ = $(UI_DIR)/ui.o $(UI_DIR)/graphics.o $(UI_DIR)/animation.o
SAVE_OBJ = $(SAVE_DIR)/save.o
MAIN_OBJ = main.o

# All object files
OBJS = $(MAIN_OBJ) $(DATA_OBJ) $(GAME_OBJ) $(INPUT_OBJ) $(UI_OBJ) $(SAVE_OBJ)

# Default target
all: $(TARGET)

# Link all object files to create executable
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile main.c
$(MAIN_OBJ): $(MAIN_SRC)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Person 1: Questions
$(DATA_DIR)/%.o: $(DATA_DIR)/%.c
	@echo "Compiling Person 1: $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Person 2: Game Logic
$(GAME_DIR)/%.o: $(GAME_DIR)/%.c
	@echo "Compiling Person 2: $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Person 3: Input
$(INPUT_DIR)/%.o: $(INPUT_DIR)/%.c
	@echo "Compiling Person 3: $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Person 4: UI
$(UI_DIR)/%.o: $(UI_DIR)/%.c
	@echo "Compiling Person 4: $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Person 5: Save/Load
$(SAVE_DIR)/%.o: $(SAVE_DIR)/%.c
	@echo "Compiling Person 5: $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	@echo "Running CodeRush..."
	@./$(TARGET)

# Clean build files
clean:
	@echo "Cleaning build files..."
	@$(CLEAN_CMD)
	@echo "Clean complete!"

# Clean all (including save data)
cleanall: clean
	@echo "Removing save data..."
ifeq ($(OS),Windows_NT)
	@del /Q save\data\*.txt save\data\*.dat 2>nul || echo No save data to remove
else
	@rm -f save/data/*.txt save/data/*.dat
endif
	@echo "All clean!"

# Help
help:
	@echo "CodeRush Makefile Commands:"
	@echo ""
	@echo "  make          - Compile the project"
	@echo "  make run      - Compile and run the game"
	@echo "  make clean    - Remove object files and executable"
	@echo "  make cleanall - Remove everything including save data"
	@echo "  make help     - Show this help message"
	@echo ""

# Phony targets
.PHONY: all run clean cleanall help