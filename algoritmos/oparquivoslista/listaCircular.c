#include <stdio.h>
#include <stdlib.h>

typedef struct NoCircular {
    int valor;
    struct NoCircular* prox;
} NoCircular;


NoCircular* inserir_fim(NoCircular* lista, int valor) {
    NoCircular* novo = malloc(sizeof(NoCircular));
    novo->valor = valor;
    novo->prox = NULL;

    if (lista == NULL) {
        novo->prox = novo; // aponta pra si mesmo
        return novo;
    }

    NoCircular* atual = lista;
    while (atual->prox != lista)
        atual = atual->prox;

    atual->prox = novo;
    novo->prox = lista;

    return lista;
}

void imprimir(NoCircular* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    NoCircular* atual = lista;
    do {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    } while (atual != lista);

    printf("(volta)\n");
}

NoCircular* carregar_lista_circular(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    NoCircular* lista = NULL;
    int valor;

    while (fscanf(f, "%d", &valor) == 1) {
        lista = inserir_fim(lista, valor);
    }

    fclose(f);
    return lista;
}
void liberar_lista(NoCircular* lista) {
    if (lista == NULL) return;

    NoCircular* atual = lista->prox;
    while (atual != lista) {
        NoCircular* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

int main() {
    NoCircular* lista = carregar_lista_circular("valores.txt");

    if (lista == NULL) {
        printf("Arquivo vazio ou não encontrado.\n");
    } else {
        printf("Lista circular:\n");
        imprimir(lista);
    }

    liberar_lista(lista);
    return 0;
}
