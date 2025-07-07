#include "bd.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BDPaciente *bd_criar(void) {
    BDPaciente *bd = malloc(sizeof(BDPaciente));
    if (bd) bd->inicio = NULL;
    return bd;
}

void bd_destruir(BDPaciente *bd) {
    No *atual = bd->inicio;
    while (atual) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(bd);
}

void bd_inserir(BDPaciente *bd, Paciente p) {
    No *novo = malloc(sizeof(No));
    novo->paciente = p;
    novo->proximo = bd->inicio;
    bd->inicio = novo;
}

void bd_carregar_arquivo(BDPaciente *bd, const char *filename) {
    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) {
        printf("Arquivo %s não encontrado.\n", filename);
        return;
    }
    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // pula cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        Paciente p = paciente_parse(linha);
        bd_inserir(bd, p);
    }
    fclose(arquivo);
}

void bd_salvar_arquivo(BDPaciente *bd, const char *filename) {
    FILE *arquivo = fopen(filename, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", filename);
        return;
    }
    fprintf(arquivo, "ID,CPF,Nome,Idade,Data_Cadastro\n");
    No *atual = bd->inicio;
    while (atual) {
        Paciente p = atual->paciente;
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void bd_imprimir(BDPaciente *bd, int paginacao) {
    No *atual = bd->inicio;
    int count = 0;
    printf("\n%-5s | %-17s | %-20s | %-7s | %-12s\n",
           "ID", "CPF", "Nome", "Idade", "Data_Cadastro");
    printf("-----------------------------------------------------------\n");
    while (atual) {
        paciente_imprimir(atual->paciente);
        atual = atual->proximo;
        count++;
        if (count % paginacao == 0) {
            char op;
            printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ",
                   count/paginacao);
            op = getchar();
            if (op == 'Q' || op == 'q') break;
        }
    }
    printf("\nTotal: %d pacientes.\n", count);
}

void bd_buscar(BDPaciente *bd, const char *query, int tipo) {
    No *atual = bd->inicio;
    int encontrou = 0;
    while (atual) {
        Paciente p = atual->paciente;
        if ((tipo == 1 && strncasecmp(p.nome, query, strlen(query)) == 0) ||
            (tipo == 2 && strncmp(p.cpf, query, strlen(query)) == 0)) {
            paciente_imprimir(p);
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
        if (atual->paciente.id == id)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

int bd_atualizar(BDPaciente *bd, int id, Paciente novo) {
    No *n = bd_buscar_por_id(bd, id);
    if (!n) return 0; // não encontrado
    n->paciente = novo;
    return 1;
}

int bd_remover(BDPaciente *bd, int id) {
    No *atual = bd->inicio, *anterior = NULL;
    while (atual) {
        if (atual->paciente.id == id) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                bd->inicio = atual->proximo;
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}
