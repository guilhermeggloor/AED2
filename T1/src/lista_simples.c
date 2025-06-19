#include <stdio.h>
#include <stdlib.h>
#include "lista_simples.h"

//procedimento de busca
No* buscar(No* inicio, int valor) {
    No* atual = inicio;

    while (atual != NULL && atual->valor <= valor) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL; // retorna nulo se não encontrado
}

No* inserir_ordenado(No* inicio, int valor) {
    No* novo = malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação.\n");
        return inicio;
    }

    novo->valor = valor;
    novo->prox = NULL;

    // verifica se ou é igual a vazia ou menor que o primeiro elemento (anterior inserido já)
    if (inicio == NULL || valor < inicio->valor) {
        novo->prox = inicio;
        return novo; // novo se torna o primeiro
    }

    // Inserção no meio ou final
    No* atual = inicio;
    while (atual->prox != NULL && atual->prox->valor < valor) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    return inicio;
}

No* remover(No* lista, int valor) {
    No* atual = lista;
    No* anterior = NULL;

    while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->valor == valor) {
        if (anterior == NULL) {
            // Remover o primeiro nó
            No* temp = atual->prox;
            free(atual);
            return temp;
        } else {
            anterior->prox = atual->prox;
            free(atual);
            return lista;
        }
    }

    // se valor não encontrado, retorna a lista original
    return lista;
}

// função para imprimir a lista simples
void imprimir_lista_simples(No* inicio) {
    No* atual = inicio;
    printf("Lista: ");

    while (atual != NULL) {
        printf("[%d ] -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

// função para desalocar a lista simples
void destruir_lista_simples(No* lista) {
    while(lista) {
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}
