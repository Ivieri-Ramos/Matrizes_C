#ifndef ALGEBRALINEAR_CALCULAR_DIFERENCA_H
#define ALGEBRALINEAR_CALCULAR_DIFERENCA_H

#include "funcoes_mat.h"

typedef struct dados_observados {
    int t;
    double Nt;
} dados_observados;

void calcular_erro_absoluto();

#endif //ALGEBRALINEAR_CALCULAR_DIFERENCA_H