#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração das funções

// Mostra o menu inicial e lida com a escolha feita.
int menu_inicial(FILE *input_file_1);

// Realiza a consulta do paciente pelo nome ou CPF.
int consultar_paciente(FILE *input_file_1);

// Atualiza os dados de um paciente.
int atualizar_paciente(FILE *input_file_1);

// Remove um paciente.
int remover_paciente(FILE *input_file_1);

// Insere um novo paciente.
int inserir_paciente(FILE *input_file_1);

// Imprime a lista de pacientes (20 pacientes por página) e opçã de voltar pro menu.
int imprimir_lista_pacientes(FILE *input_file_1);

// Limpa a tela e sai do programa (ou retorna ao menu).
int sair(FILE *input_file_1);

// Vê se o arquivo CSV está vazio, retornando 0 se estiver vazio e 1 se houver conteúdo.
int arquivo_esta_vazio(FILE *input_file_1);

#endif /* ARQUIVO_H */