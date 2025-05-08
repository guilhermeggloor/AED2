#include <stdio.h>
#include <stdlib.h>

//implementar Lista simplesmente encadeada sem nó cabeça ordenada: busca, inserção e remoção ;

struct s_no
{
    int info;
    struct s_no *prox;
};
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

void insereListaOrdenadasemNo(struct s_no **ptlista, int x)
{
    struct s_no *p, *ant, *novo;
    novo = (struct s_no *)malloc(sizeof(struct s_no));
    novo->info = x;
    ant = NULL;
    p = *ptlista;

    while (p != NULL && p->info < x)
    {
        ant = p;
        p = p->prox;
    }

    if (ant == NULL)
    {
        novo->prox = *ptlista;
        *ptlista = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

void removeListaOrdenadasemNo(struct s_no **ptlista, int x)
{
    struct s_no *p, *ant;
    ant = NULL;
    p = *ptlista;

    while (p != NULL && p->info < x)
    {
        ant = p;
        p = p->prox;
    }

    if (p != NULL && p->info == x)
    {
        if (ant == NULL)
        {
            *ptlista = p->prox;
        }
        else
        {
            ant->prox = p->prox;
        }
        free(p);
    }
}
