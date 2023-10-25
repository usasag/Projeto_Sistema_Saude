#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud.h"

#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

int main() {
    int patientCodes[MAX_PATIENTS];
    char names[MAX_PATIENTS][50];
    char RGs[MAX_PATIENTS][15];
    char CPFs[MAX_PATIENTS][15];
    char bloodTypes[MAX_PATIENTS][5];
    char genders[MAX_PATIENTS][10];
    char RHFactors[MAX_PATIENTS];
    char addresses[MAX_PATIENTS][100];
    char DOBs[MAX_PATIENTS][11];
    int ages[MAX_PATIENTS];

    int appointmentCodes[MAX_APPOINTMENTS];
    int patientCodesForAppointments[MAX_APPOINTMENTS];
    char types[MAX_APPOINTMENTS][20];
    char appointmentDates[MAX_APPOINTMENTS][11];
    char statuses[MAX_APPOINTMENTS][50];
    float prices[MAX_APPOINTMENTS];

    int patientCount = 0;
    int appointmentCount = 0;
    int nextPatientCode = 1000; // Initial patient code


    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Patient\n");
        printf("2. Add Appointment\n");
        printf("3. Remove Patient\n");
        printf("4. Remove Appointment\n");
        printf("5. Display Patient Information\n");
        printf("6. Display Appointments\n");
        printf("7. List Patients with Info\n");
        printf("8. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            patientCount = addPatient(patientCodes, names, RGs, CPFs, bloodTypes, RHFactors, addresses, DOBs, ages, nextPatientCode, patientCount);
        } else if (choice == 2) {
            appointmentCount = addAppointment(appointmentCodes, patientCodesForAppointments, types, appointmentDates, statuses, prices, appointmentCount, patientCount);
        } else if (choice == 3) {
            patientCount = removePatient(patientCodes, names, RGs, CPFs, bloodTypes, RHFactors, addresses, DOBs, ages, patientCount);
        } else if (choice == 4) {
            appointmentCount = removeAppointment(appointmentCodes, statuses, appointmentCount);
        } else if (choice == 5) {
            displayPatientInfo(patientCodes, names, RGs, CPFs, bloodTypes, RHFactors, addresses, DOBs, ages, patientCount);
        } else if (choice == 6) {
            displayAppointments(appointmentCodes, patientCodesForAppointments, types, appointmentDates, statuses, prices, appointmentCount);
        } else if (choice == 7) {
            listPatientsWithInfo(patientCodes, names, DOBs, genders, patientCount);
        } else if (choice == 8) {
            exit(0);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int addPatient(int patientCodes[], char names[][50], char RGs[][15], char CPFs[][15], char bloodTypes[][5], char RHFactors[], char addresses[][100], char DOBs[][11], int ages[], int nextPatientCode, int patientCount) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Maximum number of patients reached.\n");
        return nextPatientCode;
    }

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char inputBuffer[50]; // Temporary buffer to read the name

    printf("Enter name: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; // Remove the trailing newline

    // Check if the inputBuffer contains a valid name
    if (strlen(inputBuffer) == 0) {
        printf("Please enter a valid name.\n");
        return patientCount;
    }

    // Copy the valid name to the names array
    strncpy(names[patientCount], inputBuffer, sizeof(names[0]));

    // Clear the input buffer before continuing
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter RG: ");
    fgets(RGs[patientCount], sizeof(RGs[0]), stdin);
    RGs[patientCount][strcspn(RGs[patientCount], "\n")] = '\0';

    printf("Enter CPF: ");
    fgets(CPFs[patientCount], sizeof(CPFs[0]), stdin);
    CPFs[patientCount][strcspn(CPFs[patientCount], "\n")] = '\0';

    printf("Enter Blood Type: ");
    fgets(bloodTypes[patientCount], sizeof(bloodTypes[0]), stdin);
    bloodTypes[patientCount][strcspn(bloodTypes[patientCount], "\n")] = '\0';

    printf("Enter RH Factor: ");
    scanf(" %c", &RHFactors[patientCount]);

    // Clear the input buffer before address input
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Address: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; // Remove the trailing newline

    // Check if the inputBuffer contains a valid address
    if (strlen(inputBuffer) == 0) {
        printf("Please enter a valid address.\n");
        return patientCount;
    }

    // Copy the valid address to the addresses array
    strncpy(addresses[patientCount], inputBuffer, sizeof(addresses[0]));

    printf("Enter DOB (dd/mm/yyyy): ");
    fgets(DOBs[patientCount], sizeof(DOBs[0]), stdin);
    DOBs[patientCount][strcspn(DOBs[patientCount], "\n")] = '\0';

    ages[patientCount] = calculateAge(DOBs[patientCount]);

    // Assign the next available patient code and increment
    patientCodes[patientCount] = nextPatientCode;

    nextPatientCode++;

    printf("Patient added successfully. Patient Code: %d\n", patientCodes[patientCount - 1]);

    return nextPatientCode;
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

    // Check if there's already an appointment for this patient on the same day
    char newAppointmentDate[11];
    printf("Enter Appointment Date (dd/mm/yyyy): ");
    scanf(" %[^\n]", newAppointmentDate);
    for (int i = 0; i < appointmentCount; i++) {
        if (patientCodes[i] == patientCode && strcmp(appointmentDates[i], newAppointmentDate) == 0) {
            printf("Error: There's already an appointment for this patient on the same day.\n");
            return appointmentCount;
        }
    }

    patientCodes[appointmentCount] = patientCode;

    printf("Enter Type (appointment/return): ");
    scanf(" %[^\n]", types[appointmentCount]);
    strcpy(appointmentDates[appointmentCount], newAppointmentDate);
    strcpy(statuses[appointmentCount], "Scheduled"); // Set status to "Scheduled" initially
    printf("Enter Price: ");
    scanf("%f", &prices[appointmentCount]);

    appointmentCount++;
    printf("Appointment added successfully. Appointment Code: %d\n", appointmentCodes[appointmentCount - 1]);

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

int removePatient
(int patientCodes[],
 char names[][50],
 char RGs[][15],
 char CPFs[][15],
 char bloodTypes[][5],
 char RHFactors[],
 char addresses[][100],
 char DOBs[][11],
 int ages[],
 int patientCount)
 {
    if (patientCount == 0) {
        printf("No patients available for removal.\n");
        return patientCount;
    }

    int patientCode;
    printf("Enter Patient Code for removal: ");
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
        return patientCount;
    }

    // Confirm the patient's name before removal
    printf("Confirm the patient's name for removal (type exactly): ");
    char confirmName[50];
    scanf(" %[^\n]", confirmName);

    if (strcmp(names[patientIndex], confirmName) != 0) {
        printf("Patient's name does not match. Removal canceled.\n");
        return patientCount;
    }

    // Shift remaining patients to fill the gap
    for (int i = patientIndex; i < patientCount - 1; i++) {
        patientCodes[i] = patientCodes[i + 1];
        strcpy(names[i], names[i + 1]);
        strcpy(RGs[i], RGs[i + 1]);
        strcpy(CPFs[i], CPFs[i + 1]);
        strcpy(bloodTypes[i], bloodTypes[i + 1]);
        RHFactors[i] = RHFactors[i + 1];
        strcpy(addresses[i], addresses[i + 1]);
        strcpy(DOBs[i], DOBs[i + 1]);
        ages[i] = ages[i + 1];
    }

    printf("Patient removed successfully.\n");
    return patientCount - 1; // Return the updated patient count
}

int removeAppointment
(int appointmentCodes[],
 char statuses[][50],
 int appointmentCount) {
    if (appointmentCount == 0) {
        printf("No appointments available for removal.\n");
        return appointmentCount;
    }

    int appointmentCode;
    printf("Enter Appointment Code for removal: ");
    scanf("%d", &appointmentCode);

    int appointmentIndex = -1;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointmentCodes[i] == appointmentCode) {
            appointmentIndex = i;
            break;
        }
    }

    if (appointmentIndex == -1) {
        printf("Appointment with the given code not found.\n");
        return appointmentCount;
    }

    // Confirm the appointment code before removal
    printf("Confirm the appointment code for removal: ");
    int confirmCode;
    scanf("%d", &confirmCode);

    if (confirmCode != appointmentCode) {
        printf("Appointment code does not match. Removal canceled.\n");
        return appointmentCount;
    }

    // Shift remaining appointments to fill the gap
    for (int i = appointmentIndex; i < appointmentCount - 1; i++) {
        appointmentCodes[i] = appointmentCodes[i + 1];
        strcpy(statuses[i], statuses[i + 1]);
    }

    printf("Appointment removed successfully.\n");
    return appointmentCount - 1; // Return the updated appointment count
}

void listPatientsWithInfo(int patientCodes[], char names[][50], char DOBs[][11], char genders[][10], int patientCount) {
    if (patientCount == 0) {
        printf("No patients available for listing.\n");
        return;
    }

    printf("Patient List with Info:\n");
    for (int i = 0; i < patientCount; i++) {
        // Age determination based on DOB
        int age = calculateAge(DOBs[i]);

        printf("Patient Code: %d\n", patientCodes[i]);
        printf("Name: %s\n", names[i]);
        printf("Age: %d\n", age);
        printf("Gender: %s\n", genders[i]);
        printf("Date of Birth: %s\n", DOBs[i]);
        printf("\n");
    }
}


