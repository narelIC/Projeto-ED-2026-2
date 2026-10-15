#include <stdio.h>
#include <stdbool.h>
#include "arvore.h"
#include "lista.h"

/*
    monta a árvore de huffman com a lista ordenada
*/

node_t *arvoreHuff(node_t **head, int *tamLista)
{

<<<<<<< HEAD
    node_t *left, *right, *Pai = NULL;

    // Caso especial: arquivo com apenas um tipo de byte.
    // Cria um nó pai '*' com a única folha à esquerda, para que ela tenha código "0".
    if (*tamLista == 1)
    {
        left = removeCabeca(head, tamLista);
        Pai = inserir_ord(head, left->freq, '*', tamLista);
        Pai->left = left;
        return Pai;
    }
=======
    node_t *left, *right, *Pai;
>>>>>>> cff14ac56a4aca8378d83086016f7ef9da95d72b

    while (*tamLista > 1)
    {

        left = removeCabeca(head, tamLista);
        right = removeCabeca(head, tamLista);

        Pai = inserir_ord(head, left->freq + right->freq, '*', tamLista);
        // Função da lista.c
        Pai->left = left;
        Pai->right = right;
    }

    return Pai;
}

bool ehFolha(node_t **head)
{
    return (*head)->left == NULL && (*head)->right == NULL;
}
/*
    acha o tamanho da árvore
*/

int tamanhoArvore(node_t *no)
{
    if (no == NULL)
    {
        return 0;
    }

    // Recursivamente calcula a profundidade das subárvores esquerda e direita
    int esq = tamanhoArvore(no->left);
    int dir = tamanhoArvore(no->right);

<<<<<<< HEAD
    unsigned char x = recuperarByteDePonteiroVoid(no); // Recupera o byte (void *) do nó
=======
    unsigned char x = no->byte; // Acessa diretamente o byte do nó
>>>>>>> cff14ac56a4aca8378d83086016f7ef9da95d72b

    // Caso especial para caracteres '*' e '\\', onde precisamos contabilizar um valor especial para nós folha
    if ((((x == '*') || (x == '\\')) && ehFolha(&no)))
    {
        return 2 + esq + dir; // Considera um ajuste especial na profundidade
    }

    // Para nós normais, retorna a maior profundidade entre os ramos esquerdo e direito
    return 1 + esq + dir;
}