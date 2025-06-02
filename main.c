/*
 * Trabalho de Cadastro de Pacientes
 *
 * Funcionalidades implementadas:
 *   - Consulta de pacientes por nome ou CPF.
 *   - Impressão da lista de pacientes com paginação (20 registros por página)
 *     e opção de retorno ao menu.
 *
 * Decisões de implementação:
 *   - Para identificar e trabalhar com os dados do paciente, foi utilizado o TAD "Paciente".
 *     Esse TAD possui os campos:
 *         id           (int)         - Número dentificador do paciente.
 *         cpf          (char[20])    - CPF do paciente.
 *         nome         (char[100])   - Nome completo do paciente.
 *         idade        (int)         - Idade do paciente.
 *         data_cadastro(char[15])    - Data de cadastro do paciente.
 *
 * Observação:
 *   - As funções atualizar, remover e inserir pacientes são _stubs_ (não implementadas).
 */

#include "arquivo.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função auxiliar para fazer a busca de uma substring.
   Retorna um ponteiro para a primeira ocorrência (sem diferença entre maiúsculas e minúsculas)
   ou NULL se não encontrar.
*/
char *strcasestr_custom(const char *haystack, const char *needle) {
  if (!*needle)
    return (char *)haystack;
  for (; *haystack; haystack++) {
    if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
      const char *h = haystack, *n = needle;
      while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
        h++;
        n++;
      }
      if (!*n)
        return (char *)haystack;
    }
  }
  return NULL;
}

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

/* Função que converte uma linha do arquivo CSV em um objeto.
   As linhas devem seguir o seguinte formato:
   id,cpf,nome,idade,data_cadastro
*/
Paciente parsePaciente(char *line) {
  Paciente p;
  char *token;

  /* Obtém o id */
  token = strtok(line, ",");
  p.id = (token != NULL) ? atoi(token) : 0;

  /* Obtém o CPF */
  token = strtok(NULL, ",");
  if (token)
    strncpy(p.cpf, token, sizeof(p.cpf) - 1);
  else
    strcpy(p.cpf, "");

  /* Obtém o nome */
  token = strtok(NULL, ",");
  if (token)
    strncpy(p.nome, token, sizeof(p.nome) - 1);
  else
    strcpy(p.nome, "");

  /* Obtém a idade */
  token = strtok(NULL, ",");
  p.idade = (token != NULL) ? atoi(token) : 0;

  /* Obtém a data de cadastro */
  token = strtok(NULL, ",");
  if (token) {
    strncpy(p.data_cadastro, token, sizeof(p.data_cadastro) - 1);
    p.data_cadastro[sizeof(p.data_cadastro) - 1] = '\0';
    p.data_cadastro[strcspn(p.data_cadastro, "\n")] = '\0';
  } else {
    strcpy(p.data_cadastro, "");
  }
  return p;
}

