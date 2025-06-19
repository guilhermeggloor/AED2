#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No* novoNo(int32_t chave) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info.chave = chave;
    novo->info.esq = 0;
    novo->info.dir = 0;
    novo->esq = NULL;
    novo->dir = NULL;
}

No* buscar(No* raiz, int32_t chave) {
    if(raiz == NULL || raiz->info.chave == chave) {
        return raiz;
    }
    if(chave < raiz->info.chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

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

int32_t encontrarMenor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual->info.chave;
}

int32_t encontrarMaior(No* raiz) {
    No* atual = raiz;
    while(atual && atual->dir != NULL) 
        atual = atual->dir;
    return atual->info.chave;
}

void preOrdem(No* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        preOrdem(raiz->esq, arquivo);
        preOrdem(raiz->dir, arquivo);
    }
}

void ordem_simetrica(No* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        ordem_simetrica(raiz->esq, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        ordem_simetrica(raiz->dir, arquivo);
    }
}

void posOrdem(No* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        posOrdem(raiz->esq, arquivo);
        posOrdem(raiz->dir, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
    }
}




int main(){


    return 0;
}