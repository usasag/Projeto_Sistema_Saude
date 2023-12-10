
#ifndef PROJETO_SISTEMA_SAUDE_TRABALHO_PACIENTES_H
#define PROJETO_SISTEMA_SAUDE_TRABALHO_PACIENTES_H
#include "utilidades.h"
#include "crud.h"

int codigosPacientesParaAtendimentos[MAX_ATENDIMENTOS];

int adicionarPaciente
        (
                int codigosPacientes[], char nomes[][50], char generos[][10],
                char RGs[][15], char CPFs[][15], char tiposSanguineos[][5],
                char fatoresRH[], char enderecos[][100],
                char datasNascimento[][11], int idades[],
                int proximoCodigoPaciente, int totalPacientes)
{
    if (totalPacientes >= MAX_PACIENTES) {
        printf("Numero maximo de pacientes atingido.\n");
        return proximoCodigoPaciente;
    }

    // Limpar o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Solicitar o nome até que seja fornecido (obrigatório)
    do {
        printf("\nDigite o nome: ");
        if (fgets(nomes[totalPacientes], sizeof(nomes[0]), stdin) != NULL) {
            nomes[totalPacientes][strcspn(nomes[totalPacientes], "\n")] = '\0';
        } else {
            printf("Por favor, insira um nome valido.\n");
        }
    } while (strlen(nomes[totalPacientes]) == 0);

    // Escolher o Gênero (F ou M)
    printf("Informe o genero biologico (Digite apenas F ou M): ");
    char genero;
    scanf(" %c", &genero);

    if (genero != 'F' && genero != 'M') {
        printf("Escolha invalida. Nenhuma informacao alterada.\n");
        return proximoCodigoPaciente;
    }

    generos[totalPacientes][0] = genero;
    generos[totalPacientes][1] = '\0';

    // Solicitar o RG
    printf("Digite o RG: ");
    if (fgets(RGs[totalPacientes], sizeof(RGs[0]), stdin) != NULL) {
        RGs[totalPacientes][strcspn(RGs[totalPacientes], "\n")] = '\0';
    }

    while (getchar() != '\n');
    // Solicitar o CPF (Obrigatório)
    while (1) {
        printf("Digite o CPF (apenas os numeros): ");
        if (fgets(CPFs[totalPacientes], sizeof(CPFs[0]), stdin) != NULL) {
            CPFs[totalPacientes][strcspn(CPFs[totalPacientes], "\n")] = '\0';
            if (strlen(CPFs[totalPacientes]) == 11) {
                break;
            }
        }
        printf("Por favor insira um CPF valido (11 digitos).\n" );
    }

    // Escolher o Tipo Sanguíneo
    int escolhaTipoSanguineo;
    printf("Escolha o Tipo Sanguineo\n 1. A\n 2. B\n 3. AB\n 4. O\n ");
    scanf("%d", &escolhaTipoSanguineo);

    if (escolhaTipoSanguineo < 1 || escolhaTipoSanguineo > 4) {
        printf("Escolha invalida. Nenhuma informacao alterada.\n");
        return proximoCodigoPaciente;
    }

    char tiposSanguineosPossiveis[4][3] = { "A", "B", "AB", "O" };
    strcpy(tiposSanguineos[totalPacientes], tiposSanguineosPossiveis[escolhaTipoSanguineo - 1]);

    // Se o tipo sanguíneo for informado, só então pedir o fator RH
    if (tiposSanguineos[totalPacientes][0] != '\0') {
        printf("Escolha o Fator RH (+/-): ");
        scanf(" %c", &fatoresRH[totalPacientes]);

        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("Digite o endereco: ");
    if (fgets(enderecos[totalPacientes], sizeof(enderecos[0]), stdin) != NULL) {
        enderecos[totalPacientes][strcspn(enderecos[totalPacientes], "\n")] = '\0';
    }

    // Solicitar a data de nascimento até que seja fornecida (obrigatório)
    do {
        printf("Digite a data de nascimento (obrigatoriamente no formato dd/mm/yyyy): ");
        if (fgets(datasNascimento[totalPacientes], sizeof(datasNascimento[0]), stdin) != NULL) {
            datasNascimento[totalPacientes][strcspn(datasNascimento[totalPacientes], "\n")] = '\0';
        }
    } while (strlen(datasNascimento[totalPacientes]) <= 9);

    // Calcular a idade e atribuir o próximo código de paciente disponível
    idades[totalPacientes] = calcularIdade(datasNascimento[totalPacientes]);
    codigosPacientes[totalPacientes] = proximoCodigoPaciente;
    proximoCodigoPaciente++;
    fflush(stdin);

    printf("Paciente adicionado com sucesso.\n Codigo do Paciente: %d\n", codigosPacientes[totalPacientes]);
    return proximoCodigoPaciente;
}

int removerPaciente
        (
                int codigosPacientes[],char nomes[][50],
                char RGs[][15],char CPFs[][15],
                char tiposSanguineos[][5],char fatoresRH[],
                char enderecos[][100],char datasNascimento[][11],
                int idades[],int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel para remocao.\n");
        return totalPacientes;
    }

    int codigoPaciente;
    printf("Digite o Codigo do Paciente para remocao: ");
    scanf("%d", &codigoPaciente);

    int indicePaciente = -1;
    for (int i = 0; i < totalPacientes; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            indicePaciente = i;
            break;
        }
    }

    if (indicePaciente == -1) {
        printf("Paciente com o codigo fornecido nao encontrado.\n");
        return totalPacientes;
    }

    // Confirmar o nome do paciente antes de remover
    printf("Confirme o nome do paciente para remocao (digite exatamente): ");
    char nomeConfirmacao[50];
    scanf(" %[^\n]", nomeConfirmacao);

    if (strcmp(nomes[indicePaciente], nomeConfirmacao) != 0) {
        printf("O nome do paciente nao corresponde. Remocao cancelada.\n");
        return totalPacientes;
    }

    // Deslocar os pacientes restantes para preencher a lacuna.
    for (int i = indicePaciente; i < totalPacientes - 1; i++) {
        codigosPacientes[i] = codigosPacientes[i + 1];
        strcpy(nomes[i], nomes[i + 1]);
        strcpy(RGs[i], RGs[i + 1]);
        strcpy(CPFs[i], CPFs[i + 1]);
        strcpy(tiposSanguineos[i], tiposSanguineos[i + 1]);
        fatoresRH[i] = fatoresRH[i + 1];
        strcpy(enderecos[i], enderecos[i + 1]);
        strcpy(datasNascimento[i], datasNascimento[i + 1]);
        idades[i] = idades[i + 1];
    }

    printf("Paciente removido com sucesso. \n");
    return totalPacientes - 1; // Retorna o número atualizado dos pacientes.
}

