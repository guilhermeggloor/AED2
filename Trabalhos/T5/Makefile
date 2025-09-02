# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
LDFLAGS = -lm -lrt# Para a biblioteca matemática, se necessário

# Diretórios
SRCDIR = src
BINDIR = bin
DATADIR = data

# Fontes e objetos
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/algoritmos.c
OBJECTS = $(SOURCES:.c=.o)
MAIN_EXEC = $(BINDIR)/ordenador
GENERATOR_EXEC = $(BINDIR)/gerador

# Alvo principal: compila tudo
all: $(MAIN_EXEC) $(GENERATOR_EXEC)

# Regra para criar o executável principal 'ordenador'
$(MAIN_EXEC): $(OBJECTS)
	@mkdir -p $(@D) # Cria o diretório bin se não existir
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Executável 'ordenador' compilado em $(MAIN_EXEC)"

# Regra para criar o executável 'gerador'
$(GENERATOR_EXEC): gera_in_out.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Executável 'gerador' compilado em $(GENERATOR_EXEC)"

# Regra genérica para compilar arquivos .c em .o dentro de src/
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Alvo para gerar os arquivos de teste
# Exemplo: make generate_tests
generate_tests: $(GENERATOR_EXEC)
	@mkdir -p $(DATADIR)/in $(DATADIR)/out
	@echo "Gerando arquivos de teste..."
	# Testes pequenos para todos os algoritmos
	@for size in 10 100 1000 10000 100000; do \
		for type in c d a; do \
			./$(GENERATOR_EXEC) $$size $$type; \
			mv $$size.$$type $(DATADIR)/in/; \
			mv $$size.$$type.out $(DATADIR)/out/; \
		done; \
	done
	# Testes grandes para os algoritmos eficientes
	@for size in 500000 5000000; do \
		for type in c d a; do \
			./$(GENERATOR_EXEC) $$size $$type; \
			mv $$size.$$type $(DATADIR)/in/; \
			mv $$size.$$type.out $(DATADIR)/out/; \
		done; \
	done
	# O teste de 50M pode demorar e ocupar muito espaço (~200MB), gerado sob demanda
	@echo "Arquivos de teste gerados em $(DATADIR)/"
	@echo "Para gerar o teste de 50M, use: make generate_50M"

# Alvo para gerar o teste de 50 milhões de elementos
generate_50M: $(GENERATOR_EXEC)
	@mkdir -p $(DATADIR)/in $(DATADIR)/out
	@echo "Gerando arquivos de 50.000.000 (pode demorar)..."
	@for type in c d a; do \
		./$(GENERATOR_EXEC) 50000000 $$type; \
		mv 50000000.$$type $(DATADIR)/in/; \
		mv 50000000.$$type.out $(DATADIR)/out/; \
	done
	@echo "Arquivos de 50M gerados."

# Alvo para limpar tudo (executáveis, objetos e arquivos de dados)
clean:
	@echo "Limpando arquivos compilados e dados gerados..."
	rm -f $(SRCDIR)/*.o $(MAIN_EXEC) $(GENERATOR_EXEC)
	rm -rf $(DATADIR)/in/* $(DATADIR)/out/*

.PHONY: all clean generate_tests generate_50M