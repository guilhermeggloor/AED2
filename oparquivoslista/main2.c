#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *file;
    file = fopen("teste.txt", "r");

    if(file == NULL) {
        printf("Não foi possivel ler o arquivo, arquivo vazio!\n");
        return 0;
    }

    char frase[100];

    while(fgets(frase, 100, file) != NULL) {
        printf("%s", frase);
    }

    fclose(file);

    return 0;
}