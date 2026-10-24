#include <stdio.h>
#include "lista.h"
#include "arvore.h"
#include "compressao.h"
#include <stdint.h>

unsigned long long int calcularTamanho(FILE *arquivo)
{
    unsigned long long int posicaoAtual = ftell(arquivo);

    fseek(arquivo, 0, SEEK_END);

    unsigned long long int tamanho_do_arquivo = ftell(arquivo);

    fseek(arquivo, posicaoAtual, SEEK_SET) != 0;

    return tamanho_do_arquivo;
}

void mapearBytesParaCodigos(node_t *tree_node, BitHuff table[], BitHuff codigo_parafolha)
{
    if (tree_node == NULL)
    {
        return;
    }

    if (tree_node->left == NULL && tree_node->right == NULL)
    {
        table[recuperarByteDePonteiroVoid(tree_node)] = codigo_parafolha;

        return;
    }

    codigo_parafolha.size++;

    switch (1)
    {
    case 1:

        if (tree_node->left != NULL)
        {
            BitHuff leftCode = codigo_parafolha;

            leftCode.bitH <<= 1;

            mapearBytesParaCodigos(tree_node->left, table, leftCode);
        }

    case 2:

        if (tree_node->right != NULL)
        {
            BitHuff rightCode = codigo_parafolha;

            rightCode.bitH = (rightCode.bitH << 1) | 1;

            mapearBytesParaCodigos(tree_node->right, table, rightCode);
        }
        break;
    }
}

int tamanho_lixo(int frequency[], BitHuff table[])
{
    long long bits_antes = 0;
    long long bits_depois = 0;

    int i = 0;
    while (i < 256)
    {
        if (frequency[i] != 0)
        {
            bits_antes += (long long)frequency[i] * 8;

            bits_depois += (long long)frequency[i] * table[i].size;
        }
        i++;
    }

    int trash = (bits_antes - bits_depois) % 8;

    return trash;
}

void escrever_no_Cabecalho_Arquivo_compac(FILE *file, int trashSize, int treeSize)
{
    unsigned char primeiro_byte = 0x00;
    unsigned char segundo_byte = 0x00;

    primeiro_byte = primeiro_byte | (trashSize << 5);

    primeiro_byte = primeiro_byte | (treeSize >> 8);

    segundo_byte = segundo_byte | treeSize;

    fwrite(&primeiro_byte, sizeof(unsigned char), 1, file);
    fwrite(&segundo_byte, sizeof(unsigned char), 1, file);
}

void escrever_arvore(FILE *file, node_t *arvore_b)
{
    if (arvore_b == NULL)
    {
        return;
    }
    unsigned char valor = recuperarByteDePonteiroVoid(arvore_b);

    if (arvore_b->left == NULL && arvore_b->right == NULL && (valor == '*' || valor == '\\'))
    {
        uint8_t scape = (uint8_t)'\\';

        fwrite(&scape, sizeof(uint8_t), 1, file);
    }
    uint8_t byte = valor;

    fwrite(&byte, sizeof(uint8_t), 1, file);

    escrever_arvore(file, arvore_b->left);

    escrever_arvore(file, arvore_b->right);
}

void gravarCodigos(FILE *fileIn, FILE *fileOut, BitHuff table[], int trashSize)
{
    uint8_t acumulador_bits = 0;
    int tamanho_acumulador = 0;
    int caractere;

    while ((caractere = getc(fileIn)) != EOF)
    {
        BitHuff entry = table[caractere];

        for (int i = entry.size - 1; i >= 0; --i)
        {
            acumulador_bits = (acumulador_bits << 1) | ((entry.bitH >> i) & 1);
            tamanho_acumulador++;

            if (tamanho_acumulador == 8)
            {
                fwrite(&acumulador_bits, sizeof(uint8_t), 1, fileOut);
                acumulador_bits = 0;
                tamanho_acumulador = 0;
            }
        }
    }

    if (tamanho_acumulador > 0)
    {
        acumulador_bits <<= trashSize;

        fwrite(&acumulador_bits, sizeof(uint8_t), 1, fileOut);
    }
}
