#ifndef PILHA_H
#define PILHA_H

typedef struct NoPilha {
    int valor;
    struct NoPilha* prox;
} NoPilha;

typedef struct Pilha {
    NoPilha* topo;
} Pilha;

Pilha* criar_pilha(void);
void inserir_pilha(Pilha* pilha, int valor); // push
int remover_pilha(Pilha* pilha);             // pop, retorna -1 se vazia
void imprimir_pilha(Pilha* pilha);
void destruir_pilha(Pilha* pilha);
void interface_pilha(void); 

#endif