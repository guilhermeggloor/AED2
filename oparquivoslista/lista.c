#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

// Insere no início
No* inserir(No* lista, int valor) {
    No* novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = lista;
    return novo;
}

// Imprime
void imprimir(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void salvar_em_arquivo(No* lista, const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "w");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    No* atual = lista;
    while (atual != NULL) {
        fprintf(f, "%d\n", atual->valor);
        atual = atual->prox;
    }

    fclose(f);
}

No* carregar_de_arquivo(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    No* lista = NULL;
    int valor;
    while (fscanf(f, "%d", &valor) != EOF) {
        lista = inserir(lista, valor);  // insere no início
    }

    fclose(f);
    return lista;
}

int main() {
    No* lista = NULL;

    // Inserindo elementos
    lista = inserir(lista, 10);
    lista = inserir(lista, 20);
    lista = inserir(lista, 30);

    printf("Lista atual:\n");
    imprimir(lista);

    salvar_em_arquivo(lista, "lista.txt");

    // Liberar lista
    while (lista != NULL) {
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    // Carregando do arquivo
    lista = carregar_de_arquivo("lista.txt");
    printf("\nLista carregada do arquivo:\n");
    imprimir(lista);

    return 0;
}


