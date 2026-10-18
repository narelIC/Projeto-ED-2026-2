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

// Divide o filho cheio do nó pai na posição i
void dividirFilho(No *pai, int i, No *filho) {
    int t = 2; // Grau mínimo para MAX_CHAVES = 3
    No *z = criarNo(filho->folha);
    z->numChaves = t - 1; // 1 chave

    // Copia a segunda metade das chaves do filho para z
    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = filho->chaves[j + t];
    }

    // Se não for folha, copia os ponteiros dos filhos também
    if (!filho->folha) {
        for (int j = 0; j < t; j++) {
            z->filhos[j] = filho->filhos[j + t];
            filho->filhos[j + t] = NULL;
        }
    }

    filho->numChaves = t - 1;

    // Abre espaço nos filhos do pai para o novo nó z
    for (int j = pai->numChaves; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }

    pai->filhos[i + 1] = z;

    // Move as chaves do pai para abrir espaço para a chave do meio
    for (int j = pai->numChaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }

    // Sobe a chave do meio do filho para o pai
    pai->chaves[i] = filho->chaves[t - 1];
    pai->numChaves++;
}

// Insere a chave em um nó que não está cheio
void inserirNaoCheio(No *no, int valor) {
    int i = no->numChaves - 1;

    if (no->folha) {
        // Encontra a posição correta e desloca as chaves para a direita
        while (i >= 0 && valor < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = valor;
        no->numChaves++;
    } else {
        // Encontra o filho que deve receber a chave
        while (i >= 0 && valor < no->chaves[i]) {
            i--;
        }
        i++;

        // Se o filho estiver cheio, divide-o
        if (no->filhos[i]->numChaves == MAX_CHAVES) {
            dividirFilho(no, i, no->filhos[i]);
            if (valor > no->chaves[i]) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], valor);
    }
}

// Função principal de inserção na Árvore B
void inserir(No **raizRef, int valor) {
    No *raiz = *raizRef;

    // Se a raiz estiver cheia, a árvore cresce em altura
    if (raiz->numChaves == MAX_CHAVES) {
        No *s = criarNo(0);
        *raizRef = s;
        s->filhos[0] = raiz;
        dividirFilho(s, 0, raiz);
        inserirNaoCheio(s, valor);
    } else {
        inserirNaoCheio(raiz, valor);
    }
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

// Função recursiva para liberar toda a memória da árvore
void liberarArvore(No *no) {
    if (no == NULL) return;
    if (!no->folha) {
        for (int i = 0; i <= no->numChaves; i++) {
            liberarArvore(no->filhos[i]);
        }
    }
    free(no);
}

int main(void) {
    int valores[] = {10, 20, 5, 7, 12, 15, 25, 30};

No *raiz = criarNo(1);

for (int i = 0; i < 8; i++) {
    inserir(&raiz, valores[i]);
}

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

    // Libera todos os nós criados na árvore recursivamente
    liberarArvore(raiz);

    return 0;
}
