#include "respostas_trabalho.h"

#include <stdio.h>
#include <math.h>
#include <float.h>

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

const size_t tam_dados_observados = sizeof(dados_funcoes) / sizeof(dados_funcoes[0]);
const size_t tam_modelos_funcoes = sizeof(modelos_funcao) / sizeof(modelos_funcao[0]);

// --- FUNÇÕES AUXILIARES ---

// Calcula o erro absoluto total de um modelo específico (usado na opção 4 e 5)
double calcular_total_abs(const int indice_modelo) {
    double total = 0.0;
    for (size_t i = 0; i < tam_dados_observados; i++) {
        const double val = modelos_funcao[indice_modelo](dados_funcoes[i].t);
        total += fabs(dados_funcoes[i].Nt - val);
    }
    return total;
}

// Opção 1: Mostra apenas os valores calculados
void exibir_valores_calculados() {
    printf("\n--- COMPARACAO DE VALORES (f_i(t)) ---\n");
    printf("%-5s | %-8s", "t", "N(t)");
    for(size_t m=0; m< tam_modelos_funcoes; m++) printf(" | f%zu(t)   ", m+1);
    printf("\n------+----------");
    for(size_t m=0; m< tam_modelos_funcoes; m++) printf("+----------");
    printf("\n");

    for (size_t i = 0; i < tam_dados_observados; i++) {
        printf("%5d | %8.2f", dados_funcoes[i].t, dados_funcoes[i].Nt);
        for (size_t m = 0; m < tam_modelos_funcoes; m++) {
            printf(" | %8.2f", modelos_funcao[m](dados_funcoes[i].t));
        }
        printf("\n");
    }
}

// Opção 2 e 3: Função genérica para exibir erros (Evita duplicar código)
void exibir_tabela_erros(const tipo_erro erro_atual) {
    char *titulo = (erro_atual == ERRO_ABSOLUTO) ? "ERRO ABSOLUTO |N(t) - f(t)|" : "ERRO RELATIVO (%)";

    printf("\n--- %s ---\n", titulo);
    printf("%-5s", "t");
    for(size_t m=0; m< tam_modelos_funcoes; m++) printf(" | Err f%zu  ", m+1);
    printf("\n------+");
    for(size_t m=0; m< tam_modelos_funcoes; m++) printf("----------+");
    printf("\n");

    for (size_t i = 0; i < tam_dados_observados; i++) {
        printf("%5d", dados_funcoes[i].t);
        for (size_t m = 0; m < tam_modelos_funcoes; m++) {
            const double val = modelos_funcao[m](dados_funcoes[i].t);
            const double abs = fabs(dados_funcoes[i].Nt - val);
            const double erro = (erro_atual == ERRO_ABSOLUTO) ? abs : (abs / dados_funcoes[i].Nt * 100.0);

            if(erro_atual == 0) printf(" | %8.4f", erro);
            else          printf(" | %7.2f%%", erro);
        }
        printf("\n");
    }
}

// Opção 4: Totais
void exibir_totais() {
    printf("\n--- TOTAIS ACUMULADOS ---\n");
    printf("%-10s | %-15s | %-15s\n", "Funcao", "Total Abs.", "Total Rel.");
    printf("-----------+-----------------+-----------------\n");

    for (size_t m = 0; m < tam_modelos_funcoes; m++) {
        double tot_abs = 0, tot_rel = 0;
        for (size_t i = 0; i < tam_dados_observados; i++) {
            double val = modelos_funcao[m](dados_funcoes[i].t);
            double diff = fabs(dados_funcoes[i].Nt - val);
            tot_abs += diff;
            tot_rel += (diff / dados_funcoes[i].Nt * 100.0);
        }
        printf("f%zu(t)     | %15.4f | %14.2f%%\n", m+1, tot_abs, tot_rel);
    }
}

// Opção 5: Conclusão
void exibir_melhor_aproximacao() {
    int melhor_id = -1;
    double menor_erro = DBL_MAX;
    for (size_t m = 0; m < tam_modelos_funcoes; m++) {
        const double erro_atual = calcular_total_abs((int)m); // Reusa a função auxiliar
        if (erro_atual < menor_erro) {
            menor_erro = erro_atual;
            melhor_id = (int) m + 1;
        }
    }
    printf("\n=== CONCLUSAO ===\n");
    printf("A melhor aproximacao e a FUNCAO f%d(t)\n", melhor_id);
    printf("Erro Total Absoluto: %.4f\n", menor_erro);
}