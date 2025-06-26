#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No* prox;
    struct No* ant;
}No;

No* inserir_ordenado(No* lista, int info) {
    No* novo = malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;

    if(lista == NULL || info < lista->info) {
        novo->prox = lista;
        if(lista != NULL) {
            lista->ant = novo;
        }
        return novo;
    }

    No* atual = lista;

    while(atual->prox != NULL && atual->prox->info < info) 
    {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    novo->ant = atual;

    if(atual->prox != NULL) {
        atual->prox->ant = novo;
    }

    atual->prox = novo;

    return lista;
}

void imprimir_direto(No* lista) {
    No* atual = lista;
    while(atual != NULL) {
        printf("%d -> ", atual->info);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void imprimir_reverso(No* lista) {

    if(lista == NULL) {
        printf("Lista vazia...");
        return;
    }

    No* atual = lista;

    while(atual->prox != NULL) {
        atual = atual->prox;
    }

    while(atual != NULL) {
        printf("%d -> ", atual->info);
        atual = atual->ant;
    }
    printf("NULL\n");
}

No* carregar_lista(const char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "r");
    if(f == NULL) {
        perror("Erro ao abrir arquivo!");
        return NULL;
    }

    No* lista = NULL;
    int info;

    while(fscanf(f, "%d", &info) == 1) {
        lista = inserir_ordenado(lista, info);
    }

    fclose(f);
    return lista;
}

void liberar(No* lista) {
    while(lista != NULL) {
        No* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main()
{
    No* lista = carregar_lista("numero.txt");

    if(lista == NULL) {
        printf("Arquivo vazio ou inexistente");
    }else {
        printf("Lista em ordem direta:\n ");
        imprimir_direto(lista);

        printf("Lista em ordem reversa:\n ");
        imprimir_reverso(lista);
    }

    return 0;
}