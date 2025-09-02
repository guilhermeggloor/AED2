#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"
#include "print-avl.h"

#define ARQUIVO_BINARIO "arvore.bin"

int main()
{
    s_no* raiz = NULL;
    int opcao, valor;

    // carrega o arquivo binario na raiz
    raiz = carregarArvoreBin(ARQUIVO_BINARIO);

    printf("Arvore Carregada no arquivo. Pressione qualquer tecla pra continuar...");
    imprime_arvore(raiz);

    do {
        printf("\nArvore AVL:\n ");
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
                imprime_arvore(raiz);
                break;

            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                if(buscar(raiz, valor))
                    printf("Valor %d encontrado.\n", valor);
                else
                    printf("Valor %d não encontrado.\n", valor);
                printf("Pressione qualquer tecla pra continuar...");
                getchar();
                getchar();
                break;
            case 3: {
                if(raiz == NULL) {
                    printf("A Arvore esta vazia!\n");
                }else {
                    int32_t menor = encontrarMenor(raiz);
                    printf("Menor valor: %d\n", menor);
                }
                printf("Pressione qualquer tecla para continuar...\n");
                getchar(); getchar();
                break;
            }
            case 4: {
                if(raiz == NULL) {
                    printf("A Arvore esta vazia!\n");
                }else {
                    int32_t maior = encontrarMaior(raiz);
                    printf("Maior valor: %d\n", maior);
                }
                printf("Pressione qualquer tecla para continuar...\n");
                getchar(); getchar();
                break;
            }
            case 5:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                imprime_arvore(raiz);
                break;
            case 6:
            // impressão em pré ordem, em ordem e pós-ordem em modo texto
                printf("Impressão em modo texto:\n ");
                printf("Pré-ordem: ");
                imprimirPreOrdem(raiz);
                printf("\nEm Ordem: ");
                imprimirEmOrdem(raiz);
                printf("\nPós-ordem: ");
                imprimirPosOrdem(raiz);
                printf("\n\nPressione qualquer tecla para ver a impressão gráfica...\n");
                getchar(); getchar();
                imprime_arvore(raiz);
                break;
            case 7:
            // ao sair grava e salva o arquivo da arvore em formato binario
                salvarArvore(raiz, ARQUIVO_BINARIO);
                liberarArvore(raiz);
                printf("Arvore salva, saindo...\n");
                break;

            default:
                printf("Opção invalida!\n");
                printf("Pressione qualquer tecla para continuar...\n");
                getchar(); getchar();
        }
    }while (opcao != 7);

    return 0;
}