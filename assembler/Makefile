CC := gcc
FLAGS := -Wall -I./src -L./bin

SRC_DIR = ./src
BIN_DIR = ./bin
TEST_DIR = ./tests

SRC := $(shell find $(SRC_DIR) | grep -e "\.c")
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

TEST_SRC := $(shell find $(TEST_DIR) | grep -e "\.c")
TEST_BIN := $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%.test,$(TEST_SRC))
TEST_OBJS := $(filter-out $(BIN_DIR)/index.o,$(OBJS))

BIN := ./bin/index

container:
	sudo podman build -t localhost/gcc . > /dev/null
	sudo podman run localhost/gcc

build: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c -o $@ $^

test: $(TEST_BIN)
	@for test in $(TEST_BIN); do \
		echo "=== Running test $$test... ==="; \
		$$test; \
	done

test_build: $(TEST_BIN)

$(BIN_DIR)/%.test: $(TEST_DIR)/%.c $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -r bin
