#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// cria um novo nó da arvore
s_no* novoNo(int32_t chave) {
    s_no* novo = (s_no*)malloc(sizeof(s_no));
    novo->info.chave = chave;
    novo->info.esq = 0;
    novo->info.dir = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// busca do elemento correspondente - 2
s_no* buscar(s_no* raiz, int32_t chave) {
    if(raiz == NULL || raiz->info.chave == chave) {
        return raiz;
    }
    if(chave < raiz->info.chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

// operação de inserção - 1
s_no* inserir(s_no* raiz, int32_t chave) {
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
        printf("Chave %d já existe na árvore, insira outra\n", chave);
        return raiz;
    }

    return raiz;
}

// operação de remoção - 5
s_no* remover(s_no* raiz, int32_t chave) {
    if (raiz == NULL) return NULL;

    if(chave < raiz->info.chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->info.chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        if (raiz->esq == NULL) {
            s_no* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            s_no* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        int32_t menor = encontrarMenor(raiz->dir);
        raiz->info.chave = menor;
        raiz->dir = remover(raiz->dir, menor);
    }
    return raiz;
}

// encontrar o menor elemento da arvore - 3
int32_t encontrarMenor(s_no* raiz) {
    s_no* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual->info.chave;
}

// encontrar o maior elemento da arvore - 4
int32_t encontrarMaior(s_no* raiz) {
    s_no* atual = raiz;
    while(atual && atual->dir != NULL)
        atual = atual->dir;
    return atual->info.chave;
}

// percurso em pre ordem
void preOrdem(s_no* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        preOrdem(raiz->esq, arquivo);
        preOrdem(raiz->dir, arquivo);
    }
}

// percurso em ordem
void ordem_simetrica(s_no* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        ordem_simetrica(raiz->esq, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
        ordem_simetrica(raiz->dir, arquivo);
    }
}

// percurso em pós ordem
void posOrdem(s_no* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        posOrdem(raiz->esq, arquivo);
        posOrdem(raiz->dir, arquivo);
        fwrite(&(raiz->info), sizeof(s_arq_no), 1, arquivo);
    }
}

// salva a arvore em pré ordem com arquivo
void salvarArvPreOrdem(s_no* raiz, FILE* arquivo) {
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
s_no* carregarArvPreOrdem(FILE* arquivo) {
    int info;
    if (fread(&info, sizeof(int), 1, arquivo) !=  1)
        return NULL;

    if (info == -1)
        return NULL;

    s_no* no = novoNo(info);
    no->esq = carregarArvPreOrdem(arquivo);
    no->dir = carregarArvPreOrdem(arquivo);

    return no;
}

// salva a arvore no arquivo.bin
void salvarArvore(s_no* raiz, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if(!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    salvarArvPreOrdem(raiz, arquivo);
    fclose(arquivo);
}

// finalmente carrega mais uma vez a arvore no arquivo.bin (trabalheira que deu esse negócio)
s_no* carregarArvoreBin(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if(!arquivo) {
        perror("Erro ao abrir arquivo para leitura");
        return NULL;
    }
    s_no* raiz = carregarArvPreOrdem(arquivo);
    fclose(arquivo);
    return raiz;
}

// desaloca e libera a arvore (importante quando for sair do programa)
void liberarArvore(s_no* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

// operação para imprimir a arvore em pré ordem e mostrar ao usuário no terminal
void imprimirPreOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->info.chave);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
}

// operação para imprimir em ordem e mostrar o usuário
void imprimirEmOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d ", raiz->info.chave);
    imprimirEmOrdem(raiz->dir);
}

// cansei, op. bla bla bla, imprimi em pós ordem ao usuário.
void imprimirPosOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d ", raiz->info.chave);
}
