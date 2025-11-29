#include "matrizes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define INTERVALO_ZERO 1e-9 //isso e para que quando for 0,0000000001 ele valide corretamente

void imprimir_mat(const matriz *matriz_imprimir) {
    if (matriz_imprimir -> dados == NULL) return;
    for (size_t i = 0; i < matriz_imprimir -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_imprimir -> mat_colunas; j++) {
            printf("%.4lf ", matriz_imprimir -> dados[i][j]);
        }
        printf("\n");
    }
}

void matriz_init(matriz *matriz) {
    matriz -> mat_linhas = 0;
    matriz -> mat_colunas = 0;
    matriz -> dados = NULL;
}

matriz_resultado criar_matriz(matriz *matriz, const size_t linhas, const size_t colunas) {
    if (linhas == 0 || colunas == 0) return MAT_ERRO_PARAMETRO_INVALIDO;
    matriz_init(matriz);
    matriz -> dados = (double **) malloc(sizeof(int *) * linhas);
    if (matriz -> dados == NULL) {
        return MAT_ERRO_ALOCACAO;
    }
    double *dados_ligados = (double *) malloc(sizeof(double) * linhas * colunas);
    if (dados_ligados == NULL) {
        free(matriz -> dados);
        matriz -> dados = NULL;
        return MAT_ERRO_ALOCACAO;
    }
    for (size_t i = 0; i < linhas; i++) {
        matriz -> dados[i] = dados_ligados + (i * colunas);
    }
    matriz -> mat_colunas = colunas;
    matriz -> mat_linhas = linhas;
    return MAT_SUCESSO;
}

void preencher_matriz(matriz *matriz_preencher) {
    for (size_t i = 0; i < matriz_preencher -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_preencher -> mat_colunas; j++) {
            matriz_preencher -> dados[i][j] = rand() % 50;
        }
    }
}

void free_matriz(matriz *matriz) {
    free(matriz -> dados[0]);
    free(matriz -> dados);
    matriz -> dados = NULL;
}

matriz_resultado soma_matriz(matriz *matriz_destino, const matriz *matriz_s1, const matriz *matriz_s2) {
    if (matriz_destino -> dados == NULL || matriz_s1 -> dados == NULL || matriz_s2 -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_destino -> mat_colunas != matriz_s1 -> mat_colunas ||
        matriz_destino -> mat_colunas != matriz_s2 -> mat_colunas ||
        matriz_destino -> mat_linhas != matriz_s1 -> mat_linhas ||
        matriz_destino -> mat_linhas != matriz_s2 -> mat_linhas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }

    const size_t total_somas = matriz_destino -> mat_linhas * matriz_destino -> mat_colunas;
    double *dados_dest = matriz_destino -> dados[0];
    const double *dados_s1 = matriz_s1 -> dados[0];
    const double *dados_s2 = matriz_s2 -> dados[0];
    for (size_t i = 0; i < total_somas; i++) {
        dados_dest[i] = dados_s1[i] + dados_s2[i];
    }
    return MAT_SUCESSO;
}

matriz_resultado multiplicar_matriz(matriz *matriz_destino, const matriz *matriz_m1, const matriz *matriz_m2) {
    if (matriz_destino -> dados == NULL || matriz_m1 -> dados == NULL || matriz_m2 -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_destino -> mat_linhas != matriz_m1 -> mat_linhas ||
        matriz_destino -> mat_colunas != matriz_m2 -> mat_colunas ||
        matriz_m1 -> mat_colunas !=  matriz_m2 -> mat_linhas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }
    if (matriz_destino -> dados == matriz_m1 -> dados ||
        matriz_destino -> dados == matriz_m2 -> dados) {
        return MAT_ERRO_OVERLAP;
    }
    const size_t tamanho_memoria_dest = matriz_destino -> mat_linhas * matriz_destino -> mat_colunas * sizeof(double);
    memset(matriz_destino -> dados[0], 0, tamanho_memoria_dest);
    for (size_t i = 0; i < matriz_m1 -> mat_linhas; i++) {
        for (size_t k = 0; k < matriz_m1 -> mat_colunas; k++) {
            const double valor_m1 = matriz_m1 -> dados[i][k];
            for (size_t j = 0; j < matriz_m2 -> mat_colunas; j++) {
                matriz_destino -> dados[i][j] += valor_m1 * matriz_m2 -> dados[k][j];
            }
        }
    }
    return MAT_SUCESSO;
}

matriz_resultado transpor_matriz(matriz *matriz_dest, const matriz *matriz_org) {
    if (matriz_dest -> dados == NULL || matriz_org -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_dest -> dados == matriz_org -> dados) {
        return MAT_ERRO_OVERLAP;
    }
    if (matriz_dest -> mat_linhas != matriz_org -> mat_colunas ||
        matriz_dest -> mat_colunas != matriz_org -> mat_linhas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }

    for (size_t i = 0; i < matriz_org -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_org -> mat_colunas; j++) {
            matriz_dest -> dados[j][i] = matriz_org -> dados[i][j];
        }
    }

    return MAT_SUCESSO;
}

