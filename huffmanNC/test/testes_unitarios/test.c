#include <stdio.h>
#include "lista.h"
#include "arvore.h"
#include "compressao.h"
#include "descompressao.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#define MAX 100

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void liberarArvore(node_t *node)
{
    if (node == NULL)
        return;
    liberarArvore(node->left);
    liberarArvore(node->right);
    free(node);
}

void test_ehFolha()
{
    node_t folha;
    folha.left = NULL;
    folha.right = NULL;

    node_t *ptrFolha = &folha;

    CU_ASSERT_TRUE(ehFolha(&ptrFolha));

    node_t noComFilhos;
    noComFilhos.left = &folha;
    noComFilhos.right = NULL;

    node_t *ptrNoComFilhos = &noComFilhos;

    CU_ASSERT_FALSE(ehFolha(&ptrNoComFilhos));
}

void test_tamanhoArvore()
{
    CU_ASSERT_EQUAL(tamanhoArvore(NULL), 0);

    node_t noA, noB, noC;
    noA.byte = ponteiroparaVoid('A');
    noA.left = NULL;
    noA.right = NULL;

    noB.byte = ponteiroparaVoid('*');
    noB.left = NULL;
    noB.right = NULL;

    noC.byte = ponteiroparaVoid('B');
    noC.left = &noA;
    noC.right = &noB;

    CU_ASSERT_EQUAL(tamanhoArvore(&noA), 1);

    CU_ASSERT_EQUAL(tamanhoArvore(&noB), 2);

    CU_ASSERT_EQUAL(tamanhoArvore(&noC), 4);
}

void test_inserir_ord()
{
    node_t *head = NULL;
    int tamLista = 0;

    node_t *n1 = inserir_ord(&head, 5, 'a', &tamLista);
    CU_ASSERT_PTR_NOT_NULL(n1);
    CU_ASSERT_EQUAL(head, n1);
    CU_ASSERT_EQUAL(n1->freq, 5);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(n1), 'a');
    CU_ASSERT_PTR_NULL(n1->prox);
    CU_ASSERT_EQUAL(tamLista, 1);

    node_t *n2 = inserir_ord(&head, 10, 'b', &tamLista);
    CU_ASSERT_PTR_NOT_NULL(n2);
    CU_ASSERT_EQUAL(n2->freq, 10);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(n2), 'b');
    CU_ASSERT_PTR_NULL(n2->prox);
    CU_ASSERT_EQUAL(head->prox, n2);
    CU_ASSERT_EQUAL(tamLista, 2);

    node_t *n3 = inserir_ord(&head, 3, 'c', &tamLista);
    CU_ASSERT_PTR_NOT_NULL(n3);
    CU_ASSERT_EQUAL(n3->freq, 3);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(n3), 'c');
    CU_ASSERT_PTR_EQUAL(n3->prox, n1);
    CU_ASSERT_EQUAL(head, n3);
    CU_ASSERT_EQUAL(tamLista, 3);

    node_t *n4 = inserir_ord(&head, 7, 'd', &tamLista);
    CU_ASSERT_PTR_NOT_NULL(n4);
    CU_ASSERT_EQUAL(n4->freq, 7);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(n4), 'd');
    CU_ASSERT_PTR_EQUAL(n4->prox, n2);
    CU_ASSERT_EQUAL(n1->prox, n4);
    CU_ASSERT_EQUAL(tamLista, 4);
}

void test_arvoreHuff()
{
    node_t *head = NULL;
    int tamLista = 0;

    inserir_ord(&head, 5, 'A', &tamLista);
    inserir_ord(&head, 3, 'B', &tamLista);
    inserir_ord(&head, 2, 'C', &tamLista);

    node_t *huffTree = arvoreHuff(&head, &tamLista);

    CU_ASSERT_PTR_NOT_NULL(huffTree);
    CU_ASSERT_EQUAL(huffTree->freq, 10);

    CU_ASSERT_PTR_NOT_NULL(huffTree->left);
    CU_ASSERT_PTR_NOT_NULL(huffTree->right);

    CU_ASSERT_EQUAL(huffTree->left->freq, 5);

    CU_ASSERT_EQUAL(huffTree->right->freq, 5);
}

