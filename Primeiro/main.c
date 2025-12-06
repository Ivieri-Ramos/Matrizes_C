#include <locale.h>

#include "matrizes.h"
#include "utils.h"
#include "funcoes_mat.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "calcular_diferenca.h"

/*
 *o main eu deixei livre so para testes, entretanto, a ideia seria usar ele
 *justamente para colocar o switch case de menu aqui e fazer o negócio funcionar
 e deixar a parte logica em outros arquivos, como funcoes_mat.c
 */

int main() {
    calcular_erro_absoluto();
    /*
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