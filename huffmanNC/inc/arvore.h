#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>
#include "lista.h"

bool ehFolha(node_t **head);

node_t *arvoreHuff(node_t **head, int *tamLista);

int tamanhoArvore(node_t *no);

#endif
