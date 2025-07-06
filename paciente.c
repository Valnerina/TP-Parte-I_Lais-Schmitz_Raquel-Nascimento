#include "paciente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

Paciente paciente_parse(char *linha_csv) {
    Paciente p;
    char *token;

    token = strtok(linha_csv, ",");
    p.id = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    strncpy(p.cpf, token ? token : "", sizeof(p.cpf));
    p.cpf[sizeof(p.cpf) - 1] = '\0';

    token = strtok(NULL, ",");
    strncpy(p.nome, token ? token : "", sizeof(p.nome));
    p.nome[sizeof(p.nome) - 1] = '\0';

    token = strtok(NULL, ",");
    p.idade = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    if (token) {
        strncpy(p.data_cadastro, token, sizeof(p.data_cadastro));
        p.data_cadastro[strcspn(p.data_cadastro, "\r\n")] = '\0';
    } else {
        strcpy(p.data_cadastro, "");
    }

    return p;
}

void paciente_imprimir(Paciente p) {
    printf("%-5d | %-17s | %-20s | %-7d | %-12s\n",
           p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
}
