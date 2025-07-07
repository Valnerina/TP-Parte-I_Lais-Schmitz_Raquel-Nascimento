#ifndef BD_H
#define BD_H

#include "paciente.h"

typedef struct No {
    Paciente paciente;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
} BDPaciente;

BDPaciente *bd_criar(void);
void bd_destruir(BDPaciente *bd); 

void bd_carregar_arquivo(BDPaciente *bd, const char *filename);
void bd_salvar_arquivo(BDPaciente *bd, const char *filename);

void bd_inserir(BDPaciente *bd, Paciente p);
void bd_imprimir(BDPaciente *bd, int paginacao);
void bd_buscar(BDPaciente *bd, const char *query, int tipo);

int bd_remover(BDPaciente *bd, int id);
int bd_atualizar(BDPaciente *bd, int id, Paciente novo);
No* bd_buscar_por_id(BDPaciente *bd, int id);

#endif
