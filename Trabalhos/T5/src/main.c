#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "algoritmos.h"

// Função para calcular o tempo decorrido
double get_time_diff(struct timespec* start, struct timespec* end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e9;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <num_algoritmo> <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    int algo_choice = atoi(argv[1]);
    char* input_filename = argv[2];
    char* output_filename = argv[3];

    // --- Leitura do Arquivo de Entrada ---
    FILE* fp_in = fopen(input_filename, "rb");
    if (!fp_in) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    // Calcula o número de elementos usando o tamanho do arquivo
    struct stat st;
    stat(input_filename, &st);
    long file_size = st.st_size;
    int num_elements = file_size / sizeof(int32_t);

    if (num_elements <= 0) {
        fprintf(stderr, "Arquivo de entrada vazio ou inválido.\n");
        fclose(fp_in);
        return 1;
    }

    int32_t* data = (int32_t*)malloc(file_size);
    if (!data) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(fp_in);
        return 1;
    }

    fread(data, sizeof(int32_t), num_elements, fp_in);
    fclose(fp_in);

    // --- Seleção e Execução do Algoritmo com Medição de Tempo ---
    struct timespec start, end;
    
    // Usar CLOCK_MONOTONIC garante que o tempo medido não seja afetado por mudanças no relógio do sistema
    clock_gettime(CLOCK_MONOTONIC, &start);

    switch (algo_choice) {
        case 1: bubble_sort(data, num_elements); break;
        case 2: bubble_sort_improved(data, num_elements); break;
        case 3: insertion_sort(data, num_elements); break;
        case 4: merge_sort(data, num_elements); break;
        case 5: quick_sort_last(data, num_elements); break;
        case 6: quick_sort_random(data, num_elements); break;
        case 7: quick_sort_median3(data, num_elements); break;
        case 8: heap_sort(data, num_elements); break;
        default:
            fprintf(stderr, "Número de algoritmo inválido: %d. Escolha de 1 a 8.\n", algo_choice);
            free(data);
            return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_spent = get_time_diff(&start, &end);
    printf("%.3f\n", time_spent);

    // --- Escrita no Arquivo de Saída ---
    FILE* fp_out = fopen(output_filename, "wb");
    if (!fp_out) {
        perror("Erro ao abrir arquivo de saída");
        free(data);
        return 1;
    }

    fwrite(data, sizeof(int32_t), num_elements, fp_out);
    fclose(fp_out);

    // --- Limpeza ---
    free(data);

    return 0;
}