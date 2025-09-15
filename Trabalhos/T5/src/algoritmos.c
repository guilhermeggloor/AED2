#include "algoritmos.h"
#include <stdlib.h> 
#include <time.h>

// Função para trocar dois elementos
void swap(int32_t* a, int32_t* b) {
    int32_t t = *a;
    *a = *b;
    *b = t;
}

// Particionamento de Lomuto:
// Pega o último elemento como pivô, coloca o pivô em sua posição correta
// no vetor ordenado, e coloca todos os menores à esquerda do pivô
// e todos os maiores à direita.
int partition_lomuto(int32_t* arr, int low, int high) {
    int32_t pivot = arr[high]; // Pivô é o último elemento
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] < pivot) {
            i++; // Incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


// implementação do bubble sort original
void bubble_sort(int32_t* array, int size) { 
    if(size < 2) {
        return;
    }

    //O laço externo controla qauntas vezes vamos percorrer o vetor
    // Após 'i' passagem, os 'i' maiores elementos já estão em suas posições finais
    for (int i = 0; i < size - 1; i++) {

        // O laço interno realiza as comparações/trocas e ele vai até 'size - i - 1'
        for (int j = 0; j < size - i - 1; j++) {

            //se o elemento atual for maior que o próximo ? troca
            if (array[j] > array[j+1]) {
                int32_t temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

// Implementação do bubble sort melhorado
void bubble_sort_improved(int32_t* array, int size) { 
    if(size < 2) {
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        // 'swapped' funciona como uma flag
        int swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                int32_t temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

                //Se a troca ocorre ? atualiza a flag em 1
                swapped = 1;
            }
        }

        // se no final do laço interno nenhuma troca ocorre, o vetor ta ordenado
        if (swapped == 0) {
            break;
        }
    }
 }

void insertion_sort(int32_t* array, int size) { 
    if (size < 2) {
        return;
    }

    for (int i = 1; i < size; i++) {
        int32_t key = array[i]; //chave inserida
        int j = i-1;

        // move elementos do subarray que são maiores que a chave para uma posição a frente de sua posição atual
        while (j >= 0 && array[j] > key) {
            array[j+1] = array[j];
            j = j -1;
        }
        //insere a chave na posição correta
        array[j + 1] = key;
    }
}

// --- Funções Auxiliares para o Merge Sort ---
void merge(int32_t* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int32_t* L = (int32_t*)malloc(n1 * sizeof(int32_t));
    int32_t* R = (int32_t*)malloc(n2 * sizeof(int32_t));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_recursive(int32_t* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m);
        merge_sort_recursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Implementação da chamada de Merge Sort
void merge_sort(int32_t* array, int size) {
    if (size < 2) return;
    merge_sort_recursive(array, 0, size - 1);
}

// algoritmo recursivo de quick sort ultimo
void quick_sort_last_recursive(int32_t* arr, int low, int high) {
    if (low < high) {
        // pi é o índice de particionamento, arr[pi] está agora no lugar certo.
        int pi = partition_lomuto(arr, low, high);

        // Ordena recursivamente os elementos antes e depois da partição
        quick_sort_last_recursive(arr, low, pi - 1);
        quick_sort_last_recursive(arr, pi + 1, high);
    }
}

// Função de chamada do quick sort de ultimo elemento
void quick_sort_last(int32_t* array, int size) {
    if (size < 2) return;
    quick_sort_last_recursive(array, 0, size - 1);
}

// Algoritmo recursivo do quick sort randomico
void quick_sort_random_recursive(int32_t* arr, int low, int high) {
    if (low < high) {
        // Escolhe um pivô aleatório e o move para o final
        int random_pivot_index = low + rand() % (high - low + 1);
        swap(&arr[random_pivot_index], &arr[high]);

        // Particiona usando o pivô que agora está no final
        int pi = partition_lomuto(arr, low, high);
        
        quick_sort_random_recursive(arr, low, pi - 1);
        quick_sort_random_recursive(arr, pi + 1, high);
    }
}

// Função de chamada do quick sort randomico
void quick_sort_random(int32_t* array, int size) {
    if (size < 2) return;
    // Semeia o gerador de números aleatórios UMA VEZ.
    srand(time(NULL)); 
    quick_sort_random_recursive(array, 0, size - 1);
}

// Algoritmo de mediana 3 recursivo do quick sort
void quick_sort_median3_recursive(int32_t* arr, int low, int high) {
    if (low < high) {
        // Lógica da mediana de três
        int mid = low + (high - low) / 2;
        // Coloca o mediano entre arr[low], arr[mid], arr[high] na posição 'high'
        if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
        if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
        if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
        // Agora, arr[mid] é o mediano dos três.
        // O particionamento de Lomuto espera o pivô em 'high'.
        swap(&arr[mid], &arr[high]);

        int pi = partition_lomuto(arr, low, high);

        quick_sort_median3_recursive(arr, low, pi - 1);
        quick_sort_median3_recursive(arr, pi + 1, high);
    }
}

// Função de chamada do quick sort de mediana 3 
void quick_sort_median3(int32_t* array, int size) {
    if (size < 2) return;
    quick_sort_median3_recursive(array, 0, size - 1);
}


// Função auxiliar para transformar um subvetor com raiz em 'i' em um max-heap.
// 'n' é o tamanho do heap.
void heapify(int32_t* arr, int n, int i) {
    int largest = i;       // Inicializa o maior como a raiz
    int left = 2 * i + 1;  // Filho da esquerda
    int right = 2 * i + 2; // Filho da direita

    // Se o filho da esquerda é maior que a raiz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Se o filho da direita é maior que o maior até agora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Se o maior não é a raiz
    if (largest != i) {
        swap(&arr[i], &arr[largest]); // Troca a raiz com o maior

        // Chama heapify recursivamente na subárvore afetada
        heapify(arr, n, largest);
    }
}

// Função principal e de chamada do Heapsort
void heap_sort(int32_t* array, int size) {
    if (size < 2) {
        return;
    }

    // Constrói o max-heap (reorganizando o vetor)
    // Começa da metade do vetor e vai até o início, garantindo que cada subárvore seja um max-heap.
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }

    // Extrai um por um os elementos do heap
    for (int i = size - 1; i > 0; i--) {
        // Move a raiz atual (maior elemento) para o final
        swap(&array[0], &array[i]);

        // Chama heapify na heap reduzida para obter o próximo maior elemento na raiz
        heapify(array, i, 0);
    }
}