matriz_resultado is_identidade(const matriz *matriz_teste) {
    if (matriz_teste -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_teste -> mat_linhas != matriz_teste -> mat_colunas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }

    for (size_t i = 0; i < matriz_teste -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_teste -> mat_colunas; j++) {
            if (j == i) {
                if (matriz_teste -> dados[i][j] != 1) {
                    return MAT_NAO_IDENTIDADE;
                }
            }
            else {
                if (matriz_teste -> dados[i][j] != 0) {
                    return MAT_NAO_IDENTIDADE;
                }
            }
        }
    }
    return MAT_SUCESSO;
}

matriz_resultado set_identidade(matriz *matriz_identidade) {
    if (matriz_identidade -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_identidade -> mat_linhas != matriz_identidade -> mat_colunas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }
    for (size_t i = 0; i < matriz_identidade -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_identidade -> mat_colunas; j++) {
            matriz_identidade -> dados[i][j] = (i == j) ? 1 : 0;
        }
    }
    return MAT_SUCESSO;
}

matriz_resultado criar_inversa(matriz *matriz_destino, const matriz *matriz_original) {
    if (matriz_destino -> dados == NULL || matriz_original -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_destino -> mat_linhas != matriz_destino -> mat_colunas ||
        matriz_original -> mat_linhas != matriz_original -> mat_colunas ||
        matriz_destino -> mat_linhas != matriz_original -> mat_linhas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }
    const size_t tamanho_max = matriz_destino -> mat_linhas;
    matriz matriz_clone;
    criar_matriz(&matriz_clone, tamanho_max, tamanho_max);
    copiar_matrizes(&matriz_clone, matriz_original);
    set_identidade(matriz_destino);
    for (size_t k = 0; k < tamanho_max; k++) {
        if (fabs(matriz_clone.dados[k][k]) < INTERVALO_ZERO) {
            bool trocou = false;
            for (size_t j = k + 1; j < tamanho_max; j++) {
                if (fabs(matriz_clone.dados[j][k]) > INTERVALO_ZERO) {
                    for (size_t i = 0; i < tamanho_max; i++) {
                        const double temp_orig = matriz_clone.dados[k][i];
                        matriz_clone.dados[k][i] = matriz_clone.dados[j][i];
                        matriz_clone.dados[j][i] = temp_orig;
                        const double temp_dest = matriz_destino -> dados[k][i];
                        matriz_destino -> dados[k][i] = matriz_destino -> dados[j][i];
                        matriz_destino -> dados[j][i] = temp_dest;
                    }
                    trocou = true;
                    break;
                }
            }
            if (!trocou) {
                free_matriz(&matriz_clone);
                return MAT_SINGULAR;
            }
        }
        const double div = matriz_clone.dados[k][k];
        for (size_t i = 0; i < tamanho_max; i++) {
            matriz_clone.dados[k][i] /= div;
            matriz_destino -> dados[k][i] /= div;
        }
        for (size_t i = 0; i < tamanho_max; i++) {
            if (i == k) continue;
            const double fator = matriz_clone.dados[i][k];
            if (fabs(fator) < INTERVALO_ZERO) continue;
            for (size_t j = 0; j < tamanho_max; j++) {
                matriz_clone.dados[i][j] -= fator * matriz_clone.dados[k][j];
                matriz_destino -> dados[i][j] -= fator * matriz_destino -> dados[k][j];
            }
        }
    }
    matriz_fix_zero(matriz_destino);
    free_matriz(&matriz_clone);
    return MAT_SUCESSO;
}

matriz_resultado copiar_matrizes(matriz *matriz_destino, const matriz *matriz_original) {
    if (matriz_destino -> dados == NULL || matriz_original -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    if (matriz_destino -> mat_linhas != matriz_original -> mat_linhas ||
        matriz_destino -> mat_colunas != matriz_original -> mat_colunas) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }
    const size_t total_op = matriz_destino -> mat_linhas * matriz_destino -> mat_colunas;
    double *dest = matriz_destino -> dados[0];
    const double *orig = matriz_original -> dados[0];
    memcpy(dest, orig, total_op * sizeof(double));
    return MAT_SUCESSO;
}

matriz_resultado matriz_fix_zero(matriz *matriz_orig) {
    if (matriz_orig -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    const size_t total_op = matriz_orig -> mat_linhas * matriz_orig -> mat_colunas;
    double *dest = matriz_orig -> dados[0];
    for (size_t i = 0; i < total_op; i++) {
        if (fabs(dest[i]) < INTERVALO_ZERO) {
            dest[i] = 0.0;
        }
    }
    return MAT_SUCESSO;
}

matriz_resultado vetor_para_matriz(matriz *matriz_dest, const double *vetor, const size_t tam_vetor) {
    if (matriz_dest -> dados == NULL || vetor == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    const size_t tam_matriz = matriz_dest -> mat_linhas * matriz_dest -> mat_colunas;
    if (tam_vetor != tam_matriz) {
        return MAT_ERRO_DIMENSAO_INCOMPATIVEL;
    }
    memcpy(matriz_dest -> dados[0], vetor, tam_vetor * sizeof(double));
    return MAT_SUCESSO;
}