#include "bd.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BDPaciente *bd_criar(void) {
    BDPaciente *bd = malloc(sizeof(BDPaciente)); // Aloca memória para o banco
    if (bd) bd->inicio = NULL; // Inicializa lista vazia
    return bd;
}

void bd_destruir(BDPaciente *bd) {
    No *atual = bd->inicio;
    while (atual) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp); // Libera cada nó
    }
    free(bd); // Libera a estrutura do banco
}

void bd_inserir(BDPaciente *bd, Paciente p) {
    No *novo = malloc(sizeof(No)); // Cria novo nó
    novo->paciente = p; // Atribui paciente
    novo->proximo = bd->inicio; // Insere no início
    bd->inicio = novo;
}

void bd_carregar_arquivo(BDPaciente *bd, const char *filename) {
    FILE *arquivo = fopen(filename, "r"); // Abre arquivo para leitura
    if (!arquivo) {
        printf("Arquivo %s não encontrado.\n", filename);
        return;
    }
    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) { 
        Paciente p = paciente_parse(linha); // Converte linha para paciente
        bd_inserir(bd, p); // Insere no banco
    }
    fclose(arquivo); // Fecha arquivo
}

void bd_salvar_arquivo(BDPaciente *bd, const char *filename) {
    FILE *arquivo = fopen(filename, "w"); // Abre arquivo para escrita
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", filename);
        return;
    }
    fprintf(arquivo, "ID,CPF,Nome,Idade,Data_Cadastro\n"); // Cabeçalho CSV
    No *atual = bd->inicio;
    while (atual) {
        Paciente p = atual->paciente;
        fprintf(arquivo, "%d,%s,%s,%d,%s\n", // Escreve paciente
                p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
        atual = atual->proximo;
    }
    fclose(arquivo); // Fecha arquivo
}

void bd_imprimir(BDPaciente *bd, int paginacao) {
    No *atual = bd->inicio;
    int count = 0;
    printf("\n%-5s | %-17s | %-20s | %-7s | %-12s\n",
           "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    printf("-----------------------------------------------------------\n");
    while (atual) {
        paciente_imprimir(atual->paciente); // Mostra paciente
        atual = atual->proximo;
        count++;
        if (count % paginacao == 0) { // Controle de página
            char op;
            printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ",
                   count/paginacao);
            op = getchar();
            if (op == 'Q' || op == 'q') break;
        }
    }
    printf("\nTotal: %d pacientes.\n", count); // Mostra total
}

void bd_buscar(BDPaciente *bd, const char *query, int tipo) {
    No *atual = bd->inicio;
    int encontrou = 0;
    while (atual) {
        Paciente p = atual->paciente;
        if ((tipo == 1 && strncasecmp(p.nome, query, strlen(query)) == 0) ||
            (tipo == 2 && strncmp(p.cpf, query, strlen(query)) == 0)) {
            paciente_imprimir(p); // Imprime se encontrou
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou)
        printf("Nenhum paciente encontrado com o prefixo informado.\n");
}

No* bd_buscar_por_id(BDPaciente *bd, int id) {
    No *atual = bd->inicio;
    while (atual) {
        if (atual->paciente.id == id) // Verifica ID
            return atual;
        atual = atual->proximo;
    }
    return NULL; // Não achou
}

int bd_atualizar(BDPaciente *bd, int id, Paciente novo) {
    No *n = bd_buscar_por_id(bd, id); // Busca nó por ID
    if (!n) return 0; // Não encontrou
    n->paciente = novo; // Atualiza dados
    return 1; // Sucesso
}

int bd_remover(BDPaciente *bd, int id) {
    No *atual = bd->inicio, *anterior = NULL;
    while (atual) {
        if (atual->paciente.id == id) { // Achou paciente
            if (anterior)
                anterior->proximo = atual->proximo; // Remove do meio/fim
            else
                bd->inicio = atual->proximo; // Remove do início
            free(atual); // Libera memória
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0; // Não encontrou
}
