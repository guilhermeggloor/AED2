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

// busca do elemento correspondente
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

// ATENÇÃO: A assinatura e o retorno destas funções MUDARAM.
// Elas agora são 'void' e recebem um ponteiro para ponteiro.

// Rotação simples à direita (caso1)
void rotacaoDireita(s_no** pt) {
    s_no* y = *pt;
    s_no* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    *pt = x; // A nova raiz da subárvore agora é x
}

// Rotação simples à esquerda (caso2)
void rotacaoEsquerda(s_no** pt) {
    s_no* x = *pt;
    s_no* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    *pt = y; // A nova raiz da subárvore agora é y
}

// Rebalanceamento quando a subárvore esquerda fica muito alta
void caso1(s_no** pt, int* h) {
    printf("Rebalanceamento (Esquerda) no no %d\n", (*pt)->chave);
    s_no* ptu = (*pt)->esq;

    // Caso 1.1: Rotação Simples à Direita (LL)
    if (ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    }
    // Caso 1.2: Rotação Dupla Esquerda-Direita (LR)
    else {
        s_no* ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;

        // Ajusta os balances com base no pivo da rotação dupla
        if (ptv->bal == -1) (*pt)->bal = 1;
        else (*pt)->bal = 0;
        if (ptv->bal == 1) ptu->bal = -1;
        else ptu->bal = 0;

        *pt = ptv;
    }

    (*pt)->bal = 0;
    *h = 0; // A altura foi normalizada
}

// Rebalanceamento quando a subárvore direita fica muito alta
void caso2(s_no** pt, int* h) {
    printf("Rebalanceamento (Direita) no no %d\n", (*pt)->chave);
    s_no* ptu = (*pt)->dir;

    // Caso 2.1: Rotação Simples à Esquerda (RR)
    if (ptu->bal == 1) {
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    }
    // Caso 2.2: Rotação Dupla Direita-Esquerda (RL)
    else {
        s_no* ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;

        // Ajusta os balances com base no pivo da rotação dupla
        if (ptv->bal == 1) (*pt)->bal = -1;
        else (*pt)->bal = 0;
        if (ptv->bal == -1) ptu->bal = 1;
        else ptu->bal = 0;

        *pt = ptv;
    }

    (*pt)->bal = 0;
    *h = 0; // A altura foi normalizada
}
void inserir_recursivo(s_no** pt, int32_t chave, int* h) {
    // Se o nó é nulo, chegamos ao ponto de inserção
    if (*pt == NULL) {
        *pt = novoNo(chave);
        *h = 1; // Avisa para a chamada anterior que a altura cresceu
        return;
    }

    // Se a chave já existe, retorne.
    if (chave == (*pt)->chave) {
        printf("Chave %d já existe na árvore.\n", chave);
        *h = 0;
        return;
    }

    // Navega para a subárvore correta
    if (chave < (*pt)->chave) {
        inserir_recursivo(&(*pt)->esq, chave, h);
        // Na volta da recursão, se a altura da subárvore esquerda cresce ? 
        if (*h) {
            switch ((*pt)->bal) {
                case 1: // Estava pesado à direita, fica balanceado
                    (*pt)->bal = 0;
                    *h = 0;
                    break;
                case 0: // balanceado, agora fica  à esquerda
                    (*pt)->bal = -1;
                    *h = 1;
                    break;
                case -1: // pesado à esquerda, precisa rebalancear
                    caso1(pt, h);
                    break;
            }
        }
    } else {
        inserir_recursivo(&(*pt)->dir, chave, h);
        // Na volta da recursão, se a altura da subárvore direita cresceu...
        if (*h) {
            switch ((*pt)->bal) {
                case -1: // Estava pesado à esquerda, agora fica balanceado
                    (*pt)->bal = 0;
                    *h = 0;
                    break;
                case 0: // Estava balanceado, agora fica pesado à direita
                    (*pt)->bal = 1;
                    *h = 1;
                    break;
                case 1: // Estava pesado à direita, agora precisa rebalancear
                    caso2(pt, h);
                    break;
            }
        }
    }
}
// função de chamada
s_no* inserir(s_no* raiz, int32_t chave) {
    int h = 0; // Começa com a flag de altura 'falsa'
    inserir_recursivo(&raiz, chave, &h);
    return raiz; // Retorna a raiz (que pode ter mudado)
}

// função recursiva principal para a remoção
void remover_recursivo(s_no** pt, int32_t chave, int* h) {
    // Se o nó não for encontrado
    if (*pt == NULL) {
        printf("Chave %d não encontrada para remoção.\n", chave);
        *h = 0;
        return; //termina
    }

    //PROCURA PELO NÓ
    if (chave < (*pt)->chave) {
        remover_recursivo(&(*pt)->esq, chave, h);
        // Na volta da recursão, se a subárvore esquerda encolheu...
        if (*h) {
            // Lógica de rebalanceamento para o "crescimento" relativo da direita
            switch ((*pt)->bal) {
                case -1: (*pt)->bal = 0; *h = 1; break;
                case 0:  (*pt)->bal = 1; *h = 0; break;
                case 1:  caso2(pt, h); break; // Rebalanceia o lado direito
            }
        }
    } else if (chave > (*pt)->chave) {
        remover_recursivo(&(*pt)->dir, chave, h);
        // Na volta da recursão, se a subárvore direita encolheu...
        if (*h) {
            // Lógica de rebalanceamento para o "crescimento" relativo da esquerda
            switch ((*pt)->bal) {
                case 1:  (*pt)->bal = 0; *h = 1; break;
                case 0:  (*pt)->bal = -1; *h = 0; break;
                case -1: caso1(pt, h); break; // Rebalanceia o lado esquerdo
            }
        }
    }
    //NÓ ENCONTRADO - EXECUTA A REMOÇÃO
    else {
        s_no* aux = *pt;
        // Caso com 0 ou 1 filho (à direita)
        if (aux->esq == NULL) {
            *pt = aux->dir;
            *h = 1; // A árvore encolheu
            free(aux);
        }
        // Caso com 1 filho (à esquerda)
        else if (aux->dir == NULL) {
            *pt = aux->esq;
            *h = 1; // A árvore encolheu
            free(aux);
        }
        // Caso com 2 filhos
        else {
            // Encontra o sucessor (menor nó da subárvore direita)
            s_no* sucessor = aux->dir;
            while (sucessor->esq != NULL) {
                sucessor = sucessor->esq;
            }
            // Copia a chave do sucessor para o nó atual
            aux->chave = sucessor->chave;
            // Remove o nó sucessor da subárvore direita
            remover_recursivo(&aux->dir, sucessor->chave, h);
            // Na volta, se a subárvore direita encolheu, rebalanceia
            if (*h) {
                 switch ((*pt)->bal) {
                    case 1:  (*pt)->bal = 0; *h = 1; break;
                    case 0:  (*pt)->bal = -1; *h = 0; break;
                    case -1: caso1(pt, h); break;
                }
            }
        }
    }
}

// Função "wrapper" para ser chamada pelo main.c
s_no* remover(s_no* raiz, int32_t chave) {
    int h = 0; // Flag que indica se a altura da subárvore diminuiu
    remover_recursivo(&raiz, chave, &h);
    return raiz;
}

s_no* encontrarNoMenor(s_no* no) {
    s_no* atual = no;
    // Loop para encontrar a folha mais à esquerda
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
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

// imprimi em pós ordem ao usuário.
void imprimirPosOrdem(s_no* raiz) {
    if (raiz == NULL) return;
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf("%d(bal: %d)", raiz->chave, raiz-> bal);
}
