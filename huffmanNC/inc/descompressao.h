#ifndef DESCOMPRIMIR_H
#define DESCOMPRIMIR_H

#include <stdio.h>
#include "lista.h"
#include "arvore.h"

int tamanho_lixo_arquivoCompactado(FILE *archive);

int tamanho_arvore_arquivoCompactado(FILE *archive);

node_t *montar_arvore(FILE *archive, short int *treeSize);

int verificar_bit_i(unsigned char c, int i);

void recuperar_bytes(FILE *fileIn, FILE *fileOut, short int trashSize, unsigned long long int sizeFile, node_t *huffTree);

#endif
