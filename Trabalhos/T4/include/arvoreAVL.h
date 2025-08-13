#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct s_arq_no
{
    int32_t chave:28;
    int32_t bal:2;
    uint32_t esq:1;
    uint32_t dir:1;
} s_arq_no;

// struct do nó da arvore
typedef struct s_no {
    int32_t chave:28;
    int32_t bal:2;
    int32_t reservado:2;
    struct s_no* esq;
    struct s_no* dir;
} s_no;

// métodos: busca, inserção, remoção, maior, menor, sucessor, predecessor
s_no* novoNo(int32_t chave);
s_no* inserir(s_no* raiz, int32_t chave);
s_no* remover(s_no* raiz, int32_t chave);
s_no* buscar(s_no* raiz, int32_t chave);
int32_t encontrarMenor(s_no* raiz);
int32_t encontrarMaior(s_no* raiz);
s_no* encontrarPredecessor(s_no* raiz, int32_t chave);
s_no* encontrarSucessor(s_no* raiz, int32_t chave);

// pre ordem, ordem simetrica e pos ordem
void preOrdem(s_no* raiz, FILE* arquivo);
void ordem_simetrica(s_no* raiz, FILE* arquivo);
void posOrdem(s_no* raiz, FILE* arquivo);

// arquivo binário
void salvarArvPreOrdem(s_no* raiz, FILE* arquivo);
s_no* carregarArvPreOrdem(FILE* arquivo);

// liberar a salvar
void liberarArvore(s_no* raiz);
void salvarArvore(s_no* raiz, const char* nome_arquivo);
s_no* carregarArvoreBin(const char* nome_arquivo);

// impressão no terminal em pré, ordem e pós
void imprimirPreOrdem(s_no* raiz);
void imprimirEmOrdem(s_no* raiz);
void imprimirPosOrdem(s_no* raiz);