void test_recuperar_bytes()
{
    FILE *fileIn = fopen("entrada.bin", "wb");
    FILE *fileOut = fopen("saida.txt", "wb");
    CU_ASSERT_PTR_NOT_NULL(fileIn);
    CU_ASSERT_PTR_NOT_NULL(fileOut);

    unsigned char bytes[] = {0b00000001, 0b00000010};
    fwrite(bytes, sizeof(unsigned char), sizeof(bytes), fileIn);
    fclose(fileIn);

    node_t *head = NULL;
    int tamLista = 0;
    inserir_ord(&head, 5, 'A', &tamLista);
    inserir_ord(&head, 3, 'B', &tamLista);

    node_t *huffTree = arvoreHuff(&head, &tamLista);

    fileIn = fopen("entrada.bin", "rb");
    recuperar_bytes(fileIn, fileOut, 0, sizeof(bytes), huffTree);
    fclose(fileIn);
    fclose(fileOut);

    fileOut = fopen("saida.txt", "rb");
    CU_ASSERT_PTR_NOT_NULL(fileOut);

    unsigned char output[2];
    fread(output, sizeof(unsigned char), sizeof(output), fileOut);
    CU_ASSERT_EQUAL(output[1], 'B');

    fclose(fileOut);
}

void test_escrever_arvore_simples()
{
    FILE *file = fopen("teste.bin", "wb");
    CU_ASSERT_PTR_NOT_NULL(file);

    node_t raiz;
    raiz.byte = ponteiroparaVoid('A');
    raiz.left = NULL;
    raiz.right = NULL;

    escrever_arvore(file, &raiz);
    fclose(file);

    file = fopen("teste.bin", "rb");
    CU_ASSERT_PTR_NOT_NULL(file);

    uint8_t resultado;
    fread(&resultado, sizeof(uint8_t), 1, file);
    CU_ASSERT_EQUAL(resultado, 'A');

    fclose(file);
}

void test_calcularTamanho()
{
    FILE *arquivo = fopen("teste_tamanho.txt", "wb");
    CU_ASSERT_PTR_NOT_NULL(arquivo);

    const char *dados = "Testando tamanho do arquivo.";
    fwrite(dados, sizeof(char), strlen(dados), arquivo);
    fclose(arquivo);

    arquivo = fopen("teste_tamanho.txt", "rb");
    unsigned long long int tamanho = calcularTamanho(arquivo);
    CU_ASSERT_EQUAL(tamanho, strlen(dados));

    fclose(arquivo);
    remove("teste_tamanho.txt");
}

void test_mapearBytesParaCodigos()
{
    node_t folhaA = {.byte = ponteiroparaVoid('A'), .freq = 5, .left = NULL, .right = NULL};
    node_t folhaB = {.byte = ponteiroparaVoid('B'), .freq = 3, .left = NULL, .right = NULL};
    node_t raiz = {.byte = ponteiroparaVoid('*'), .freq = 8, .left = &folhaA, .right = &folhaB};

    BitHuff table[256] = {0};
    BitHuff codigo = {.bitH = 0, .size = 0};

    mapearBytesParaCodigos(&raiz, table, codigo);

    CU_ASSERT_EQUAL(table[recuperarByteDePonteiroVoid(&folhaA)].bitH, 0b0);
    CU_ASSERT_EQUAL(table[recuperarByteDePonteiroVoid(&folhaB)].bitH, 0b1);
}

void test_tamanho_lixo()
{
    int frequency[256] = {0};
    frequency['A'] = 8;
    frequency['B'] = 8;

    BitHuff table[256] = {0};
    table[(unsigned char)'A'].size = 1;
    table[(unsigned char)'B'].size = 2;

    int lixo = tamanho_lixo(frequency, table);

    CU_ASSERT_EQUAL(lixo, 0);
}

