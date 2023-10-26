#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

#define MAX_PACIENTES 100
#define MAX_AGENDAMENTOS 100

int codigosPacientesParaAgendamentos[MAX_AGENDAMENTOS];
int numeroAgendamentoPorPaciente[MAX_PACIENTES] = {0};

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

    int codigosAgendamentos[MAX_AGENDAMENTOS];
    char tipos[MAX_AGENDAMENTOS][20];
    char datasAgendamento[MAX_AGENDAMENTOS][11];
    char status[MAX_AGENDAMENTOS][50];
    float precos[MAX_AGENDAMENTOS];

    int totalAgendamentos = 0;
    int proximoCodigoPaciente = 1000; // Código inicial do paciente
    int totalPacientes = proximoCodigoPaciente - 1000;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar Paciente\n");
        printf("2. Adicionar Agendamento\n");
        printf("3. Remover Paciente\n");
        printf("4. Remover Agendamento\n");
        printf("5. Exibir Informacoes do Paciente\n");
        printf("6. Exibir Agendamentos\n");
        printf("7. Listar Pacientes com Informacoes\n");
        printf("8. Sair\n");

        int escolha;
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            proximoCodigoPaciente = adicionarPaciente
                    (
                            codigosPacientes,
                            nomes,
                            generos,
                            RGs,
                            CPFs,
                            tiposSanguineos,
                            fatoresRH,
                            enderecos,
                            datasNascimento,
                            idades,
                            proximoCodigoPaciente,
                            totalPacientes
                    );
            totalPacientes = proximoCodigoPaciente - 1000;
        } else if (escolha == 2) {
            totalAgendamentos = adicionarAgendamento
                    (
                            codigosAgendamentos,
                            codigosPacientes,
                            tipos,
                            datasAgendamento,
                            status,
                            precos,
                            totalAgendamentos,
                            totalPacientes
                    );
        } else if (escolha == 3) {
            totalPacientes = removerPaciente
                    (
                            codigosPacientes,
                            nomes,
                            RGs,
                            CPFs,
                            tiposSanguineos,
                            fatoresRH,
                            enderecos,
                            datasNascimento,
                            idades,
                            totalPacientes
                    );
        } else if (escolha == 4) {
            totalAgendamentos = removerAgendamento
                    (
                            codigosAgendamentos,
                            status,
                            totalAgendamentos
                    );
        } else if (escolha == 5) {
            exibirInformacoesPaciente
                    (
                            codigosPacientes,
                            nomes,
                            RGs,
                            CPFs,
                            tiposSanguineos,
                            fatoresRH,
                            enderecos,
                            datasNascimento,
                            idades,
                            totalPacientes
                    );
        } else if (escolha == 6) {
            exibirAgendamentos
                    (
                            codigosAgendamentos,
                            codigosPacientes,
                            tipos,
                            datasAgendamento,
                            status,
                            precos,
                            totalAgendamentos
                    );
        } else if (escolha == 7) {
            listarPacientesComInformacoes
                    (
                            codigosPacientes,
                            nomes,
                            datasNascimento,
                            generos,
                            totalPacientes
                    );
        } else if (escolha == 8) {
            exit(0);
        } else {
            printf("Escolha invalida. Por favor, tente novamente.\n");
        }
    }

    return 0;
}

