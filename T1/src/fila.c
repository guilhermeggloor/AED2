#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila(void) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// procedimento inserir
void inserir_fila(Fila* fila, int valor) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    novo->valor = valor;
    novo->prox = NULL;
    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }
    fila->fim = novo;
}

// procedimento remover elemento da fila (no caso vai sempre remover o primeiro elemento)
int remover_fila(Fila* fila) {
    if (!fila->inicio) return -1; // Fila vazia
    NoFila* temp = fila->inicio;
    int valor = temp->valor;
    fila->inicio = temp->prox;
    if (!fila->inicio) fila->fim = NULL;
    free(temp);
    return valor;
}

// função de impressão
void imprimir_fila(Fila* fila) {
    NoFila* atual = fila->inicio;
    printf("Fila: ");
    while (atual) {
        printf("[%d]", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

// desaloca
void destruir_fila(Fila* fila) {
    while (fila->inicio) {
        remover_fila(fila);
    }
    free(fila);
}