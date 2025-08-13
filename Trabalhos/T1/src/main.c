#include <stdio.h>
#include <stdlib.h>

//include das listas
#include "lista_simples.h"
#include "lista_circular.h"
#include "lista_dupla.h"
#include "fila.h"
#include "pilha.h"

// iniciar como nulo
s_no* lista_simples = NULL;
NoCircular* lista_circular = NULL;
NoDuplo* lista_dupla = NULL;
Fila* fila = NULL;
Pilha* pilha = NULL;

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
                interface_lista_circular();
                break;
            case 3:
                interface_lista_dupla();
                break;
            case 4:
                interface_fila();
                break;
            case 5:
                interface_pilha();
                break;
            case 0:
                // Verificar se é diferente de nulo e Desalocar todas as estruturas antes de sair
                if (lista_simples != NULL) {
                 destruir_lista_simples(lista_simples);
                 lista_simples = NULL;
                }
                if (lista_circular != NULL) {
                    destruir_lista_circular(lista_circular);
                    lista_circular = NULL;
                }
                if (lista_dupla != NULL) {
                    destruir_lista_dupla(lista_dupla);
                    lista_dupla = NULL;
                }
                if (fila != NULL) {
                    destruir_fila(fila);
                    fila = NULL;
                }
                if (pilha != NULL) {
                    destruir_pilha(pilha);
                    pilha = NULL;
            }
                printf("Encerrando programa....\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void interface_lista_simples() {

    int opcao_operacao = -1;

    // interface para operação das listas (vai ser replicada para as outras estruturas)
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
                s_no* resultado = buscar(lista_simples, valor);
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

void interface_lista_circular() {
    int opcao_operacao = -1;

    while (opcao_operacao != 0) {
        printf("\n--- Lista circular simplesmente encadeada ---\n");
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
                NoCircular* resultado = buscar_circular(lista_circular, valor);
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
                lista_circular = inserir_ordenado_circular(lista_circular, valor);
                break;
            }
            case 3:
                int valor;
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                lista_circular = remover_circular(lista_circular, valor);
                break;
            case 4:
                imprimir_lista_circular(lista_circular);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void interface_lista_dupla() {
    int opcao_operacao = -1;

    if(lista_dupla == NULL) {
        lista_dupla = criar_lista_dupla();
    }

    while (opcao_operacao != 0) {
        printf("\n--- Lista duplamente encadeada ---\n");
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
                NoDuplo* resultado = buscar_dupla(lista_dupla, valor);
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
                inserir_dupla(lista_dupla, valor);
                break;
            }
            case 3:
                int valor;
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                remover_duplo(lista_dupla, valor);
                break;
            case 4:
                imprimir_lista_dupla(lista_dupla);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void interface_fila(void) {
    int opcao_operacao = -1;

    if (fila == NULL) {
        fila = criar_fila();
    }

    while (opcao_operacao != 0) {
        printf("\n--- Fila (FIFO) ---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Mostrar fila\n");
        printf("0. Voltar\n");
        printf("Escolha uma operação: ");
        scanf("%d", &opcao_operacao);

        switch (opcao_operacao) {
            case 1: {
                int valor;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir_fila(fila, valor);
                break;
            }
            case 2: {
                int removido = remover_fila(fila);
                if (removido == -1) {
                    printf("Fila vazia, nada a remover.\n");
                } else {
                    printf("Valor removido: %d\n", removido);
                }
                break;
            }
            case 3:
                imprimir_fila(fila);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}

void interface_pilha(void) {
    int opcao_operacao = -1;
    if (pilha == NULL) {
        pilha = criar_pilha();
    }

    while (opcao_operacao != 0) {
        printf("\n--- Pilha (LIFO) ---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Mostrar pilha\n");
        printf("0. Voltar\n");
        printf("Escolha uma operação: ");
        scanf("%d", &opcao_operacao);

        switch (opcao_operacao) {
            case 1: {
                int valor;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir_pilha(pilha, valor);
                break;
            }
            case 2: {
                int removido = remover_pilha(pilha);
                if (removido == -1) {
                    printf("Pilha vazia, nada a remover.\n");
                } else {
                    printf("Valor removido: %d\n", removido);
                }
                break;
            }
            case 3:
                imprimir_pilha(pilha);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    }
}