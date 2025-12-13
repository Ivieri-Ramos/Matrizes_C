#include <math.h>
#include <stdio.h>

#include "matrizes.h"

#define TRY(func) \
if ((status = (func)) != MAT_SUCESSO) goto matriz_cleanup

//função_4 é a f4(x)
matriz_resultado descobrir_f4() {
    matriz matX, matY, matXT, matXtX, matXtX_inv, matXtY, matB;
    INIT_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
    matriz_resultado status = MAT_SUCESSO;
    TRY (criar_matriz(&matX, 6, 3));
    TRY (vetor_para_matriz(&matX, (double[]){
     /* x² + bx + c */
        0, 0, 1,
        9, 3, 1,
        36, 6, 1,
        81, 9, 1,
        144, 12, 1,
        225, 15, 1
    }, 18));
    //aqui foi criada a matriz X, que contém a função quadrática ax² + bx + c
    TRY (criar_matriz(&matY, 6, 1)); //esses números "mágicos" representam o tamanho dela no exercício
    TRY (vetor_para_matriz(&matY, (double[]){
    21.5,
    19.8,
    20.0,
    22.2,
    24.8,
    25.8}, 6));
    //aqui foi criada a matriz Y, que contém o resultado de f(x)
    TRY (criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas));
    TRY (transpor_matriz(&matXT, &matX));
    //aqui foi criado a matriz XT, ou seja, a transposta de X
    TRY (criar_matriz(&matXtX, matXT.mat_linhas, matX.mat_colunas));
    TRY (multiplicar_matriz(&matXtX, &matXT, &matX));
    free_matriz(&matX);
    //aqui foi criado o resultado de XT vezes X, ou seja, criamos uma matriz 3x3
    TRY (criar_matriz(&matXtX_inv, matXtX.mat_linhas, matXtX.mat_colunas));
    TRY (criar_inversa(&matXtX_inv, &matXtX));
    free_matriz(&matXtX);
    //aqui foi criado a inversa de XT vezes X, ou seja, a primeira_multiplicacao
    TRY (criar_matriz(&matXtY, matXT.mat_linhas, matY.mat_colunas));
    TRY (multiplicar_matriz(&matXtY, &matXT, &matY));
    free_matriz(&matXT);
    //aqui foi criado o resultada da transposta de X vezes a matriz Y
    TRY (criar_matriz(&matB, matXtX_inv.mat_linhas, matXtY.mat_colunas));
    TRY (multiplicar_matriz(&matB, &matXtX_inv, &matXtY));
    //e por fim encontramos a matriz B usando o resultado da inversa vezes a multiplicação que acabamos de encontrar
    TRY (imprimir_mat_formatada(&matB)); //imprimimos o resultado e então damos free no resto
    /*
     * note que durante o processo, sempre devemos criar a matriz antes
     * e delimitarmos as suas linhas e colunas, esse mesmo processo é executado também
     * em f3(x), só que de uma forma mais simples, já que temos menos variáveis
     */
    matriz_cleanup:
        FREE_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
        return status;
}

matriz_resultado descobrir_f3() {
    /*
     * a função f3(x) funciona exatamente igual a como foi explicado na
     * função 4, entretanto, nos apenas usamos menos variáveis
     */
    matriz matX, matY, matXT, matXtX, matXtX_inv, matXtY, matB;
    INIT_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
    matriz_resultado status = MAT_SUCESSO;
    TRY (criar_matriz(&matX, 5, 2));
    TRY (vetor_para_matriz(&matX, (double[]){
     /* x² + bx */
        9, 3,
        36, 6,
        81, 9,
        144, 12,
        225, 15
    }, 10));
    TRY (criar_matriz(&matY, 5, 1));
    TRY (vetor_para_matriz(&matY, (double[]){
        -1.7,
        -1.5,
        0.7,
        3.3,
        4.3
    }, 5));
    TRY (criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas));
    TRY (transpor_matriz(&matXT, &matX));
    TRY (criar_matriz(&matXtX, matXT.mat_linhas, matX.mat_colunas));
    TRY (multiplicar_matriz(&matXtX, &matXT, &matX));
    free_matriz(&matX);
    TRY (criar_matriz(&matXtX_inv, matXtX.mat_linhas, matXtX.mat_colunas));
    TRY (criar_inversa(&matXtX_inv, &matXtX));
    free_matriz(&matXtX);
    TRY (criar_matriz(&matXtY, matXT.mat_linhas, matY.mat_colunas));
    TRY (multiplicar_matriz(&matXtY, &matXT, &matY));
    free_matriz(&matXT);
    free_matriz(&matY);
    TRY (criar_matriz(&matB, matXtX_inv.mat_linhas, matXtY.mat_colunas));
    TRY (multiplicar_matriz(&matB, &matXtX_inv, &matXtY));
    TRY (imprimir_mat_formatada(&matB));
    matriz_cleanup:
        FREE_ALL(&matX, &matXT, &matY, &matXtX, &matXtX_inv, &matXtY, &matB);
        return status;
}

double funcao_1(const double t) {return pow((t - 3), 2) + 19.8;}
double funcao_2(const double t) {return 0.0410468 * pow((t - 3), 2) + 19.8;}
double funcao_3(const double t) {return pow((0.052346 * t), 2) + (-0.447888 * t) + 21.5;}
double funcao_4(const double t) {return pow((0.045833 * t), 2) + (-0.318929 * t) + 20.960714;}

#undef TRY