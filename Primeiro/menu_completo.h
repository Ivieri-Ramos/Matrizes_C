#ifndef ALGEBRALINEAR_MENU_COMPLETO_H
#define ALGEBRALINEAR_MENU_COMPLETO_H

typedef enum opcoes_menu_ex {
    SAIR,
    PRIMEIRA_QUESTAO,
    SEGUNDA_QUESTAO,
    TERCEIRA_QUESTAO,
    QUARTA_QUESTAO,
    QUINTA_QUESTAO,
    OPCAO_INVALIDA
} opcoes_menu_ex;

void menu_sexto_ex();
void menu_mini_exs();
int escolher_opcao();
opcoes_menu_ex retornar_op_menu(int opcao);

#endif //ALGEBRALINEAR_MENU_COMPLETO_H