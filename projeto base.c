#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

int codigosPacientesParaAtendimentos[MAX_ATENDIMENTOS];
int numeroAtendimentoPorPaciente[MAX_PACIENTES] = {0};

int main() {
    int codigosPacientes[MAX_PACIENTES];
    char nomes[MAX_PACIENTES][50];
    char RGs[MAX_PACIENTES][15];
    char CPFs[MAX_PACIENTES][15];
    char tiposSanguineos[MAX_PACIENTES][5];
    char generos[MAX_PACIENTES][10];
    char fatoresRH[MAX_PACIENTES];
    char enderecos[MAX_PACIENTES][100];
    char datasNascimento[MAX_PACIENTES][11];
    int idades[MAX_PACIENTES];
    int ordemPorNome[MAX_PACIENTES];


    int codigosAtendimentos[MAX_ATENDIMENTOS];
    char tipos[MAX_ATENDIMENTOS][20];
    char datasAtendimento[MAX_ATENDIMENTOS][11];
    char status[MAX_ATENDIMENTOS][50];
    float precos[MAX_ATENDIMENTOS];

    int totalAtendimentos = 0;
    int proximoCodigoPaciente = 1000; // Código inicial do paciente
    int totalPacientes = proximoCodigoPaciente - 1000;

    while (1) {
        printf("--------------------------------------------\n");
        printf("Pacientes:\n");
        printf("\n1. Adicionar Paciente\n");
        printf("2. Remover Paciente\n");
        printf("3. Editar Informacoes do Paciente\n");
        printf("4. Exibir Informacoes do Paciente\n");
        printf("5. Listar Pacientes com Informacoes\n");
        printf("6. Listar Pacientes com Consultas em um Dia\n");
        printf("7. Listar Pacientes por Tipo Sanguineo\n");
        printf("8. Listar Pacientes por Ordem Alfabetica\n");
        printf("\n--------------------------------------------\n");
        printf("Atendimentos:\n");
        printf("\n9. Adicionar Atendimento\n");
        printf("10. Remover Atendimento\n");
        printf("11. Editar Atendimentos\n");
        printf("12. Exibir Atendimentos\n");
        printf("13. Listar Soma dos Atendimentos Pagos por Paciente\n");
        printf("14. Listar Soma dos Atendimentos Pagos em um Dia\n");
        printf("15. Listar Soma dos Atendimentos Pagos por Periodo\n");
        printf("--------------------------------------------\n");
        printf("0. Sair\n");
        printf("--------------------------------------------\n");

        int escolha;
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            proximoCodigoPaciente = adicionarPaciente
                    (
                            codigosPacientes, nomes,
                            generos, RGs,
                            CPFs, tiposSanguineos,
                            fatoresRH, enderecos,
                            datasNascimento, idades,
                            proximoCodigoPaciente, totalPacientes
                    );
            totalPacientes = proximoCodigoPaciente - 1000;
        } else if (escolha == 2) {
            totalPacientes = removerPaciente
                    (
                            codigosPacientes, nomes,
                            RGs, CPFs,
                            tiposSanguineos, fatoresRH,
                            enderecos, datasNascimento,
                            idades, totalPacientes
                    );
        } else if (escolha == 3) {
            alterarDadosPaciente
                    (
                            codigosPacientes, nomes,
                            generos, RGs,
                            CPFs, tiposSanguineos,
                            fatoresRH, enderecos,
                            datasNascimento, idades,
                            totalPacientes
                    );
        } else if (escolha == 4) {
            exibirInformacoesPaciente
                    (
                            codigosPacientes, nomes,
                            RGs, CPFs,
                            tiposSanguineos, fatoresRH,
                            enderecos, datasNascimento,
                            idades, totalPacientes
                    );
        } else if (escolha == 5) {
            listarPacientesComInformacoes
                    (
                            codigosPacientes, nomes,
                            idades, generos,
                            totalPacientes
                    );
        } else if (escolha == 6) {
            listarConsultasPorData
                    (
                            codigosPacientes, nomes,
                            generos, datasNascimento,
                            idades, codigosAtendimentos,
                            tipos, precos, datasAtendimento,
                            totalPacientes, totalAtendimentos
                    );
        } else if (escolha == 7) {
            listarPacientesPorTipoSanguineo
                    (
                            codigosPacientes, nomes,
                            tiposSanguineos, fatoresRH,
                            datasNascimento, totalPacientes
                    );
        } else if (escolha == 8) {
            mostrarPacientesOrdenados
            (
                    codigosPacientes,nomes,
                    idades, totalPacientes);
        } else if (escolha == 9) {
            totalAtendimentos = adicionarAtendimento
                    (
                            codigosAtendimentos, codigosPacientes,
                            tipos, datasAtendimento,
                            status, precos,
                            totalAtendimentos, totalPacientes
                    );
        } else if (escolha == 10) {
            totalAtendimentos = removerAtendimento
                    (
                            codigosAtendimentos, status, totalAtendimentos
                    );
        } else if (escolha == 11) {
            editarAtendimento(
                    codigosAtendimentos, totalAtendimentos,
                    codigosPacientes, tipos,
                    datasAtendimento, status, precos, totalPacientes
            );
        } else if (escolha == 12) {
            exibirAtendimentos
                    (
                            codigosAtendimentos,
                            codigosPacientes, tipos,
                            datasAtendimento, status,
                            precos, totalAtendimentos
                    );
        } else if (escolha == 13) {
            mostrarSomaConsultasPorPaciente // Bugado
                    (
                            codigosAtendimentos, precos,
                            totalAtendimentos,codigosPacientes
                    );
        } else if (escolha == 14) {
            mostrarSomaConsultasPorData
                    (
                            codigosAtendimentos, precos,
                            totalAtendimentos, datasAtendimento
                    );
        } else if (escolha == 15) {
            mostrarSomaConsultasPorPeriodo
                    (
                            codigosAtendimentos, precos,
                            datasAtendimento, totalAtendimentos
                    );
        } else if (escolha == 0) {
            exit(0);
        } else {
            printf("Escolha inválida. Por favor, tente novamente.\n");
        }
    }
}

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

    while ((c = getchar()) != '\n');
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

