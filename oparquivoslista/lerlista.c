#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

// Insere no final da lista (para manter a ordem do arquivo)
No* inserir_fim(No* lista, int valor) {
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (lista == NULL)
        return novo;

    No* atual = lista;
    while (atual->prox != NULL)
        atual = atual->prox;

    atual->prox = novo;
    return lista;
}

// Imprime a lista
void imprimir(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

No* carregar_lista_do_arquivo(const char* nome_arquivo) {
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

int main() {
    No* lista = carregar_lista_do_arquivo("valores.txt");

    if (lista == NULL) {
        printf("Nenhum dado foi carregado ou o arquivo está vazio.\n");
    } else {
        printf("Lista carregada do arquivo:\n");
        imprimir(lista);
    }

    // Liberar memória
    while (lista != NULL) {
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}

