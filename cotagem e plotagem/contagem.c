#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------------- Lista Encadeada ---------------- */

typedef struct no_lista
{
    int valor;
    struct no_lista *prox;
} NoLista;

NoLista *inserir_lista(NoLista *cabeca, int valor)
{
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    novo->valor = valor;
    novo->prox = cabeca; // insere no início
    return novo;
}

int buscar_lista(NoLista *cabeca, int valor)
{
    int comparacoes = 0;
    NoLista *atual = cabeca;
    while (atual != NULL)
    {
        comparacoes++;
        if (atual->valor == valor)
        {
            return comparacoes;
        }
        atual = atual->prox;
    }
    return comparacoes; // não encontrado
}

void liberar_lista(NoLista *cabeca)
{
    while (cabeca != NULL)
    {
        NoLista *aux = cabeca;
        cabeca = cabeca->prox;
        free(aux);
    }
}

/* ---------------- Árvore de Busca Binária ---------------- */

typedef struct no_abb
{
    int valor;
    struct no_abb *esq;
    struct no_abb *dir;
} NoABB;

NoABB *inserir_abb(NoABB *raiz, int valor)
{
    NoABB *novo = (NoABB *)malloc(sizeof(NoABB));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    if (raiz == NULL)
    {
        return novo;
    }

    // inserção iterativa (evita recursão profunda)
    NoABB *atual = raiz;
    while (1)
    {
        if (valor < atual->valor)
        {
            if (atual->esq == NULL)
            {
                atual->esq = novo;
                break;
            }
            atual = atual->esq;
        }
        else
        {
            if (atual->dir == NULL)
            {
                atual->dir = novo;
                break;
            }
            atual = atual->dir;
        }
    }
    return raiz;
}

int buscar_abb(NoABB *raiz, int valor)
{
    int comparacoes = 0;
    NoABB *atual = raiz;
    while (atual != NULL)
    {
        comparacoes++;
        if (atual->valor == valor)
        {
            return comparacoes;
        }
        if (valor < atual->valor)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    return comparacoes; // não encontrado
}

void liberar_abb(NoABB *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    liberar_abb(raiz->esq);
    liberar_abb(raiz->dir);
    free(raiz);
}

/* ---------------- Sorteio ---------------- */

// Número aleatório entre 0 e max-1.
// Combina duas chamadas de rand() porque no Windows RAND_MAX é só 32767.
int aleatorio(int max)
{
    long valor = ((long)rand() << 15) | rand();
    return (int)(valor % max);
}

// Comparação usada pelo qsort para ordenar os sorteios em ordem crescente
int comparar_inteiros(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/* ---------------- Programa principal ---------------- */

int main(int argc, char *argv[])
{
    int n = 10000;       // quantidade de números armazenados
    int sorteios = 1000; // quantidade de buscas

    if (argc > 1)
    {
        n = atoi(argv[1]);
    }
    if (argc > 2)
    {
        sorteios = atoi(argv[2]);
    }
    if (n <= 0 || sorteios <= 0)
    {
        printf("Uso: %s [quantidade_de_numeros] [quantidade_de_sorteios]\n", argv[0]);
        return 1;
    }

    srand((unsigned)time(NULL)); // dados diferentes a cada execução

    // Números de 1 a n embaralhados (Fisher-Yates), para não haver repetidos
    // e para a ABB não ficar degenerada por inserção em ordem.
    int *numeros = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        numeros[i] = i + 1;
    }
    for (int i = n - 1; i > 0; i--)
    {
        int j = aleatorio(i + 1);
        int aux = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = aux;
    }

    // Lista: números em ordem crescente a partir da cabeça (1, 2, ..., n).
    // Como inserir_lista insere no início, inserimos de n até 1.
    // Assim, achar o número k custa exatamente k comparações (gráfico linear).
    NoLista *lista = NULL;
    for (int i = n; i >= 1; i--)
    {
        lista = inserir_lista(lista, i);
    }

    // ABB: os mesmos números, em ordem aleatória
    NoABB *abb = NULL;
    for (int i = 0; i < n; i++)
    {
        abb = inserir_abb(abb, numeros[i]);
    }

    // Sorteia os números e os coloca em ordem crescente
    int *sorteados = (int *)malloc(sorteios * sizeof(int));
    for (int s = 0; s < sorteios; s++)
    {
        sorteados[s] = aleatorio(n) + 1;
    }
    qsort(sorteados, sorteios, sizeof(int), comparar_inteiros);

    FILE *csv = fopen("contagem.csv", "w");
    if (csv == NULL)
    {
        perror("Erro ao criar contagem.csv");
        return 1;
    }
    fprintf(csv, "numero,comparacoes_lista,comparacoes_abb\n");

    long long total_lista = 0, total_abb = 0;
    for (int s = 0; s < sorteios; s++)
    {
        int sorteado = sorteados[s];
        int c_lista = buscar_lista(lista, sorteado);
        int c_abb = buscar_abb(abb, sorteado);

        total_lista += c_lista;
        total_abb += c_abb;
        fprintf(csv, "%d,%d,%d\n", sorteado, c_lista, c_abb);
    }
    fclose(csv);

    printf("Numeros armazenados: %d\n", n);
    printf("Sorteios realizados: %d\n", sorteios);
    printf("Media de comparacoes na lista: %.2f\n", (double)total_lista / sorteios);
    printf("Media de comparacoes na ABB:   %.2f\n", (double)total_abb / sorteios);
    printf("Resultados gravados em contagem.csv\n");

    liberar_lista(lista);
    liberar_abb(abb);
    free(numeros);
    free(sorteados);
    return 0;
}