void test_escrever_no_Cabecalho_Arquivo_compac()
{
    FILE *tempFile;
    unsigned char primeiro_byte;
    unsigned char segundo_byte;

    tempFile = fopen("temp_test_file.bin", "wb+");
    CU_ASSERT_PTR_NOT_NULL(tempFile);

    int trashSize = 3;
    int treeSize = 1024;

    escrever_no_Cabecalho_Arquivo_compac(tempFile, trashSize, treeSize);

    fseek(tempFile, 0, SEEK_SET);
    fread(&primeiro_byte, sizeof(unsigned char), 1, tempFile);
    fread(&segundo_byte, sizeof(unsigned char), 1, tempFile);

    CU_ASSERT_EQUAL(primeiro_byte, (trashSize << 5) | (treeSize >> 8));

    CU_ASSERT_EQUAL(segundo_byte, treeSize & 0xFF);

    fclose(tempFile);
    remove("temp_test_file.bin");
}

void test_gravarCodigos()
{
    FILE *tempFileIn;
    FILE *tempFileOut;
    BitHuff table[256] = {0};

    table['a'] = (BitHuff){0b10, 2};
    table['b'] = (BitHuff){0b11, 2};

    tempFileIn = fopen("temp_input.txt", "wb+");
    CU_ASSERT_PTR_NOT_NULL(tempFileIn);
    fputc('a', tempFileIn);
    fputc('a', tempFileIn);
    fputc('a', tempFileIn);
    fputc('b', tempFileIn);
    fputc('b', tempFileIn);
    fputc('b', tempFileIn);
    fseek(tempFileIn, 0, SEEK_SET);

    tempFileOut = fopen("temp_output.bin", "wb+");
    CU_ASSERT_PTR_NOT_NULL(tempFileOut);

    int trashSize = 0;
    gravarCodigos(tempFileIn, tempFileOut, table, trashSize);

    fseek(tempFileOut, 0, SEEK_SET);
    uint8_t byte;
    fread(&byte, sizeof(uint8_t), 1, tempFileOut);

    CU_ASSERT_EQUAL(byte, 171);

    fclose(tempFileIn);
    fclose(tempFileOut);
    remove("temp_input.txt");
    remove("temp_output.bin");
}

void test_tamanho_lixo_arquivoCompactado(void)
{
    FILE *testFile = fopen("testfile.bin", "wb");
    if (testFile == NULL)
    {
        CU_FAIL("Failed to create test file");
        return;
    }

    unsigned char byteToWrite = 0b11100000;
    fwrite(&byteToWrite, sizeof(unsigned char), 1, testFile);
    fclose(testFile);

    testFile = fopen("testfile.bin", "rb");
    CU_ASSERT_PTR_NOT_NULL(testFile);

    int result = tamanho_lixo_arquivoCompactado(testFile);
    CU_ASSERT_EQUAL(result, 7);

    fclose(testFile);

    remove("testfile.bin");
}

void test_montar_arvore(void)
{
    short int treeSize = 5;
    unsigned char bytes[] = {'\\', 'a', '*', 'b', '*', 'c'};

    node_t *root = NULL;

    root = criarNo(ponteiroparaVoid('a'), 0);
    root->left = criarNo(ponteiroparaVoid('b'), 0);
    root->right = criarNo(ponteiroparaVoid('c'), 0);

    CU_ASSERT_PTR_NOT_NULL(root);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(root), 'a');
    CU_ASSERT_PTR_NOT_NULL(root->left);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(root->left), 'b');
    CU_ASSERT_PTR_NOT_NULL(root->right);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(root->right), 'c');

    liberarArvore(root);
}

void test_verificar_bit_i()
{
    CU_ASSERT_EQUAL(verificar_bit_i(0b00000001, 0), 1);
    CU_ASSERT_EQUAL(verificar_bit_i(0b00000001, 1), 0);
    CU_ASSERT_EQUAL(verificar_bit_i(0b00000010, 1), 1);
    CU_ASSERT_EQUAL(verificar_bit_i(0b00000010, 0), 0);
    CU_ASSERT_EQUAL(verificar_bit_i(0b00001111, 3), 1);
    CU_ASSERT_EQUAL(verificar_bit_i(0b00001111, 4), 0);
    CU_ASSERT_EQUAL(verificar_bit_i(0b11111111, 7), 1);
    CU_ASSERT_EQUAL(verificar_bit_i(0b11111111, 8), 0);
}

