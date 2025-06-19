#include <stdio.h>
#include <stdlib.h>

typedef struct NoDuplo {
    int valor;
    struct NoDuplo* prox;
    struct NoDuplo* ant;
} NoDuplo;

NoDuplo* inserir_fim(NoDuplo* lista, int valor) {
    NoDuplo* novo = malloc(sizeof(NoDuplo));
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if (lista == NULL)
        return novo;

    NoDuplo* atual = lista;
    while (atual->prox != NULL)
        atual = atual->prox;

    atual->prox = novo;
    novo->ant = atual;

    return lista;
}

void imprimir_direto(NoDuplo* lista) {
    NoDuplo* atual = lista;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void imprimir_reverso(NoDuplo* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    NoDuplo* atual = lista;
    while (atual->prox != NULL)  // vai até o último
        atual = atual->prox;

    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->ant;
    }
    printf("NULL\n");
}

NoDuplo* carregar_lista_dupla(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    NoDuplo* lista = NULL;
    int valor;

    while (fscanf(f, "%d", &valor) == 1) {
        lista = inserir_fim(lista, valor);
    }

    fclose(f);
    return lista;
}

void liberar_lista(NoDuplo* lista) {
    while (lista != NULL) {
        NoDuplo* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    NoDuplo* lista = carregar_lista_dupla("valores.txt");

    if (lista == NULL) {
        printf("Arquivo vazio ou inexistente.\n");
    } else {
        printf("Lista em ordem direta:\n");
        imprimir_direto(lista);

        printf("Lista em ordem reversa:\n");
        imprimir_reverso(lista);
    }

    liberar_lista(lista);
    return 0;
}
