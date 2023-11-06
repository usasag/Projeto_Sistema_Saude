#define PROJETO_SISTEMA_SAUDE_TRABALHO_FUNCS_H
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_PACIENTES 100
#define MAX_ATENDIMENTOS 100

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
int adicionarAtendimento
        (
                int codigosAtendimentos[],
                int codigosPacientes[],
                char tipos[][20],
                char datasAtendimento[][11],
                char status[][50],
                float precos[],
                int totalAtendimentos,
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
void exibirAtendimentos
        (
                int codigosAtendimentos[], int codigosPacientes[],
                char tipos[][20], char datasAtendimento[][11],
                char status[][50], float precos[],
                int totalAtendimentos
        );
int removerPaciente
        (
                int codigosPacientes[],char nomes[][50],
                char RGs[][15],char CPFs[][15],
                char tiposSanguineos[][5],char fatoresRH[],
                char enderecos[][100],char datasNascimento[][11],
                int idades[],int totalPacientes
         );
int removerAtendimento
        (
                int codigosAtendimentos[],char status[][50],
                int totalAtendimentos
         );
void exibirAtendimentos
        (
                int codigosAtendimentos[], int codigosPacientes[],
                char tipos[][20], char datasAtendimento[][11],
                char status[][50], float precos[],
                int totalAtendimentos
        );
void listarPacientesComInformacoes
        (
                int codigosPacientes[],
                char nomes[][50],
                int idades[],
                char generos[][10],
                int totalPacientes
        );
int calcularIdade
        (
                const char dataNascimento[]
        );

void alterarDadosPaciente
        (
                int codigosPacientes[], char nomes[][50],
                char generos[][10], char RGs[][15],
                char CPFs[][15], char tiposSanguineos[][5],
                char fatoresRH[], char enderecos[][100],
                char datasNascimento[][11], int idades[],
                int totalPacientes
        );

void listarPacientesPorTipoSanguineo
        (
                int codigosPacientes[], char nomes[][50],
                char tiposSanguineos[][5], char fatoresRH[],
                char datasNascimento[][11], int totalPacientes
        );

void listarConsultasPorData
        (
                int codigosPacientes[], char nomes[][50], char generos[][10], int idades[],
                int codigosAtendimentos[], char tipos[][20], float precos[],
                char datasAtendimento[][11], int totalPacientes, int totalAtendimentos
        );

void mostrarPacientesOrdenados
        (
                int codigosPacientes[], char nomes[][50],
                int idades[], int totalPacientes
        );
void mostrarSomaConsultasPorPaciente
        (
                int codigosAtendimentos[], float precos[],
                int totalAtendimentos, int codigosPacientesParaAtendimentos[]
        );
void mostrarSomaConsultasPorData
        (
                float precos[], int totalAtendimentos,
                char datasAtendimento[][11]
        );
void mostrarSomaConsultasPorPeriodo
        (
                float precos[], char datasAtendimento[][11],
                int totalAtendimentos
        );

void editarAtendimento(
        int codigosAtendimentos[], int totalAtendimentos,
        int codigosPacientes[], char tipos[][20],
        char datasAtendimento[][11], char status[][50],
        float precos[], int totalPacientes
);
