INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -I$(INCLUDE_DIR)
# Adiciona a flag da biblioteca ncurses
LIBS = -lncurses

SOURCES = $(wildcard $(SRC_DIR)/*.c) main.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c)) \
          $(patsubst %.c, $(BUILD_DIR)/%.o, $(wildcard main.c))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	# Adiciona $(LIBS) ao final do comando de compilação
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET) arvore.bin

.PHONY: all clean