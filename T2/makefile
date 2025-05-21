# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Executável
TARGET = main

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos .c para .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Garante que a pasta build exista
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean