#include <stdio.h>
#include <stdlib.h>

struct s_no
{
    int info;
    struct s_no *prox;
};

int main()
{

    struct s_no *ptlista = NULL,
                *p1, *p2, *p3, *pont;

    // aloca nós
    p1 = malloc(sizeof(struct s_no));
    p2 = malloc(sizeof(struct s_no));
    p3 = malloc(sizeof(struct s_no));

    // Inicializa nós (valores e encadeamento)
    p1->info = 1;
    p1->prox = p2;
    p2->info = 2;
    p2->prox = p3;
    p3->info = 3;
    p3->prox = NULL;
    ptlista = p1; // Inicializa ponteiro do inicio da lista

    // Imprime valores na lista
    pont = ptlista;
    while (pont != NULL)
    {
        printf("%i -> ", pont->info);
        pont = pont->prox;
    }

    return 0;
}