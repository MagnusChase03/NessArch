CC := gcc
FLAGS := -Wall

SRC_DIR := ./src
BIN_DIR := ./bin

EXECUTABLE := ./bin/emulator
SRC_FILES := $(shell find ./src | grep -e "\.c")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))

$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c -o $@ $^

clean:
	rm -rf bin
