#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

// Definição do nó da lista
typedef struct s_no {
    int valor;
    struct s_no* prox;
} s_no;

// Função de busca: retorna ponteiro para o nó com o valor, ou NULL se não encontrar
s_no* buscar(s_no* inicio, int valor);
// inserindo valor ordenado
s_no* inserir_ordenado(s_no* inicio, int valor);
s_no* remover(s_no* lista, int valor);
void imprimir_lista_simples(s_no* inicio);
void interface_lista_simples(void);
void destruir_lista_simples(s_no* lista);

#endif
