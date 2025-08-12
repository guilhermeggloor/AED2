#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *file;
    file = fopen("numero.txt", "r");

    if (file == NULL) {
        printf("Arquivo não pode ser aberto!\n");
        return 0;
    }

    int x,y,z;
    fscanf(file, "%d %d %d", &x, &y, &z);
    printf( "%i %i %i\n", x, y, z);
    fclose(file);
    // fprintf(file, "Pao com mortadela");
    // fclose(file);

    return 0;   
}