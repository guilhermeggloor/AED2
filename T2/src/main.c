#include <stdio.h>
#include <stdlib.h>

//include das listas
#include "lista_simples.h"
#include "lista_circular.h"
#include "lista_dupla.h"
#include "fila.h"
#include "pilha.h"

int main() {
    int estrutura = -1;

    while (1) {
        printf("Escolha a estrutura de dados:\n");
        printf("1. Lista simplesmente encadeada\n");
        printf("2. Lista circular simplesmente encadeada\n");
        printf("3. Lista duplamente encadeada com nó cabeça\n");
        printf("4. Fila (FIFO)\n");
        printf("5. Pilha (LIFO)\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &estrutura);

        switch (estrutura) {
            case 1:
                interface_lista_simples(); 
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 0:
                printf("Encerrando o programa.\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void interface_lista_simples() {
    int opcao_operacao = -1;
    static No* lista_simples = NULL;

    while (opcao_operacao != 0) {
        printf("\n--- Lista simplesmente encadeada ---\n");
        printf("1. Buscar\n");
        printf("2. Inserir\n");
        printf("3. Remover\n");
        printf("4. Mostrar lista\n");
        printf("0. Voltar\n");
        printf("Escolha uma operação: ");
        scanf("%d", &opcao_operacao);

        switch (opcao_operacao) {
            case 1: {
                int valor;
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                No* resultado = buscar(lista_simples, valor);
                if (resultado) {
                    printf("Valor %d encontrado.\n", valor);
                } else {
                    printf("Valor %d não encontrado.\n", valor);
                }
                break;
            }
            case 2: {
                int valor;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                lista_simples = inserir_ordenado(lista_simples, valor);
                break;
            }
            case 3:
                int valor;
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                lista_simples = remover(lista_simples, valor);
                break;
            case 4:
                imprimir_lista_simples(lista_simples);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}

