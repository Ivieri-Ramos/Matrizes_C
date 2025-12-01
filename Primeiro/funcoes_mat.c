#include <math.h>
#include <stdio.h>

#include "matrizes.h"

//função_4 é a f4(x)
matriz_resultado funcao_4() {
    matriz matX, matY, matXT, matXtX, matXtX_inv, matXtY, matB;
    INIT_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
    matriz_resultado status = MAT_SUCESSO;
    if ((status = criar_matriz(&matX, 6, 3)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = vetor_para_matriz(&matX, (double[]){
     /* x² + bx + c */
        0, 0, 1,
        9, 3, 1,
        36, 6, 1,
        81, 9, 1,
        144, 12, 1,
        225, 15, 1
    }, 18)) != MAT_SUCESSO) goto matriz_cleanup;
    //aqui foi criada a matriz X, que contém a função quadrática ax² + bx + c
    if ((status = criar_matriz(&matY, 6, 1)) != MAT_SUCESSO) goto matriz_cleanup; //esses números "mágicos" representam o tamanho dela no exercício
    if ((status = vetor_para_matriz(&matY, (double[]){
    21.5,
    19.8,
    20.0,
    22.2,
    24.8,
    25.8}, 6)) != MAT_SUCESSO) goto matriz_cleanup;
    //aqui foi criada a matriz Y, que contém o resultado de f(x)
    if ((status = criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = transpor_matriz(&matXT, &matX)) != MAT_SUCESSO) goto matriz_cleanup;
    //aqui foi criado a matriz XT, ou seja, a transposta de X
    if ((status = criar_matriz(&matXtX, matXT.mat_linhas, matX.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matXtX, &matXT, &matX)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matX);
    //aqui foi criado o resultado de XT vezes X, ou seja, criamos uma matriz 3x3
    if ((status = criar_matriz(&matXtX_inv, matXtX.mat_linhas, matXtX.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = criar_inversa(&matXtX_inv, &matXtX)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matXtX);
    //aqui foi criado a inversa de XT vezes X, ou seja, a primeira_multiplicacao
    if ((status = criar_matriz(&matXtY, matXT.mat_linhas, matY.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matXtY, &matXT, &matY)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matXT);
    //aqui foi criado o resultada da transposta de X vezes a matriz Y
    if ((status = criar_matriz(&matB, matXtX_inv.mat_linhas, matXtY.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matB, &matXtX_inv, &matXtY)) != MAT_SUCESSO) goto matriz_cleanup;
    //e por fim encontramos a matriz B usando o resultado da inversa vezes a multiplicação que acabamos de encontrar
    if ((status = imprimir_mat(&matB)) != MAT_SUCESSO) goto matriz_cleanup;
    //imprimimos o resultado e então damos free no resto
    /*
     * note que durante o processo, sempre devemos criar a matriz antes
     * e delimitamos suas linhas e colunas, esse mesmo processo é executado também
     * em f3(x), só que de uma forma mais simples, já que temos menos valores,
     */
    matriz_cleanup:
        FREE_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
        return status;
}

void funcao_2() {
    #define VALOR_C 0.0410468

    int x = 0;
    //essa função é só aplicando f2(x)
    for (size_t i = 0; i < 6; i++, x += 3) {
        printf("%.2lf\n", VALOR_C * pow(x - 3, 2) + 19.8);
    }
}

matriz_resultado funcao_3() {
    /*
     * a função f3(x) funciona exatamente igual a como foi explicado na
     * função 4, entretanto, nos apenas usamos menos variáveis
     */
    matriz matX, matY, matXT, matXtX, matXtX_inv, matXtY, matB;
    INIT_ALL(&matX, &matY, &matXT, &matXtX, &matXtX_inv, &matXtY, &matB);
    matriz_resultado status = MAT_SUCESSO;
    if ((status = criar_matriz(&matX, 5, 2)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = vetor_para_matriz(&matX, (double[]){
     /* x² + bx */
        9, 3,
        36, 6,
        81, 9,
        144, 12,
        225, 15
    }, 10)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = criar_matriz(&matY, 5, 1)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = vetor_para_matriz(&matY, (double[]){
        -1.7,
        -1.5,
        0.7,
        3.3,
        4.3
    }, 5)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = transpor_matriz(&matXT, &matX)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = criar_matriz(&matXtX, matXT.mat_linhas, matX.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matXtX, &matXT, &matX)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matX);
    if ((status = criar_matriz(&matXtX_inv, matXtX.mat_linhas, matXtX.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = criar_inversa(&matXtX_inv, &matXtX)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matXtX);

    if ((status = criar_matriz(&matXtY, matXT.mat_linhas, matY.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matXtY, &matXT, &matY)) != MAT_SUCESSO) goto matriz_cleanup;
    free_matriz(&matXT);
    free_matriz(&matY);
    if ((status = criar_matriz(&matB, matXtX_inv.mat_linhas, matXtY.mat_colunas)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = multiplicar_matriz(&matB, &matXtX_inv, &matXtY)) != MAT_SUCESSO) goto matriz_cleanup;
    if ((status = imprimir_mat(&matB)) != MAT_SUCESSO) goto matriz_cleanup;
    matriz_cleanup:
        FREE_ALL(&matX, &matXT, &matY, &matXtX, &matXtX_inv, &matXtY, &matB);
        return status;
}