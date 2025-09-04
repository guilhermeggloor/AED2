#include "algoritmos.h"
#include <stdlib.h> 

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

// Implemntação da função de chamada do merge sort 
void merge_sort(int32_t* array, int size) { 

}
void quick_sort_last(int32_t* array, int size) { /* TODO */ }
void quick_sort_random(int32_t* array, int size) { /* TODO */ }
void quick_sort_median3(int32_t* array, int size) { /* TODO */ }
void heap_sort(int32_t* array, int size) { /* TODO */ }