#include <stdio.h>

int main()
{
    char v[6] = {'a', 'b', 'c', 'd', 'e', '\0'};

    printf("%s", v);

    printf("\nv = %p, c = %li", sizeof(v[0]));

    for (unsigned i = 0; i < 6; i++)
        printf("\i %i, end %p", i, v + i - 1);

    printf("\n");
    char *p = v;
    char *pend = v + 6;

    while (*p < pend)
        printf("%c", *p++);

    return 0;
}