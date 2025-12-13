#include "menu_completo.h"

#include <locale.h>

/*
 *o main eu deixei livre so para testes, entretanto, a ideia seria usar ele
 *justamente para colocar o switch case de menu aqui e fazer o negócio funcionar
 e deixar a parte logica em outros arquivos, como funcoes_mat.c
 */

int main() {
    setlocale(LC_ALL, "Portuguese.UTF-8");
    menu_completo();
    return 0;
}