void listarPacientesComInformacoes
        (
                int codigosPacientes[],char nomes[][50],
                int idades[], char generos[][10],
                int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente para ser listado.\n");
        return;
    }

    printf("\nLista de Pacientes com Informacoes:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf("Codigo: %d\n", codigosPacientes[i]);
        printf("Genero: %s\n", generos[i]);
        printf("Nome: %s\n", nomes[i]);
        printf("Idade: %d\n", idades[i]);
        printf("---------------------------------------------\n");
    }
}

void alterarDadosPaciente
        (
                int codigosPacientes[], char nomes[][50],
                char generos[][10], char RGs[][15],
                char CPFs[][15], char tiposSanguineos[][5],
                char fatoresRH[], char enderecos[][100],
                char datasNascimento[][11], int idades[],
                int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel para edicao.\n");
        return;
    }

    int codigoPaciente;
    printf("Digite o Codigo do Paciente para edicao: ");
    scanf("%d", &codigoPaciente);

    int indicePaciente = -1;
    for (int i = 0; i < totalPacientes; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            indicePaciente = i;
            break;
        }
    }

    if (indicePaciente == -1) {
        printf("Paciente com o codigo fornecido não encontrado.\n");
        return;
    }

    int escolha = -1;
    while (escolha != 0) {
        printf("Informacoes do Paciente (Codigo %d):\n", codigoPaciente);
        printf("1. Nome: %s\n", nomes[indicePaciente]);
        printf("2. Genero: %s\n", generos[indicePaciente]);
        printf("3. RG: %s\n", RGs[indicePaciente]);
        printf("4. CPF: %s\n", CPFs[indicePaciente]);
        printf("5. Tipo Sanguineo: %s\n", tiposSanguineos[indicePaciente]);
        printf("6. Fator RH: %c\n", fatoresRH[indicePaciente]);
        printf("7. Endereco: %s\n", enderecos[indicePaciente]);
        printf("8. Data de Nascimento: %s\n", datasNascimento[indicePaciente]);
        printf("9. Idade: %d\n", idades[indicePaciente]);
        printf("0. Sair\n");

        printf("Selecione a informacao a ser alterada (0 para sair): ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            printf("Digite o novo nome: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            while (1) {
                if (fgets(nomes[indicePaciente], sizeof(nomes[indicePaciente]), stdin)) {
                    nomes[indicePaciente][strcspn(nomes[indicePaciente], "\n")] = '\0';
                    if (strlen(nomes[indicePaciente]) > 0) {
                        break;
                    } else {
                        printf("Por favor, insira um nome valido: ");
                    }
                } else {
                    printf("Nome nao especificado.\n");
                    return;
                }
            }
        }
        else if (escolha == 2) {
            printf("Novo Genero: ");
            while (getchar() != '\n');
            fgets(generos[indicePaciente], sizeof(generos[0]), stdin);
            generos[indicePaciente][strcspn(generos[indicePaciente], "\n")] = '\0';
        }
        else if (escolha == 3) {
            printf("Novo RG: ");
            while (getchar() != '\n');
            fgets(RGs[indicePaciente], sizeof(RGs[0]), stdin);
            RGs[indicePaciente][strcspn(RGs[indicePaciente], "\n")] = '\0';
        }
        else if (escolha == 4) {
            printf("Digite o novo CPF: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            while (1) {
                if (fgets(CPFs[indicePaciente], sizeof(CPFs[indicePaciente]), stdin)) {
                    CPFs[indicePaciente][strcspn(CPFs[indicePaciente], "\n")] = '\0';
                    if (strlen(CPFs[indicePaciente]) > 0) {
                        break;
                    } else {
                        printf("Por favor, insira um CPF valido: ");
                    }
                } else {
                    printf("CPF nao especificado.\n");
                    return;
                }
            }
        }
        else if (escolha == 5) {
            printf("Novo Tipo Sanguineo: ");
            while (getchar() != '\n');
            fgets(tiposSanguineos[indicePaciente], sizeof(tiposSanguineos[0]), stdin);
            tiposSanguineos[indicePaciente][strcspn(tiposSanguineos[indicePaciente], "\n")] = '\0';
        }
        else if (escolha == 6) {
            printf("Novo Fator RH: ");
            scanf(" %c", &fatoresRH[indicePaciente]);
        }
        else if (escolha == 7) {
            printf("Novo Endereco: ");
            while (getchar() != '\n');
            fgets(enderecos[indicePaciente], sizeof(enderecos[0]), stdin);
            enderecos[indicePaciente][strcspn(enderecos[indicePaciente], "\n")] = '\0';
        }
        else if (escolha == 8) {
            printf("Digite a nova data de nascimento: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            while (1) {
                if (fgets(datasNascimento[indicePaciente], sizeof(datasNascimento[indicePaciente]), stdin)) {
                    datasNascimento[indicePaciente][strcspn(datasNascimento[indicePaciente], "\n")] = '\0';
                    if (strlen(datasNascimento[indicePaciente]) > 0) {
                        break;
                    } else {
                        printf("Por favor, insira uma data de nacimento valida: ");
                    }
                } else {
                    printf("Data de nascimento nao especificado.\n");
                    return;
                }
            }
            idades[indicePaciente] = calcularIdade(datasNascimento[indicePaciente]);
        }
        else if (escolha == 9) {
            printf("A idade e automaticamente calculada com base na data de nascimento.\n");
        }
        else if (escolha == 0) {
            return;
        }
        else {
            printf("Escolha invalida. Tente novamente.\n");
        }
    }

    printf("Informacoes do Paciente (Codigo %d) atualizadas com sucesso.\n", codigoPaciente);
}

