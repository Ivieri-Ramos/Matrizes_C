#include <stdio.h>

#include "matrizes.h"

#include <stdlib.h>
#include <time.h>

#define TAMANHO_TESTE 2

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
