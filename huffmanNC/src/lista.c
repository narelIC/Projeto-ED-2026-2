#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

node_t *criar_List()
{
    return NULL;
}

void *ponteiroparaVoid(unsigned char byte)
{
    unsigned char *ponteiro = malloc(sizeof(unsigned char));
    *ponteiro = byte;
    return (void *)ponteiro;
}

node_t *removeCabeca(node_t **head, int *tamLista)
{
    node_t *atual = NULL;
    if (*head != NULL)
    {
        atual = *head;
        *head = (*head)->prox;
        atual->prox = NULL;
        (*tamLista)--;
    }
    return atual;
}

node_t *inserir_ord(node_t **head, int freq, char byte, int *tamLista)
{
    node_t *novo = (node_t *)malloc(sizeof(node_t));
    novo->freq = freq;
    novo->byte = ponteiroparaVoid(byte);
    novo->left = NULL;
    novo->right = NULL;

    node_t *atual = *head;
    node_t *anter = NULL;

    if (*head == NULL)
    {
        *head = novo;
        novo->prox = NULL;
        (*tamLista)++;
        return novo;
    }

    while (atual != NULL)
    {
        if (atual->freq < novo->freq)
        {
            anter = atual;
            atual = atual->prox;
        }
        else
        {
            if (anter == NULL)
            {
                *head = novo;
            }
            else
            {
                anter->prox = novo;
            }

            novo->prox = atual;
            (*tamLista)++;
            return novo;
        }
    }
    anter->prox = novo;
    novo->prox = NULL;
    (*tamLista)++;
    return novo;
}

node_t *listFreq(FILE *arq, int frequencias[256], int *tamLista)
{
    unsigned char caractere;

    while (fread(&caractere, sizeof(unsigned char), 1, arq))
    {
        frequencias[caractere]++;
    }
    node_t *lista = criar_List();

    for (int i = 0; i < 256; i++)
    {
        if (frequencias[i] > 0)
        {
            inserir_ord(&lista, frequencias[i], i, tamLista);
        }
    }

    return lista;
}

unsigned char recuperarByteDePonteiroVoid(void *byte)
{
    unsigned char *item = (unsigned char *)((node_t *)byte)->byte;
    return *item;
}

node_t *criarNo(void *byte, int frequency)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->prox = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->byte = byte;
    newNode->freq = frequency;
    return newNode;
}
