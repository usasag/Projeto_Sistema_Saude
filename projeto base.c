#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"
#include "pacientes.h"
#include "atendimento.h"

struct Pacientes {
    int codigosPacientes;
    char nomes[50];
    char RGs[15];
    char CPFs[15];
    char tiposSanguineos[5];
    char generos[2];
    char fatoresRH[2];
    char enderecos[100];
    char datasNascimento[11];
    int idades;
};

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
        printf("16. Listar Todos os Atendimentos por Ordem de Data Decrescente\n");
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
                            generos,
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
                    datasAtendimento, status, precos
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
            mostrarSomaConsultasPorPaciente
                    (
                            precos, totalAtendimentos
                    );
        } else if (escolha == 14) {
            mostrarSomaConsultasPorData
                    (
                            precos, totalAtendimentos,
                            datasAtendimento
                    );
        } else if (escolha == 15) {
            mostrarSomaConsultasPorPeriodo
                    (
                            precos, datasAtendimento,
                            totalAtendimentos
                    );
        } else if (escolha == 16) {
            mostrarTodosAtendimentosPorDataDecrescente
                    (
                            codigosAtendimentos, tipos,
                            status, datasAtendimento,
                            precos, totalAtendimentos
                    );
        } else if (escolha == 0) {
            exit(0);
        } else {
            printf("Escolha inválida. Por favor, tente novamente.\n");
        }
    }
}

void listarConsultasPorData // Precisa ajeitar
        (
                int codigosPacientes[], char nomes[][50], char generos[][10], int idades[],
                int codigosAtendimentos[], char tipos[][20], float precos[],
                char datasAtendimento[][11], int totalPacientes, int totalAtendimentos
        )
{
    char dataBuscada[11];
    printf("Digite a data (dd/mm/aaaa) para listar as consultas: ");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fflush(stdin);
    fgets(dataBuscada, sizeof(dataBuscada), stdin);
    dataBuscada[strcspn(dataBuscada, "\n")] = '\0';

    int encontrados = 0;

    for (int i = 0; i < totalAtendimentos; i++) {
        printf("Datas dos atendimentos: %s\n %s\n",datasAtendimento[i], dataBuscada);
        if (strcmp(datasAtendimento[i], dataBuscada) > 0) {
            for (int j = 0; j < totalPacientes; j++) {
                if (codigosPacientes[j] == codigosAtendimentos[i]) {
                    encontrados = 1;
                    printf("--------------------------------------------------\n");
                    printf("Paciente:\n");
                    printf("Codigo: %d\n", codigosPacientes[j]);
                    printf("Nome: %s\n", nomes[j]);
                    printf("Genero: %s\n", generos[j]);
                    printf("Idade: %d\n", idades[j]);

                    printf("Atendimento:\n");
                    printf("Codigo: %d\n", codigosAtendimentos[i]);
                    printf("Tipo: %s\n", tipos[i]);
                    printf("Preco: %.2f\n", precos[i]);
                    printf("\n");
                    printf("--------------------------------------------------\n");
                }
            }
        }
    }

    if (!encontrados) {
        printf("Nenhuma consulta encontrada para a data especificada.\n");
    }
}