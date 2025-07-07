#ifndef UI_H
#define UI_H

#include "bd.h"

int ui_exibir_por_nome_ou_cpf(BDPaciente *bd);

void ui_exibir_menu(BDPaciente *bd, const char *arquivo);
void ui_consultar(BDPaciente *bd);
void ui_inserir(BDPaciente *bd);
void ui_remover(BDPaciente *bd);
void ui_atualizar(BDPaciente *bd);

#endif
