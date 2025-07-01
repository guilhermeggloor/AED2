#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// cria um novo nó da arvore
No* novoNo(int32_t chave) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info.chave = chave;
    novo->info.esq = 0;
    novo->info.dir = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// busca do elemento correspondente - 2
No* buscar(No* raiz, int32_t chave) {
    if(raiz == NULL || raiz->info.chave == chave) {
        return raiz;
    }
    if(chave < raiz->info.chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

// operação de inserção - 1
No* inserir(No* raiz, int32_t chave) {
    if (raiz == NULL)
        return novoNo(chave);

    if (chave < raiz->info.chave) {
        raiz->info.esq = 1;
        raiz->esq = inserir(raiz->esq, chave);
    } else if (chave > raiz->info.chave) {
        raiz->info.dir = 1;
        raiz->dir = inserir(raiz->dir, chave);
    } else {
        // chave já existente na arvore, mandar um aviso
        printf("Chave %d já existe na árvore, insira outra\n");
        return raiz;
    }

    return raiz;
}

// operação de remoção - 5
No* remover(No* raiz, int32_t chave) {
    if (raiz == NULL) return NULL;

    if(chave < raiz->info.chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->info.chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        No* temp = encontrarMenor(raiz->dir);
        raiz->info.chave = temp->info.chave;
        raiz->dir = remover(raiz->dir, temp->info.chave);
    }
}

// encontrar o menor elemento da arvore - 3
int32_t encontrarMenor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual->info.chave;
}

// encontrar o maior elemento da arvore - 4
int32_t encontrarMaior(No* raiz) {
    No* atual = raiz;
    while(atual && atual->dir != NULL) 
        atual = atual->dir;
    return atual->info.chave;
}

// percurso em pre ordem
void preOrdem(No* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        preOrdem(raiz->esq, arquivo);
        preOrdem(raiz->dir, arquivo);
    }
}

// percurso em ordem
void ordem_simetrica(No* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        ordem_simetrica(raiz->esq, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        ordem_simetrica(raiz->dir, arquivo);
    }
}

// percurso em pós ordem
void posOrdem(No* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        posOrdem(raiz->esq, arquivo);
        posOrdem(raiz->dir, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
    }
}

// salva a arvore em pré ordem com arquivo
void salvarArvPreOrdem(No* raiz, FILE* arquivo) {
    if (raiz == NULL) {
        int marcador = -1;
        fwrite(&marcador, sizeof(int), 1, arquivo);
        return;
    }
    fwrite(&raiz->info, sizeof(int), 1, arquivo);
    salvarArvPreOrdem(raiz->esq, arquivo);
    salvarArvPreOrdem(raiz->dir, arquivo);
}

// Carrega a arvore em pré ordem com operação de arquivo
No* carregarArvPreOrdem(FILE* arquivo) {
    int info;
    if (fread(&info, sizeof(int), 1, arquivo) !=  1)
        return NULL;

    if (info == -1)
        return NULL;

    No* no = novoNo(info);
    no->esq = carregarArvPreOrdem(arquivo);
    no->dir = carregarArvPreOrdem(arquivo);

    return no;
}

// salva a arvore no arquivo.bin
void salvarArvore(No* raiz, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if(!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    salvarArvPreOrdem(raiz, arquivo);
    fclose(arquivo);
}

// finalmente carrega mais uma vez a arvore no arquivo.bin (trabalheira que deu esse negócio)
No* carregarArvoreBin(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if(!arquivo) {
        perror("Erro ao abrir arquivo para leitura");
        return NULL;
    }
    No* raiz = carregarArvPreOrdem(arquivo);
    fclose(arquivo);
    return raiz;
}

// desaloca e libera a arvore (importante quando for sair do programa)
void liberarArvore(No* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

// operação para imprimir a arvore em pré ordem e mostrar ao usuário no terminal
void imprimirPreOrdem(No* raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->info.chave);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
}

// operação para imprimir em ordem e mostrar o usuário
void imprimirEmOrdem(No* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d ", raiz->info.chave);
    imprimirEmOrdem(raiz->dir);
}

// cansei, op. bla bla bla, imprimi em pós ordem ao usuário.
void imprimirPosOrdem(No* raiz) {
    if (raiz == NULL) return;
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d ", raiz->info.chave);
}
