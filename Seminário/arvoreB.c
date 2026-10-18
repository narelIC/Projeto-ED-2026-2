#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAVES 3

typedef struct No {
    int chaves[MAX_CHAVES];
    struct No *filhos[MAX_CHAVES + 1];
    int numChaves;
    int folha;
} No;

// Cria um nó
No *criarNo(int folha) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    novo->numChaves = 0;
    novo->folha = folha;

    for (int i = 0; i <= MAX_CHAVES; i++) {
        novo->filhos[i] = NULL;
    }

    return novo;
}

// Busca uma chave na Arvore B
No *buscar(No *raiz, int valor) {
    int i = 0;

    // Encontra a posicao onde a chave estaria
    while (i < raiz->numChaves &&
           valor > raiz->chaves[i]) {
        i++;
    }

    // A chave foi encontrada
    if (i < raiz->numChaves &&
        valor == raiz->chaves[i]) {
        return raiz;
    }

    // Se for folha, a chave nao existe
    if (raiz->folha) {
        return NULL;
    }

    // Continua a busca no filho adequado
    return buscar(raiz->filhos[i], valor);
}

int main(void) {
    // Monta a raiz
    No *raiz = criarNo(0);
    raiz->numChaves = 2;
    raiz->chaves[0] = 10;
    raiz->chaves[1] = 20;

    // Monta o filho da esquerda
    raiz->filhos[0] = criarNo(1);
    raiz->filhos[0]->numChaves = 2;
    raiz->filhos[0]->chaves[0] = 5;
    raiz->filhos[0]->chaves[1] = 7;

    // Monta o filho do meio
    raiz->filhos[1] = criarNo(1);
    raiz->filhos[1]->numChaves = 2;
    raiz->filhos[1]->chaves[0] = 12;
    raiz->filhos[1]->chaves[1] = 15;

    // Monta o filho da direita
    raiz->filhos[2] = criarNo(1);
    raiz->filhos[2]->numChaves = 2;
    raiz->filhos[2]->chaves[0] = 25;
    raiz->filhos[2]->chaves[1] = 30;

    int valor;

    printf("Digite o valor que deseja buscar: ");
    scanf("%d", &valor);

    No *resultado = buscar(raiz, valor);

    if (resultado != NULL) {
        printf("Valor %d encontrado na Arvore B!\n",
               valor);
    } else {
        printf("Valor %d nao encontrado.\n", valor);
    }

    // Libera os nos criados
    for (int i = 0; i < 3; i++) {
        free(raiz->filhos[i]);
    }
    free(raiz);

    return 0;
}
