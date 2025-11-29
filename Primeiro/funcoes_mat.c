#include <math.h>
#include <stdio.h>

#include "matrizes.h"

void funcao_4() {
    matriz matX;
    criar_matriz(&matX, 6, 3);
    vetor_para_matriz(&matX, (double[]){
        0, 0, 1,
        9, 3, 1,
        36, 6, 1,
        81, 9, 1,
        144, 12, 1,
        225, 15, 1
    }, 18);
    matriz matB;
    criar_matriz(&matB, 3, 1);
    /*
     vetor_para_matriz(&matB, (double[]){
        1,
        1,
        1
    }, 3);
    */
    matriz matY;
    criar_matriz(&matY, 6, 1);
    vetor_para_matriz(&matY, (double[]){
    21.5,
    19.8,
    20.0,
    22.2,
    24.8,
    25.8}, 6);

    matriz matXT;
    criar_matriz(&matXT, 3, 6);
    transpor_matriz(&matXT, &matX);
    matriz mat_primeira_multiplicacao;
    criar_matriz(&mat_primeira_multiplicacao, 3, 3);
    multiplicar_matriz(&mat_primeira_multiplicacao, &matXT, &matX);

    matriz mat_resultado_inversa;

    criar_matriz(&mat_resultado_inversa, 3, 3);

    criar_inversa(&mat_resultado_inversa, &mat_primeira_multiplicacao);

    matriz mat_segunda_multiplicacao;
    criar_matriz(&mat_segunda_multiplicacao, 3, 1);

    multiplicar_matriz(&mat_segunda_multiplicacao, &matXT, &matY);

    multiplicar_matriz(&matB, &mat_resultado_inversa, &mat_segunda_multiplicacao);

    imprimir_mat(&matB);

    free_matriz(&matX);
    free_matriz(&matY);
    free_matriz(&matXT);
    free_matriz(&mat_primeira_multiplicacao);
    free_matriz(&matB);
    free_matriz(&mat_segunda_multiplicacao);
}

void funcao_2() {
    #define VALOR_C 0.0410468

    int x = 0;

    for (size_t i = 0; i < 6; i++, x += 3) {
        printf("%.2lf\n", VALOR_C * pow(x - 3, 2) + 19.8);
    }
}

void funcao_3() {
    matriz matX;
    criar_matriz(&matX, 5, 2);
    vetor_para_matriz(&matX, (double[]){
        9, 3,
        36, 6,
        81, 9,
        144, 12,
        225, 15
    }, 10);
    matriz matY;
    criar_matriz(&matY, 5, 1);
    vetor_para_matriz(&matY, (double[]){
        -1.7,
        -1.5,
        0.7,
        3.3,
        4.3
    }, 5);
    matriz matXT;
    criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas);
    transpor_matriz(&matXT, &matX);
    matriz mat_primeira_multiplicacao;
    criar_matriz(&mat_primeira_multiplicacao, matXT.mat_linhas, matX.mat_colunas);
    multiplicar_matriz(&mat_primeira_multiplicacao, &matXT, &matX);
    matriz mat_resultado_inversa;
    criar_matriz(&mat_resultado_inversa, mat_primeira_multiplicacao.mat_linhas, mat_primeira_multiplicacao.mat_colunas);
    criar_inversa(&mat_resultado_inversa, &mat_primeira_multiplicacao);
    free_matriz(&mat_primeira_multiplicacao);

    matriz mat_segunda_multiplicacao;
    criar_matriz(&mat_segunda_multiplicacao, mat_resultado_inversa.mat_linhas, matXT.mat_colunas);
    multiplicar_matriz(&mat_segunda_multiplicacao, &mat_resultado_inversa, &matXT);
    free_matriz(&matXT);
    free_matriz(&mat_resultado_inversa);
    matriz matB;
    criar_matriz(&matB, mat_segunda_multiplicacao.mat_linhas, matY.mat_colunas);
    multiplicar_matriz(&matB, &mat_segunda_multiplicacao, &matY);
    imprimir_mat(&matB);
    free_matriz(&matY);
    free_matriz(&mat_segunda_multiplicacao);
    free_matriz(&matX);
    free_matriz(&matB);
}