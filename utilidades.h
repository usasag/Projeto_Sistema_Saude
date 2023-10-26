
#ifndef PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
#define PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcularIdade(const char dataNascimento[]) {
    // Supondo que a data seja conhecida...
    int anoAtual = 2023; // Substitua pelo ano atual real
    int mesAtual = 10;   // Substitua pelo mês atual real
    int diaAtual = 26;    // Substitua pelo dia atual real

    // Extrair o ano, mês e dia de nascimento da string de data de nascimento
    int anoNascimento, mesNascimento, diaNascimento;
    if (sscanf(dataNascimento, "%d/%d/%d", &diaNascimento, &mesNascimento, &anoNascimento) != 3) {
        // Formato de data de nascimento inválido
        return -1;
    }

    // Calcular a idade
    int idade = anoAtual - anoNascimento;

    // Verificar se o aniversário ainda não ocorreu neste ano
    if (mesAtual < mesNascimento || (mesAtual == mesNascimento && diaAtual < diaNascimento)) {
        idade--; // Subtrair 1 ano da idade
    }

    return idade;
}

#endif //PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
