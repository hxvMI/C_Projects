#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function declarations
void displayTaxInformation(double income, double deduction, double taxableIncome, char taxGroup, double taxOwed);
void userInput(double *income, double *deduction);
double computeTaxableIncome(double income, double deduction);
double computeTax(char taxGroup, double taxable);
char computeTaxGroup(double taxable);

// Main function
int main() {
    // Variables
    double income, deduction, taxableIncome, taxOwed;
    char taxGroup;

    // Getting Values
    userInput(&income, &deduction);
    taxableIncome = computeTaxableIncome(income, deduction);
    taxGroup = computeTaxGroup(taxableIncome);
    taxOwed = computeTax(taxGroup, taxableIncome);

    // Display tax information
    displayTaxInformation(income, deduction, taxableIncome, taxGroup, taxOwed);

    return 0;
}

// Display tax information
void displayTaxInformation(double income, double deduction, double taxableIncome, char taxGroup, double taxOwed) {
    printf("\nIncome         = $%.2lf\n", income);
    printf("Deductions     = $%.2lf\n", deduction);
    printf("Taxable Income = $%.2lf\n", taxableIncome);
    printf("Tax group      = %c\n", taxGroup);
    printf("Tax owed       = $%.2lf\n", taxOwed);
}

// Function to compute tax owed based on tax group letter and taxable income
double computeTax(char taxGroup, double taxable) {
    // Variables
    double taxOwed;

    // Depending on the group
    if(taxGroup == 'S' || taxGroup == 'Q'){
        taxOwed = taxable * 0.25;
    }
    else if(taxGroup == 'M'){
        taxOwed = taxable * 0.10;
    }
    else if(taxGroup == 'A' || taxGroup == 'R'){
        taxOwed = taxable * 0.03;
    }
    else if(taxGroup == 'P'){
        taxOwed = 0.0;
    }
    else{
        printf("Error!");
        exit(EXIT_FAILURE);
    }

    // If tax > 50000 then tax = 50000
    if(taxOwed > 50000){
        return 50000;
    }
    else{
        return taxOwed;
    }
}

// Function to compute tax group based on income
char computeTaxGroup(double taxable) {
    if (taxable >= 500000) {
        return 'S';
    }
    else if(taxable >= 200000){
        return 'Q';
    }
    else if(taxable >= 100000){
        return 'M';
    }
    else if(taxable >= 50000){
        return 'A';
    }
    else if(taxable >= 20000){
        return 'R';
    }
    else{
        return 'P';
    }
}

// Function to compute taxable income based on income and deduction values
double computeTaxableIncome(double income, double deduction) {
    if (income >= deduction){
        return income - deduction;
    }
    else{
        return 0.0;
    }
}

// Set input income and deduction
void userInput(double *income, double *deduction) {
    // Variables
    double amount;
    *income = 0.0;
    *deduction = 0.0;

    // Get inputs repeatedly until 0.0 is entered
    while (1) {
        printf("Enter next amount : ");

        // Read userInput using scanf
        if (scanf("%lf", &amount) == 1) {
            if (amount == 0.0){
                break;
            }
            else if(amount > 0.0){
                *income += amount;
            }
            else if(amount < 0.0){
                *deduction += fabs(amount);
            }
        }
    }
}
