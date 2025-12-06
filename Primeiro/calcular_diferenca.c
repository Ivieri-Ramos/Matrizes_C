#include "calcular_diferenca.h"

#include <stdio.h>
#include <math.h>

const dados_observados dados_funcoes[] = {
    0, 21.5,
    3, 19.8,
    6, 20.0,
    9, 22.2,
    12, 24.8,
    15, 25.8,
};

const funcao_modelo modelos_funcao[] = {
    funcao_1,
    funcao_2,
    funcao_3,
    funcao_4,
};

void calcular_erro_absoluto() {
    const size_t tam_dados_observados = sizeof(dados_funcoes) / sizeof(dados_funcoes[0]);
    const size_t tam_modelos_funcoes = sizeof(modelos_funcao) / sizeof(modelos_funcao[0]);

    typedef struct diferenca_absoluta {
        int nmr_funcao;
        double valor_abs;
    } diferenca_absoluta;

    diferenca_absoluta dif_absoluta[tam_dados_observados];
    for (size_t i = 0; i < tam_dados_observados; i++) {
        dif_absoluta[i].nmr_funcao = 0;
    }
    double menor_diferenca[tam_dados_observados];
    for (size_t i = 0; i < tam_dados_observados; i++) {
        for (size_t j = 0; j < tam_modelos_funcoes; j++) {
            const funcao_modelo funcao_atual = modelos_funcao[j];
            const double diferenca_calculada = fabs(dados_funcoes[i].Nt - funcao_atual(dados_funcoes[i].t));
            if (j == 0) {
                dif_absoluta[i].valor_abs = diferenca_calculada;
                dif_absoluta[i].nmr_funcao = j + 1;
            }
            else if (dif_absoluta[i].valor_abs > diferenca_calculada) {
                dif_absoluta[i].valor_abs = diferenca_calculada;
                dif_absoluta[i].nmr_funcao = j + 1;
            }
        }
    }
    for (size_t i = 0; i < tam_dados_observados; i++) {
        printf("%.2lf\n", dif_absoluta[i].valor_abs);
        printf("funcao: %d\n", dif_absoluta[i].nmr_funcao);
    }
}