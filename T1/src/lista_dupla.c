#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla.h"

NoDuplo* criar_lista_dupla(void) {
    NoDuplo* cabeca = (NoDuplo*)malloc(sizeof(NoDuplo));
    cabeca->prox = cabeca;
    cabeca->ant = cabeca;
    return cabeca;
}

// procedimento inserir da lista dupla
void inserir_dupla(NoDuplo* cabeca, int valor) {
    NoDuplo* novo = (NoDuplo*)malloc(sizeof(NoDuplo));
    novo->valor = valor;
    novo->prox = cabeca;
    novo->ant = cabeca->ant;
    cabeca->ant->prox = novo;
    cabeca->ant = novo;
}

// procedimento remover da lista dupla
void remover_duplo(NoDuplo* cabeca, int valor) {
    NoDuplo* atual = cabeca->prox;
    while (atual != cabeca) {
        if (atual->valor == valor) {
            atual->ant->prox = atual->prox;
            atual->prox->ant = atual->ant;
            free(atual);
            return;
        }
        atual = atual->prox;
    }
}

// Procedimento de busca
NoDuplo* buscar_dupla(NoDuplo* cabeca, int valor) {
    NoDuplo* atual = cabeca->prox;
    while (atual != cabeca) {
        if (atual->valor == valor) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void imprimir_lista_dupla(NoDuplo* cabeca) {
    NoDuplo* atual = cabeca->prox;
    printf("Lista dupla: ");
    while (atual != cabeca) {
        printf("[%d] <-> ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");

    //Mostrar o inicio e fim da lista dupla
    if(cabeca->prox != cabeca) {
        printf("Inicio: [%d]\n", cabeca->prox->valor);
        printf("Fim: [%d]\n", cabeca->ant->valor);
    } else {
        printf("Lista vazia.\n");  
    }
}

//desaloca
void destruir_lista_dupla(NoDuplo* cabeca) {
    if (!cabeca) return;
    NoDuplo* atual = cabeca->prox;
    while (atual != cabeca) {
        NoDuplo* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(cabeca);
}