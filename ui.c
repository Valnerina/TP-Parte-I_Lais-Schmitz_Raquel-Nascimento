#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Consulta pacientes por nome ou CPF
int ui_exibir_por_nome_ou_cpf(BDPaciente *bd) {
    char opcao;
    char termo[100];
    int encontrou = 0;

    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n\n");
    scanf(" %c", &opcao);
    while (getchar() != '\n'); // limpa buffer

    if (opcao == '1') {
        printf("Digite o nome: ");
        fgets(termo, sizeof(termo), stdin); // lê nome
        termo[strcspn(termo, "\n")] = 0; // remove '\n'

        // imprime cabeçalho
        printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
        No *atual = bd->inicio;
        while (atual) {
            Paciente p = atual->paciente;
            // compara prefixo do nome
            if (strlen(termo) > 0 && strncasecmp(p.nome, termo, strlen(termo)) == 0) {
                paciente_imprimir(p);
                encontrou = 1;
            }
            atual = atual->proximo;
        }
    } else if (opcao == '2') {
        printf("Digite o CPF: ");
        fgets(termo, sizeof(termo), stdin); // lê CPF
        termo[strcspn(termo, "\n")] = 0;

        // imprime cabeçalho
        printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
        No *atual = bd->inicio;
        while (atual) {
            Paciente p = atual->paciente;
            // compara prefixo do CPF
            if (strlen(termo) > 0 && strncmp(p.cpf, termo, strlen(termo)) == 0) {
                paciente_imprimir(p);
                encontrou = 1;
            }
            atual = atual->proximo;
        }
    } else {
        printf("Opção inválida. Voltando...\n\n");
    }

    if (encontrou == 0) {
        printf("Paciente não encontrado.\n\n");
        return 0;
    }
    printf("\n");
    return 1;
}

// separar por nome e cpf
void ui_consultar(BDPaciente *bd) {
    char tipo;
    char query[100];
    int encontrou = 0;

    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu\n\n");

    scanf(" %c", &tipo);
    while (getchar() != '\n'); // limpa buffer

    if (tipo == '3') return; // retorna ao menu

    // Consulta por nome
    if (tipo == '1') {
        printf("Digite o nome: ");
        fgets(query, sizeof(query), stdin); // lê nome
        query[strcspn(query, "\n")] = '\0';

        printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");

        No *atual = bd->inicio;
        while (atual) {
            Paciente p = atual->paciente;
            if (strlen(query) > 0 && strncasecmp(p.nome, query, strlen(query)) == 0) {
                paciente_imprimir(p);
                encontrou = 1;
            }
            atual = atual->proximo;
        }

        if (!encontrou)
            printf("Paciente não encontrado no sistema.\n");

    } else if (tipo == '2') {
        printf("Digite o CPF: ");
        scanf("%s", query);
        while (getchar() != '\n'); // limpa buffer

        printf("\n%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");

        No *atual = bd->inicio;
        while (atual) {
            Paciente p = atual->paciente;
            if (strncmp(p.cpf, query, strlen(query)) == 0) {
                paciente_imprimir(p);
                encontrou = 1;
            }
            atual = atual->proximo;
        }

        if (!encontrou)
            printf("Paciente não encontrado no sistema.\n");
    } else {
        printf("Opção inválida. Retornando...\n");
    }

    printf("\n");
}

