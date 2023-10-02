#include <stdio.h>
#include <stdlib.h>
#include "crud.h"

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
        int ages[], // To be calculated in a future library
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

int main() {
    int patientCodes[MAX_PATIENTS];
    char names[MAX_PATIENTS][50];
    char RGs[MAX_PATIENTS][15];
    char CPFs[MAX_PATIENTS][15];
    char bloodTypes[MAX_PATIENTS][5];
    char RHFactors[MAX_PATIENTS];
    char addresses[MAX_PATIENTS][100];
    char DOBs[MAX_PATIENTS][11];
    int ages[MAX_PATIENTS]; // To be calculated in a future library

    int appointmentCodes[MAX_APPOINTMENTS];
    int patientCodesForAppointments[MAX_APPOINTMENTS];
    char types[MAX_APPOINTMENTS][20];
    char appointmentDates[MAX_APPOINTMENTS][11];
    char statuses[MAX_APPOINTMENTS][50];
    float prices[MAX_APPOINTMENTS];

    int patientCount = 0;
    int appointmentCount = 0;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Patient\n");
        printf("2. Add Appointment\n");
        printf("3. Display Patient Information\n");
        printf("4. Display Appointments\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            patientCount = addPatient(patientCodes, names, RGs, CPFs, bloodTypes, RHFactors, addresses, DOBs, ages, patientCount);
        } else if (choice == 2) {
            appointmentCount = addAppointment(appointmentCodes, patientCodesForAppointments, types, appointmentDates, statuses, prices, appointmentCount, patientCount);
        } else if (choice == 3) {
            displayPatientInfo(patientCodes, names, RGs, CPFs, bloodTypes, RHFactors, addresses, DOBs, ages, patientCount);
        } else if (choice == 4) {
            displayAppointments(appointmentCodes, patientCodesForAppointments, types, appointmentDates, statuses, prices, appointmentCount);
        } else if (choice == 5) {
            exit(0);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

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
        int patientCount
){
    if (patientCount >= MAX_PATIENTS) {
        printf("Maximum number of patients reached.\n");
        return patientCount;
    }

    printf("Enter Patient Code: ");
    scanf("%d", &patientCodes[patientCount]);
    printf("Enter Name: ");
    scanf(" %[^\n]", names[patientCount]);
    printf("Enter RG: ");
    scanf(" %[^\n]", RGs[patientCount]);
    printf("Enter CPF: ");
    scanf(" %[^\n]", CPFs[patientCount]);
    printf("Enter Blood Type: ");
    scanf(" %[^\n]", bloodTypes[patientCount]);
    printf("Enter RH Factor: ");
    scanf(" %c", &RHFactors[patientCount]);
    printf("Enter Address: ");
    scanf(" %[^\n]", addresses[patientCount]);
    printf("Enter Date of Birth (dd/mm/yyyy): ");
    scanf(" %[^\n]", DOBs[patientCount]);

    ages[patientCount] = calculateAge(DOBs[patientCount]); // To be calculated in a future library

    patientCount++;
    printf("Patient added successfully.\n");

    return patientCount;
}

int addAppointment
(
        int appointmentCodes[], int patientCodes[],
        char types[][20], char appointmentDates[][11],
        char statuses[][50], float prices[],
        int appointmentCount, int patientCount
        ) {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("Maximum number of appointments reached.\n");
        return appointmentCount;
    }

    if (patientCount == 0) {
        printf("No patients available. Please add a patient first.\n");
        return appointmentCount;
    }

    printf("Enter Appointment Code: ");
    scanf("%d", &appointmentCodes[appointmentCount]);

    int patientCode;
    printf("Enter Patient Code: ");
    scanf("%d", &patientCode);

    // Check if the patient with the given code exists
    int patientIndex = -1;
    for (int i = 0; i < patientCount; i++) {
        if (patientCodes[i] == patientCode) {
            patientIndex = i;
            break;
        }
    }

    if (patientIndex == -1) {
        printf("Patient with the given code not found.\n");
        return appointmentCount;
    }

    patientCodes[appointmentCount] = patientCode;

    printf("Enter Type (appointment/return): ");
    scanf(" %[^\n]", types[appointmentCount]);
    printf("Enter Appointment Date (dd/mm/yyyy): ");
    scanf(" %[^\n]", appointmentDates[appointmentCount]);
    printf("Enter Status: ");
    scanf(" %[^\n]", statuses[appointmentCount]);
    printf("Enter Price: ");
    scanf("%f", &prices[appointmentCount]);

    appointmentCount++;
    printf("Appointment added successfully.\n");

    return appointmentCount;
}

void displayPatientInfo
(
        int patientCodes[], char names[][50],
        char RGs[][15], char CPFs[][15],
        char bloodTypes[][5], char RHFactors[],
        char addresses[][100], char DOBs[][11],
        int ages[], int patientCount
        )
        {
    if (patientCount == 0) {
        printf("No patients available.\n");
        return;
    }

    int patientCode;
    printf("Enter Patient Code: ");
    scanf("%d", &patientCode);

    int patientIndex = -1;
    for (int i = 0; i < patientCount; i++) {
        if (patientCodes[i] == patientCode) {
            patientIndex = i;
            break;
        }
    }

    if (patientIndex == -1) {
        printf("Patient with the given code not found.\n");
    } else {
        // Display patient information
        printf("Patient Code: %d\n", patientCodes[patientIndex]);
        printf("Name: %s\n", names[patientIndex]);
        printf("RG: %s\n", RGs[patientIndex]);
        printf("CPF: %s\n", CPFs[patientIndex]);
        printf("Blood Type: %s\n", bloodTypes[patientIndex]);
        printf("RH Factor: %c\n", RHFactors[patientIndex]);
        printf("Address: %s\n", addresses[patientIndex]);
        printf("Date of Birth: %s\n", DOBs[patientIndex]);
        printf("Age: %d\n", ages[patientIndex]); // To be calculated in a future library
    }
}

void displayAppointments
(
        int appointmentCodes[], int patientCodes[],
        char types[][20], char appointmentDates[][11],
        char statuses[][50], float prices[],
        int appointmentCount
        ) {
    if (appointmentCount == 0) {
        printf("No appointments available.\n");
        return;
    }

    int patientCode;
    printf("Enter Patient Code: ");
    scanf("%d", &patientCode);

    printf("Appointments for Patient Code %d:\n", patientCode);

    for (int i = 0; i < appointmentCount; i++) {
        if (patientCodes[i] == patientCode) {
            // Display appointment information
            printf("Appointment Code: %d\n", appointmentCodes[i]);
            printf("Patient Code: %d\n", patientCodes[i]);
            printf("Type: %s\n", types[i]);
            printf("Appointment Date: %s\n", appointmentDates[i]);
            printf("Status: %s\n", statuses[i]);
            printf("Price: %.2f\n", prices[i]);
        }
    }
}
