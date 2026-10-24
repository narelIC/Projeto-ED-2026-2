#include <stdio.h>
#include "lista.h"
#include "arvore.h"
#include "descompressao.h"

int tamanho_lixo_arquivoCompactado(FILE *archive)
{
    if (archive == NULL)
    {
        return -1;
    }

    unsigned char byte;
    fread(&byte, sizeof(unsigned char), 1, archive);

    int trashSize = byte & 0xE0;

    trashSize = trashSize >> 5;

    fseek(archive, 0, SEEK_SET);

    return trashSize;
}

int tamanho_arvore_arquivoCompactado(FILE *archive)
{
    unsigned char byte1, byte2;

    fread(&byte1, sizeof(unsigned char), 1, archive);
    fread(&byte2, sizeof(unsigned char), 1, archive);

    byte1 = byte1 & 0x1F;

    short int treeSize = (byte1 << 8) | byte2;

    return treeSize;
}

node_t *montar_arvore(FILE *archive, short int *treeSize)
{
    unsigned char byte;
    node_t *huffTree = NULL;

    while (*treeSize > 0)
    {
        fread(&byte, sizeof(unsigned char), 1, archive);

        if (byte == '\\')
        {
            (*treeSize)--;
            fread(&byte, sizeof(unsigned char), 1, archive);
            huffTree = criarNo(ponteiroparaVoid(byte), 0);
            (*treeSize)--;
            return huffTree;
        }

        huffTree = criarNo(ponteiroparaVoid(byte), 0);
        (*treeSize)--;

        if (byte == '*')
        {
            huffTree->left = montar_arvore(archive, treeSize);
            huffTree->right = montar_arvore(archive, treeSize);
        }
        return huffTree;
    }

    return NULL;
}

int verificar_bit_i(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return (mask & c) ? 1 : 0;
}

void recuperar_bytes(FILE *fileIn, FILE *fileOut, short int trashSize, unsigned long long int sizeFile, node_t *huffTree)
{
    unsigned char byte;
    node_t *aux = huffTree;
    int bitPosition = 0;
    unsigned long long int bitsToProcess = sizeFile * 8 - trashSize;

    for (unsigned long long int bitIndex = 0; bitIndex < bitsToProcess; bitIndex++)
    {
        if (bitIndex % 8 == 0)
        {
            fread(&byte, sizeof(unsigned char), 1, fileIn);
        }

        bitPosition = 7 - (bitIndex % 8);

        if (verificar_bit_i(byte, bitPosition))
        {
            aux = aux->right;
        }
        else
        {
            aux = aux->left;
        }

        if (ehFolha(&aux))
        {
            unsigned char caractere = recuperarByteDePonteiroVoid(aux);
            fwrite(&caractere, sizeof(unsigned char), 1, fileOut);
            aux = huffTree;
        }
    }
}