int adicionarAtendimento
        (
                int codigosAtendimentos[], int codigosPacientes[],
                char tipos[][20], char datasAtendimento[][11],
                char status[][50], float precos[],
                int totalAtendimentos, int totalPacientes
        )
{
    if (totalAtendimentos >= MAX_ATENDIMENTOS) {
        printf("Limite maximo de atendimentos atingido.\n");
        return totalAtendimentos;
    }

    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel. Adicione um paciente primeiro.\n");
        return totalAtendimentos;
    }

    // Definir automaticamente o código do atendimento sequencial
    int proximoCodigoAtendimento = totalAtendimentos + 1;
    codigosAtendimentos[totalAtendimentos] = proximoCodigoAtendimento;

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
        return totalAtendimentos;
    }

    int c;
    char novaDataAtendimento[11];

    while ((c = getchar()) != '\n' && c != EOF);
    do {
        printf("Digite a data do atendimento (dd/mm/yyyy): ");
        if (fgets(novaDataAtendimento, sizeof(novaDataAtendimento), stdin) != NULL) {
            novaDataAtendimento[strcspn(novaDataAtendimento, "\n")] = '\0';
        } else {
            printf("Por favor, insira uma data de atendimento valida.\n");
        }
    } while (strlen(novaDataAtendimento) == 0);

    // Verificar se já existe um atendimento para este paciente na mesma data
    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosPacientesParaAtendimentos[i] == codigoPaciente &&
            strcmp(datasAtendimento[i], novaDataAtendimento) == 0) {
            printf("Erro: Ja existe um atendimento para este paciente na mesma data.\n");
            return totalAtendimentos;
        }
    }

    codigosPacientesParaAtendimentos[totalAtendimentos] = codigoPaciente;

    printf("Selecione o Tipo de Atendimento\n1 - Atendimento\n 2 - Retorno\n ");
    int tipoAtendimento;
    scanf("%d", &tipoAtendimento);

    if (tipoAtendimento == 1) {
        strcpy(tipos[totalAtendimentos], "Atendimento");
    } else if (tipoAtendimento == 2) {
        strcpy(tipos[totalAtendimentos], "Retorno");
    } else {
        printf("Escolha invalida. Nenhuma informacao alterada.\n");
        return totalAtendimentos;
    }

    strcpy(datasAtendimento[totalAtendimentos], novaDataAtendimento);
    strcpy(status[totalAtendimentos], "Agendado");
    printf("Digite o Preco: ");
    scanf("%f", &precos[totalAtendimentos]);

    totalAtendimentos++;
    printf("Atendimento adicionado com sucesso. Codigo do Atendimento: %d\n",
           codigosAtendimentos[totalAtendimentos - 1]);

    return totalAtendimentos;
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
        printf("Idade: %d\n", idades[indicePaciente]); // A ser calculada em uma biblioteca futura
    }
}

