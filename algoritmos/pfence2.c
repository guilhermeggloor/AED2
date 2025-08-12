#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int value; // valor a ser ordenado
    int initPosition; // posição inicial no vetor desordenado
} Element;

#define SIZE_ARRAY 10

void swapElements(Element[], int, int);
int getRandomPivot(int, int);
int getMedianOfThreePivot(Element[], int, int, int);
void goDown(Element[], int, int);
void arrange(Element[], int);

void bubbleSortOriginal(Element[SIZE_ARRAY]);
void bubbleSortImproved(Element[SIZE_ARRAY]);
void insertionSort(Element[SIZE_ARRAY]);
void merge(Element[SIZE_ARRAY], Element[SIZE_ARRAY], int, int, int);
void mergeSort(Element[SIZE_ARRAY], Element[SIZE_ARRAY], int, int);
void quickSortLastElementPivot(Element[SIZE_ARRAY], int, int);
void quickSortRandomPivot(Element[SIZE_ARRAY], int, int);
void quickSortMedianOfThreePivot(Element[SIZE_ARRAY], int, int);
void heapSort(Element[SIZE_ARRAY]);

void printArray(Element[SIZE_ARRAY]);

int main(void) {
    /*
        Código para verificar na prática a estabilidade
        dos algoritmos implementados.

        O que observar?
            Neste exemplo, temos números iguais juntos:
                - 2 na posição 4
                - 2 na posição 5
            O algoritmo será estável se manter esses números
            nas mesmas posições após a ordenação.

        Exemplo:
            Índices:            [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            Antes da ordenação: [6, 1, 3, 7, 2, 2, 9, 4, 5, 0]

            Índices:            [9, 1, 5, 4, 2, 7, 8, 0, 3, 6] -> os '2's foram troccados
            Após a ordenação:   [0, 1, 2, 2, 3, 4, 5, 6, 7, 9]

            Se a posição dos dois '2's (originalmente nas posições 4 e 5)
            não mudar, o algoritmo é considerado estável.
    */

    Element list[SIZE_ARRAY] = {
        {6, 0},
        {1, 1},
        {3, 2},
        {7, 3},
        {2, 4},
        {2, 5},
        {9, 6},
        {4, 7},
        {5, 8},
        {0, 9}
    };

    Element tmpList[SIZE_ARRAY];

    printf("\nArray original: ");
    printArray(list);

    printf("\nBubble Sort Original: ");
    bubbleSortOriginal(list);
    printArray(list);

    printf("\nBubble Sort Melhorado: ");
    bubbleSortImproved(list);
    printArray(list);

    printf("\nInsertion Sort: ");
    insertionSort(list);
    printArray(list);

    printf("\nMergeSort: ");
    mergeSort(list, tmpList, 0, SIZE_ARRAY - 1);
    printArray(list);

    printf("\nQuickSort com pivo no ultimo elemento: ");
    quickSortLastElementPivot(list, 0, SIZE_ARRAY - 1);
    printArray(list);

    printf("\nQuickSort com pivo aleatorio: ");
    quickSortRandomPivot(list, 0, SIZE_ARRAY - 1);
    printArray(list);

    printf("\nQuickSort com Mediana de Tres: ");
    quickSortMedianOfThreePivot(list, 0, SIZE_ARRAY - 1);
    printArray(list);

    printf("\nHeapSort: ");
    heapSort(list);
    printArray(list);


    return 0;
}

void printArray(Element list[SIZE_ARRAY]) {
    // Imprime os índices iniciais
    printf("\nIndices Iniciais:  ");
    for (int i = 0; i < SIZE_ARRAY; ++i) {
        printf("%d  ", list[i].initPosition);
    }
    printf("\n");

    // Imprime os valores ordenados
    printf("Valores Ordenados: ");
    for (int i = 0; i < SIZE_ARRAY; ++i) {
        printf("%d  ", list[i].value);
    }
    printf("\n");
}


