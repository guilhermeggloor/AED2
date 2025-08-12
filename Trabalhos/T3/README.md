# 🌲 Árvore Binária de Busca em C

# Feito por: Guilherme Garcia Gloor

## 📁 Estrutura do Projeto

├── include/
│ └── arvore.h # Declarações da estrutura e funções da árvore
├── src/
│ └── arvore.c # Implementação das funções da árvore
├── main.c # Interface principal com o usuário
├── arvore.bin # (Gerado) Arquivo binário com os dados da árvore
├── Makefile # Automação da compilação
└── README.md # Este arquivo

Este Trabalho implementa uma Árvore Binária de Busca e simula sua estrutura de forma textual no terminal

O projeto consta com: 

- Operação de inserção 
- Busca de valores
- impressão em pré-ordem, em ordem e pós-ordem
- Ao sair a Arvore Salva e carrega em um arquivo binário 
- Interface via terminal
- ao finalizar a arvore é desalocada.

## Como Compilar e Executar

### Importante: 
- Compilador C (ex: "gcc")
- Terminal Linux (ou WSL/git bash no Windows)


- digite "make" no terminal
- e depois ./main
- para limpar "make clean"

### Arquivo binário 

Para verificar o arquivo binário instale a extensão Hex editor no Vscode para verificar se está em pré ordem a impressão

com Hex editor pode observar se está salvo no formato .bin

ou se preferir digite no terminal: "xxd 'arquivo.bin'"