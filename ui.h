#ifndef UI_H
#define UI_H

#include "bd.h" // Interface do banco de pacientes

// Exibe pacientes por nome ou CPF
int ui_exibir_por_nome_ou_cpf(BDPaciente *bd);

// Exibe o menu principal da interface
void ui_exibir_menu(BDPaciente *bd, const char *arquivo);

// Permite consultar pacientes pelo nome ou CPF
void ui_consultar(BDPaciente *bd);

// Insere um novo paciente no banco
void ui_inserir(BDPaciente *bd);

// Remove um paciente do banco pelo ID
void ui_remover(BDPaciente *bd);

// Atualiza os dados de um paciente existente
void ui_atualizar(BDPaciente *bd);

#endif
