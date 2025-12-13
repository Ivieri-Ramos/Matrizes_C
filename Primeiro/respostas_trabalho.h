#ifndef ALGEBRALINEAR_CALCULAR_DIFERENCA_H
#define ALGEBRALINEAR_CALCULAR_DIFERENCA_H

#include "funcoes_mat.h"

typedef struct dados_observados {
    int t;
    double Nt;
} dados_observados;

typedef enum tipo_erro {
    ERRO_ABSOLUTO = 0, //quando for calcular o erro absoluto das funções
    ERRO_RELATIVO, //quando for calcular o erro relativo
} tipo_erro;

void exibir_melhor_aproximacao();
void exibir_totais();
void exibir_tabela_erros(tipo_erro erro_atual);
void exibir_valores_calculados();
double calcular_total_abs(int indice_modelo);
void primeiro_ex();
matriz_resultado segundo_ex();
matriz_resultado terceiro_ex();
matriz_resultado quarto_ex();
matriz_resultado quinto_ex();

#endif //ALGEBRALINEAR_CALCULAR_DIFERENCA_H