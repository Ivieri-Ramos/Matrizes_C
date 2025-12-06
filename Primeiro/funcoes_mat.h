#ifndef ALGEBRALINEAR_FUNCOES_MAT_H
#define ALGEBRALINEAR_FUNCOES_MAT_H

#include "matrizes.h"

typedef double (*funcao_modelo)(double t);

matriz_resultado descobrir_f4();
matriz_resultado descobrir_f3();

double funcao_1(double t);
double funcao_2(double t);
double funcao_3(double t);
double funcao_4(double t);

#endif //ALGEBRALINEAR_FUNCOES_MAT_H