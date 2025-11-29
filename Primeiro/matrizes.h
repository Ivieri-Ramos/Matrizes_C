#ifndef ALGEBRALINEAR_MATRIZES_H
#define ALGEBRALINEAR_MATRIZES_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    MAT_SUCESSO = 0,            // Tudo correu bem
    MAT_ERRO_ALOCACAO,          // Falha no malloc
    MAT_ERRO_PONTEIRO_NULO,     // Passaram NULL onde não devia
    MAT_ERRO_DIMENSAO_INCOMPATIVEL, // Tentar somar 3x3 com 4x4
    MAT_ERRO_PARAMETRO_INVALIDO, // Ex: linhas ou colunas iguais a 0
    MAT_ERRO_OVERLAP, //Não pode usar o destino igual ao operandos
    MAT_NAO_IDENTIDADE, //quando a matriz nao for a identidade
    MAT_SINGULAR, //se a matriz nao possuir inversa
} matriz_resultado;

typedef struct matriz {
    size_t mat_linhas;
    size_t mat_colunas;
    double **dados;
} matriz;

void imprimir_mat(const matriz *matriz_imprimir);
void matriz_init(matriz *matriz);
void preencher_matriz(matriz *matriz_preencher);
void free_matriz(matriz *matriz);
matriz_resultado criar_matriz(matriz *matriz, size_t linhas, size_t colunas);
matriz_resultado soma_matriz(matriz *matriz_destino, const matriz *matriz_s1, const matriz *matriz_s2);
matriz_resultado multiplicar_matriz(matriz *matriz_destino, const matriz *matriz_m1, const matriz *matriz_m2);
matriz_resultado transpor_matriz(matriz *matriz_dest, const matriz *matriz_org);
matriz_resultado is_identidade(const matriz *matriz_teste);
matriz_resultado set_identidade(matriz *matriz_identidade);
matriz_resultado copiar_matrizes(matriz *matriz_destino, const matriz *matriz_original);
matriz_resultado criar_inversa(matriz *matriz_destino, const matriz *matriz_original);
matriz_resultado matriz_fix_zero(matriz *matriz_orig);
matriz_resultado vetor_para_matriz(matriz *matriz_dest, const double *vetor, size_t tam_vetor);

void funcao_2();
void funcao_3();

#endif //ALGEBRALINEAR_MATRIZES_H