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
    novo->bal = 0;
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

// SUBSTITUA SUA FUNÇÃO rotacaoDireita POR ESTA
s_no* rotacaoDireita(s_no* y) {
    printf("\n--- INICIANDO ROTACAO DIREITA no no [Chave: %d, Endereco: %p] ---\n", y->chave, (void*)y);

    s_no* x = y->esq;
    printf("  -> Filho esquerdo (novo pivo 'x') e [Chave: %d, Endereco: %p]\n", x->chave, (void*)x);

    s_no* T2 = x->dir;
    if (T2 != NULL) {
        printf("  -> Subarvore T2 (filho direito de 'x') e [Chave: %d, Endereco: %p]\n", T2->chave, (void*)T2);
    } else {
        printf("  -> Subarvore T2 (filho direito de 'x') e [NULL]\n");
    }

    // Realiza a rotação
    printf("  -> ETAPA 1: x->dir = y (pivo aponta para antiga raiz)\n");
    x->dir = y;
    printf("  -> ETAPA 2: y->esq = T2 (antiga raiz adota T2)\n");
    y->esq = T2;

    // Atualiza os fatores de balanceamento
    printf("  -> Atualizando balanceamento de 'y' (antiga raiz)...\n");
    y->bal = obterBalanceamento(y);
    printf("  -> Atualizando balanceamento de 'x' (nova raiz)...\n");
    x->bal = obterBalanceamento(x);

    printf("--- ROTACAO DIREITA CONCLUIDA. Nova raiz da subarvore e [Chave: %d, Endereco: %p] ---\n\n", x->chave, (void*)x);
    return x;
}

// SUBSTITUA SUA FUNÇÃO rotacaoEsquerda POR ESTA
s_no* rotacaoEsquerda(s_no* x) {
    printf("\n--- INICIANDO ROTACAO ESQUERDA no no [Chave: %d, Endereco: %p] ---\n", x->chave, (void*)x);

    s_no* y = x->dir;
    printf("  -> Filho direito (novo pivo 'y') e [Chave: %d, Endereco: %p]\n", y->chave, (void*)y);

    s_no* T2 = y->esq;
    if (T2 != NULL) {
        printf("  -> Subarvore T2 (filho esquerdo de 'y') e [Chave: %d, Endereco: %p]\n", T2->chave, (void*)T2);
    } else {
        printf("  -> Subarvore T2 (filho esquerdo de 'y') e [NULL]\n");
    }

    // Realiza a rotação
    printf("  -> ETAPA 1: y->esq = x (pivo aponta para antiga raiz)\n");
    y->esq = x;
    printf("  -> ETAPA 2: x->dir = T2 (antiga raiz adota T2)\n");
    x->dir = T2;

    // Atualiza os fatores de balanceamento
    printf("  -> Atualizando balanceamento de 'x' (antiga raiz)...\n");
    x->bal = obterBalanceamento(x);
    printf("  -> Atualizando balanceamento de 'y' (nova raiz)...\n");
    y->bal = obterBalanceamento(y);

    printf("--- ROTACAO ESQUERDA CONCLUIDA. Nova raiz da subarvore e [Chave: %d, Endereco: %p] ---\n\n", y->chave, (void*)y);
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
    if (balanco < -1) {
        if(obterBalanceamento(no->esq) <= 0) {
            printf("Rotação Direita (LL) em torno do novo nó %d\n", no->chave);
            return rotacaoDireita(no);
        }
        else {
            printf("Rotação Esquerda-Direita (LR) em torno do novo nó %d\n", no->chave);
            no->esq = rotacaoEsquerda(no->esq);
            return rotacaoDireita(no);
        }
    }

    if (balanco > -1) {
        if(obterBalanceamento(no->dir) >= 0) {
            printf("Rotação Esquerda (RR) em torno do novo nó %d\n", no->chave);
            return rotacaoEsquerda(no);
        }
        else {
            printf("Rotação Direita-Esquerda (RL) em torno do novo nó %d\n", no->chave);
            no->dir = rotacaoDireita(no->dir);
            return rotacaoEsquerda(no);
        }
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
            raiz->esq = rotacaoEsquerda(raiz->esq);
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
    if(raiz == NULL) {
        return;
    }

    s_arq_no no_para_arquivo;
    no_para_arquivo.chave = raiz->chave;
    no_para_arquivo.bal = raiz->bal;
    // Define as flags de existência dos filhos
    no_para_arquivo.esq = (raiz->esq != NULL);
    no_para_arquivo.dir = (raiz->dir != NULL);

    // Grava a struct formatada no arquivo
    fwrite(&no_para_arquivo, sizeof(s_arq_no), 1, arquivo);

    // Recorre para os filhos (que só serão gravados se existirem
    salvarArvPreOrdem(raiz->esq, arquivo);
    salvarArvPreOrdem(raiz->dir, arquivo);
}

// Carrega a arvore em pré ordem com operação de arquivo
s_no* carregarArvPreOrdem(FILE* arquivo) {
    s_arq_no no_do_arquivo;

    if(fread(&no_do_arquivo, sizeof(s_arq_no), 1, arquivo) != 1) {
        return NULL;
    }

    // Cria um nó em memória com os dados lidos
    s_no* no_na_memoria = novoNo(no_do_arquivo.chave);
    no_na_memoria->bal = no_do_arquivo.bal;
    no_na_memoria->esq = NULL; // Garante que começam como NULL
    no_na_memoria->dir = NULL;

    // Se a flag 'esq' estava ligada, reconstrói a subárvore esquerda
    if (no_do_arquivo.esq) {
        no_na_memoria->esq = carregarArvPreOrdem(arquivo);
    }

    //Se a flag 'dir' estava ligada, reconstrói a subárvore direita
    if(no_do_arquivo.dir) {
        no_na_memoria->dir = carregarArvPreOrdem(arquivo);
    }

    return no_na_memoria;
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
    printf("%d(bal: %d)", raiz->chave, raiz->bal);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
}

// operação para imprimir em ordem e mostrar o usuário
void imprimirEmOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq);
    printf("%d(bal: %d) ", raiz->chave, raiz->bal);
    imprimirEmOrdem(raiz->dir);
}

// cansei, op. bla bla bla, imprimi em pós ordem ao usuário.
void imprimirPosOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d(bal: %d)", raiz->chave, raiz-> bal);
}
