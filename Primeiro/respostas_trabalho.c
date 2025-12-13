#include "respostas_trabalho.h"
#include "matrizes.h"

#include <stdio.h>
#include <math.h>
#include <float.h>

#define TRY(func) \
if ((status = (func)) != MAT_SUCESSO) goto matriz_cleanup

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

// opção 1: mostra apenas os valores calculados
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

// opção 2 e 3: função genérica para exibir erros (usa-se um enum para não ter DRY)
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

// opção 4: totais
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

// opção 5: conclusão
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

void primeiro_ex() {
    printf("--- EXPLICITANDO f₂(x) ---\n\n");
    printf("Como visto no PDF, o valor da variável c ficou 0,0410468, portanto:\n");
    printf("f₂(x): 0,0410468(x - 3)² + 19,8\n");
}

matriz_resultado segundo_ex() {
    printf("--- EXPLICITANDO Xᵀ EM f₃(x) ---\n\n");
    matriz_resultado status = MAT_SUCESSO;
    matriz matX, matXT;
    INIT_ALL(&matX, &matXT);
    TRY (criar_matriz(&matX, 5, 2));
    TRY (vetor_para_matriz(&matX, (double[]) {
        9, 3,
        36, 6,
        81, 9,
        144, 12,
        225, 15,
    }, 10));
    TRY (criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas));
    TRY (transpor_matriz(&matXT, &matX));
    printf("A transposta de X em f₃(x) fica:\n");
    TRY (imprimir_mat_formatada(&matXT));

    matriz_cleanup:
        FREE_ALL(&matX, &matXT);
        return status;
}

matriz_resultado terceiro_ex() {
    printf("--- EXPLICANDO O VALOR DE β E A FUNÇÃO f₃(x) ---\n\n");
    matriz matX, matY, matB;
    matriz_resultado status = MAT_SUCESSO;
    INIT_ALL(&matX, &matY, &matB);
    TRY (criar_matriz(&matX, 5, 2));
    TRY (vetor_para_matriz(&matX, (double[]) {
        9, 3,
        36, 6,
        81, 9,
        144, 12,
        225, 15,
    }, 10));
    TRY (criar_matriz(&matY, 5, 1));
    TRY (vetor_para_matriz(&matY, (double[]) {
    -1.7,
    -1.5,
    0.7,
    3.3,
    4.3
    }, 5));
    TRY (criar_matriz(&matB, matX.mat_colunas, matY.mat_colunas));
    TRY (calcular_min_quad(&matB, &matX, &matY));
    printf("Essa é a matriz que representa o valor de β:\n");
    TRY (imprimir_mat_formatada(&matB));
    FREE_ALL(&matX, &matY, &matB);
    printf("Logo, essa é a f₃(x) agora com os coeficientes encontrados:\n");
    printf("f₃(x): 0,0523x² - 0,4479x + 21,5");
    matriz_cleanup:
        FREE_ALL(&matX, &matY, &matB);
        return status;
}

matriz_resultado quarto_ex() {
    printf("--- EXPLICITANDO Xᵀ EM f₄(x) ---\n\n");
    matriz_resultado status = MAT_SUCESSO;
    matriz matX, matXT;
    INIT_ALL(&matX, &matXT);
    TRY (criar_matriz(&matX, 6, 3));
    TRY (vetor_para_matriz(&matX, (double[]) {
        0, 0, 1,
        9, 3, 1,
        36, 6, 1,
        81, 9, 1,
        144, 12, 1,
        225, 15, 1
    }, 18));
    TRY (criar_matriz(&matXT, matX.mat_colunas, matX.mat_linhas));
    TRY (transpor_matriz(&matXT, &matX));
    printf("A transposta de X em f₄(x) fica:\n");
    TRY (imprimir_mat_formatada(&matXT));

    matriz_cleanup:
        FREE_ALL(&matX, &matXT);
        return status;
}

matriz_resultado quinto_ex() {
    printf("--- EXPLICANDO O VALOR DE β E A FUNÇÃO f₄(x) ---\n\n");
    matriz matX, matY, matB;
    matriz_resultado status = MAT_SUCESSO;
    INIT_ALL(&matX, &matY, &matB);
    TRY (criar_matriz(&matX, 6, 3));
    TRY (vetor_para_matriz(&matX, (double[]) {
        0, 0, 1,
        9, 3, 1,
        36, 6, 1,
        81, 9, 1,
        144, 12, 1,
        225, 15, 1
    }, 18));
    TRY (criar_matriz(&matY, 6, 1));
    TRY (vetor_para_matriz(&matY, (double[]) {
        21.5,
        19.8,
        20.0,
        22.2,
        24.8,
        25.8
    }, 6));
    TRY (criar_matriz(&matB, matX.mat_colunas, matY.mat_colunas));
    TRY (calcular_min_quad(&matB, &matX, &matY));
    printf("Essa é a matriz que representa o valor de β:\n");
    TRY (imprimir_mat_formatada(&matB));
    FREE_ALL(&matX, &matY, &matB);
    printf("Logo, essa é a f₄(x) agora com os coeficientes encontrados:\n");
    printf("f₃(x): 0,0458x² - 0,3189x + 20,9607");
    matriz_cleanup:
        FREE_ALL(&matX, &matY, &matB);
        return status;
}

#undef TRY