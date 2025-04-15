#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
    int x = 0;
    int n = 0;
    int soma = 0;
    int media = 0;
    int maior = INT_MIN;
    int menor = INT_MAX;

    printf("ler x: ");
    scanf("%d", &x);

    while (x > 0)
    {
        n = n + 1;
        soma = soma + x;

        if (x < menor)
        {
            menor = x;
        }

        if (x > maior)
        {
            maior = x;
        }
        printf("ler x: ");
        scanf("%d", &x);
        if (n > 0)
        {
            media = (soma / n);
        }
    }

    printf("maior: %d\n", maior);
    printf("menor: %d\n", menor);
    printf("soma: %d\n", soma);
    printf("media: %d\n", media);

    return 0;
}