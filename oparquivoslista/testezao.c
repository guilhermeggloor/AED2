#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;  

No* inserir(No* Lista, int valor) {
    No* novo = malloc(sizeof(No));

    if(novo == NULL) {
        printf("eroo de alocação!");
        exit(1);
    }
    novo->valor = valor;
    novo->prox = Lista;
    return novo;
}

void imprimir(No* Lista) {
    No* atual = Lista;
    while(atual !=  NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void salvar_em_arquivo(No* Lista, const char* nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "w");
    if (f == NULL) {
        perror("Erro ao abrir arquivo!");
        return;
    }

    No* atual = Lista;
    while(atual != NULL) {
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
