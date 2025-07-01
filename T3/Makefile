INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

SOURCES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean	