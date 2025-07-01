#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct s_arq_no
{
    int32_t chave:30;   
    uint32_t esq:1;
    uint32_t dir:1;
} s_arq_no;

// struct do nó da arvore
typedef struct No {
    s_arq_no info;
    struct No* esq;
    struct No* dir;
} No;

// métodos: busca, inserção, remoção, maior, menor, sucessor, predecessor
No* novoNo(int32_t chave);
No* inserir(No* raiz, int32_t chave);
No* remover(No* raiz, int32_t chave);
No* buscar(No* raiz, int32_t chave);
int32_t encontrarMenor(No* raiz);
int32_t encontrarMaior(No* raiz);
No* encontrarPredecessor(No* raiz, int32_t chave);
No* encontrarSucessor(No* raiz, int32_t chave);

// pre ordem, ordem simetrica e pos ordem
void preOrdem(No* raiz, FILE* arquivo);
void ordem_simetrica(No* raiz, FILE* arquivo);
void posOrdem(No* raiz, FILE* arquivo);

// arquivo binário
void salvarArvPreOrdem(No* raiz, FILE* arquivo);
No* carregarArvPreOrdem(FILE* arquivo);

// liberar a salvar
void liberarArvore(No* raiz);
void salvarArvore(No* raiz, const char* nome_arquivo);
No* carregarArvoreBin(const char* nome_arquivo);


void imprimirPreOrdem(No* raiz);
void imprimirEmOrdem(No* raiz);
void imprimirPosOrdem(No* raiz);

