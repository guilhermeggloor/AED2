#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* ant;
    struct No* prox;
} No;


No* inserir_fim(No* lista, int valor) {
    No* novo = malloc(sizeof(No
));
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if (lista == NULL)
        return novo; // Primeiro nó

    No* atual = lista;
    while (atual->prox != NULL)
        atual = atual->prox;

    atual->prox = novo;
    novo->ant = atual;

    return lista;
}

No* carregar_lista_dupla(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    No* lista = NULL;
    int valor;

    while (fscanf(f, "%d", &valor) == 1) {
        lista = inserir_fim(lista, valor);
    }

    fclose(f);
    return lista;
}

void imprimir_direto(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void imprimir_reverso(No* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    // Vai até o último
    No* atual = lista;
    while (atual->prox != NULL)
        atual = atual->prox;

    // Volta imprimindo
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->ant;
    }
    printf("NULL\n");
}

void liberar_lista(No* lista) {
    while (lista != NULL) {
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    No* lista = carregar_lista_dupla("valores.txt");

    if (lista == NULL) {
        printf("Lista vazia ou erro ao abrir o arquivo.\n");
    } else {
        printf("Impressão direta:\n");
        imprimir_direto(lista);

        printf("Impressão reversa:\n");
        imprimir_reverso(lista);
    }

    liberar_lista(lista);
    return 0;
}
