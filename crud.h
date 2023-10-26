#define PROJETO_SISTEMA_SAUDE_TRABALHO_FUNCS_H
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

// PROTOTYPES FOR REFERENCE
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
        );
int adicionarAgendamento
        (
                int codigosAgendamentos[],
                int codigosPacientes[],
                char tipos[][20],
                char datasAgendamento[][11],
                char status[][50],
                float precos[],
                int totalAgendamentos,
                int totalPacientes
        );
void exibirInformacoesPaciente
        (
                int codigosPacientes[], char nomes[][50],
                char RGs[][15], char CPFs[][15],
                char tiposSanguineos[][5], char fatoresRH[],
                char enderecos[][100], char datasNascimento[][11],
                int idades[], int totalPacientes
        );
void exibirAgendamentos
        (
                int codigosAgendamentos[], int codigosPacientes[],
                char tipos[][20], char datasAgendamento[][11],
                char status[][50], float precos[],
                int totalAgendamentos
        );
int removerPaciente
        (int codigosPacientes[],
         char nomes[][50],
         char RGs[][15],
         char CPFs[][15],
         char tiposSanguineos[][5],
         char fatoresRH[],
         char enderecos[][100],
         char datasNascimento[][11],
         int idades[],
         int totalPacientes);
int removerAgendamento
        (int codigosAgendamentos[],
         char status[][50],
         int totalAgendamentos);
void exibirAgendamentos
        (
                int codigosAgendamentos[], int codigosPacientes[],
                char tipos[][20], char datasAgendamento[][11],
                char status[][50], float precos[],
                int totalAgendamentos
        );
void listarPacientesComInformacoes
        (
                int codigosPacientes[],
                char nomes[][50],
                char datasNascimento[][11],
                char generos[][10],
                int totalPacientes
        );
int calcularIdade
(
        const char dataNascimento[]
        );

