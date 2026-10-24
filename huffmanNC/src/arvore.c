#include <stdio.h>
#include <stdbool.h>
#include "arvore.h"
#include "lista.h"

node_t *arvoreHuff(node_t **head, int *tamLista)
{
    node_t *left, *right, *Pai = NULL;

    if (*tamLista == 1)
    {
        left = removeCabeca(head, tamLista);
        Pai = inserir_ord(head, left->freq, '*', tamLista);
        Pai->left = left;
        return Pai;
    }

    while (*tamLista > 1)
    {
        left = removeCabeca(head, tamLista);
        right = removeCabeca(head, tamLista);

        Pai = inserir_ord(head, left->freq + right->freq, '*', tamLista);

        Pai->left = left;
        Pai->right = right;
    }

    return Pai;
}

bool ehFolha(node_t **head)
{
    return (*head)->left == NULL && (*head)->right == NULL;
}

int tamanhoArvore(node_t *no)
{
    if (no == NULL)
    {
        return 0;
    }

    int esq = tamanhoArvore(no->left);
    int dir = tamanhoArvore(no->right);

    unsigned char x = recuperarByteDePonteiroVoid(no);

    if ((((x == '*') || (x == '\\')) && ehFolha(&no)))
    {
        return 2 + esq + dir;
    }

    return 1 + esq + dir;
}
