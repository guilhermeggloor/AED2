#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stdint.h>

// 1 - Bubble-sort original
void bubble_sort(int32_t* array, int size);

// 2 - Bubble-sort melhorado
void bubble_sort_improved(int32_t* array, int size);

// 3 - Insertion-sort
void insertion_sort(int32_t* array, int size);

// 4 - Mergesort
void merge_sort(int32_t* array, int size);

// 5 - Quicksort (pivô: último elemento)
void quick_sort_last(int32_t* array, int size);

// 6 - Quicksort (pivô: aleatório)
void quick_sort_random(int32_t* array, int size);

// 7 - Quicksort (pivô: mediana de três)
void quick_sort_median3(int32_t* array, int size);

// 8 - Heapsort
void heap_sort(int32_t* array, int size);

#endif // ALGORITMOS_H