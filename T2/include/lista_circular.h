#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

// Definição do nó da lista circular
typedef struct NoCircular {
    int valor;
    struct NoCircular* prox;
} NoCircular;

NoCircular* inserir_ordenado_circular(NoCircular* lista, int valor);
NoCircular* remover_circular(NoCircular* lista, int valor);
NoCircular* buscar_circular(NoCircular* lista, int valor);
void imprimir_lista_circular(NoCircular* lista);
void interface_lista_circular(void);


#endif

