#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

// Definição do nó da lista
typedef struct No {
    int valor;
    struct No* prox;
} No;

// Função de busca: retorna ponteiro para o nó com o valor, ou NULL se não encontrar
No* buscar(No* inicio, int valor);
// inserindo valor ordenado
No* inserir_ordenado(No* inicio, int valor);
No* remover(No* lista, int valor);
void imprimir_lista_simples(No* inicio);
void interface_lista_simples(void);
void destruir_lista_simples(No* lista);

#endif
