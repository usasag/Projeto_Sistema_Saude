#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

#define MAX_PACIENTES 100
#define MAX_ATENDIMENTOS 100

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

    int codigosAtendimentos[MAX_ATENDIMENTOS];
    char tipos[MAX_ATENDIMENTOS][20];
    char datasAtendimento[MAX_ATENDIMENTOS][11];
    char status[MAX_ATENDIMENTOS][50];
    float precos[MAX_ATENDIMENTOS];

    int totalAtendimentos = 0;
    int proximoCodigoPaciente = 1000; // Código inicial do paciente
    int totalPacientes = proximoCodigoPaciente - 1000;

    while (1) {
        printf("\nPacientes:\n");
        printf("1. Adicionar Paciente\n");
        printf("2. Remover Paciente\n");
        printf("3. Alterar Informacoes do Paciente\n");
        printf("4. Exibir Informacoes do Paciente\n");
        printf("5. Listar Pacientes com Informacoes\n");
        printf("6. Listar Pacientes por Tipo Sanguineo\n");
        printf("7. Listar Pacientes por Ordem Alfabetica\n");
        printf("\nAtendimentos:\n");
        printf("8. Adicionar Atendimento\n");
        printf("9. Remover Atendimento\n");
        printf("10. Exibir Atendimentos\n");
        printf("11. Listar Consultas por Data\n");
        printf("\n0. Sair\n");

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
                            datasNascimento, generos,
                            totalPacientes
                    );
        } else if (escolha == 6) {
            listarPacientesPorTipoSanguineo
                    (
                            codigosPacientes, nomes,
                            tiposSanguineos, fatoresRH,
                            datasNascimento, totalPacientes
                    );
        } else if (escolha == 7) {
            mostrarPacientesOrdenados
            (
                    codigosPacientes,nomes,
                    totalPacientes, idades);
        } else if (escolha == 8) {
            totalAtendimentos = adicionarAtendimento
                    (
                            codigosAtendimentos, codigosPacientes,
                            tipos, datasAtendimento,
                            status, precos,
                            totalAtendimentos, totalPacientes
                    );
        } else if (escolha == 9) {
            totalAtendimentos = removerAtendimento
                    (
                            codigosAtendimentos, status, totalAtendimentos
                    );
        } else if (escolha == 10) {
            exibirAtendimentos
                    (
                            codigosAtendimentos,
                            codigosPacientes, tipos,
                            datasAtendimento, status,
                            precos, totalAtendimentos
                    );
        } else if (escolha == 11) {
            listarConsultasPorData
                    (
                            codigosPacientes, nomes,
                            generos, datasNascimento,
                            idades, codigosAtendimentos,
                            tipos, precos, datasAtendimento,
                            totalPacientes, totalAtendimentos
                    );
        } else if (escolha == 0) {
            exit(0);
        } else {
            printf("Escolha inválida. Por favor, tente novamente.\n");
        }
    }
}

#include <stdio.h>
#include <string.h>

int adicionarPaciente(int codigosPacientes[], char nomes[][50], char generos[][10],
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

    // Solicitar o genero biologico
    printf("Digite o genero biologico (F/M): ");
    if (fgets(generos[totalPacientes], sizeof(generos[0]), stdin) != NULL) {
        generos[totalPacientes][strcspn(generos[totalPacientes], "\n")] = '\0';
    }

    // Solicitar o RG
    printf("Digite o RG: ");
    if (fgets(RGs[totalPacientes], sizeof(RGs[0]), stdin) != NULL) {
        RGs[totalPacientes][strcspn(RGs[totalPacientes], "\n")] = '\0';
    }

    // Solicitar o CPF (obrigatório)
    printf("Digite o CPF (apenas os numeros): ");
    if (fgets(CPFs[totalPacientes], sizeof(CPFs[0]), stdin) != NULL) {
        CPFs[totalPacientes][strcspn(CPFs[totalPacientes], "\n")] = '\0';
    } else {
        printf("Por favor, insira um CPF valido.\n");
        return proximoCodigoPaciente;
    }

    // Solicitar o tipo sanguineo
    printf("Digite o tipo sanguineo (A/B/AB/O): ");
    if (fgets(tiposSanguineos[totalPacientes], sizeof(tiposSanguineos[0]), stdin) != NULL) {
        tiposSanguineos[totalPacientes][strcspn(tiposSanguineos[totalPacientes], "\n")] = '\0';
    }

    // Solicitar o fator RH
    printf("Digite o fator RH (+/-): ");
    if (fgets(fatoresRH, 2, stdin) != NULL) {
        fatoresRH[totalPacientes][strcspn(fatoresRH, "\n")] = '\0';
    }

    // Solicitar o endereco
    printf("Digite o endereco: ");
    if (fgets(enderecos[totalPacientes], sizeof(enderecos[0]), stdin) != NULL) {
        enderecos[totalPacientes][strcspn(enderecos[totalPacientes], "\n")] = '\0';
    }

    // Solicitar a data de nascimento até que seja fornecida (obrigatório)
    do {
        printf("Digite a data de nascimento (dd/mm/yyyy): ");
        if (fgets(datasNascimento[totalPacientes], sizeof(datasNascimento[0]), stdin) != NULL) {
            datasNascimento[totalPacientes][strcspn(datasNascimento[totalPacientes], "\n")] = '\0';
        } else {
            printf("Por favor, insira uma data de nascimento valida.\n");
        }
    } while (strlen(datasNascimento[totalPacientes]) == 0);

    // Calcular a idade e atribuir o próximo código de paciente disponível
    idades[totalPacientes] = calcularIdade(datasNascimento[totalPacientes]);
    codigosPacientes[totalPacientes] = proximoCodigoPaciente;
    proximoCodigoPaciente++;

    printf("Paciente adicionado com sucesso.\n Codigo do Paciente: %d\n", codigosPacientes[totalPacientes]);
    return proximoCodigoPaciente;
}

