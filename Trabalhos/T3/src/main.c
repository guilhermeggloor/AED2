#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define ARQUIVO_BINARIO "arvore.bin"

int main()
{
    s_no* raiz = NULL;
    int opcao, valor;

    // carrega o arquivo binario na raiz
    raiz = carregarArvoreBin(ARQUIVO_BINARIO);

    do {
        printf("\nArvore Binaria:\n ");
        printf("1 - Inserir\n");
        printf("2 - Busca\n");
        printf("3 - Encontrar Menor\n");
        printf("4 - Encontrar Maior\n");
        printf("5 - Remover\n");
        printf("6 - Imprimir árvore\n");
        printf("7 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // interface do programa no terminal
        switch(opcao) {
            case 1:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;

            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                if(buscar(raiz, valor))
                    printf("Valor %d encontrado.\n", valor);
                else
                    printf("Valor %d não encontrado.\n", valor);
                break;
            case 3: {
                int32_t menor = encontrarMenor(raiz);
                printf("Menor valor: %d\n", menor);
                break;
            }
            case 4: {
                int32_t maior = encontrarMaior(raiz);
                printf("Maior valor: %d\n", maior);
                break;
            }
            case 5:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 6:
            // impressão em pré ordem, em ordem e pós-ordem
                printf("Pré-ordem: ");
                imprimirPreOrdem(raiz);
                printf("\nEm Ordem: ");
                imprimirEmOrdem(raiz);
                printf("\nPós-ordem: ");
                imprimirPosOrdem(raiz);
                printf("\n");
                break;
            case 7:
            // ao sair grava e salva o arquivo da arvore em formato binario
                salvarArvore(raiz, ARQUIVO_BINARIO);
                liberarArvore(raiz);
                break;

            default:
                printf("Opção invalida!\n");
        }
    }while (opcao != 7);

    return 0;
}