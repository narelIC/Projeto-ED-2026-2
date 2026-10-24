#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  void *byte;
  int freq;
  struct node *left;
  struct node *right;
  struct node *prox;
} node_t;

node_t *criar_List();

void *ponteiroparaVoid(unsigned char byte);

node_t *removeCabeca(node_t **head, int *tamLista);

node_t *inserir_ord(node_t **head, int freq, char byte, int *tamLista);

node_t *listFreq(FILE *arq, int frequencias[256], int *tamLista);

unsigned char recuperarByteDePonteiroVoid(void *byte);

node_t *criarNo(void *byte, int frequency);

#endif
