#include "matrizes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>

#define LARGURA_NUMERO 10   // Espaço reservado para o valor numérico
#define CASAS_DECIMAIS 4    // Precisão
// Espaço total da célula = 1 (espaço esq) + LARGURA + 1 (espaço dir)
#define LARGURA_CELULA (1 + LARGURA_NUMERO + 1)
#define INTERVALO_ZERO 1e-9 //isso e para que quando for 0,0000000001 ele valide corretamente

#define IMPRIMIR_LINHA_DIVISORIA() { \
printf("     +"); \
for (size_t k = 0; k < colunas; k++) { \
for(int L=0; L < LARGURA_CELULA; L++) printf("-"); \
printf("+"); \
} \
printf("\n"); \
}

#define TRY(func) \
if ((status = (func)) != MAT_SUCESSO) goto matriz_cleanup

matriz_resultado imprimir_mat_formatada(const matriz *matriz_imprimir) {
    if (matriz_imprimir == NULL || matriz_imprimir->dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }

    size_t linhas = matriz_imprimir->mat_linhas;
    size_t colunas = matriz_imprimir->mat_colunas;

    printf("\n");

    // --- 1. CABEÇALHO DAS COLUNAS (Índices Centralizados) ---
    // Margem esquerda para alinhar com a coluna de índices de linha
    // " 001 |" ocupa 6 caracteres (espaço + 3 digitos + espaço + pipe)
    printf("      ");

    char buffer_indice[20]; // Buffer temporário para converter o número em texto

    for (size_t j = 0; j < colunas; j++) {
        // Converte o índice para string para saber o tamanho exato (ex: "1" tem len 1, "10" tem len 2)
        sprintf(buffer_indice, "%zu", j + 1);
        const size_t len = strlen(buffer_indice);

        // Matemática da centralização
        const int espaco_livre = LARGURA_CELULA - len;
        const int pad_esq = espaco_livre / 2;
        const int pad_dir = espaco_livre - pad_esq;

        // Imprime: Espaços Esq + Indice + Espaços Dir + Espaço separador visual
        // O último espaço é para alinhar com o pipe '|' da linha de baixo
        printf("%*s%s%*s ", pad_esq, "", buffer_indice, pad_dir, "");
    }
    printf("\n");

    IMPRIMIR_LINHA_DIVISORIA(); // Topo da tabela

    // --- 2. CORPO DA MATRIZ ---
    for (size_t i = 0; i < linhas; i++) {

        // Índice da Linha (Ex: "   1 |")
        printf(" %3zu |", i + 1);

        for (size_t j = 0; j < colunas; j++) {
            // Imprime o dado: espaço + numero + espaço + pipe
            // O espaço extra no final (antes do |) vem do formato "%*. *lf "
            printf(" %*.*lf |", LARGURA_NUMERO, CASAS_DECIMAIS, matriz_imprimir->dados[i][j]);
        }
        printf("\n");

        IMPRIMIR_LINHA_DIVISORIA(); // Linha divisória entre dados
    }
    printf("\n");

    return MAT_SUCESSO;
}

void matriz_init(matriz *matriz) { //matriz_init inicia matriz com valores zero
    matriz -> mat_linhas = 0;
    matriz -> mat_colunas = 0;
    matriz -> dados = NULL;
}

matriz_resultado criar_matriz(matriz *matriz, const size_t linhas, const size_t colunas) {
    if (linhas == 0 || colunas == 0) return MAT_ERRO_PARAMETRO_INVALIDO;
    matriz_init(matriz); //iniciamos a matriz
    matriz -> dados = (double **) malloc(sizeof(double *) * linhas);
    if (matriz -> dados == NULL) {
        return MAT_ERRO_ALOCACAO;
    } //alocamos um vetor de ponteiros de double
    double *dados_ligados = (double *) malloc(sizeof(double) * linhas * colunas);
    if (dados_ligados == NULL) {
        free(matriz -> dados);
        matriz -> dados = NULL;
        return MAT_ERRO_ALOCACAO;
    } //alocamos um bloco gigante de double
    for (size_t i = 0; i < linhas; i++) {
        matriz -> dados[i] = dados_ligados + (i * colunas);
    } //e por fim, ligamos cada pedaço dos ponteiros nas suas respectivas colunas
    matriz -> mat_colunas = colunas;
    matriz -> mat_linhas = linhas;
    return MAT_SUCESSO;
}

