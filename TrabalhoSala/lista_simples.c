#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int info;
    struct No* prox;
}No;

No *inserir_fim(No* lista, int info)
{
    No* novo = malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL;

    if (lista == NULL)
    {
        return novo;
    }

    No* atual = lista;
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }

    atual->prox = novo;
    return lista;
}

No *carregar_lista(const char* nome_arquivo)
{
    FILE* f = fopen(nome_arquivo, "r");

    if (f == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    No* lista = NULL;
    int info;

    while (fscanf(f, "%d", &info) == 1)
    {
        lista = inserir_fim(lista, info);
    }

    fclose(f);
    return lista;
}

void imprimir_lista(No* lista)
{
    No* atual = lista;
    while (atual != NULL)
    {
        printf("%d -> ", atual->info);
        atual = atual->prox;
    }
    printf(" NULL\n");
}

void liberar_lista(No *lista)
{
    while (lista != NULL)
    {
        No *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main()
{
    No* lista = carregar_lista("numero.txt");

    if (lista == NULL)
    {
        printf("Lista vazia ou erro de leitura.\n");
    }
    else
    {
        imprimir_lista(lista);
    }

    return 0;
}