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
#include "paciente.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Em main.c, acima da definição da função 
static char *strcasestr_custom(const char *haystack, const char *needle);

/* Função auxiliar para fazer a busca de uma substring.
   Retorna um ponteiro para a primeira ocorrência (sem diferença entre maiúsculas e minúsculas)
   ou NULL se não encontrar.
*/
char *strcasestr_custom(const char *haystack, const char *needle) {
  if (!*needle)
    return NULL;

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

/* Função que converte uma linha do arquivo CSV em um objeto.
   As linhas devem seguir o seguinte formato:
   id,cpf,nome,idade,data_cadastro
*/
Paciente parsePaciente(char *line) {
  Paciente p;
  char *token;

  /* Obtém o id */
  token = strtok(line, ",");
  // p.id = (token != NULL) ? atoi(token) : 0;
  if (token) {
    // Avance por quaisquer espaços em branco no início do token
    while (isspace((unsigned char)*token)) {
        token++;
    }
    p.id = atoi(token);
  } else {
    p.id = 0;
  }

  /* Obtém o CPF */
  token = strtok(NULL, ",");
  if (token) {
    strncpy(p.cpf, token, sizeof(p.cpf) - 1);
    p.cpf[sizeof(p.cpf) - 1] = '\0';
  } else {
    strcpy(p.cpf, "");
  }
  /* Obtém o nome */
  token = strtok(NULL, ",");
  if (token) {
    strncpy(p.nome, token, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0';
  } else {
    strcpy(p.nome, "");
  }
  /* Obtém a idade */
  token = strtok(NULL, ",");
  p.idade = (token != NULL) ? atoi(token) : 0;

  /* Obtém a data de cadastro */
  token = strtok(NULL, ",");
  if (token) {
    strncpy(p.data_cadastro, token, sizeof(p.data_cadastro) - 1);
    p.data_cadastro[sizeof(p.data_cadastro) - 1] = '\0';
    p.data_cadastro[strcspn(p.data_cadastro, "\r\n")] = '\0';
  } else {
    strcpy(p.data_cadastro, "");
  }
  return p;
}

/* Função para imprimir os dados de um paciente formatados */
void imprimirPaciente(Paciente p) {
  printf("%-5d | %-17s | %-20s | %-7d | %-12s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
}

/* Função de consulta de paciente.
   Lê a escolha do usuário (por nome ou CPF), faz a busca dos registros e imprime os dados encontrados.
*/
int consultar_paciente(FILE *input_file_1) {
  char u;
  char line[256];
  int c; // Para a limpeza do buffer

  do { // Início do loop do-while para manter o menu de consulta ativo
    printf("Escolha o modo de consulta: \n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu inicial\n");
    printf("\n");
    scanf(" %c", &u);
    printf("\n");

    // Limpa o buffer de entrada APÓS LER A OPÇÃO (u)
    while ((c = getchar()) != '\n' && c != EOF);

    // Se o usuário escolher retornar ao menu principal, saia do loop
    if (u == '3') {
        return menu_inicial(input_file_1);
    }

    // Se a opção não for válida, imprima erro e continue o loop
    if (u != '1' && u != '2') {
        printf("Opção inválida! Tente novamente.\n\n");
        continue; // Volta para o início do loop do-while
    }

    // Se a opção é '1' ou '2', prepare para a busca:
    rewind(input_file_1); // Volta o ponteiro do arquivo para o início para ler do zero
    /* Descarta a primeira linha do arquivo CSV (cabeçalho) */
    fgets(line, sizeof(line), input_file_1);


    // Consultar por nome
    if (u == '1') {
      int a = 1;
      char nome[100];
      printf("Digite o nome: \n");
      // scanf(" %s", nome); // Esta linha DEVE ESTAR COMENTADA OU REMOVIDA.
      fgets(nome, sizeof(nome), stdin); // Leitura correta para nomes com espaços
      nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n'
      printf("\n");

      // Cabeçalho formatado para alinhar com imprimirPaciente
      printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
      while (fgets(line, sizeof(line), input_file_1)) {
        char line_copy[256]; // Crie uma cópia da linha para strtok
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';

        Paciente p = parsePaciente(line_copy); // Passe a cópia da linha
        /* Utiliza strncasecmp para buscar o nome por prefixo */
        if (strlen(nome) > 0 && strncasecmp(p.nome, nome, strlen(nome)) == 0) { // Garante que 'nome' não é vazio e busca por prefixo
          a = 0;
          imprimirPaciente(p);
        }
      }
      if (a == 1) {
        printf("Paciente não encontrado no sistema.\n");
      }
      printf("\n");
    }
      
    // Consultar por CPF
    else if (u == '2') {
      int a = 1;
      char cpf[100];
      printf("Digite o cpf: \n\n");
      scanf("%s", cpf); // OK para CPF (geralmente sem espaços)
      // Limpa o buffer de entrada após este scanf
      while ((c = getchar()) != '\n' && c != EOF); 

      // Cabeçalho formatado para alinhar com imprimirPaciente
      printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
      while (fgets(line, sizeof(line), input_file_1)) {
        char line_copy[256]; // Crie uma cópia da linha para strtok
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';

        Paciente p = parsePaciente(line_copy); // Passe a cópia da linha
        if (strlen(cpf) > 0 && strstr(p.cpf, cpf) != NULL) { // Garante que 'cpf' não é vazio e busca substring
          a = 0;
          imprimirPaciente(p);
        }
      }
      if (a == 1) {
        printf("Paciente não encontrado no sistema.\n");
      }
      printf("\n");
    }
  } while (u != '3'); // Continua o loop do-while até que o usuário escolha '3' para retornar
    
  return menu_inicial(input_file_1); // Retorna ao menu inicial quando o loop termina por escolha do usuário
}

// Função para apenas imprimir o paciente buscado
void exibir_pacientes_por_nome_ou_cpf(FILE *input_file_1) {
  char opcao;
  char line[256];
  int c;

  printf("Escolha o modo de consulta:\n");
  printf("1 - Por nome\n");
  printf("2 - Por CPF\n");
  printf("\n");
  scanf(" %c", &opcao);
  while ((c = getchar()) != '\n' && c != EOF); // limpa buffer

  rewind(input_file_1);
  fgets(line, sizeof(line), input_file_1); // pula cabeçalho

  if (opcao == '1') {
    char nome[100];
    printf("Digite o nome:\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    while (fgets(line, sizeof(line), input_file_1)) {
      char line_copy[256];
      strncpy(line_copy, line, sizeof(line_copy) - 1);
      line_copy[sizeof(line_copy) - 1] = '\0';

      Paciente p = parsePaciente(line_copy);
      if (strlen(nome) > 0 && strncasecmp(p.nome, nome, strlen(nome)) == 0) {
        imprimirPaciente(p);
      }
    }
  } else if (opcao == '2') {
    char cpf[100];
    printf("Digite o CPF:\n");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    while (fgets(line, sizeof(line), input_file_1)) {
      char line_copy[256];
      strncpy(line_copy, line, sizeof(line_copy) - 1);
      line_copy[sizeof(line_copy) - 1] = '\0';

      Paciente p = parsePaciente(line_copy);
      if (strstr(p.cpf, cpf) != NULL) {
        imprimirPaciente(p);
      }
    }
  } else {
    printf("Opção inválida. Voltando...\n");
  }

  printf("\n");
}


/* FUNÇÕES STUB (a serem implementadas futuramente) */
int atualizar_paciente(FILE *input_file_1) {
  exibir_pacientes_por_nome_ou_cpf(input_file_1); // Chama a função de consulta primeiro

  FILE *temp_file = fopen("temp.csv", "w");
  if (!temp_file) {
    printf("Erro ao criar arquivo temporário.\n");
    return menu_inicial(input_file_1);
  }

  rewind(input_file_1);
  char line[256];
  int id_alvo;
  int encontrado = 0;
  Paciente paciente_antigo, paciente_novo;

  // Copia o cabeçalho
  fgets(line, sizeof(line), input_file_1);
  fputs(line, temp_file);

  printf("Digite o ID do registro a ser atualizado:\n\n[Usuário] ");
  scanf("%d", &id_alvo);
  getchar(); // Limpa '\n'

  rewind(input_file_1);
  fgets(line, sizeof(line), input_file_1); // pula cabeçalho

  while (fgets(line, sizeof(line), input_file_1)) {
    Paciente p = parsePaciente(line);

    if (p.id == id_alvo) {
      encontrado = 1;
      paciente_antigo = p;

      printf("\n[Sistema]\nDigite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro\n");
      printf("(para manter o valor atual de um campo, digite '-'):\n\n[Usuário]\n");

      char buffer[100];

      // CPF
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if (strcmp(buffer, "-") != 0) {
        snprintf(p.cpf, sizeof(p.cpf), "%.3s.%.3s.%.3s-%.2s", buffer, buffer+3, buffer+6, buffer+9);
      }

      // Nome
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if (strcmp(buffer, "-") != 0) {
        strncpy(p.nome, buffer, sizeof(p.nome));
      }

      // Idade
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if (strcmp(buffer, "-") != 0) {
        p.idade = atoi(buffer);
      }

      // Data_Cadastro
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if (strcmp(buffer, "-") != 0) {
        strncpy(p.data_cadastro, buffer, sizeof(p.data_cadastro));
      }

      paciente_novo = p;

      printf("\n[Sistema]\nConfirma os novos valores para o registro abaixo? (S/N)\n\n");
      printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
      imprimirPaciente(paciente_novo);

      char confirmacao;
      scanf(" %c", &confirmacao);
      getchar();

      if (confirmacao == 'S' || confirmacao == 's') {
        fprintf(temp_file, "%d,%s,%s,%d,%s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
        printf("\n[Sistema]\nRegistro atualizado com sucesso.\n\n");
      } else {
        fprintf(temp_file, "%d,%s,%s,%d,%s\n", paciente_antigo.id, paciente_antigo.cpf,
                paciente_antigo.nome, paciente_antigo.idade, paciente_antigo.data_cadastro);
        printf("\n[Sistema]\nAtualização cancelada. Registro mantido.\n\n");
      }

    } else {
      // Copia linha original para o arquivo temporário
      fprintf(temp_file, "%d,%s,%s,%d,%s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    }
  }

  fclose(input_file_1);
  fclose(temp_file);

  // Substitui o original
  remove("bd_paciente.csv");
  rename("temp.csv", "bd_paciente.csv");

  // Reabre atualizado
  input_file_1 = fopen("bd_paciente.csv", "r");

  if (!encontrado) {
    printf("\n[Sistema] ID não encontrado.\n\n");
  }

  return menu_inicial(input_file_1);
}


int remover_paciente(FILE *input_file_1) {
  exibir_pacientes_por_nome_ou_cpf(input_file_1); // Mostra lista antes da escolha

  FILE *temp_file = fopen("temp.csv", "w");
  if (!temp_file) {
    printf("Erro ao criar arquivo temporário.\n");
    return menu_inicial(input_file_1);
  }

  rewind(input_file_1);
  char line[256];
  int id_alvo;
  int encontrado = 0;
  Paciente paciente_removido;

  // Copia o cabeçalho
  fgets(line, sizeof(line), input_file_1);
  fputs(line, temp_file);

  printf("Digite o ID do registro a ser removido:\n\n[Usuário] ");
  scanf("%d", &id_alvo);
  getchar(); // limpa '\n'

  rewind(input_file_1);
  fgets(line, sizeof(line), input_file_1); // pula cabeçalho

  while (fgets(line, sizeof(line), input_file_1)) {
    Paciente p = parsePaciente(line);

    if (p.id == id_alvo) {
      encontrado = 1;
      paciente_removido = p;

      printf("\n[Sistema]\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n\n");
      printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
      imprimirPaciente(p);

      char confirmacao;
      scanf(" %c", &confirmacao);
      getchar();

      if (confirmacao == 'S' || confirmacao == 's') {
        printf("\n[Sistema]\nRegistro removido com sucesso.\n\n");
        continue; // não grava este paciente no novo arquivo
      } else {
        // grava o paciente de volta se o usuário cancelou
        fprintf(temp_file, "%d,%s,%s,%d,%s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
        printf("\n[Sistema]\nRemoção cancelada. Registro mantido.\n\n");
      }
    } else {
      // grava os outros normalmente
      fprintf(temp_file, "%d,%s,%s,%d,%s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    }
  }

  fclose(input_file_1);
  fclose(temp_file);

  remove("bd_paciente.csv");
  rename("temp.csv", "bd_paciente.csv");

  input_file_1 = fopen("bd_paciente.csv", "r");

  if (!encontrado) {
    printf("\n[Sistema] ID não encontrado.\n\n");
  }

  return menu_inicial(input_file_1);
}


int inserir_paciente(FILE *input_file_1) {
  FILE *output_file = fopen("bd_paciente.csv", "a+");
  if (!output_file) {
    printf("Erro ao abrir arquivo para escrita.\n");
    return menu_inicial(input_file_1);
  }

  // Geração automática de ID
  rewind(input_file_1);
  char line[256];
  int maior_id = 0;

  fgets(line, sizeof(line), input_file_1); // pula cabeçalho
  while (fgets(line, sizeof(line), input_file_1)) {
    Paciente p = parsePaciente(line);
    if (p.id > maior_id)
      maior_id = p.id;
  }

  Paciente novo;
  novo.id = maior_id + 1;

  char buffer[100];

  printf("Para inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro:\n\n");
  while (getchar() != '\n');  // limpa o \n deixado 
  // CPF (apenas números, 11 dígitos)
  do {
    printf("CPF (somente números, 11 dígitos): ");
    fflush(stdout); // garante que o printf aparece antes da entrada

    if (!fgets(buffer, sizeof(buffer), stdin)) {
      printf("[Erro] Erro na leitura do CPF. Tente novamente.\n");
      continue;
    }

    buffer[strcspn(buffer, "\n")] = 0; // remove \n

    // Validação só após leitura
    int valido = strlen(buffer) == 11;
    for (int i = 0; i < strlen(buffer) && valido; i++) {
      if (!isdigit(buffer[i])) valido = 0;
    }

    if (!valido) {
      printf("[Erro] CPF inválido! Tente novamente.\n");
    } else {
      snprintf(novo.cpf, sizeof(novo.cpf), "%.3s.%.3s.%.3s-%.2s", buffer, buffer+3, buffer+6, buffer+9);
      break;
    }
  } while (1);

  // Nome
  do {
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    if (strlen(novo.nome) == 0) {
      printf("[Erro] Nome não pode estar vazio.\n");
    } else {
      break;
    }
  } while (1);

  // Idade
  do {
    printf("Idade: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    novo.idade = atoi(buffer);
    if (novo.idade <= 0 || novo.idade > 130) {
      printf("[Erro] Idade inválida.\n");
    } else {
      break;
    }
  } while (1);

  // Data de cadastro
  do {
    printf("Data de cadastro (AAAA-MM-DD): ");
    fgets(novo.data_cadastro, sizeof(novo.data_cadastro), stdin);
    novo.data_cadastro[strcspn(novo.data_cadastro, "\n")] = 0;

    int ano, mes, dia;
    if (sscanf(novo.data_cadastro, "%d-%d-%d", &ano, &mes, &dia) == 3 &&
        ano >= 1900 && ano <= 2100 &&
        mes >= 1 && mes <= 12 &&
        dia >= 1 && dia <= 31) {
      break;
    } else {
      printf("[Erro] Data inválida! Use o formato correto.\n");
    }
  } while (1);

  printf("\n[Sistema]\nConfirma a inserção do registro abaixo? (S/N)\n\n");
  printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
  imprimirPaciente(novo);

  char confirmacao;
  scanf(" %c", &confirmacao);
  getchar();

  if (confirmacao == 'S' || confirmacao == 's') {
    fprintf(output_file, "%d,%s,%s,%d,%s\n", novo.id, novo.cpf, novo.nome, novo.idade, novo.data_cadastro);
    printf("\n[Sistema]\nO registro foi inserido com sucesso.\n\n");
  } else {
    printf("\n[Sistema]\nInserção cancelada.\n\n");
  }

  fclose(output_file);
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
int sair() {
  // fclose(input_file_1); // Fecha o arquivo antes de sair
  system("clear");
  return 0; // Sai do programa
}

// Função para ver se o arquivo está vazio (excluir)
int arquivo_esta_vazio(FILE *input_file_1) {
  int primeiro_caractere = fgetc(input_file_1);
  ungetc(primeiro_caractere, input_file_1);
  if (primeiro_caractere == EOF) {
    return 0; // vazio
  } else {
    return 1; // possui dados
  }
}

// Função para ver se o arquivo contem pacientes
int arquivo_contem_pacientes(FILE *input_file_1) {
    char line[256];
    rewind(input_file_1);
    fgets(line, sizeof(line), input_file_1); // Lê a linha do cabeçalho
    if (fgets(line, sizeof(line), input_file_1) != NULL) { // Tenta ler a próxima linha
        rewind(input_file_1); // Volta ao início para outras operações
        return 1; // Contém dados (além do cabeçalho)
    }
    rewind(input_file_1); // Volta ao início para outras operações
    return 0; // Contém apenas o cabeçalho ou está vazio
}

/* Menu inicial */
int menu_inicial(FILE *input_file_1) {
  char acao;

  rewind(input_file_1);

  printf("Escolha uma opção: \n");
  printf("1 - Consultar paciente\n");  // Buscar por CPF ou Nome
  if (arquivo_contem_pacientes(input_file_1)) {
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
    sair();
    printf("\n");
    return 1;
  } else {
    printf("Opção inválida. Retornando ao menu...\n\n");
    return menu_inicial(input_file_1);
  }

  return acao;
}

/* Função principal */
int main(void) {
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