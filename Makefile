CC = gcc
CFLAGS = -Wall -Wextra -Werror -O0 -g

SRC_DIR   = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

BIN = gedit

.PHONY: all clean run

all: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BIN) $(BUILD_DIR)
