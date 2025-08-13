#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"

// cria um novo nó da arvore
s_no* novoNo(int32_t chave) {
    s_no* novo = (s_no*)malloc(sizeof(s_no));
    if(!novo) {
        perror("falha na alocação de memória para o novo nó");
        exit(EXIT_FAILURE);
    }
    novo->chave = chave;
    novo->esq = 0;
    novo->dir = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// busca do elemento correspondente - 2
s_no* buscar(s_no* raiz, int32_t chave) {
    if(raiz == NULL || raiz->chave == chave) {
        return raiz;
    }
    if(chave < raiz->chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

int altura(s_no* no) {
    if(no == NULL)
        return 0;

    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

int obterBalanceamento(s_no* no) {
    if(no == NULL)
        return 0;
    return altura(no->dir) - altura(no->esq);
}

s_no* rotacaoDireita(s_no* y) {
    s_no* x = y->esq;
    s_no* T2 = x->dir;

    // realiza a rotação
    x->dir = y;
    y->esq = T2;

    //Atualiza os fatores de balanceamento dos nós afetados
    y->bal = obterBalanceamento(y);
    x->bal = obterBalanceamento(x);

    return x;
}

s_no* rotacaoEsquerda(s_no* x) {
    s_no* y = x->dir;
    s_no* T2 = y->esq;

    // realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza os fatores de balanceamento dos nós afetados
    x->bal = obterBalanceamento(x);
    y->bal = obterBalanceamento(y);

    return y;

}

// operação de inserção - 1
s_no* inserir(s_no* no, int32_t chave) {
    if (no == NULL)
        return (novoNo(chave));

    if (chave < no->chave)
        no->esq = inserir(no->esq, chave);
    else if (chave > no->chave)
        no->dir = inserir(no->dir, chave);
    else {
        printf("chave %d já existente na árvore.\n", chave);
        return no;
    }

    // Atualizando fator do nó de balanceamento de ant
    no->bal = obterBalanceamento(no);
    int balanco = no->bal;

    // Verifica se o nó é desbalanceado e executa as rotações

    //Caso da esquerda (LL)
    // O desbalanceamento é -2 e a nova chave foi inserida na subárvore esquerda do filho esquerdo
    if(balanco < -1 && chave < no->esq->chave) {
        printf("Rotação Direita (LL) em torno do nó %d\n", no->chave);
        return rotacaoDireita(no);
    }

    //Caso direita (RR)
    // O desbalanceamento é +2 e a nova chave foi inserida na subárvore direita do filho direito
    if(balanco > 1 && chave > no->dir->chave) {
        printf("Rotação Esquerda (RR) em torno do nó %d\n", no->chave);
        return rotacaoEsquerda(no);
    }

    //Caso esquerda-direita (LR)
    // O desbalanceamento é -2 e a nova chave foi inserida na subárvore direita do filho esquerdo
    if(balanco < -1 && chave > no->esq->chave) {
        printf("Rotação Esquerda-Direita (LR) em torno do novo nó %d\n", no->chave);
        no->esq = rotacaoEsquerda(no);
        return rotacaoDireita(no);
    }

    //Caso direita-esquerda (RL)
    // O desbalanceamento é +2 e a nova chave foi inserida na subárvore esquerda do filho direito
    if(balanco > 1 && chave < no->dir->chave) {
        printf("Rotação Direita-Esquerda (RL) em torno do novo nó %d\n", no->chave);
        no->dir = rotacaoDireita(no);
        return rotacaoEsquerda(no);
    }

    // Retorna o ponteiro do nó (sem mudanças se estava balanceado ou não)
    return no;
}

s_no* encontrarNoMenor(s_no* no) {
    s_no* atual = no;
    // Loop para encontrar a folha mais à esquerda
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// operação de remoção - 5
s_no* remover(s_no* raiz, int32_t chave) {
    if (raiz == NULL) return NULL;

    if(chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->chave) {
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

        // nó com dois filhos: pega o sucessor em ordem (o menor da subárvore direita)
        s_no* temp = encontrarNoMenor(raiz->dir);

        // Copia o conteudo do sucessor para este nó
        raiz->chave = temp->chave;

        // remove o sucessor
        raiz->dir = remover(raiz->dir, temp->chave);
    }
    if(raiz == NULL)
        return raiz;

    // Atualiza o fator de balanceamento do nó atual
    raiz->bal = obterBalanceamento(raiz);
    int balanco = raiz->bal;

    // Verifica se o nó fica desbalanceado e executa as rotações
    //Caso pesado à Direita (balanco > 1)
    if(balanco > 1 ) {
        // Caso Direita-Direita (RR)
        if(obterBalanceamento(raiz->dir) >= 0) {
            printf("Rotação Esquerda (RR) na remoção do nó %d\n", raiz->chave);
            return rotacaoEsquerda(raiz);
        }
        // Caso Direita-Esqurda (RL)
        else {
            printf("Rotação Direita (RL) na remoção do nó %d\n", raiz->chave);
            raiz->dir = rotacaoDireita(raiz->dir);
            return rotacaoEsquerda(raiz);
        }
    }

    if (balanco < -1) {
        // Caso Esquerda-Esquerda (LL)
        if(obterBalanceamento(raiz->esq) <= 0) {
            printf("Rotação Direita (LL) na remoção do nó %d\n", raiz->chave);
            return rotacaoDireita(raiz);
        }
        //Caso Esquerda-Direita (LR)
        else {
            printf("Rotação Esquerda-Direita (LR) na remoção do nó %d\n", raiz->chave);
            raiz->esq = rotacaoEsquerda(raiz->dir);
            return rotacaoDireita(raiz);
        }
    }

    return raiz;
}

// encontrar o menor elemento da arvore - 3
int32_t encontrarMenor(s_no* raiz) {
    s_no* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual->chave;
}

// encontrar o maior elemento da arvore - 4
int32_t encontrarMaior(s_no* raiz) {
    s_no* atual = raiz;
    while(atual && atual->dir != NULL)
        atual = atual->dir;
    return atual->chave;
}

// percurso em pre ordem
void preOrdem(s_no* raiz, FILE* arquivo) {
    if (raiz != NULL) {
        fwrite(&(raiz), sizeof(s_arq_no), 1, arquivo);
        preOrdem(raiz->esq, arquivo);
        preOrdem(raiz->dir, arquivo);
    }
}

// percurso em ordem
void ordem_simetrica(s_no* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        ordem_simetrica(raiz->esq, arquivo);
        fwrite(&(raiz), sizeof(s_arq_no), 1, arquivo);
        ordem_simetrica(raiz->dir, arquivo);
    }
}

// percurso em pós ordem
void posOrdem(s_no* raiz, FILE* arquivo) {
    if(raiz != NULL) {
        posOrdem(raiz->esq, arquivo);
        posOrdem(raiz->dir, arquivo);
        fwrite(&(raiz), sizeof(s_arq_no), 1, arquivo);
    }
}

// salva a arvore em pré ordem com arquivo
void salvarArvPreOrdem(s_no* raiz, FILE* arquivo) {
    if (raiz == NULL) {
        int marcador = -1;
        fwrite(&marcador, sizeof(int), 1, arquivo);
        return;
    }
    fwrite(&raiz, sizeof(int), 1, arquivo);
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
    printf("%d ", raiz->chave);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
}

// operação para imprimir em ordem e mostrar o usuário
void imprimirEmOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    imprimirEmOrdem(raiz->dir);
}

// cansei, op. bla bla bla, imprimi em pós ordem ao usuário.
void imprimirPosOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d ", raiz->chave);
}
