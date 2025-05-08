# Variáveis de compilação
CC = gcc
CFLAGS = -Iinclude -I$(PWD)/gfx -Wall -Wextra -pedantic -lm
LDFLAGS = -L$(PWD)/gfx -lgfx -lSDL -lSDL_gfx -lSDL_ttf -lm
SRCS = src/main.c src/lista_simples.c src/d/lista_dupla.c src/lista_circular.c src/fila.c src/pilha.c
OBJS = $(SRCS:src/%.c=objects/%.o)
TARGET = Lista

# Regra padrão
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Regra para compilar arquivos .c em .o
objects/%.o: src/%.c
	@mkdir -p objects
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET) *~

# Phony targets para evitar conflitos com arquivos de mesmo nome
.PHONY: all clean