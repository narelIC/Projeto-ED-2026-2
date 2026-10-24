#ifndef COMPRESSAO_H
#define COMPRESSAO_H

#include <stdio.h>
#include "lista.h"
#include "arvore.h"
#include <stdint.h>

typedef struct bithuff
{
  unsigned long long int bitH;
  int size;
} BitHuff;

unsigned long long int calcularTamanho(FILE *arquivo);

void mapearBytesParaCodigos(node_t *tree_node, BitHuff table[], BitHuff codigo_parafolha);

int tamanho_lixo(int frequency[], BitHuff table[]);

void escrever_no_Cabecalho_Arquivo_compac(FILE *file, int trashSize, int treeSize);

void escrever_arvore(FILE *file, node_t *arvore_b);

void gravarCodigos(FILE *fileIn, FILE *fileOut, BitHuff table[], int trashSize);

#endif