// verificar se digitou certo
void ui_inserir(BDPaciente *bd) {
    Paciente novo;
    char buffer[100];

    printf("Para inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro:\n\n");

    // CPF
    while (1) {
        printf("CPF (somente números, 11 dígitos): ");
        fflush(stdout); // exibe imediato
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("[Erro] Erro na leitura do CPF. Tente novamente.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0; // remove \n

        // verifica se tem 11 dígitos
        int valido = strlen(buffer) == 11;
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len && valido; i++) {
            if (!isdigit(buffer[i])) valido = 0;
        }

        if (!valido) {
            printf("[Erro] CPF inválido! Tente novamente.\n");
        } else {
            // formata o CPF com pontos e traço
            snprintf(novo.cpf, sizeof(novo.cpf), "%.3s.%.3s.%.3s-%.2s", buffer, buffer+3, buffer+6, buffer+9);
            break;
        }
    }

    // Nome
    while (1) {
        printf("Nome: ");
        fgets(novo.nome, sizeof(novo.nome), stdin);
        novo.nome[strcspn(novo.nome, "\n")] = 0;
        if (strlen(novo.nome) == 0) {
            printf("[Erro] Nome não pode estar vazio.\n");
        } else {
            break;
        }
    }

    // Idade
    while (1) {
        printf("Idade: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        novo.idade = atoi(buffer);
        if (novo.idade <= 0 || novo.idade > 130) {
            printf("[Erro] Idade inválida.\n");
        } else {
            break;
        }
    }

    // Data de cadastro
    while (1) {
        printf("Data de cadastro (AAAA-MM-DD): ");
        fgets(novo.data_cadastro, sizeof(novo.data_cadastro), stdin);
        novo.data_cadastro[strcspn(novo.data_cadastro, "\n")] = 0;

        int ano, mes, dia;
        // valida estrutura da data
        if (sscanf(novo.data_cadastro, "%d-%d-%d", &ano, &mes, &dia) == 3 &&
            ano >= 1900 && ano <= 2100 &&
            mes >= 1 && mes <= 12 &&
            dia >= 1 && dia <= 31) {
            break;
        } else {
            printf("[Erro] Data inválida! Use o formato correto.\n");
        }
    }

    novo.id = 0; // será atribuído no bd_inserir

    // Confirmação
    printf("\n[Sistema]\nConfirma a inserção do registro abaixo? (S/N)\n\n");
    printf("%-4s %-17s %-20s %-7s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    paciente_imprimir(novo);

    char confirmacao;
    scanf(" %c", &confirmacao);
    getchar();

    if (confirmacao == 'S' || confirmacao == 's') {
        bd_inserir(bd, novo);
        printf("\n[Sistema]\nO registro foi inserido com sucesso.\n\n");
    } else {
        printf("\n[Sistema]\nInserção cancelada.\n\n");
    }
}

// tem que chamar consultar primeiro para verificar se o paciente esta na memoria 
void ui_atualizar(BDPaciente *bd) {
    // mostra pacientes para o usuário escolher
    if (!ui_exibir_por_nome_ou_cpf(bd)) {
        printf("Retornando ao menu...\n");
        return;
    }

    int id;
    printf("Digite o ID do registro a ser atualizado: ");
    scanf("%d", &id); getchar();

    No *n = bd_buscar_por_id(bd, id);
    if (!n) {
        printf("ID não encontrado.\n");
        return;
    }

    Paciente *p = &n->paciente;
    Paciente novo = *p; // cópia para edição

    int valid = 0;
    char buffer[100];

    do {
        valid = 1; // assume válido até que algum campo falhe

        // CPF
        printf("Digite o novo CPF (apenas números, ou '-' p/ manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "-") != 0) {
            if (strlen(buffer) == 11 && strspn(buffer, "0123456789") == 11) {
                snprintf(novo.cpf, sizeof(novo.cpf),
                         "%.3s.%.3s.%.3s-%.2s", buffer, buffer+3, buffer+6, buffer+9);
            } else {
                printf("[Erro] CPF inválido. Tente novamente.\n\n");
                valid = 0;
                continue;
            }
        }

        // Nome
        printf("Digite o novo Nome (ou '-' p/ manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "-") != 0) {
            if (strlen(buffer) == 0) {
                printf("[Erro] Nome não pode ser vazio. Tente novamente.\n\n");
                valid = 0;
                continue;
            }
            strncpy(novo.nome, buffer, sizeof(novo.nome));
        }

        // Idade
        printf("Digite nova Idade (ou '-' p/ manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "-") != 0) {
            int idade = atoi(buffer);
            if (idade <= 0 || idade > 130) {
                printf("[Erro] Idade inválida. Tente novamente.\n\n");
                valid = 0;
                continue;
            }
            novo.idade = idade;
        }

        // Data de cadastro
        printf("Digite nova Data Cadastro (ou '-' p/ manter): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, "-") != 0) {
            int ano, mes, dia;
            if (sscanf(buffer, "%d-%d-%d", &ano, &mes, &dia) == 3 &&
                ano >= 1900 && ano <= 2100 &&
                mes >= 1 && mes <= 12 &&
                dia >= 1 && dia <= 31) {
                strncpy(novo.data_cadastro, buffer, sizeof(novo.data_cadastro));
            } else {
                printf("[Erro] Data inválida. Tente novamente.\n\n");
                valid = 0;
                continue;
            }
        }

    } while (!valid);

    // Confirmação
    printf("\nConfirma atualização do registro?\n\n");
    paciente_imprimir(novo);
    printf("S/N: ");
    char op = getchar(); getchar();

    if (op == 'S' || op == 's') {
        *p = novo;
        printf("Registro atualizado com sucesso.\n\n");
    } else {
        printf("Atualização cancelada.\n\n");
    }
}

// tem que chamar consultar primeiro para verificar se o paciente esta na memoria 
void ui_remover(BDPaciente *bd) {
    ui_exibir_por_nome_ou_cpf(bd); // primeira exibição
    if (!ui_exibir_por_nome_ou_cpf(bd)) { // segunda tentativa
        return;
    }
    
    int id;
    printf("Digite o ID do registro a ser removido: ");
    scanf("%d", &id); getchar();

    No *n = bd_buscar_por_id(bd, id);
    if (!n) {
        printf("ID não encontrado.\n");
        return;
    }

    printf("Tem certeza que deseja remover este registro?\n");
    paciente_imprimir(n->paciente);
    printf("S/N: ");
    char op = getchar(); getchar();
    if (op == 'S' || op == 's') {
        bd_remover(bd, id);
        printf("Registro removido.\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}

// espaço entre as funções 
void ui_exibir_menu(BDPaciente *bd, const char *arquivo) {
    char opcao;
    do {
        printf("1 - Consultar paciente\n"
               "2 - Atualizar paciente\n"
               "3 - Remover paciente\n"
               "4 - Inserir paciente\n"
               "5 - Imprimir lista\n"
               "Q - Sair\n\nEscolha: \n\n");

        scanf(" %c", &opcao); getchar(); //recebe a opção que o usuario digitar 

        switch (opcao) {
            case '1': ui_consultar(bd); break;
            case '2': ui_atualizar(bd); break;
            case '3': ui_remover(bd); break;
            case '4': ui_inserir(bd); bd_salvar_arquivo(bd, arquivo); break;
            case '5': bd_imprimir(bd, 20); break;
            case 'Q': case 'q': printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');
}