int adicionarAtendimento
        (
                int codigosAtendimentos[], int codigosPacientes[],
                char tipos[][20], char datasAtendimento[][11],
                char status[][50], float precos[],
                int totalAtendimentos, int totalPacientes
        ) {
    if (totalAtendimentos >= MAX_ATENDIMENTOS) {
        printf("Limite maximo de atendimentos atingido.\n");
        return totalAtendimentos;
    }

    if (totalPacientes == 0) {
        printf("Nenhum paciente disponível. Adicione um paciente primeiro.\n");
        return totalAtendimentos;
    }

    printf("Digite o Codigo do Atendimento: ");
    scanf("%d", &codigosAtendimentos[totalAtendimentos]);

    // Gerar o código automaticamente (não implementado ainda)
    /* char codigoAtendimento[20];
    snprintf
    (codigoAtendimento,
     sizeof(codigoAtendimento),
     "%d_%d", codigoPaciente,
     numeroAtendimentoPorPaciente[indicePaciente] + 1
     );
    */

    int codigoPaciente;
    printf("Digite o Codigo do Paciente: ");
    scanf("%d", &codigoPaciente);

    // Verificar se o paciente com o código fornecido existe
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
    while ((c = getchar()) != '\n' && c != EOF);

    char novaDataAtendimento[11];
    printf("Digite a Data do Atendimento (dd/mm/aaaa): ");
    fgets(novaDataAtendimento, sizeof(novaDataAtendimento), stdin);
    novaDataAtendimento[strcspn(novaDataAtendimento, "\n")] = '\0';

    // Verificar se já existe um atendimento para este paciente na mesma data
    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosPacientesParaAtendimentos[i] == codigoPaciente &&
            strcmp(datasAtendimento[i], novaDataAtendimento) == 0) {
            printf("Erro: Ja existe um atendimento para este paciente na mesma data.\n");
            return totalAtendimentos;
        }
    }

    strcpy(datasAtendimento[totalAtendimentos], novaDataAtendimento);
    codigosPacientesParaAtendimentos[totalAtendimentos] = codigoPaciente;

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o Tipo (atendimento/retorno): ");
    scanf(" %[^\n]", tipos[totalAtendimentos]);
    strcpy(datasAtendimento[totalAtendimentos], novaDataAtendimento);
    strcpy(status[totalAtendimentos], "Agendado"); // Inicialmente define como "Agendado"
    printf("Digite o Preco: ");
    scanf("%f", &precos[totalAtendimentos]);

    totalAtendimentos++;
    printf("Atendimento adicionado com sucesso.\nCodigo do Atendimento: %d\n",
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
                int codigosPacientes[],
                char nomes[][50],
                char datasNascimento[][11],
                char generos[][10],
                int totalPacientes
        )
{
    if (totalPacientes == 0) {
        printf("Nenhum paciente disponivel para listagem.\n");
        return;
    }

    printf("Lista de Pacientes com Informacoes:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf(" Codigo do Paciente: %d\n", codigosPacientes[i]);
        printf(" Nome: %s\n", nomes[i]);
        printf(" Idade: %d\n", calcularIdade(datasNascimento[i]));
        printf(" Genero: %s\n", generos[i]);
        printf("----------------------------------------\n");
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
            printf("Novo Nome: ");
            while (getchar() != '\n');
            fgets(nomes[indicePaciente], sizeof(nomes[0]), stdin);
            nomes[indicePaciente][strcspn(nomes[indicePaciente], "\n")] = '\0';
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
            printf("Novo CPF: ");
            while (getchar() != '\n');
            fgets(CPFs[indicePaciente], sizeof(CPFs[0]), stdin);
            CPFs[indicePaciente][strcspn(CPFs[indicePaciente], "\n")] = '\0';
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
            printf("Nova Data de Nascimento (dd/mm/aaaa): ");
            while (getchar() != '\n');
            fgets(datasNascimento[indicePaciente], sizeof(datasNascimento[0]), stdin);
            datasNascimento[indicePaciente][strcspn(datasNascimento[indicePaciente], "\n")] = '\0';
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

void ordenarPacientesPorNome(int codigosPacientes[], char nomes[][50], int totalPacientes, int idades[50]) {
    int troca = 1;
    while (troca) {
        troca = 0;
        for (int i = 0; i < totalPacientes - 1; i++) {
            if (strcmp(nomes[i], nomes[i + 1]) > 0) {
                // Trocar os códigos, nomes e idades dos pacientes
                int tempCodigo = codigosPacientes[i];
                codigosPacientes[i] = codigosPacientes[i + 1];
                codigosPacientes[i + 1] = tempCodigo;

                char tempNome[100];
                strcpy(tempNome, nomes[i]);
                strcpy(nomes[i], nomes[i + 1]);
                strcpy(nomes[i + 1], tempNome);

                int tempIdade = idades[i];
                idades[i] = idades[i + 1];
                idades[i + 1] = tempIdade;

                troca = 1;
            }
        }
    }
}

void mostrarPacientesOrdenados(int codigosPacientes[], char nomes[][50], int totalPacientes, int idades[]) {
    ordenarPacientesPorNome(codigosPacientes, nomes, totalPacientes, idades);

    printf("\nLista de Pacientes Ordenados por Nome:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf("Codigo: %d\n", codigosPacientes[i]);
        printf("Nome: %s\n", nomes[i]);
        printf("Idade: %d\n", idades[i]);
        printf("---------------------------------------------\n");
    }
}