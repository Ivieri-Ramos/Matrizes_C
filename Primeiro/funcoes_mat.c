#include <math.h>
#include <stdio.h>

#include "matrizes.h"

//função_4 é a f4(x)
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
    //aqui foi criada a matriz X, que contém a função quadrática ax^2 + bx + c
    matriz matY;
    criar_matriz(&matY, 6, 1);
    vetor_para_matriz(&matY, (double[]){
    21.5,
    19.8,
    20.0,
    22.2,
    24.8,
    25.8}, 6);
    //aqui foi criada a matriz Y, que contém o resultado de f(x)
    matriz matXT;
    criar_matriz(&matXT, 3, 6);
    transpor_matriz(&matXT, &matX);
    //aqui foi criado a matriz XT, ou seja, a transposta de X
    matriz mat_primeira_multiplicacao;
    criar_matriz(&mat_primeira_multiplicacao, 3, 3);
    multiplicar_matriz(&mat_primeira_multiplicacao, &matXT, &matX);
    //aqui foi criado o resultado de XT vezes X, ou seja, criamos uma matriz 3x3
    matriz mat_resultado_inversa;
    criar_matriz(&mat_resultado_inversa, 3, 3);
    criar_inversa(&mat_resultado_inversa, &mat_primeira_multiplicacao);
    //aqui foi criado a inversa de XT vezes X, ou seja, a primeira_multiplicacao
    matriz mat_segunda_multiplicacao;
    criar_matriz(&mat_segunda_multiplicacao, 3, 1);
    multiplicar_matriz(&mat_segunda_multiplicacao, &matXT, &matY);
    //aqui foi criado o resultada da transposta de X vezes a matriz Y
    matriz matB;
    criar_matriz(&matB, 3, 1);
    multiplicar_matriz(&matB, &mat_resultado_inversa, &mat_segunda_multiplicacao);
    //e por fim encontramos a matriz B usando o resultado da inversa vezes a multiplicação que acabamos de encontrar
    imprimir_mat(&matB);
    //imprimimos o resultado e então damos free no resto
    free_matriz(&matX);
    free_matriz(&matY);
    free_matriz(&matXT);
    free_matriz(&mat_primeira_multiplicacao);
    free_matriz(&matB);
    free_matriz(&mat_segunda_multiplicacao);
    /*
     * note que durante o processo, sempre devemos criar a matriz antes
     * e delimitamos suas linhas e colunas, esse mesmo processo é executado também
     * em f3(x), só que de uma forma mais simples, já que temos menos valores,
     */
}

void funcao_2() {
    #define VALOR_C 0.0410468

    int x = 0;
    //essa função é só aplicando f2(x)
    for (size_t i = 0; i < 6; i++, x += 3) {
        printf("%.2lf\n", VALOR_C * pow(x - 3, 2) + 19.8);
    }
}

void funcao_3() {
    /*
     * a função f3(x) funciona exatamente igual a como foi explicado na
     * função 4, entretanto, nos apenas usamos menos variáveis
     */
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