/* Função para imprimir os dados de um paciente formatados */
void imprimirPaciente(Paciente p) {
  printf("%-4d %-17s %-20s %-7d %-12s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
}

/* Função de consulta de paciente.
   Lê a escolha do usuário (por nome ou CPF), faz a busca dos registros e imprime os dados encontrados.
*/
int consultar_paciente(FILE *input_file_1) {
  char u;
  char line[256];

  printf("Escolha o modo de consulta: \n");
  printf("1 - Por nome\n");
  printf("2 - Por CPF\n");
  printf("3 - Retornar ao menu inicial\n");
  printf("\n");
  scanf(" %c", &u);
  printf("\n");

  rewind(input_file_1);
  /* Descarta a primeira linha do arquivo CSV */
  fgets(line, sizeof(line), input_file_1);

  // Consultar por nome
  if (u == '1') {
    int a = 1;
    char nome[100];
    printf("Digite o nome: \n");
    scanf(" %s", nome);
    printf("\n");

    printf("ID   CPF               Nome                Idade   Data_Cadastro\n");
    while (fgets(line, sizeof(line), input_file_1)) {
      Paciente p = parsePaciente(line);
      /* Utiliza a função auxiliar para buscar o nome */
      if (strcasestr_custom(p.nome, nome) != NULL) {
        a = 0;
        imprimirPaciente(p);
      }
    }
    if (a == 1) {
      printf("Paciente não encontrado no sistema.\n");
    }
    printf("\n");
    return consultar_paciente(input_file_1);
  }
    
  // Consultar por CPF
  else if (u == '2') {
    int a = 1;
    char cpf[100];
    printf("Digite o cpf: \n\n");
    scanf("%s", cpf);
    printf("\n");

    while (fgets(line, sizeof(line), input_file_1)) {
      Paciente p = parsePaciente(line);
      if (strstr(p.cpf, cpf) != NULL) {
        a = 0;
        imprimirPaciente(p);
      }
    }
    if (a == 1) {
      printf("Paciente não encontrado no sistema.\n");
    }
    printf("\n");
    return consultar_paciente(input_file_1);
  }
  // Voltar pro menu inicial
  else if (u == '3') {
    return menu_inicial(input_file_1);
  } else {
    printf("Erro!\n");
  }
  printf("\n");
  return menu_inicial(input_file_1);
}

/* FUNÇÕES STUB (a serem implementadas futuramente) */
int atualizar_paciente(FILE *input_file_1) {
  printf("Função atualizar paciente não implementada.\n\n");
  return menu_inicial(input_file_1);
}

int remover_paciente(FILE *input_file_1) {
  printf("Função remover paciente não implementada.\n\n");
  return menu_inicial(input_file_1);
}

int inserir_paciente(FILE *input_file_1) {
  printf("Função inserir paciente não implementada.\n\n");
  return menu_inicial(input_file_1);
}

/* Imprime a lista de pacientes com 20 pacientes por página.
   A cada 20 registros, pergunta se quer continuar ou voltar ao menu.
*/
int imprimir_lista_pacientes(FILE *input_file_1) {
  char line[256];
  int contador = 0;
  char opcao;

  rewind(input_file_1);
  /* Descarta a primeira linha */
  fgets(line, sizeof(line), input_file_1);

  printf("Imprimindo lista de pacientes...\n");

  while (fgets(line, sizeof(line), input_file_1) != NULL) {
    Paciente p = parsePaciente(line);
    imprimirPaciente(p);
    contador++;

    // A cada 20 pacientes pergunta ao usuário o que deseja fazer
    if (contador % 20 == 0) {
      do {
        printf("\n--- MENU DE CONTROLE ---\n");
        printf("1 - Continuar\n");
        printf("2 - Voltar ao menu\n");
        printf("\nEscolha uma opção: \n\n");
        scanf(" %c", &opcao);
        printf("\n");
        if (opcao != '1' && opcao != '2') {
          printf("Opção inválida! Tente novamente.\n");
        }
      } while (opcao != '1' && opcao != '2');

      if (opcao == '2') {
        return menu_inicial(input_file_1);
      }
    }
  }
  printf("\n--------------------------\n");
  return menu_inicial(input_file_1);
}

/* Função sair: limpa a tela e retorna o código de saída */
int sair(FILE *input_file_1) {
  // fclose(input_file_1); // Fecha o arquivo antes de sair
  system("clear");
  return 0; // Sai do programa
}

// Função para ver se o arquivo está vazio
int arquivo_esta_vazio(FILE *input_file_1) {
  int primeiro_caractere = fgetc(input_file_1);
  ungetc(primeiro_caractere, input_file_1);
  if (primeiro_caractere == EOF) {
    return 0; // vazio
  } else {
    return 1; // possui dados
  }
}

/* Menu inicial */
int menu_inicial(FILE *input_file_1) {
  char acao;

  rewind(input_file_1);

  printf("Escolha uma opção: \n");
  printf("1 - Consultar paciente\n");  // Buscar por CPF ou Nome
  if (arquivo_esta_vazio(input_file_1)) {
    printf("2 - Atualizar paciente \n");
    printf("3 - Remover paciente \n");
    printf("4 - Inserir paciente \n");
  }
  printf("5 - Imprimir lista de pacientes \n");
  printf("Q- Sair\n");

  printf("\nDigite a opção desejada: ");
  scanf(" %c", &acao);
  printf("\nVocê digitou: %c\n\n", acao);

  if (acao == '1') {
    consultar_paciente(input_file_1);
    printf("\n");
    return 0;
  } else if (acao == '2') {
    atualizar_paciente(input_file_1);
    printf("\n");
    return 0;
  } else if (acao == '3') {
    remover_paciente(input_file_1);
    printf("\n");
    return 0;
  } else if (acao == '4') {
    inserir_paciente(input_file_1);
    printf("\n");
    return 0;
  } else if (acao == '5') {
    imprimir_lista_pacientes(input_file_1);
    printf("\n");
    return 0;
  } else if (acao == 'Q' || acao == 'q') {
    sair(input_file_1);
    printf("\n");
    return 1;
  } else {
    printf("Opção inválida. Retornando ao menu...\n\n");
    return menu_inicial(input_file_1);
  }

  return acao;
}

/* Função principal */
int main() {
  int a;
  FILE *input_file_1 = fopen("bd_paciente.csv", "r");

  // Vê se o arquivo foi aberto com sucesso
  if (input_file_1 == NULL) {
    printf("Error opening files.\n");
    return 1;
  }

  a = menu_inicial(input_file_1);
  if (a == 1) {
    fclose(input_file_1);
    return 0;
  }

  fclose(input_file_1);
  return 0;
}