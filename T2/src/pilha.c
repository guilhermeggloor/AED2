#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* criar_pilha(void) {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void inserir_pilha(Pilha* pilha, int valor) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int remover_pilha(Pilha* pilha) {
    if (!pilha->topo) return -1; // Pilha vazia
    NoPilha* temp = pilha->topo;
    int valor = temp->valor;
    pilha->topo = temp->prox;
    free(temp);
    return valor;
}

void imprimir_pilha(Pilha* pilha) {
    NoPilha* atual = pilha->topo;
    printf("Topo\n");
    while (atual) {
        printf("| %d |\n", atual->valor);
        atual = atual->prox;
    }
    printf("Base\n");
}

void destruir_pilha(Pilha* pilha) {
    while (pilha->topo) {
        remover_pilha(pilha);
    }
    free(pilha);
}