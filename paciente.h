#ifndef PACIENTE_H
#define PACIENTE_H

/*
 * TAD Paciente
 * Representa os dados de um paciente no sistema.
 */
typedef struct {
    int id;
    char cpf[20];
    char nome[100];
    int idade;
    char data_cadastro[15];
} Paciente;

// Converte uma linha CSV em um objeto Paciente
Paciente paciente_parse(char *linha_csv);

// Imprime um paciente formatado
void paciente_imprimir(Paciente p);

#endif
