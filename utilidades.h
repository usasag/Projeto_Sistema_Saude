
#ifndef PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
#define PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculateAge(const char DOB[]) {
    // Assuming the date is known...
    int currentYear = 2023; // Replace with the actual current year
    int currentMonth = 10;   // Replace with the actual current month
    int currentDay = 25;    // Replace with the actual current day

    // Extract the birth year, month, and day from the DOB string
    int birthYear, birthMonth, birthDay;
    if (sscanf(DOB, "%d/%d/%d", &birthDay, &birthMonth, &birthYear) != 3) {
        // Invalid DOB format
        return -1;
    }

    // Calculate the age
    int age = currentYear - birthYear;

    // Check if the birthday hasn't occurred yet this year
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        age--; // Subtract 1 year from the age
    }

    return age;
}

#endif //PROJETO_SISTEMA_SAUDE_TRABALHO_UTILIDADES_H
