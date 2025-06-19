#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    int valor;
    struct NoFila* prox;
} NoFila;

typedef struct Fila {
    NoFila* inicio;
    NoFila* fim;    
} Fila;

Fila* criar_fila(void);
void inserir_fila(Fila* fila, int valor);
int remover_fila(Fila* fila);
void imprimir_fila(Fila* fila);
void destruir_fila(Fila* fila);
void interface_fila(void);



#endif