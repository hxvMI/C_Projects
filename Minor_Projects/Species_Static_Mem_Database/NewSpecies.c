/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/*---------------------------------------------------------------------------*/


// String representations of animal types
static const char *ANIMAL_TYPE_STRING[] = {"mammal", "insect", "bird", "fish"};


// Enumeration of animal types
enum AnimalType {MAMMAL, INSECT, BIRD, FISH};


// Array of structures
struct Species {
    double size;
    char name[128];
    enum AnimalType type;
};


// Function to determine the animal type based on input name
bool determineAnimalType(const char *inputName, enum AnimalType *type) {
    if (strcmp(inputName, "mammal") == 0) *type = MAMMAL;
    else if (strcmp(inputName, "insect") == 0) *type = INSECT;
    else if (strcmp(inputName, "bird") == 0) *type = BIRD;
    else if (strcmp(inputName, "fish") == 0) *type = FISH;
    else {
        printf("Please enter a valid type: mammal, insect, bird, or fish\n");
        return false;
    }
    return true;
}


// Function to print information of each species
void printSpecies(struct Species *speciesArray, int speciesCount) {
    printf("\nThe following new species were found:\n");
    for (int i = 0; i < speciesCount; i++) {
        printf("%-20s has size %6.2lf and is a %s\n", speciesArray[i].name, speciesArray[i].size,
 ANIMAL_TYPE_STRING[speciesArray[i].type]);
    }
}


int main() {
    // Declare Variables
    char inputName[128];
    struct Species *speciesArray = (struct Species *)malloc(sizeof(struct Species));
    int speciesCount = 0;

    
    if (speciesArray == NULL) {
        printf("Problem with Memory allocation\n");
        return 1;
    }
    

    // Get animal name input
    printf("\n\nNewSpecies\nEnter animal information (\"exit\" to exit)");
    printf("\nWhat is the name : ");
    scanf("%s", inputName);

    
    // Continues till "exit" is input
    while (strcmp(inputName, "exit") != 0) {
        speciesArray = (struct Species *)realloc(speciesArray, (speciesCount + 1) * sizeof(struct Species));

        
        if (speciesArray == NULL) {
            printf("Problem with Memory allocation\n");
            return 1;
        }
        

        // Copy species name
        strcpy(speciesArray[speciesCount].name, inputName);
        

        // Get animal size input and determines if it's a valid number
        printf("What is the size : ");
        if (scanf("%lf", &speciesArray[speciesCount].size) != 1) {
            printf("Please enter a valid number.\n");
            free(speciesArray); // Free allocated memory
            return 2; // Exit the program
        }        


        // Get animal type input
        printf("What is the type : ");
        scanf("%s", inputName);
        

        // Determine if animal type is valid via if false exits prog
        // if valid increases species count
        if (determineAnimalType(inputName, &speciesArray[speciesCount].type) != 1) {
            free(speciesArray);
            return 2;
        }
        else speciesCount++;
        

        // Start of next input cycle
        printf("Enter animal information (\"exit\" to exit)");
        printf("\nWhat is the name : ");
        scanf("%s", inputName);
    }


    printSpecies(speciesArray, speciesCount);


    free(speciesArray);
    return 0;
}