void exibirAtendimentos
        (
                int codigosAtendimentos[], int codigosPacientes[],
                char tipos[][20], char datasAtendimento[][11],
                char status[][50], float precos[],
                int totalAtendimentos
        ) {
    if (totalAtendimentos == 0) {
        printf("Nenhum atendimento disponivel.\n");
        return;
    }

    int codigoPaciente;
    printf("Digite o Codigo do Paciente: ");
    scanf("%d", &codigoPaciente);

    printf("Atendimentos para o Codigo do Paciente %d:\n", codigoPaciente);

    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            // Exibir informações do atendimento
            printf("Codigo do Atendimento: %d\n", codigosAtendimentos[i]);
            printf("Codigo do Paciente: %d\n", codigosPacientes[i]);
            printf("Tipo: %s\n", tipos[i]);
            printf("Data do Atendimento: %s\n", datasAtendimento[i]);
            printf("Status: %s\n", status[i]);
            printf("Preco: %.2f\n", precos[i]);
        }
    }
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

    // Deslocar os pacientes restantes para preencher o vazio (não sei se é a melhor prática fazer assim, mas ta funcionando)
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
    return totalPacientes - 1; // Retorna o número atualizado dos pacientes
}

int removerAtendimento
        (int codigosAtendimentos[],
         char status[][50],
         int totalAtendimentos) {
    if (totalAtendimentos == 0) {
        printf("Nenhum atendimento disponivel para remocao.\n");
        return totalAtendimentos;
    }

    int codigoAtendimento;
    printf("Digite o Codigo do Atendimento para remocao: ");
    scanf("%d", &codigoAtendimento);

    int indiceAtendimento = -1;
    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosAtendimentos[i] == codigoAtendimento) {
            indiceAtendimento = i;
            break;
        }
    }

    if (indiceAtendimento == -1) {
        printf("Atendimento com o codigo fornecido nao encontrado.\n");
        return totalAtendimentos;
    }

    // Confirmar o código do atendimento antes de remover
    printf("Confirme o codigo do atendimento para remocao: ");
    int codigoConfirmacao;
    scanf("%d", &codigoConfirmacao);

    if (codigoConfirmacao != codigoAtendimento) {
        printf("O codigo do atendimento nao corresponde. Remocao cancelada.\n");
        return totalAtendimentos;
    }

    // Deslocar os atendimentos restantes para preencher a lacuna (mesma coisa dos pacientes)
    for (int i = indiceAtendimento; i < totalAtendimentos - 1; i++) {
        codigosAtendimentos[i] = codigosAtendimentos[i + 1];
        strcpy(status[i], status[i + 1]);
    }

    printf("Atendimento removido com sucesso.\n");
    return totalAtendimentos - 1; // Retorna o número atualizado de atendimentos
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

