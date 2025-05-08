#include <stdio.h>

unsigned Busca(int *S, unsigned n, int x, unsigned i)
{   
    if(i > n)
        return 0;
    if( S[i] == x)
        return 1;

    Busca(S, n, x, i+1);
}

int main()
{
    int S[5] = {1, 5, 2, 3, 8};
    unsigned n = 5;

    
    printf("Encontrou? %s\n", Busca(S, n, 4, 0)?"Sim!" : "Não!");

    return 0;
}


/* 
Busca(S, n, x, i)
    se i > n então
        retorna F
    se S[i] == x então
        retorna V
    
    retorna Busca(S, n, x, i+1) --> nunca esqueça de colocar retornar

*/