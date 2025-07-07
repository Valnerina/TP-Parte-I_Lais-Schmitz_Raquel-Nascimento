#ifndef BD_H
#define BD_H

#include "paciente.h"

// Nó da lista ligada, contendo um paciente e ponteiro para o próximo
typedef struct No {
    Paciente paciente;
    struct No *proximo;
} No;

// Estrutura do banco de pacientes, aponta para o início da lista
typedef struct {
    No *inicio;
} BDPaciente;

// Cria um banco de dados vazio
BDPaciente *bd_criar(void);

// Libera toda a memória alocada pelo banco
void bd_destruir(BDPaciente *bd); 

// Carrega pacientes de um arquivo texto para o banco
void bd_carregar_arquivo(BDPaciente *bd, const char *filename);

// Salva os pacientes em um arquivo texto
void bd_salvar_arquivo(BDPaciente *bd, const char *filename);

// Insere um novo paciente na lista
void bd_inserir(BDPaciente *bd, Paciente p);

// Imprime os pacientes com paginação
void bd_imprimir(BDPaciente *bd, int paginacao);

// Busca paciente por nome ou CPF (tipo define o critério)
void bd_buscar(BDPaciente *bd, const char *query, int tipo);

// Remove paciente com ID correspondente
int bd_remover(BDPaciente *bd, int id);

// Atualiza os dados de um paciente com ID especificado
int bd_atualizar(BDPaciente *bd, int id, Paciente novo);

// Retorna o nó do paciente com o ID fornecido
No* bd_buscar_por_id(BDPaciente *bd, int id);

#endif
