#include <stdio.h>
#include <stdlib.h>

int Fat(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n * (Fat(n - 1));
    }
}

int main()
{
    int num;

    // Teste com diferentes valores de n
    printf("Digite um numero para calcular o fatorial: ");
    scanf("%d", &num);

    // Chama a função Fat e imprime o resultado
    printf("Fatorial de %d é %d\n", num, Fat(num));

    return 0;
}