void listarConsultasPorData
        (
                int codigosPacientes[], char nomes[][50], char generos[][10],
                char datasNascimento[][11], int idades[],
                int codigosAtendimentos[], char tipos[][20], float precos[],
                char datasAtendimento[][11], int totalPacientes, int totalAtendimentos
        )
{
    char dataBuscada[11];
    printf("Digite a data (dd/mm/aaaa) para listar as consultas: ");

    while (getchar() != '\n');
    fgets(dataBuscada, sizeof(dataBuscada), stdin);
    dataBuscada[strcspn(dataBuscada, "\n")] = '\0';

    int encontrados = 0;

    for (int i = 0; i < totalAtendimentos; i++) {
        if (strcmp(datasAtendimento[i], dataBuscada) == 0) {
            for (int j = 0; j < totalPacientes; j++) {
                if (codigosPacientes[j] == codigosAtendimentos[i]) {
                    encontrados = 1;
                    printf("Paciente:\n");
                    printf("Código: %d\n", codigosPacientes[j]);
                    printf("Nome: %s\n", nomes[j]);
                    printf("Gênero: %s\n", generos[j]);
                    printf("Idade: %d\n", idades[j]);

                    printf("Atendimento:\n");
                    printf("Código: %d\n", codigosAtendimentos[i]);
                    printf("Tipo: %s\n", tipos[i]);
                    printf("Preço: %.2f\n", precos[i]);
                    printf("\n");
                }
            }
        }
    }

    if (!encontrados) {
        printf("Nenhuma consulta encontrada para a data especificada.\n");
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
                // Trocar os códigos, nomes e idades dos pacientes
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
            int ordemPorNome[MAX_PACIENTES]; // vetor de índices ordenado por nome
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

void mostrarSomaConsultasPorPaciente // nao funciona ainda
(
        int codigosAtendimentos[], float precos[],
        int totalAtendimentos, int codigosPacientes[]
        )
        {
    if (totalAtendimentos == 0) {
        printf("Nao existem atendimentos para mostrar.");
        return;
    }

    float soma = 0;

    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosAtendimentos[i] == codigosPacientes[i]) {
            soma += precos[i];
        }
    }

    printf("Soma das consultas pagas pelo paciente %d: %.2f\n", codigosPacientes, soma);
}

void mostrarSomaConsultasPorData
(
        int codigosAtendimentos[], float precos[],
        int totalAtendimentos, char datasAtendimento[][11]
        ) {
    if (totalAtendimentos == 0) {
        printf("Nao existem atendimentos para mostrar.\n");
        return;
    }

    char dataAtendimento[11];
    float soma = 0;

    int c;

    while ((c = getchar()) == '\n' && c == EOF);

    printf("Digite uma data para somar os atendimentos feitos nela: ");
    fgets(dataAtendimento, sizeof(dataAtendimento), stdin);
    dataAtendimento[strcspn(dataAtendimento, "\n")] = '\0';

    for (int i = 0; i < totalAtendimentos; i++) {
        if (strcmp(datasAtendimento[i], dataAtendimento) == 0) {
            soma += precos[i];
        }
    }

    printf("Soma das consultas pagas para a data %s: %.2f\n", dataAtendimento, soma);
}

void mostrarSomaConsultasPorPeriodo
        (
            int codigosAtendimentos[], float precos[],
            char datasAtendimento[][11], int totalAtendimentos
        )
        {

    if (totalAtendimentos == 0) {
        printf("Nao existem atendimentos para mostrar.\n");
        return;
    }

    char dataInicial[11];
    char dataFinal[11];
    float soma = 0;


            int c;

            while ((c = getchar()) == '\n' && c == EOF);

            printf("Digite uma data inicial: ");
            fgets(dataInicial, sizeof(dataInicial), stdin);
            dataInicial[strcspn(dataInicial, "\n")] = '\0';

            while ((c = getchar()) == '\n' && c == EOF);
            printf("Digite uma data final: ");
            fgets(dataFinal, sizeof(dataFinal), stdin);
            dataFinal[strcspn(dataFinal, "\n")] = '\0';

            for (int i = 0; i < totalAtendimentos; i++) {
        if (strcmp(datasAtendimento[i], dataInicial) >= 0 && strcmp(datasAtendimento[i], dataFinal) <= 0) {
            soma += precos[i];
        }
    }

    printf("Soma das consultas pagas para o periodo de %s a %s: %.2f\n", dataInicial, dataFinal, soma);
}