void test_criar_List()
{
    node_t *lista = criar_List();

    CU_ASSERT_PTR_NULL(lista);
}

void test_ponteiroparaVoid()
{
    unsigned char valor = 42;
    unsigned char *resultado = (unsigned char *)ponteiroparaVoid(valor);

    CU_ASSERT_PTR_NOT_NULL(resultado);
    CU_ASSERT_EQUAL(*resultado, valor);

    free(resultado);
}

void test_removeCabeca()
{
    node_t *head = malloc(sizeof(node_t));
    head->byte = ponteiroparaVoid('a');
    head->freq = 1;

    node_t *segundo = malloc(sizeof(node_t));
    segundo->byte = ponteiroparaVoid('b');
    segundo->freq = 2;

    node_t *terceiro = malloc(sizeof(node_t));
    terceiro->byte = ponteiroparaVoid('c');
    terceiro->freq = 3;

    head->prox = segundo;
    segundo->prox = terceiro;
    terceiro->prox = NULL;

    int tamLista = 3;

    node_t *removido = removeCabeca(&head, &tamLista);

    CU_ASSERT_PTR_NOT_NULL(removido);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(removido), 'a');
    CU_ASSERT_EQUAL(removido->freq, 1);

    CU_ASSERT_PTR_NOT_NULL(head);
    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(head), 'b');
    CU_ASSERT_EQUAL(tamLista, 2);

    free(removido);
    free(segundo);
    free(terceiro);
}

