#include <stdio.h>

void pivom3(unsigned ini, unsigned fim)
{
    printf("pivom3\n");
}

void pivoaleat(unsigned ini, unsigned fim)
{
    printf("pivoaleat\n");
}

void pivoprim(unsigned ini, unsigned fim)
{
    printf("pivoprim\n");
}

struct arvB
{
    unsigned m;
    //outras 
    //
    
};

int main()
{
    void (*pivot)(unsigned, unsigned);

    pivot = pivoaleat;

    pivot(0, 100);

    return 0;
}