#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

// Definição do nó da lista dupla
typedef struct NoDuplo {
    int valor;
    struct NoDuplo* prox;
    struct NoDuplo* ant;
} NoDuplo;

NoDuplo* criar_lista_dupla(void);

void inserir_dupla(NoDuplo* cabeca, int valor);   //insere no final
void remover_duplo(NoDuplo* cabeca, int valor);   // remove nó com o valor
NoDuplo* buscar_dupla(NoDuplo* cabeca, int valor);  //busca nó com o valor
void imprimir_lista_dupla(NoDuplo* cabeca);
void interface_lista_dupla(void);
void destruir_lista_dupla(NoDuplo* cabeca);


#endif