void listarPacientesPorTipoSanguineo
        (
                int codigosPacientes[], char nomes[][50],
                char tiposSanguineos[][5], char fatoresRH[],
                char datasNascimento[][11], int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel para listar.\n");
        return;
    }

    char tipoSanguineoBuscado[5];
    printf("Digite o tipo sanguineo a ser listado: ");
    while (getchar() != '\n');
    fgets(tipoSanguineoBuscado, sizeof(tipoSanguineoBuscado), stdin);
    tipoSanguineoBuscado[strcspn(tipoSanguineoBuscado, "\n")] = '\0';

    int encontrados = 0;

    for (int i = 0; i < totalPacientes; i++) {
        if (strcmp(tiposSanguineos[i], tipoSanguineoBuscado) == 0) {
            encontrados = 1;
            printf("Codigo do Paciente: %d\n", codigosPacientes[i]);
            printf("Nome: %s\n", nomes[i]);
            printf("Tipo Sanguineo: %s\n", tiposSanguineos[i]);
            printf("Fator RH: %c\n", fatoresRH[i]);
            printf("Idade: %d\n", calcularIdade(datasNascimento[i]));
            printf("\n");
        }
    }

    if (!encontrados) {
        printf("Nenhum paciente encontrado com o tipo sanguineo especificado.\n");
    }
}