int adicionarPaciente
        (
                int codigosPacientes[],
                char nomes[][50],
                char generos[][10],
                char RGs[][15],
                char CPFs[][15],
                char tiposSanguineos[][5],
                char fatoresRH[],
                char enderecos[][100],
                char datasNascimento[][11],
                int idades[],
                int proximoCodigoPaciente,
                int totalPacientes
        )
{
    if (totalPacientes >= MAX_PACIENTES) {
        printf("Numero maximo de pacientes atingido.\n");
        return proximoCodigoPaciente;
    }

    // Limpar o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite o nome: ");
    scanf("%[^\n]", nomes[totalPacientes]);

    // Verificar se o nome é válido.
    if (strlen(nomes[totalPacientes]) == 0) {
        printf("Por favor, insira um nome valido.\n");
        return proximoCodigoPaciente;
    }

    // Limpar o buffer de entrada antes de continuar
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o genero biologico (F/M): ");
    scanf("%c",generos[totalPacientes]);

    // Verificar se o gênero é válido
    if (strlen(generos[totalPacientes]) == 0) {
        printf("Por favor, insira um gênero valido.\n");
        return totalPacientes;
    }

    // Limpar o buffer...
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o RG: ");
    fgets(RGs[totalPacientes], sizeof(RGs[0]), stdin);
    RGs[totalPacientes][strcspn(RGs[totalPacientes], "\n")] = '\0';

    printf("Digite o CPF: ");
    fgets(CPFs[totalPacientes], sizeof(CPFs[0]), stdin);
    CPFs[totalPacientes][strcspn(CPFs[totalPacientes], "\n")] = '\0';

    printf("Digite o tipo sanguineo: ");
    fgets(tiposSanguineos[totalPacientes], sizeof(tiposSanguineos[0]), stdin);
    tiposSanguineos[totalPacientes][strcspn(tiposSanguineos[totalPacientes], "\n")] = '\0';

    printf("Digite o fator RH: ");
    scanf(" %c", &fatoresRH[totalPacientes]);

    // Limpar o buffer de entrada antes de inserir o endereço
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o endereco: ");
    scanf("%[^\n]",enderecos[totalPacientes]);

    // Verificar se o endereço é válido
    if (strlen(enderecos[totalPacientes]) == 0) {
        printf("Por favor, insira um endereco valido.\n");
        return totalPacientes;
    }

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite a data de nascimento (dd/mm/yyyy): ");
    fgets(datasNascimento[totalPacientes], sizeof(datasNascimento[0]), stdin);
    datasNascimento[totalPacientes][strcspn(datasNascimento[totalPacientes], "\n")] = '\0';

    idades[totalPacientes] = calcularIdade(datasNascimento[totalPacientes]);

    // Atribuir o próximo código de paciente disponível e incrementar
    codigosPacientes[totalPacientes] = proximoCodigoPaciente;

    proximoCodigoPaciente++;

    printf("Paciente adicionado com sucesso. Codigo do Paciente: %d\n", codigosPacientes[totalPacientes]);

    return proximoCodigoPaciente;
}

int adicionarAgendamento
        (
                int codigosAgendamentos[], int codigosPacientes[],
                char tipos[][20], char datasAgendamento[][11],
                char status[][50], float precos[],
                int totalAgendamentos, int totalPacientes
        ) {
    if (totalAgendamentos >= MAX_AGENDAMENTOS) {
        printf("Limite maximo de agendamentos atingido.\n");
        return totalAgendamentos;
    }

    if (totalPacientes == 0) {
        printf("Nenhum paciente disponível. Adicione um paciente primeiro.\n");
        return totalAgendamentos;
    }

    printf("Digite o Codigo do Agendamento: ");
    scanf("%d", &codigosAgendamentos[totalAgendamentos]);

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
        return totalAgendamentos;
    }


    // Gerear o código automaticamente (não implementado ainda)
    char codigoAgendamento[20];
    snprintf
    (codigoAgendamento,
     sizeof(codigoAgendamento),
     "%d_%d", codigoPaciente,
     numeroAgendamentoPorPaciente[indicePaciente] + 1
     );


    // Verificar se já existe um agendamento para este paciente na mesma data
    char novaDataAgendamento[11];
    printf("Digite a Data do Agendamento (dd/mm/aaaa): ");
    scanf(" %[^\n]", novaDataAgendamento);
    for (int i = 0; i < totalAgendamentos; i++) {
        if (codigosPacientesParaAgendamentos[i] == codigoPaciente &&
            strcmp(datasAgendamento[i], novaDataAgendamento) == 0) {
            printf("Erro: Ja existe um agendamento para este paciente na mesma data.\n");
            return totalAgendamentos;
        }
    }

    codigosPacientesParaAgendamentos[totalAgendamentos] = codigoPaciente;

    printf("Digite o Tipo (agendamento/retorno): ");
    scanf(" %[^\n]", tipos[totalAgendamentos]);
    strcpy(datasAgendamento[totalAgendamentos], novaDataAgendamento);
    strcpy(status[totalAgendamentos], "Agendado"); // Define o status como "Agendado" inicialmente
    printf("Digite o Preco: ");
    scanf("%f", &precos[totalAgendamentos]);

    totalAgendamentos++;
    printf("Agendamento adicionado com sucesso. Codigo do Agendamento: %d\n",
           codigosAgendamentos[totalAgendamentos - 1]);

    return totalAgendamentos;
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

