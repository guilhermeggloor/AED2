#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <time.h>

int32_t* ler_arquivo(const char* nome_arquivo, size_t* tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat(nome_arquivo, &st) != 0) {
        perror("Erro ao obter informações do arquivo");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    *tamanho = st.st_size / sizeof(int32_t);
    int32_t* vetor = malloc(st.st_size);
    if (!vetor) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    fread(vetor, sizeof(int32_t), *tamanho, arquivo);
    fclose(arquivo);
    return vetor;
}

void escrever_arquivo(const char* nome_arquivo, int32_t* vetor, size_t tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    fwrite(vetor, sizeof(int32_t), tamanho, arquivo);
    fclose(arquivo);
}

double calcular_tempo(void (*funcao_sort)(int32_t*, size_t), int32_t* vetor, size_t tamanho) {
    clock_t inicio = clock();

    // Chama a função de ordenação passada
    funcao_sort(vetor, tamanho);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return tempo;
}

void bubble_sort(int32_t* vetor, size_t tamanho) {
    for (size_t i = 0; i < tamanho - 1; i++) {
        for (size_t j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int32_t temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_melhorado(int32_t* vetor, size_t tamanho) {
    int trocou;
    for (size_t i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (size_t j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int32_t temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;  // Se não houve troca, o vetor já está ordenado
    }
}

void insertion_sort(int32_t* vetor, size_t tamanho) {
    for (size_t i = 1; i < tamanho; i++) {
        int32_t chave = vetor[i];
        size_t j = i - 1;
        while (j < tamanho && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

void merge(int32_t* vetor, size_t inicio, size_t meio, size_t fim) {
    size_t n1 = meio - inicio + 1;
    size_t n2 = fim - meio;
    int32_t* L = malloc(n1 * sizeof(int32_t));
    int32_t* R = malloc(n2 * sizeof(int32_t));

    for (size_t i = 0; i < n1; i++) L[i] = vetor[inicio + i];
    for (size_t j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];

    size_t i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k++] = L[i++];
        } else {
            vetor[k++] = R[j++];
        }
    }

    while (i < n1) vetor[k++] = L[i++];
    while (j < n2) vetor[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int32_t* vetor, size_t inicio, size_t fim) {
    if (inicio < fim) {
        size_t meio = inicio + (fim - inicio) / 2;
        merge_sort(vetor, inicio, meio);
        merge_sort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void quicksort(int32_t* vetor, size_t baixo, size_t alto) {
    if (baixo < alto) {
        size_t pivo = particionar(vetor, baixo, alto);
        quicksort(vetor, baixo, pivo - 1);
        quicksort(vetor, pivo + 1, alto);
    }
}

size_t particionar(int32_t* vetor, size_t baixo, size_t alto) {
    int32_t pivo = vetor[alto];
    size_t i = baixo - 1;
    for (size_t j = baixo; j < alto; j++) {
        if (vetor[j] <= pivo) {
            i++;
            int32_t temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    int32_t temp = vetor[i + 1];
    vetor[i + 1] = vetor[alto];
    vetor[alto] = temp;
    return i + 1;
}

size_t particionar_aleatorio(int32_t* vetor, size_t baixo, size_t alto) {
    size_t pivo_aleatorio = baixo + rand() % (alto - baixo);
    int32_t temp = vetor[pivo_aleatorio];
    vetor[pivo_aleatorio] = vetor[alto];
    vetor[alto] = temp;
    return particionar(vetor, baixo, alto);
}

void quicksort_aleatorio(int32_t* vetor, size_t baixo, size_t alto) {
    if (baixo < alto) {
        size_t pivo = particionar_aleatorio(vetor, baixo, alto);
        quicksort_aleatorio(vetor, baixo, pivo - 1);
        quicksort_aleatorio(vetor, pivo + 1, alto);
    }
}

void heapify(int32_t* vetor, size_t n, size_t i) {
    size_t maior = i;
    size_t esquerda = 2 * i + 1;
    size_t direita = 2 * i + 2;

    if (esquerda < n && vetor[esquerda] > vetor[maior])
        maior = esquerda;

    if (direita < n && vetor[direita] > vetor[maior])
        maior = direita;

    if (maior != i) {
        int32_t temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        heapify(vetor, n, maior);
    }
}

void heap_sort(int32_t* vetor, size_t n) {
    for (size_t i = n / 2 - 1; i != (size_t)-1; i--)
        heapify(vetor, n, i);

    for (size_t i = n - 1; i != 0; i--) {
        int32_t temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        heapify(vetor, i, 0);
    }
}

int mediana_de_tres(int32_t* vetor, int esq, int dir) {
    int meio = (esq + dir) / 2;

    if (vetor[esq] > vetor[meio])
        swap(&vetor[esq], &vetor[meio]);

    if (vetor[esq] > vetor[dir])
        swap(&vetor[esq], &vetor[dir]);

    if (vetor[meio] > vetor[dir])
        swap(&vetor[meio], &vetor[dir]);

    return meio;
}

void quicksort_mediana_tres(int32_t* vetor, int esq, int dir) {
    if (esq < dir) {
        int pivo = mediana_de_tres(vetor, esq, dir);
        swap(&vetor[pivo], &vetor[dir]);  // Mover pivô para o fim
        int q = particiona(vetor, esq, dir);  // Função de partição
        quicksort_mediana_tres(vetor, esq, q - 1);
        quicksort_mediana_tres(vetor, q + 1, dir);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <algoritmo> <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int algoritmo = atoi(argv[1]);
    const char* arquivo_entrada = argv[2];
    const char* arquivo_saida = argv[3];

    size_t tamanho;
    int32_t* vetor = ler_arquivo(arquivo_entrada, &tamanho);

    double tempo = 0.0;
    
    switch (algoritmo) {
        case 1:
            tempo = calcular_tempo(bubble_sort, vetor, tamanho);
            break;
        case 2:
            tempo = calcular_tempo(bubble_sort_melhorado, vetor, tamanho);
            break;
        case 3:
            tempo = calcular_tempo(insertion_sort, vetor, tamanho);
            break;
        case 4:
            tempo = calcular_tempo(merge_sort, vetor, tamanho);
            break;
        case 5:
            tempo = calcular_tempo(quicksort, vetor, tamanho);
            break;
        case 6:
            tempo = calcular_tempo(quicksort_aleatorio, vetor, tamanho);
            break;
        case 7:
            tempo = calcular_tempo(quicksort_mediana_tres, vetor, tamanho);
            break;
        case 8:
            tempo = calcular_tempo(heap_sort, vetor, tamanho);
            break;
        default:
            fprintf(stderr, "Algoritmo inválido\n");
            free(vetor);
            return EXIT_FAILURE;
    }

    printf("Tempo de execução: %.3f segundos\n", tempo);
    escrever_arquivo(arquivo_saida, vetor, tamanho);

    free(vetor);
    return EXIT_SUCCESS;

    return 0;
}