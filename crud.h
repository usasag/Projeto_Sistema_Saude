#define PROJETO_SISTEMA_SAUDE_TRABALHO_FUNCS_H
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

// PROTOTYPES FOR REFERENCE
int addPatient
        (
                int patientCodes[],
                char names[][50],
                char RGs[][15],
                char CPFs[][15],
                char bloodTypes[][5],
                char RHFactors[],
                char addresses[][100],
                char DOBs[][11],
                int ages[],
                int nextPatientCode,
                int patientCount
        );
int addAppointment
        (
                int appointmentCodes[],
                int patientCodes[],
                char types[][20],
                char appointmentDates[][11],
                char statuses[][50],
                float prices[],
                int appointmentCount,
                int patientCount
        );
void displayPatientInfo
        (
                int patientCodes[],
                char names[][50],
                char RGs[][15],
                char CPFs[][15],
                char bloodTypes[][5],
                char RHFactors[],
                char addresses[][100],
                char DOBs[][11],
                int ages[], // To be calculated in a future library
                int patientCount
        );
void displayAppointments
        (
                int appointmentCodes[],
                int patientCodes[],
                char types[][20],
                char appointmentDates[][11],
                char statuses[][50],
                float prices[],
                int appointmentCount
        );
int removePatient
(
        int patientCodes[],
        char names[][50],
        char RGs[][15],
        char CPFs[][15],
        char bloodTypes[][5],
        char RHFactors[],
        char addresses[][100],
        char DOBs[][11],
        int ages[],
        int patientCount
        );
int removeAppointment
(
        int appointmentCodes[],
        char statuses[][50],
        int appointmentCount
        );
void displayAppointments
(
        int appointmentCodes[],
        int patientCodes[],
        char types[][20],
        char appointmentDates[][11],
        char statuses[][50],
        float prices[],
        int appointmentCount
        );
void listPatientsWithInfo
(
        int patientCodes[],
        char names[][50],
        char DOBs[][11],
        char genders[][10],
        int patientCount
        );

