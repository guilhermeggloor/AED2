#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"

NoCircular* inserir_ordenado_circular(NoCircular* lista, int valor) {
    NoCircular* novo = (NoCircular*)malloc(sizeof(NoCircular));
    novo->valor = valor;
    if (!lista) {
        novo->prox = novo;
        return novo;
    }
    NoCircular *atual = lista, *anterior = NULL;
    do {
        if (valor < atual->valor) break;
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista);

    if (!anterior) { // Inserir antes do primeiro (novo menor)
        // Encontrar o último nó para atualizar o ponteiro
        NoCircular* ultimo = lista;
        while (ultimo->prox != lista) ultimo = ultimo->prox;
        novo->prox = lista;
        ultimo->prox = novo;
        return novo; // novo passa a ser o primeiro
    } else {
        anterior->prox = novo;
        novo->prox = atual;
        return (lista->valor < valor) ? lista : novo;
    }
}

NoCircular* remover_circular(NoCircular* lista, int valor) {
    if (!lista) return NULL;
    NoCircular *atual = lista, *anterior = NULL;
    do {
        if (atual->valor == valor) break;
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista);

    if (atual->valor != valor) return lista; // Não encontrou

    if (atual == lista && atual->prox == lista) {
        free(atual);
        return NULL; // Lista ficou vazia
    }

    if (atual == lista) { // Remover o primeiro
        NoCircular* ultimo = lista;
        while (ultimo->prox != lista) ultimo = ultimo->prox;
        ultimo->prox = lista->prox;
        NoCircular* novo_inicio = lista->prox;
        free(lista);
        return novo_inicio;
    } else {
        anterior->prox = atual->prox;
        free(atual);
        return lista;
    }
}

NoCircular* buscar_circular(NoCircular* lista, int valor) {
    if (!lista) return NULL;
    NoCircular* atual = lista;
    do {
        if (atual->valor == valor) return atual;
        atual = atual->prox;
    } while (atual != lista);
    return NULL;
}

void imprimir_lista_circular(NoCircular* lista) {
    if (!lista) {
        printf("Lista vazia.\n");
        return;
    }
    NoCircular* atual = lista;
    printf("Lista circular: ");
    do {
        printf("[%d] -> ", atual->valor);
        atual = atual->prox;
    } while (atual != lista);
    printf("\n");
}