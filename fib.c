#include <stdio.h>
#include <stdlib.h>

/*
fa + (i)
se i > 1 então 
	retorne i * fat(i-1)
senão 
	retoen fat(i - 1)
*/

unsigned fibi(unsigned i)
{
    if (i <= 1)
        return i;

    unsigned fibi_i;
    unsigned fibi_i1 = 1;
    unsigned fibi_i2 = 0;

    while( i >= 2 )
    {
        fibi_i = fibi_i1 + fibi_i2;
        fibi_i2 = fibi_i1;
        fibi_i1 = fibi_i;
        i--;
    }

    return fibi_i;
}

int main()
{
    unsigned n = 8;
    printf("Fib(%u) = %u\n", n, fibi(n));
}