void swapElements(Element array[], int i, int j) {
    Element tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


void bubbleSortOriginal(Element list[SIZE_ARRAY]) {
    for (int i = 0; i < SIZE_ARRAY; ++i) {
        for (int j = 0; j < SIZE_ARRAY - 1; ++j) {
            if (list[j].value > list[j + 1].value) {
                swapElements(list, j, j + 1);
            }
        }
    }
}


void bubbleSortImproved(Element list[SIZE_ARRAY]) {
    int changed = 1;
    int finish = SIZE_ARRAY - 1;
    int lastIndexChanged = SIZE_ARRAY;

    while (changed) {
        int j = 0;
        changed = 0;

        while (j < finish) {
            if (list[j].value > list[j + 1].value) {
                swapElements(list, j, j + 1);
                changed = 1;
                lastIndexChanged = j;
            }
            j++;
        }
        finish = lastIndexChanged;
    }
}


void insertionSort(Element list[SIZE_ARRAY]) {
    for (int i = 1; i < SIZE_ARRAY; ++i) {
        Element value = list[i];
        int j = i - 1;

        while (j >= 0 && value.value < list[j].value) {
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = value;
    }
}


void merge(Element list[SIZE_ARRAY], Element lTmp[SIZE_ARRAY], int init1, int init2, int end2) {
    int saveInit1 = init1;
    int end1 = init2 - 1;
    int nro = 0;
    int ind = init1;

    while (init1 <= end1 && init2 <= end2) {
        if (list[init1].value < list[init2].value) {
            lTmp[ind++] = list[init1++];
        } else {
            lTmp[ind++] = list[init2++];
        }
        nro++;
    }

    while (init1 <= end1) {
        lTmp[ind++] = list[init1++];
        nro++;
    }

    while (init2 <= end2) {
        lTmp[ind++] = list[init2++];
        nro++;
    }

    for (int i = 0; i < nro; ++i) {
        list[i + saveInit1] = lTmp[i + saveInit1];
    }
}


void mergeSort(Element list[SIZE_ARRAY], Element lTmp[SIZE_ARRAY], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        mergeSort(list, lTmp, left, middle);
        mergeSort(list, lTmp, middle + 1, right);
        merge(list, lTmp, left, middle + 1, right);
    }
}


void quickSortLastElementPivot(Element list[SIZE_ARRAY], int init, int end) {
    if (end - init < 2) {
        if (end - init == 1) {
            if (list[init].value > list[end].value) {
                swapElements(list, init, end);
            }
        }
    } else {
        Element pivot = list[end];
        int i = init;
        int j = end - 1;

        while (j >= i) {
            while (list[i].value < pivot.value) {
                i++;
            }
            while (list[j].value > pivot.value && j >= 0) {
                j--;
            }
            if (j >= i) {
                swapElements(list, i, j);
                i++;
                j--;
            }
        }
        swapElements(list, i, end);
        quickSortLastElementPivot(list, init, i - 1);
        quickSortLastElementPivot(list, i + 1, end);
    }
}

int getRandomPivot(int init, int end) {
    srand(time(NULL));
    return init + rand() % (end - init) + 1;
}

void quickSortRandomPivot(Element list[SIZE_ARRAY], int init, int end) {
    if (end - init < 2) {
        if (end - init == 1) {
            if (list[init].value > list[end].value) {
                swapElements(list, init, end);
            }
        }
    } else {
        int random = getRandomPivot(init, end);
        swapElements(list, random, end);

        int i = init;
        int j = end - 1;
        Element pivot = list[end];

        while (j >= i) {
            while (list[i].value < pivot.value) {
                i++;
            }
            while (list[j].value > pivot.value && j >= 0) {
                j--;
            }
            if (j >= i) {
                swapElements(list, i, j);
                i++;
                j--;
            }
        }
        swapElements(list, i, end);
        quickSortRandomPivot(list, init, i - 1);
        quickSortRandomPivot(list, i + 1, end);
    }
}

int getMedianOfThreePivot(Element list[], int init, int middle, int end) {
    if (list[init].value > list[middle].value ^ list[init].value > list[end].value) {
        return init;
    }
    if (list[middle].value < list[init].value ^ list[middle].value < list[end].value) {
        return middle;
    }
    return end;
}

void quickSortMedianOfThreePivot(Element list[SIZE_ARRAY], int init, int end) {
    if (end - init < 2) {
        if (end - init == 1) {
            if (list[init].value > list[end].value) {
                swapElements(list, init, end);
            }
        }
    } else {
        int median = getMedianOfThreePivot(list, init, (init + end) / 2, end);
        swapElements(list, median, end);

        Element pivot = list[end];
        int i = init;
        int j = end - 1;

        while (j >= i) {
            while (list[i].value < pivot.value && i < j) {
                i++;
            }
            while (list[j].value > pivot.value && j >= 0) {
                j--;
            }
            if (j >= i) {
                swapElements(list, i, j);
                i++;
                j--;
            }
        }

        swapElements(list, i, end);

        quickSortMedianOfThreePivot(list, init, i - 1);
        quickSortMedianOfThreePivot(list, i + 1, end);
    }
}

void goDown(Element list[], int i, int n) {
    int j = 2 * i;

    if (j <= n) {
        if (j < n) {
            if (list[j + 1].value > list[j].value) {
                j++;
            }
        }
        if (list[i].value < list[j].value) {
            swapElements(list, j, i);
            goDown(list, j, n);
        }
    }
}

void arrange(Element list[], int n) {
    for (int i = n / 2; i >= 0; --i) {
        goDown(list, i, n);
    }
}

void heapSort(Element list[SIZE_ARRAY]) {
    arrange(list, SIZE_ARRAY - 1);
    int m = SIZE_ARRAY - 1;

    while (m > 0) {
        swapElements(list, 0, m);
        m--;
        goDown(list, 0, m);
    }
}

// Autor: Henrique Gettner De Oliveira
