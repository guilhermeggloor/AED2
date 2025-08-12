#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int m;
    struct No *pont_pai;
    int *s;
    struct No **p;
}No;

No *busca(No* no, int ch)
{
    if(no != NULL) {
        int i = 0;
        while(i < no->m && ch > no->s[i]) {
            i++;
        }
        if (i < no->m && ch == no->s[i]) {
            return no;
        } else if (no->p[i] != NULL) {
            return busca(no->p[i], ch);
        } else return no;
    }else return NULL;
}

int main()
{


    return 0;
}