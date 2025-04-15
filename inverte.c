#include <stdio.h>
#include <stdlib.h>

void Inverte(int S[], int n, int i)
{
    if(i >= n / 2)
        return;

    int temp = S[i];
    S[i] = S[n - i + 1];
    S[n - i + 1] = temp;

    Inverte(S, n, i + 1);
}

int main()
{
    int S[] = {1, 2, 3, 4};
    int n = sizeof(S) / sizeof(S[0]);

    Inverte(S, n, 0);

    for(int i = 0; i < n; i++)
        printf("%d", S[i]);
    printf("\n");

    return 0;
}