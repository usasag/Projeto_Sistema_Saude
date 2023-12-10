
#ifndef PROJETO_SISTEMA_SAUDE_TRABALHO_ATENDIMENTO_H
#define PROJETO_SISTEMA_SAUDE_TRABALHO_ATENDIMENTO_H
#include "pacientes.h"

int removerAtendimento
        (
                int codigosAtendimentos[], char status[][50],
                int totalAtendimentos
         ) {
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

    // Confirmar o código do atendimento antes de remover.
    printf("Confirme o codigo do atendimento para remocao: ");
    int codigoConfirmacao;
    scanf("%d", &codigoConfirmacao);

    if (codigoConfirmacao != codigoAtendimento) {
        printf("O codigo do atendimento nao corresponde. Remocao cancelada.\n");
        return totalAtendimentos;
    }

    // Deslocar os atendimentos restantes para preencher a lacuna (mesma coisa dos pacientes).
    for (int i = indiceAtendimento; i < totalAtendimentos - 1; i++) {
        codigosAtendimentos[i] = codigosAtendimentos[i + 1];
        strcpy(status[i], status[i + 1]);
    }

    printf("Atendimento removido com sucesso.\n");
    return totalAtendimentos - 1; // Retorna o número atualizado de atendimentos
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
    } while (strlen(novaDataAtendimento) <= 9);

    strcpy(datasAtendimento[totalAtendimentos], novaDataAtendimento);
    datasAtendimento[totalAtendimentos][strcspn(datasAtendimento[totalAtendimentos], "\n")] = '\0';

    // Verificar se já existe um atendimento para este paciente na mesma data
    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosPacientesParaAtendimentos[i] == codigoPaciente &&
            strcmp(datasAtendimento[i], novaDataAtendimento) == 0) {
            printf("Ja existe um atendimento para este paciente na mesma data.\n");
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

    strcpy(status[totalAtendimentos], "Agendado");
    printf("Digite o Preco: ");
    scanf("%f", &precos[totalAtendimentos]);

    totalAtendimentos++;
    printf("Atendimento adicionado com sucesso. Codigo do Atendimento: %d\n",
           codigosAtendimentos[totalAtendimentos - 1]);

    return totalAtendimentos;
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

void mostrarSomaConsultasPorData
        (
                float precos[], int totalAtendimentos,
                char datasAtendimento[][11]
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
                float precos[], char datasAtendimento[][11],
                int totalAtendimentos
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
        float precos[]
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
        printf("--------------------------------------------------\n");
        printf("Informacoes do Atendimento:\n");
        printf("Codigo: %d\n", codigosAtendimentos[indiceAtendimento]);
        printf("Codigo do Paciente: %d\n", codigosPacientes[indiceAtendimento]);
        printf("Tipo: %s\n", tipos[indiceAtendimento]);
        printf("Data de Atendimento: %s\n", datasAtendimento[indiceAtendimento]);
        printf("Status: %s\n", status[indiceAtendimento]);
        printf("Preco: %.2f\n", precos[indiceAtendimento]);
        printf("--------------------------------------------------\n");
        printf("Selecione a informacao a ser alterada:\n");
        printf("1. Tipo\n");
        printf("2. Data de Atendimento\n");
        printf("3. Status\n");
        printf("4. Preco\n");
        printf("0. Sair\n");
        printf("--------------------------------------------------\n");

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

void mostrarSomaConsultasPorPaciente
        (
                float precos[],int totalAtendimentos
        )
{
    if (totalAtendimentos == 0) {
        printf("Nao existem atendimentos para somar.");
        return;
    }

    int codigoPacienteDesejado;
    printf("Digite o codigo do paciente para calcular a soma das consultas: ");
    scanf("%d", &codigoPacienteDesejado);

    float soma = 0;

    for (int i = 0; i < totalAtendimentos; i++) {
        if (codigosPacientesParaAtendimentos[i] == codigoPacienteDesejado) {
            soma += precos[i];
        }
    }

    printf("Soma das consultas pagas pelo paciente %d: %.2f\n", codigoPacienteDesejado, soma);
}

void ordenarAtendimentosPorDataDecrescente(
        int codigosAtendimentos[], char tipos[][20], char status[][50],
        char datasAtendimento[][11], float precos[], int totalAtendimentos) {
    int troca = 1;
    while (troca) {
        troca = 0;
        for (int i = 0; i < totalAtendimentos - 1; i++) {
            if (strcmp(datasAtendimento[i], datasAtendimento[i + 1]) < 0) {
                // Trocar os códigos, tipos, status, datas e preços dos atendimentos
                int tempCodigo = codigosAtendimentos[i];
                codigosAtendimentos[i] = codigosAtendimentos[i + 1];
                codigosAtendimentos[i + 1] = tempCodigo;

                char tempTipo[20];
                strcpy(tempTipo, tipos[i]);
                strcpy(tipos[i], tipos[i + 1]);
                strcpy(tipos[i + 1], tempTipo);

                char tempStatus[20];
                strcpy(tempStatus, status[i]);
                strcpy(status[i], status[i + 1]);
                strcpy(status[i + 1], tempStatus);

                char tempData[11];
                strcpy(tempData, datasAtendimento[i]);
                strcpy(datasAtendimento[i], datasAtendimento[i + 1]);
                strcpy(datasAtendimento[i + 1], tempData);

                float tempPreco = precos[i];
                precos[i] = precos[i + 1];
                precos[i + 1] = tempPreco;

                troca = 1;
            }
        }
    }
}

void mostrarTodosAtendimentosPorDataDecrescente(
        int codigosAtendimentos[], char tipos[][20], char status[][50],
        char datasAtendimento[][11], float precos[], int totalAtendimentos) {
    if (totalAtendimentos == 0) {
        printf("Nenhum atendimento cadastrado.\n");
        return;
    }

    ordenarAtendimentosPorDataDecrescente
            (
                codigosAtendimentos, tipos,
                status, datasAtendimento,
                precos, totalAtendimentos
            );

    printf("Todos os Atendimentos (em ordem decrescente de data):\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totalAtendimentos; i++) {
        printf("Codigo do Atendimento: %d\n", codigosAtendimentos[i]);
        printf("Tipo de Atendimento: %s\n", tipos[i]);
        printf("Status: %s\n", status[i]);
        printf("Data do Atendimento: %s\n", datasAtendimento[i]);
        printf("Preco: %.2f\n", precos[i]);
        printf("--------------------------------------------------\n");
    }
}


#endif //PROJETO_SISTEMA_SAUDE_TRABALHO_ATENDIMENTO_H