void test_listFreq()
{
    FILE *file = fopen("teste_freq.txt", "w");
    fprintf(file, "abcabcdd");
    fclose(file);

    int frequencias[256] = {0};
    int tamLista = 0;

    file = fopen("teste_freq.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    node_t *lista = listFreq(file, frequencias, &tamLista);

    CU_ASSERT_PTR_NOT_NULL(lista);

    CU_ASSERT_EQUAL(frequencias['a'], 2);
    CU_ASSERT_EQUAL(frequencias['b'], 2);
    CU_ASSERT_EQUAL(frequencias['c'], 2);
    CU_ASSERT_EQUAL(frequencias['d'], 2);
    CU_ASSERT_EQUAL(tamLista, 4);

    CU_ASSERT_EQUAL(lista->freq, 2);
    CU_ASSERT_EQUAL(lista->prox->freq, 2);
    CU_ASSERT_EQUAL(lista->prox->prox->freq, 2);
    CU_ASSERT_EQUAL(lista->prox->prox->prox->freq, 2);

    fclose(file);
    remove("teste_freq.txt");

    while (lista != NULL)
    {
        node_t *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

void test_recuperarByteDePonteiroVoid()
{
    node_t *no = malloc(sizeof(node_t));
    CU_ASSERT_PTR_NOT_NULL(no);

    no->byte = ponteiroparaVoid('X');
    unsigned char resultado = recuperarByteDePonteiroVoid(no);

    CU_ASSERT_EQUAL(resultado, 'X');

    free(no);
}

void test_criarNo()
{
    char byte = 'A';
    int frequency = 5;

    node_t *no = criarNo(&byte, frequency);
    CU_ASSERT_PTR_NOT_NULL(no);

    CU_ASSERT_EQUAL(recuperarByteDePonteiroVoid(no), byte);
    CU_ASSERT_EQUAL(no->freq, frequency);

    free(no);
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite pSuiteInserirOrd = CU_add_suite("TestSuite_inserir_ord", init_suite, clean_suite);
    CU_pSuite pSuiteRecuperarBytes = CU_add_suite("TestSuite_recuperar_bytes", init_suite, clean_suite);
    CU_pSuite pSuiteArvoreHuff = CU_add_suite("TestSuite_arvore_huff", init_suite, clean_suite);
    CU_pSuite pSuiteFolha = CU_add_suite("TestSuite_ehFolha", init_suite, clean_suite);
    CU_pSuite pSuiteTamanhoArvore = CU_add_suite("TestSuite_tamanhoArvore", init_suite, clean_suite);
    CU_pSuite pSuiteEscreverArvore = CU_add_suite("TestSuite_escreverArvore", init_suite, clean_suite);
    CU_pSuite pSuiteCalcularTamanho = CU_add_suite("TestSuite_calcularTamanho", init_suite, clean_suite);
    CU_pSuite pSuiteMapearBytes = CU_add_suite("TestSuite_mapearBytes", init_suite, clean_suite);
    CU_pSuite pSuiteTamanhoLixo = CU_add_suite("TestSuite_tamanhoLixo", init_suite, clean_suite);
    CU_pSuite pSuiteEscreverCabecalho = CU_add_suite("TestSuite_escreverCabecalho", init_suite, clean_suite);
    CU_pSuite pSuiteMontarArvore = CU_add_suite("TestSuite_montarArvore", init_suite, clean_suite);
    CU_pSuite pSuiteRemoveCabeca = CU_add_suite("TestSuite_removeCabeca", init_suite, clean_suite);
    CU_pSuite pSuiteListFreq = CU_add_suite("TestSuite_listFreq", init_suite, clean_suite);
    CU_pSuite pSuiteRecuperarByte = CU_add_suite("TestSuite_recuperarByte", init_suite, clean_suite);
    CU_pSuite pSuiteCriarNo = CU_add_suite("TestSuite_criarNo", init_suite, clean_suite);

    if (NULL == pSuiteInserirOrd || NULL == pSuiteRecuperarBytes || NULL == pSuiteArvoreHuff ||
        NULL == pSuiteFolha || NULL == pSuiteTamanhoArvore || NULL == pSuiteEscreverArvore ||
        NULL == pSuiteCalcularTamanho || NULL == pSuiteMapearBytes || NULL == pSuiteTamanhoLixo ||
        NULL == pSuiteEscreverCabecalho || NULL == pSuiteMontarArvore || NULL == pSuiteRemoveCabeca ||
        NULL == pSuiteListFreq || NULL == pSuiteRecuperarByte || NULL == pSuiteCriarNo)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(pSuiteInserirOrd, "test_inserir_ord", test_inserir_ord);
    CU_add_test(pSuiteRecuperarBytes, "test_recuperar_bytes", test_recuperar_bytes);
    CU_add_test(pSuiteArvoreHuff, "test_arvore_huff", test_arvoreHuff);
    CU_add_test(pSuiteFolha, "test_ehFolha", test_ehFolha);
    CU_add_test(pSuiteTamanhoArvore, "test_tamanhoArvore", test_tamanhoArvore);
    CU_add_test(pSuiteEscreverArvore, "test_escrever_arvore_simples", test_escrever_arvore_simples);
    CU_add_test(pSuiteCalcularTamanho, "test_calcularTamanho", test_calcularTamanho);
    CU_add_test(pSuiteMapearBytes, "test_mapearBytesParaCodigos", test_mapearBytesParaCodigos);
    CU_add_test(pSuiteTamanhoLixo, "test_tamanho_lixo", test_tamanho_lixo);
    CU_add_test(pSuiteEscreverCabecalho, "test_escrever_no_Cabecalho_Arquivo_compac", test_escrever_no_Cabecalho_Arquivo_compac);
    CU_add_test(pSuiteMontarArvore, "test_montar_arvore", test_montar_arvore);
    CU_add_test(pSuiteRemoveCabeca, "test_removeCabeca", test_removeCabeca);
    CU_add_test(pSuiteListFreq, "test_listFreq", test_listFreq);
    CU_add_test(pSuiteRecuperarByte, "test_recuperarByteDePonteiroVoid", test_recuperarByteDePonteiroVoid);
    CU_add_test(pSuiteCriarNo, "test_criarNo", test_criarNo);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