void preencher_matriz(matriz *matriz_preencher) { //essa função preenche apenas para testes
    for (size_t i = 0; i < matriz_preencher -> mat_linhas; i++) {
        for (size_t j = 0; j < matriz_preencher -> mat_colunas; j++) {
            matriz_preencher -> dados[i][j] = rand() % 50;
        }
    }
}

void free_matriz(matriz *matriz) {
    matriz -> mat_linhas = 0;
    matriz -> mat_colunas = 0;
    if (matriz -> dados != NULL) free(matriz -> dados[0]);
    free(matriz -> dados);
    matriz -> dados = NULL;
    /*
     * função para limpar a matriz, zeramos colunas e linhas, depois, liberamos
     * o bloco imenso de double e então o vetor de ponteiros, e declaramos
     * o vetor de ponteiros como NULL, para prevenir dangling pointers
     */
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
    //esse bloco anterior nós criamos uma matriz que irá servir como o apoio na criação da inversa
    for (size_t k = 0; k < tamanho_max; k++) {
        //primeiro, vemos se o valor absoluto i == j seja muito pequeno, que seria algo como 0.0000000001
        if (fabs(matriz_clone.dados[k][k]) < INTERVALO_ZERO) {
            bool trocou = false;
            for (size_t j = k + 1; j < tamanho_max; j++) {
                /*
                 *esse bloco serve para caso exista um número fora desse pequeno
                 *intervalo, nós possamos substituir o pivô por ele, usando as
                 *operações elementos L(k) troca por L(atual), se não existir,
                 *logo a inversa também não existe
                */
                if (fabs(matriz_clone.dados[j][k]) > INTERVALO_ZERO) {
                    for (size_t i = 0; i < tamanho_max; i++) {
                        const double temp_orig = matriz_clone.dados[k][i];
                        matriz_clone.dados[k][i] = matriz_clone.dados[j][i];
                        matriz_clone.dados[j][i] = temp_orig;
                        const double temp_dest = matriz_destino -> dados[k][i];
                        matriz_destino -> dados[k][i] = matriz_destino -> dados[j][i];
                        matriz_destino -> dados[j][i] = temp_dest;
                        //note que aqui é uma operação elementar
                    }
                    trocou = true;
                    break;
                }
            }
            if (!trocou) {
                free_matriz(&matriz_clone);
                return MAT_SINGULAR;
                //se não encontramos, a matriz é singular
            }
        }
        const double div = matriz_clone.dados[k][k];
        for (size_t i = 0; i < tamanho_max; i++) {
            matriz_clone.dados[k][i] /= div;
            matriz_destino -> dados[k][i] /= div;
        } //esse for serve para podermos transformar o pivô em 1
        for (size_t i = 0; i < tamanho_max; i++) {
            if (i == k) continue;
            const double fator = matriz_clone.dados[i][k];
            if (fabs(fator) < INTERVALO_ZERO) continue;
            for (size_t j = 0; j < tamanho_max; j++) {
                matriz_clone.dados[i][j] -= fator * matriz_clone.dados[k][j];
                matriz_destino -> dados[i][j] -= fator * matriz_destino -> dados[k][j];
            }
            //e por fim, nós zeramos a matriz_clone, nas linhas abaixo e acima do pivô atual
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
    //essa função serve para criarmos uma matriz na "mão"
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

const char* retornar_mensagem(const matriz_resultado result) {
    switch (result) {
        case MAT_ERRO_PONTEIRO_NULO: return "Tentou passar dado nulo";
        case MAT_ERRO_DIMENSAO_INCOMPATIVEL: return "Tamanhos incompativeis";
        case MAT_ERRO_ALOCACAO: return "Sem memória disponivel";
        case MAT_ERRO_OVERLAP: return "Tentou passar um destino igual a origem";
        case MAT_NAO_IDENTIDADE: return "Matriz nao e identidade";
        case MAT_SINGULAR: return "Matriz e singular";
        case MAT_ERRO_PARAMETRO_INVALIDO: return "Tamanho invalido";
        case MAT_SUCESSO: return "";
        default: return "Erro desconhecido: lembre o programador de adicionar aqui";
    }
}

bool validar_operacao(const matriz_resultado result) {
    if (result != MAT_SUCESSO) {
        const char* retorno = retornar_mensagem(result);
        fprintf(stderr, "%s\n", retorno);
        return false;
    }
    return true;
}

void matriz_init_all(matriz *primeira, ...) {
    va_list args;
    va_start(args, primeira);
    matriz *mat_atual = primeira;
    while (mat_atual != NULL) {
        matriz_init(mat_atual);
        mat_atual = va_arg(args, matriz*);
    }
    va_end(args);
}

void matriz_free_all(matriz *primeira, ...) {
    va_list args;
    va_start(args, primeira);
    matriz *mat_atual = primeira;
    while (mat_atual != NULL) {
        free_matriz(mat_atual);
        mat_atual = va_arg(args, matriz*);
    }
    va_end(args);
}

matriz_resultado calcular_min_quad(matriz *matB, const matriz *matX, const matriz *matY) {
    if (matX -> dados == NULL || matY -> dados == NULL || matB -> dados == NULL) {
        return MAT_ERRO_PONTEIRO_NULO;
    }
    matriz matXT, matXtX, matXtX_inv, matXtY;
    INIT_ALL(&matXT, &matXtX, &matXtX_inv, &matXtY);
    matriz_resultado status = MAT_SUCESSO;
    TRY (criar_matriz(&matXT, matX -> mat_colunas, matX -> mat_linhas));
    TRY (transpor_matriz(&matXT, matX));
    //aqui foi criado a matriz XT, ou seja, a transposta de X
    TRY (criar_matriz(&matXtX, matXT.mat_linhas, matX -> mat_colunas));
    TRY (multiplicar_matriz(&matXtX, &matXT, matX));
    //aqui foi criado o resultado de XT vezes X, ou seja, criamos uma matriz 3x3
    TRY (criar_matriz(&matXtX_inv, matXtX.mat_linhas, matXtX.mat_colunas));
    TRY (criar_inversa(&matXtX_inv, &matXtX));
    free_matriz(&matXtX);
    //aqui foi criado a inversa de XT vezes X, ou seja, a primeira_multiplicacao
    TRY (criar_matriz(&matXtY, matXT.mat_linhas, matY -> mat_colunas));
    TRY (multiplicar_matriz(&matXtY, &matXT, matY));
    free_matriz(&matXT);
    //aqui foi criado o resultada da transposta de X vezes a matriz Y
    TRY (multiplicar_matriz(matB, &matXtX_inv, &matXtY));
    //e por fim encontramos a matriz B usando o resultado da inversa vezes a multiplicação que acabamos de encontrar
    /*
     * note que durante o processo, sempre devemos criar a matriz antes
     * e delimitarmos as suas linhas e colunas, esse mesmo processo é executado também
     * em f3(x), só que de uma forma mais simples, já que temos menos variáveis
     */
    matriz_cleanup:
        FREE_ALL(&matXT, &matXtX, &matXtX_inv, &matXtY);
        return status;
}

#undef LARGURA_CELULA
#undef LARGURA_NUMERO
#undef INTERVALO_ZERO
#undef IMPRIMIR_LINHA_DIVISORIA
#undef CASAS_DECIMAIS
#undef TRY