void exibirAgendamentos
        (
                int codigosAgendamentos[], int codigosPacientes[],
                char tipos[][20], char datasAgendamento[][11],
                char status[][50], float precos[],
                int totalAgendamentos
        ) {
    if (totalAgendamentos == 0) {
        printf("Nenhum agendamento disponivel.\n");
        return;
    }

    int codigoPaciente;
    printf("Digite o Codigo do Paciente: ");
    scanf("%d", &codigoPaciente);

    printf("Agendamentos para o Codigo do Paciente %d:\n", codigoPaciente);

    for (int i = 0; i < totalAgendamentos; i++) {
        if (codigosPacientes[i] == codigoPaciente) {
            // Exibir informações do agendamento
            printf("Codigo do Agendamento: %d\n", codigosAgendamentos[i]);
            printf("Codigo do Paciente: %d\n", codigosPacientes[i]);
            printf("Tipo: %s\n", tipos[i]);
            printf("Data do Agendamento: %s\n", datasAgendamento[i]);
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

int removerAgendamento
        (int codigosAgendamentos[],
         char status[][50],
         int totalAgendamentos) {
    if (totalAgendamentos == 0) {
        printf("Nenhum agendamento disponivel para remocao.\n");
        return totalAgendamentos;
    }

    int codigoAgendamento;
    printf("Digite o Codigo do Agendamento para remocao: ");
    scanf("%d", &codigoAgendamento);

    int indiceAgendamento = -1;
    for (int i = 0; i < totalAgendamentos; i++) {
        if (codigosAgendamentos[i] == codigoAgendamento) {
            indiceAgendamento = i;
            break;
        }
    }

    if (indiceAgendamento == -1) {
        printf("Agendamento com o codigo fornecido nao encontrado.\n");
        return totalAgendamentos;
    }

    // Confirmar o código do agendamento antes de remover
    printf("Confirme o codigo do agendamento para remocao: ");
    int codigoConfirmacao;
    scanf("%d", &codigoConfirmacao);

    if (codigoConfirmacao != codigoAgendamento) {
        printf("O codigo do agendamento nao corresponde. Remocao cancelada.\n");
        return totalAgendamentos;
    }

    // Deslocar os agendamentos restantes para preencher a lacuna (mesma coisa dos pacientes)
    for (int i = indiceAgendamento; i < totalAgendamentos - 1; i++) {
        codigosAgendamentos[i] = codigosAgendamentos[i + 1];
        strcpy(status[i], status[i + 1]);
    }

    printf("Agendamento removido com sucesso.\n");
    return totalAgendamentos - 1; // Retorna o número atualizado de agendamentos
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
    for (int i = 0; i < totalPacientes; i++) {
        printf("Codigo do Paciente: %d\n", codigosPacientes[i]);
        printf("Nome: %s\n", nomes[i]);
        printf("Data de Nascimento: %s\n", datasNascimento[i]);
        printf("Genero: %s\n", generos[i]);
        printf("----------------------------------------\n");
    }
}
