#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int contar_digitos(const double dado) {
    int contador;
    long long int dado_int = floor(dado);
    for (contador = 1; dado_int >= 10; contador++) {
        dado_int /= 10;
    }
    return contador;
}