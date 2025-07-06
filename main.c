/*
 * Trabalho de Programação - Sistema HealthSys
 * Arquivo: main.c
 * Responsável por inicializar o programa e gerenciar o menu principal.
 * Autor: [Seu Nome]
 * IFES - Campus Serra - Prof. Thiago Paixão
 */

#include "bd.h"
#include "ui.h"
#include <stdio.h>

int main(void) {
    const char *arquivo = "bd_paciente.csv";

    // Cria o banco de dados (lista encadeada)
    BDPaciente *bd = bd_criar();

    // Carrega dados do CSV
    bd_carregar_arquivo(bd, arquivo);

    // Executa menu principal
    ui_exibir_menu(bd, arquivo);

    bd_destruir(bd);
    // Libera memória
    // bd_remover(bd, id);
    return 0;
}
