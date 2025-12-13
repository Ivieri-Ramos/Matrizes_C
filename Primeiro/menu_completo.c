#include "menu_completo.h"

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "respostas_trabalho.h"
#include "utils.h"

void menu_sexto_ex() {
    while (true) {
        printf("\n========================================\n");
        printf("      ANALISE NUMERICA DE FUNCOES       \n");
        printf("========================================\n");
        printf("1 - Ver valores calculados (Ex 1)\n");
        printf("2 - Ver erros absolutos (Ex 2)\n");
        printf("3 - Ver erros relativos (Ex 3)\n");
        printf("4 - Ver erros totais (Ex 4)\n");
        printf("5 - Qual a melhor funcao? (Ex 5)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        const opcoes_menu_ex op = retornar_op_menu(escolher_opcao());
        limpar_tela();
        switch (op) {
            case PRIMEIRA_QUESTAO: {
                exibir_valores_calculados();
                break;
            }
            case SEGUNDA_QUESTAO: {
                exibir_tabela_erros(ERRO_ABSOLUTO);
                break;
            }
            case TERCEIRA_QUESTAO: {
                exibir_tabela_erros(ERRO_RELATIVO);
                break;
            }
            case QUARTA_QUESTAO: {
                exibir_totais();
                break;
            }
            case QUINTA_QUESTAO: {
                exibir_melhor_aproximacao();
                break;
            }
            case SAIR: return;
                default: {
                    printf("Digite um numero inteiro!\n");
                    continue;
                }
        }
        printf("\nDigite enter para continuar!\n");
        limpar_buffer();
    }
}

void menu_mini_exs() {
    while (true) {
        printf("\n========================================\n");
        printf("      EXPLICITAR RESULTADOS ENCONTRADOS       \n");
        printf("========================================\n");
        printf("1 - Ver a função f₂(x) (Ex 1)\n");
        printf("2 - Explicitando Xᵀ em f₃(x) (Ex 2)\n");
        printf("3 - Ver o valor de β e a função f₃(x) (Ex 3)\n");
        printf("4 - Explicitando Xᵀ em f₄(x) (Ex 4)\n");
        printf("5 - Ver o valor de β e a função f₄(x) (Ex 5)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        const opcoes_menu_ex op = retornar_op_menu(escolher_opcao());
        limpar_tela();
        switch (op) {
            case PRIMEIRA_QUESTAO: {
                primeiro_ex();
                break;
            }
            case SEGUNDA_QUESTAO: {
                if (!validar_operacao(segundo_ex())) exit(EXIT_FAILURE);
                break;
            }
            case TERCEIRA_QUESTAO: {
                if (!validar_operacao(terceiro_ex())) exit(EXIT_FAILURE);
                break;
            }
            case QUARTA_QUESTAO: {
                exibir_totais();
                break;
            }
            case QUINTA_QUESTAO: {
                exibir_melhor_aproximacao();
                break;
            }
            case SAIR: return;
            default: {
                printf("Digite um numero inteiro!\n");
                continue;
            }
        }
        printf("\nDigite enter para continuar!\n");
        limpar_buffer();
    }
}

int escolher_opcao() {
    int c;
    int opcao = 0;
    bool is_numeric = false;
    while ((c = getchar()) != EOF && c != '\n') {
        if (isspace((unsigned char)c)) continue;
        if (isdigit((unsigned char)c) && !is_numeric) {
            is_numeric = true;
            opcao = c;
        }
        else {
            return -1;
        }
    }
    return opcao - '0';
}

opcoes_menu_ex retornar_op_menu(const int opcao) {
    switch (opcao) {
        case 0: return SAIR;
        case 1: return PRIMEIRA_QUESTAO;
        case 2: return SEGUNDA_QUESTAO;
        case 3: return TERCEIRA_QUESTAO;
        case 4: return QUARTA_QUESTAO;
        case 5: return QUINTA_QUESTAO;
        default: return OPCAO_INVALIDA;
    }
}