void editarAtendimento(
        int codigosAtendimentos[], int totalAtendimentos,
        int codigosPacientes[], char tipos[][20],
        char datasAtendimento[][11], char status[][50],
        float precos[], int totalPacientes
) {
    int codigoAtendimento;
    printf("Digite o Codigo do Atendimento a ser editado: ");
    scanf("%d", &codigoAtendimento);

    int indiceAtendimento = -1;
    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosAtendimentos[i] == codigoAtendimento) {
            indiceAtendimento = i;
            break;
        }
    }

    if (indiceAtendimento == -1) {
        printf("Atendimento com o codigo fornecido nao encontrado.\n");
        return;
    }

    int continuarEdicao = 1;

    while (continuarEdicao) {
        printf("Informacoes do Atendimento:\n");
        printf("Codigo: %d\n", codigosAtendimentos[indiceAtendimento]);
        printf("Codigo do Paciente: %d\n", codigosPacientes[indiceAtendimento]);
        printf("Tipo: %s\n", tipos[indiceAtendimento]);
        printf("Data de Atendimento: %s\n", datasAtendimento[indiceAtendimento]);
        printf("Status: %s\n", status[indiceAtendimento]);
        printf("Preco: %.2f\n", precos[indiceAtendimento]);
        printf("\nSelecione a informacao a ser alterada:\n");
        printf("1. Tipo\n");
        printf("2. Data de Atendimento\n");
        printf("3. Status\n");
        printf("4. Preco\n");
        printf("0. Sair\n");

        int escolha;
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        // Limpar o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (escolha) {
            case 0:
                continuarEdicao = 0;
                break;
            case 1:
                printf("Selecione o novo Tipo:\n 1. Atendimento\n 2. Retorno:\n ");
                int novoTipo;
                scanf("%d", &novoTipo);
                if (novoTipo == 1 || novoTipo == 2) {
                    if (novoTipo == 1) {
                        strcpy(tipos[indiceAtendimento], "Atendimento");
                    } else {
                        strcpy(tipos[indiceAtendimento], "Retorno");
                    }
                } else {
                    printf("Escolha invalida. Nenhuma informacao alterada.\n");
                }
                break;
            case 2:
                printf("Digite a nova Data de Atendimento (dd/mm/aaaa): ");
                scanf("%[^\n]", datasAtendimento[indiceAtendimento]);
                break;
            case 3:
                printf("Selecione o novo Status\n 1 - Agendado\n 2 - Em espera\n 3 - Em atendimento\n 4 - Concluido\n ");
                int novoStatus;
                scanf("%d", &novoStatus);
                if (novoStatus >= 1 && novoStatus <= 4) {
                    switch (novoStatus) {
                        case 1:
                            strcpy(status[indiceAtendimento], "Agendado");
                            break;
                        case 2:
                            strcpy(status[indiceAtendimento], "Em espera");
                            break;
                        case 3:
                            strcpy(status[indiceAtendimento], "Em atendimento");
                            break;
                        case 4:
                            strcpy(status[indiceAtendimento], "Concluido");
                            break;
                    }
                } else {
                    printf("Escolha invalida. Nenhuma informacao alterada.\n");
                }
                break;
            case 4:
                printf("Digite o novo Preco: ");
                scanf("%f", &precos[indiceAtendimento]);
                break;
            default:
                printf("Escolha invalida. Nenhuma informacao alterada.\n");
                break;
        }
    }
    printf("Informacao do Atendimento alterada com sucesso.\n");
}

