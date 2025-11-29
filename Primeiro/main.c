#include <stdio.h>

#include "matrizes.h"

#include <stdlib.h>
#include <time.h>

#define TAMANHO_TESTE 2

/*o main eu deixei livre so para testes, entretanto, a ideia seria usar ele
 *justamente para colocar o switch case de menu aqui e fazer o negócio funcionar
 e deixar a parte logica em outros arquivos, como funcoes_mat.c
 */
int main() {
    char *texto = (char*) malloc(100);

    for (int i = 0; i < 10; i++) {
        texto[i] = (char) (0.0523);
    }
    texto[10] = '\0';
    puts(texto);
    free(texto);
    texto = NULL;
    return 0;
}