void ordenarPacientesPorNome
        (
                int codigosPacientes[], char nomes[][50],
                int totalPacientes, int idades[], int ordemPorNome[]
        )
{
    int troca = 1;
    while (troca) {
        troca = 0;
        for (int i = 0; i < totalPacientes - 1; i++) {
            if (strcmp(nomes[i], nomes[i + 1]) > 0) {

                int tempCodigo = codigosPacientes[i];
                codigosPacientes[i] = codigosPacientes[i + 1];
                codigosPacientes[i + 1] = tempCodigo;

                int tempIdade = idades[i];
                idades[i] = idades[i + 1];
                idades[i + 1] = tempIdade;

                char tempNome[100];
                strcpy(tempNome, nomes[i]);
                strcpy(nomes[i], nomes[i + 1]);
                strcpy(nomes[i + 1], tempNome);

                int tempIndice = ordemPorNome[i];
                ordemPorNome[i] = ordemPorNome[i + 1];
                ordemPorNome[i + 1] = tempIndice;

                troca = 1;
            }
        }
    }
}

void mostrarPacientesOrdenados
        (
                int codigosPacientes[], char nomes[][50],
                int idades[], int totalPacientes
        )
{
    int ordemPorNome[MAX_PACIENTES];
    for (int i = 0; i < totalPacientes; i++) {
        ordemPorNome[i] = i;
    }
    ordenarPacientesPorNome(codigosPacientes, nomes, totalPacientes, idades, ordemPorNome);
    printf("\nLista de Pacientes Ordenados por Nome:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < totalPacientes; i++) {
        int index = ordemPorNome[i];
        printf("Codigo: %d\n", codigosPacientes[index]);
        printf("Nome: %s\n", nomes[index]);
        printf("Idade: %d\n", idades[index]);
        printf("---------------------------------------------\n");
    }
}

void exibirInformacoesPaciente
        (
                int codigosPacientes[], char nomes[][50],
                char RGs[][15], char CPFs[][15],
                char tiposSanguineos[][5], char fatoresRH[],
                char enderecos[][100], char datasNascimento[][11],
                int idades[], int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel.\n");
        return;
    }

    int codigoPaciente;
    printf("Digite o Codigo do Paciente: ");
    scanf("%d", &codigoPaciente);

    int indicePaciente = -1;
    for (int i = 0; i < totalPacientes; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            indicePaciente = i;
            break;
        }
    }

    if (indicePaciente == -1) {
        printf("Paciente com o codigo fornecido nao encontrado.\n");
    } else {
        // Exibir informações do paciente
        printf("Codigo do Paciente: %d\n", codigosPacientes[indicePaciente]);
        printf("Nome: %s\n", nomes[indicePaciente]);
        printf("RG: %s\n", RGs[indicePaciente]);
        printf("CPF: %s\n", CPFs[indicePaciente]);
        printf("Tipo Sanguineo: %s\n", tiposSanguineos[indicePaciente]);
        printf("Fator RH: %c\n", fatoresRH[indicePaciente]);
        printf("Endereco: %s\n", enderecos[indicePaciente]);
        printf("Data de Nascimento: %s\n", datasNascimento[indicePaciente]);
        printf("Idade: %d\n", idades[indicePaciente]);
    }
}

#endif //PROJETO_SISTEMA_SAUDE_TRABALHO_PACIENTES_H
