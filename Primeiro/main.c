#include <locale.h>

#include "matrizes.h"
#include "utils.h"
#include "funcoes_mat.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TAMANHO_TESTE 2

/*o main eu deixei livre so para testes, entretanto, a ideia seria usar ele
 *justamente para colocar o switch case de menu aqui e fazer o negócio funcionar
 e deixar a parte logica em outros arquivos, como funcoes_mat.c
 */
int main() {
    clock_t inicio = clock();
    if (!validar_operacao(funcao_3())) exit(EXIT_FAILURE);
    clock_t fim = clock();
    const double tempo_usado = ((double) (fim - inicio) / CLOCKS_PER_SEC);
    printf("Tempo de uso: %.6lf\n", tempo_usado);
    return 0;
}
