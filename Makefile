SRC_DIR = src
BUILD_DIR = ./build/debug
CC = clang
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = Pong
INCLUDE_PATHS = -I include
LIBRARY_PATHS = -L lib/SDL2
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g
LINKER_FLAGS = -l c++ -l SDL2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
