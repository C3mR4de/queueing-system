.PHONY: all build run clean

PROJECT_NAME := queueing-system
BUILD        ?= debug

INC_DIR := inc
SRC_DIR := src
BIN_DIR := bin

LD_LIBS      := -lm
COMMON_FLAGS := $(LD_LIBS) -Wall -Wextra -Wpedantic

DEBUG_FLAGS   := $(COMMON_FLAGS) -O0 -g
RELEASE_FLAGS := $(COMMON_FLAGS) -O2 -march=native

all: build run

build: build-$(BUILD)
run:   run-$(BUILD)

build-debug:
	gcc -I$(INC_DIR) $(SRC_DIR)/*.c -o bin/$(PROJECT_NAME)-debug $(DEBUG_FLAGS)

run-debug:
	./$(BIN_DIR)/$(PROJECT_NAME)-debug

build-release:
	gcc -I$(INC_DIR) $(SRC_DIR)/*.c -o bin/$(PROJECT_NAME)-release $(RELEASE_FLAGS)

run-release:
	./$(BIN_DIR)/$(PROJECT_NAME)-release

clean:
	rm $(BIN_DIR)/*
