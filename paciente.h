// paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

// Inclusões mínimas se necessário para a definição da struct (raro aqui)

/* --- TAD Paciente ---
   Estrutura com os dados de um paciente.
*/
typedef struct {
  int id;
  char cpf[20];
  char nome[100];
  int idade;
  char data_cadastro[15];
} Paciente;

// Protótipos de funções específicas do TAD Paciente, se houver
// Ex: void imprimirPaciente(Paciente p);

#endif /* PACIENTE_H */