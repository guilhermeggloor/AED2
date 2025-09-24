projeto_ordenacao/
├── Makefile            # Automatiza a compilação, geração de testes e limpeza
├── README.md           # Este arquivo
├── gera_in_out.c       # Código fonte do gerador de arquivos de teste
│
├── src/                # Diretório para o código fonte do programa principal
│   ├── main.c          # Lógica principal, I/O, medição de tempo
│   ├── algoritmos.c    # Implementação dos 8 algoritmos de ordenação
│   └── algoritmos.h    # Protótipos das funções de ordenação
│
├── bin/                # Diretório para os executáveis compilados
│   ├── ordenador       # O programa de ordenação
│   └── gerador         # O programa gerador de testes
│
└── data/               # Diretório para os arquivos de teste
    ├── in/             # Arquivos de entrada gerados
    └── out/            # Arquivos de saída de referência (gabarito)

## Algoritmos implementados

O programa permite escolher entre os seguintes algoritmos através de um número na linha de comando: 

1 - *Bubble Sort(Original):* Versão clássica com complexidade O(n^2).
2 - *Bubble Sort(Melhorado):* Versão com otimização para parar caso o vetor já esteja ordenado. Melhor caso O(n).
3 - *Insertion Sort:* Algoritmo eficiente para entradas pequenas ou "quase ordenadas". Complexidade O(n^2).
4 - *Merge Sort:* Algoritmo de "dividir para conquistar" com complexidade garantida de O(nlogn).
5 - *Quicksort (Pivô no Final):* Implementação clássica. Vulnerável ao pior caso O(n2) em entradas ordenadas.
6 - *Quicksort (Pivô Aleatório):* Otimização que torna o pior caso estatisticamente muito improvável.
7 - *Quicksort (Mediana de Três):* Otimização que escolhe o pivô com base no primeiro, meio e último elemento, evitando o pior caso.
8 - *Heapsort:* Utiliza a estrutura de dados Max-Heap. Complexidade garantida de O(nlogn).

## Guia de execução: 

Siga os passos abaixo para compilação


### Pré-requisitos: 

- Um Compilador C(gcc)
- A ferramenta make

### 1.Compilação

Para compilar o programa de ordenação (ordenador) e o gerador de testes (gerador), navegue até a pasta raiz do projeto e execute o comando:

- make

Isso criará os executáveis no diretório bin/.

Para limpar todos os arquivos compilados e os dados de teste gerados, use:

- make clean

### 2.Gerar arquivos de teste

O Makefile automatiza a criação dos arquivos de entrada e dos gabaritos correspondentes.

Para gerar os conjuntos de dados de 10, 100, 1.000, 10.000, 100.000, 500.000 e 5.000.000 de elementos:

- make generate_tests

Os arquivos serão criados nos formatos:

- .c (crescente)

- .d (decrescente)

- .a (aleatório)

O arquivo de 50 milhões de elementos ocupa um espaço considerável (~200MB) e pode demorar para ser gerado. Para criá-lo separadamente:

- make generate_50M

### 3.Executando o programa de ordenação

O programa ordenador recebe três argumentos da linha de comando:

- ./bin/ordenador <num_algoritmo> <arquivo_entrada> <arquivo_saida>

- <num_algoritmo>: um número de 1 a 8, correspondente ao algoritmo desejado (veja a lista acima)
- <arquivo_entrada>: O caminho para o arquivo binário a ser executado (ex: data/in/1000.a)
- <arquivo_saida>: O nome do arquivo onde o resultado ordenado será salvo

### Exemplo prático: 

Para ordenar o arquivo de 10.000 elementos aleatórios usando Merge Sort (algoritmo 4):

- ./bin/ordenador 4 data/in/1000.a data/out/resultado_mergesort.bin

O programa imprimirá no terminal o tempo de execução em segundos (com precisão de milissegundos) e criará o arquivo "resultado_mergesort.bin" em "data/out/."

### Verificando a Correção

O gerador de testes também cria um arquivo de gabarito para cada entrada (ex: para 1000.a, ele cria 1000.a.out). Você pode usar o comando cmp ou diff para comparar a sua saída do gabarito

- cmp data/out/resultado_mergesort.bin data/out/1000.a.out

Se o comando não produzir nenhuma saída, significa que os arquivos são identicos e a ordenação foi realizada com sucesso.

### 5. Exemplos de Testes de Performance

Para observar as características de cada algoritmo, experimente os seguintes testes:

#### Pior caso do Bubble Sort vs. Melhorado:
// Bubble sort 
- ./bin/ordenador 1 data/in/10000.c data/out/res.bin

// Bubble sort melhorador em vetor já ordenador (será quase instantâneo)
- ./bin/ordenador 2 data/in/10000.c data/out/res.bin

#### Pior caso do quicksort (pivô no final) vs aleatório

//Quicksort clássico em vetor decrescente (será lento, O(n^2))
- ./bin/ordenador 5 data/in/100000.d data/out/res.bin

//Quicksort aleatório no mesmo vetor (será rápido)
- ./bin/ordenador 6 data/in/100000.d data/out/res.bin

#### Comparando O(n^2) vs O(nlogn):

//Insertion Sort em 100.000 elementos aleatórios (demorará bastante)
- ./bin/ordenador 3 data/in/100000.a data/out/res.bin

//Heapsort no mesmo vetor (será muito mais rápido)
- ./bin/ordenador 8 data/in/100000.a data/out/res.bin




