#include <stdio.h>
#include <stdlib.h>

// implementar uma função busca de um elemento na lista L
// implementar busca binária se um elemento x está na lista L
// Implementar remoção de um nó na lista L
// Implementar impressão da lista
// Implementar inserção
// implementar remoção

struct s_no
{
    int info;
    struct s_no *prox;
};

void imprimeRecursiva(struct s_no *pt)
{
    if (pt != NULL)
    {
        printf("%d\n", pt->info);
        imprimeRecursiva(pt->prox);
    }
}

void imprimeIterativo(struct s_no *ptlista)
{
    struct s_no *p;
    for (p = ptlista; p != NULL; p = p->prox)
    {
        printf("%d\n", p->info);
    }
}

struct s_no *busca(int x, struct s_no *ptlista)
{
    struct s_no *p;
    p = ptlista;
    while (p != NULL && p->info != x)
    {
        p = p->prox;
    }
    return p;
}

struct s_no *buscaRecursiva(int x, struct s_no *ptlista)
{
    if (ptlista == NULL)
    {
        return NULL;
    }

    if (ptlista->info == x)
    {
        return ptlista;
    }

    return buscaRecursiva(x, ptlista->prox);
}

void insere(int x, struct s_no **ptlista)
{
    struct s_no *elemento;
    elemento = malloc(sizeof(struct s_no));
    elemento->info = x;
    elemento->prox = *ptlista;
    *ptlista = elemento;
}

// void removeLista(struct s_no *ptlista)
// {
//     struct s_no *pt;
//     pt = ptlista->prox;
//     ptlista->prox = pt->prox;
//     free(lixo);
// }

int main()
{
    struct s_no *ptlista = NULL;

    insere(5, &ptlista);
    insere(6, &ptlista);
    insere(7, &ptlista);
    insere(8, &ptlista);
    insere(1, &ptlista);
    insere(2, &ptlista);
    insere(27, &ptlista);

    imprimeIterativo(ptlista);

    return 0;
}