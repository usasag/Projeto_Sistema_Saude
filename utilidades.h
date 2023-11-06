
#ifndef PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
#define PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcularIdade(const char dataNascimento[]) {
    int anoAtual = 0;
    int mesAtual = 0;
    int diaAtual = 0;

    // Extrair o ano, mês e dia de nascimento da string de data de nascimento
    int anoNascimento, mesNascimento, diaNascimento;
    if (sscanf(dataNascimento, "%d/%d/%d", &diaNascimento, &mesNascimento, &anoNascimento) != 3) {
        return -1;
    }

    int idade = anoAtual - anoNascimento;

    // Verificar se o aniversário ainda não ocorreu neste ano
    if (mesAtual < mesNascimento || (mesAtual == mesNascimento && diaAtual < diaNascimento)) {
        idade--; // Subtrair 1 ano da idade
    }

    return idade;
}

#endif //PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
