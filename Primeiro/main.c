#include <locale.h>

#include "matrizes.h"
#include "utils.h"
#include "funcoes_mat.h"
#include "menu_completo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "respostas_trabalho.h"

/*
 *o main eu deixei livre so para testes, entretanto, a ideia seria usar ele
 *justamente para colocar o switch case de menu aqui e fazer o negócio funcionar
 e deixar a parte logica em outros arquivos, como funcoes_mat.c
 */

int main() {
    menu_mini_exs();
    /*
    int opcao;

    do {
        // Menu visual
        printf("\n========================================\n");
        printf("      ANALISE NUMERICA DE FUNCOES       \n");
        printf("========================================\n");
        printf("1. Ver valores calculados (Ex 1)\n");
        printf("2. Ver erros absolutos (Ex 2)\n");
        printf("3. Ver erros relativos (Ex 3)\n");
        printf("4. Ver erros totais (Ex 4)\n");
        printf("5. Qual a melhor funcao? (Ex 5)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        // Limpeza de tela simples (opcional)
        // system("cls"); // Windows
        // system("clear"); // Linux/Mac

        switch(opcao) {
            case 1: exibir_valores_calculados(); break;
            case 2: exibir_tabela_erros(0); break; // 0 = Absoluto
            case 3: exibir_tabela_erros(1); break; // 1 = Relativo
            case 4: exibir_totais(); break;
            case 5: exibir_melhor_aproximacao(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

        if(opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar(); getchar(); // Pausa para leitura
        }

    } while (opcao != 0);
    setlocale(LC_ALL, "Portuguese.UTF-8");
    int opcao;
    do{
        limpar_tela();
        printf("menu cálculo\n");
        printf("1- função 2\n");
        printf("2- função 3\n");
        printf("3- função 4\n");
        printf("0- sair\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1: {
                printf("\n>> rodando a função 2 <<\n");
                printf("%lf\n",funcao_2(0));
                break;
            }
            case 2: {
                printf("\n>> rodando a função 3 <<\n");
                funcao_3(0);
                break;
            }
            case 3: {
                printf("\n>> rodando a função 4 <<\n");
                funcao_4(0);
                break;
            }
            case 0: {
                printf("\n>> encerrando o programa <<\n");
                break;
            }
            default:
                printf("opção invalida");
                break;
        }
        limpar_buffer();
        limpar_buffer();
    } while(opcao != 0);
    */
    return 0;
}