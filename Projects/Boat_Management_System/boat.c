#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_BOATS 120
#define MAX_NAME_LENGTH 127
#define MAX_SLIP_NUMBER 85
#define MAX_STORAGE_SPACE_NUMBER 50


typedef enum {
    slip,
    land,
    trailor,
    storage,
    no_place
} PlaceType;


typedef union {
    int slip_number;
    char bay_letter;
    char trailor_license_tag[20];
    int storage_space_number;
} PlaceInfo;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int length_in_feet;
    PlaceType place_type;
    PlaceInfo place_info;
    float money_owed;
} Boat;


// Function declarations
void inventoryOption(Boat *boat_Array[], int boatCount);
void addOption(Boat *boat_Array[], int *boatCount, char *boatString);
void removeOption(Boat *boat_Array[], int *boatCount, char *boat_Name);
void paymentOption(Boat *boat_Array[], int boatCount, char *boat_Name, float pay_Amount);
void monthOption(Boat *boat_Array[], int boatCount);
int boatExists(Boat *boat_Array[], int boatCount, char *boat_Name);
PlaceType StringToPlaceType(char *PlaceString);
char *PlaceToString(PlaceType Place);
int compareByName(const void *a, const void *b);
void sortBoatsByName(Boat *boat_Array[], int boatCount);
void toUpperCase(char *str);
void readBoatDataFromFile(FILE *file, Boat *boat_Array[], int *boatCount);
void writeBoatDataToFile(char *filename, Boat *boat_Array[], int boatCount);
void boatManagementSystem(Boat *boat_Array[], int *boatCount);


//-------------------------------------------------------------------------------------------------
//----Convert a string to a place
PlaceType StringToPlaceType(char * PlaceString) {

    if (!strcasecmp(PlaceString, "slip")) {
        return (slip);
    }
    if (!strcasecmp(PlaceString, "land")) {
        return (land);
    }
    if (!strcasecmp(PlaceString, "trailor")) {
        return (trailor);
    }
    if (!strcasecmp(PlaceString, "storage")) {
        return (storage);
    }
    return (no_place);
}


//-------------------------------------------------------------------------------------------------
//----Convert a place to a string
char *PlaceToString(PlaceType Place) {

    switch (Place) {
        case slip:
            return ("slip");
        case land:
            return ("land");
        case trailor:
            return ("trailor");
        case storage:
            return ("storage");
        case no_place:
            return ("no_place");
        default:
            printf("How the faaark did I get here?\n");
            exit(EXIT_FAILURE);
            break;
    }
}
//-------------------------------------------------------------------------------------------------


/* 
   Compares the boat names for sorting
   if a - b = neg   a is before b
   if a - b = pos   a is after b
   if a - b = 0     a and b are same 
*/
int compareByName(const void *a, const void *b) {
    const Boat *boatA = *(const Boat **)a;
    const Boat *boatB = *(const Boat **)b;
    return strcasecmp(boatA->name, boatB->name);
}


// Sorts boats by name using compareByName function
void sortBoatsByName(Boat *boat_Array[], int boatCount) {
    qsort(boat_Array, boatCount, sizeof(Boat *), compareByName);
}


// Checks if boat is present or not for (P)ayment and (R)emove options
int boatExists(Boat *boat_Array[], int boatCount, char *boat_Name) {
    int i;


    for (i = 0; i < boatCount; i++) {
        if (strcasecmp(boat_Array[i]->name, boat_Name) == 0) {
            return 1; // Boat exists
        }
    }
    return 0; // Boat does not exist
}


// Converts a string to uppercase via forloop
void toUpperCase(char *str) {
    // Implementation of toUpperCase function
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}


// Adds new boat to boat_Array
void addOption(Boat *boat_Array[], int *boatCount, char *boatString) {
    char name[MAX_NAME_LENGTH];
    int length_in_feet;
    char placeString[20];
    char numberString[20];
    float money_owed;
    int slipNumber;
    int storageSpaceNumber;
    char landLetter;

    // Check if the input matches the CSV format
    if (sscanf(boatString, "%[^,],%d,%[^,],%[^,],%f", name, &length_in_feet, placeString, 
numberString, &money_owed) != 5) {
        printf("Invalid format. Please enter the boat data in CSV format.\n");
        return;
    }


    Boat *newBoat = (Boat *)malloc(sizeof(Boat));
    if (!newBoat) {
        printf("Memory allocation failed in addOption\n");
        return;
    }


    // Initilizes newBoat's
    newBoat->length_in_feet = length_in_feet;
    newBoat->money_owed = money_owed;
    newBoat->place_type = StringToPlaceType(placeString);


    // Check if valid according to place type
    if (strcasecmp(placeString, "slip") == 0) {
        slipNumber = atoi(numberString);
        if (slipNumber < 1 || slipNumber > MAX_SLIP_NUMBER) {
            printf("Slip number must be between 1 and %d.\n", MAX_SLIP_NUMBER);
            free(newBoat);
            return;
        }
        newBoat->place_info.slip_number = atoi(numberString);
    } 
    else if (strcasecmp(placeString, "storage") == 0) {
        storageSpaceNumber = atoi(numberString);
        if (storageSpaceNumber < 1 || storageSpaceNumber > MAX_STORAGE_SPACE_NUMBER) {
            printf("Storage space number must be between 1 and %d.\n", MAX_STORAGE_SPACE_NUMBER);
            free(newBoat);
            return;
        }
        newBoat->place_info.storage_space_number = atoi(numberString);
    } 
    else if (strcasecmp(placeString, "land") == 0) {
        landLetter = numberString[0];
        if (strlen(numberString) != 1 || !isupper(landLetter)) {
            printf("Land place info must be a single uppercase letter.\n");
            free(newBoat);
            return;
        }
        newBoat->place_info.bay_letter = landLetter;
    } 
    else {
        strcpy(newBoat->place_info.trailor_license_tag, numberString);
    }


    strncpy(newBoat->name, name, MAX_NAME_LENGTH - 1);
    newBoat->name[MAX_NAME_LENGTH - 1] = '\0';


    // Add new boat to boat_Array and notify successful addition
    boat_Array[(*boatCount)++] = newBoat;
    printf("Boat added successfully.\n");
}


// Displays view of Boat Data
void inventoryOption(Boat *boat_Array[], int boatCount) {
    int i;


    // Formated so easier to identify where issuse is by placing corresponding info above position
    printf("\n%-20s %-6s %-10s %-10s %s\n", "Boat Name", "Length", "Place Type", "Place Info", 
"Money Owed");


    for (i = 0; i < boatCount; i++) {
        printf("%-20s %-6d %-10s ", boat_Array[i]->name, boat_Array[i]->length_in_feet, 
PlaceToString(boat_Array[i]->place_type));
        switch (boat_Array[i]->place_type) {
            case slip:
                printf("#%-10d ", boat_Array[i]->place_info.slip_number);
                break;
            case land:
                printf("%-10c ", boat_Array[i]->place_info.bay_letter);
                break;
            case trailor:
                printf("%-10s ", boat_Array[i]->place_info.trailor_license_tag);
                break;
            case storage:
                printf("#%-10d ", boat_Array[i]->place_info.storage_space_number);
                break;
            default:
                printf("Invalid place ");
        }
        printf("$%8.2f\n", boat_Array[i]->money_owed);
    }
}


/*
   Replaces removed boat with boat at last index then decrements size by 1
   don't have to worry about it causing things to be unsorted if user leaves immediatly after
   since on exit the data gets sorted one last time
*/
void removeOption(Boat *boat_Array[], int *boatCount, char *boat_Name) {
    int i;
    int found = 0; // Tracks if boat is found used to exit loop
    char currentBoatName[MAX_NAME_LENGTH];


    // Converts boat name to uppercase
    toUpperCase(boat_Name);


    for (i = 0; i < *boatCount; i++) {
        currentBoatName[MAX_NAME_LENGTH];


        // Uppercases current boat name to for case insensitive comparison
        strncpy(currentBoatName, boat_Array[i]->name, MAX_NAME_LENGTH);
        toUpperCase(currentBoatName);


        if (strcasecmp(currentBoatName, boat_Name) == 0) {
            printf("Boat '%s' removed successfully.\n", boat_Array[i]->name);
            free(boat_Array[i]);
            boat_Array[i] = boat_Array[*boatCount - 1];
            (*boatCount)--;
            found = 1;
            break; // Once found can end search
        }
    }
    if (!found) {
        printf("No boat with that name.\n");
    }
}


// Applys payment to a boats debt
void paymentOption(Boat *boat_Array[], int boatCount, char *boat_Name, float pay_Amount) {
    int i;
    int found = 0; // Tracks if boat is found used to exit loop
    char currentBoatName[MAX_NAME_LENGTH];


    // Convert boat name to uppercase
    toUpperCase(boat_Name);


    for (i = 0; i < boatCount; i++) {
        currentBoatName[MAX_NAME_LENGTH];


        // Uppercase current boat name for case-insensitive comparison
        strncpy(currentBoatName, boat_Array[i]->name, MAX_NAME_LENGTH);
        toUpperCase(currentBoatName);


        if (strcasecmp(currentBoatName, boat_Name) == 0) {
            found = 1;
            if (pay_Amount > boat_Array[i]->money_owed) {
                printf("That is more than the amount owed, $%.2f\n", boat_Array[i]->money_owed);
            } 
            else {
                boat_Array[i]->money_owed -= pay_Amount;
                printf("Payment of $%.2f applied to '%s'.\n", pay_Amount, boat_Name);
            }
            break; // Once found can end search
        }
    }
    if (!found) {
        printf("No boat with that name.\n");
    }
}


// Increases amount owed depending on the type and foot lenght
void monthOption(Boat *boat_Array[], int boatCount) {
    float rate_per_foot;
    int i;


    for (i = 0; i < boatCount; i++) {
        rate_per_foot = 0.0;
        switch (boat_Array[i]->place_type) {
            case slip:
                rate_per_foot = 12.50;
                break;
            case land:
                rate_per_foot = 14.00;
                break;
            case trailor:
                rate_per_foot = 25.00;
                break;
            case storage:
                rate_per_foot = 11.20;
                break;
            default:
                printf("Invalid place type for boat '%s'.\n", boat_Array[i]->name);
                continue;
        }
        boat_Array[i]->money_owed += rate_per_foot * boat_Array[i]->length_in_feet;
    }
    printf("Monthly fees applied.\n");
}


// Reads Boat Data from file and allocates memory 
void readBoatDataFromFile(FILE *file, Boat *boat_Array[], int *boatCount) {
    char line[1024];
    char placeString[20];
    char numberString[20];

    while (fgets(line, sizeof(line), file)) {
        Boat *newBoat = (Boat *)malloc(sizeof(Boat));
        if (!newBoat) {
            printf("Memory allocation failed in readBoatDataFromFile\n");
            exit(EXIT_FAILURE);
        }


        placeString[20];
        numberString[20];


        sscanf(line, "%[^,],%d,%[^,],%[^,],%f\n", newBoat->name, &newBoat->length_in_feet, 
placeString, numberString, &newBoat->money_owed);
        newBoat->place_type = StringToPlaceType(placeString);


        // Is needed otherwise values get are read incorrectly
        // Convert slip number string to integer
        if (newBoat->place_type == slip) {
            newBoat->place_info.slip_number = atoi(numberString); 
        } 
        // Convert storage space number string to integer
        else if (newBoat->place_type == storage) {
            newBoat->place_info.storage_space_number = atoi(numberString);
        } 
        else {
        // Copy number string directly
            strcpy(newBoat->place_info.trailor_license_tag, numberString); 
        }
        boat_Array[(*boatCount)++] = newBoat;
    }
    fclose(file);
}


// Writes data back to file and frees memory
void writeBoatDataToFile(char *filename, Boat *boat_Array[], int boatCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Can't open file %s\n", filename);
        return;
    }


    // Write boat data back to the file
    for (int i = 0; i < boatCount; i++) {
        switch (boat_Array[i]->place_type) {
            case slip:
                fprintf(file, "%s,%d,%s,%d,%.2f\n", boat_Array[i]->name, 
boat_Array[i]->length_in_feet, PlaceToString(boat_Array[i]->place_type), 
boat_Array[i]->place_info.slip_number, boat_Array[i]->money_owed);
                break;
            case storage:
                fprintf(file, "%s,%d,%s,%d,%.2f\n", boat_Array[i]->name, 
boat_Array[i]->length_in_feet, PlaceToString(boat_Array[i]->place_type), 
boat_Array[i]->place_info.storage_space_number, boat_Array[i]->money_owed);
                break;
            default:
                fprintf(file, "%s,%d,%s,%s,%.2f\n", boat_Array[i]->name, 
boat_Array[i]->length_in_feet, PlaceToString(boat_Array[i]->place_type), 
boat_Array[i]->place_info.trailor_license_tag, boat_Array[i]->money_owed);
                break;
        }
        free(boat_Array[i]);
    }
    fclose(file);
}


// Handles Boat Management Menu processes
void boatManagementSystem(Boat *boat_Array[], int *boatCount) {
    char choice;
    char boatString[1024];
    char boat_Name[MAX_NAME_LENGTH];
    float pay_Amount;


    printf("\nWelcome to the Boat Management System");
    printf("\n-------------------------------------\n");


    do {
        printf("\n(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
        scanf(" %c", &choice);


        switch (choice) {
            case 'I':
            case 'i':
                sortBoatsByName(boat_Array, *boatCount);
                inventoryOption(boat_Array, *boatCount);
                break;
            case 'A':
            case 'a':
                sortBoatsByName(boat_Array, *boatCount);
                printf("Please enter the boat data in CSV format                 : ");
                scanf(" %[^\n]", boatString);
                addOption(boat_Array, boatCount, boatString);
                break;
            case 'R':
            case 'r':
                printf("Please enter the boat name                               : ");
                scanf(" %[^\n]", boat_Name);
                removeOption(boat_Array, boatCount, boat_Name);
                break;
            case 'P':
            case 'p':
                printf("Please enter the boat name                               : ");
                scanf(" %[^\n]", boat_Name);


                // Check if the boat exists before asking for payment
                if (!boatExists(boat_Array, *boatCount, boat_Name)) {
                    printf("No boat with that name.\n");
                    break;
                }


                printf("Please enter the amount to be paid                       : ");
                scanf("%f", &pay_Amount);
                paymentOption(boat_Array, *boatCount, boat_Name, pay_Amount);
                break;
            case 'M':
            case 'm':
                monthOption(boat_Array, *boatCount);
                break;
            case 'X':
            case 'x':
                printf("\nExiting the Boat Management System\n\n");
                sortBoatsByName(boat_Array, *boatCount);
                break;
            default:
                printf("Invalid option '%c'\n", choice);
        }


        // Clear input buffer otherwise input problems occur
        while (getchar() != '\n');
    } while (choice != 'X' && choice != 'x');
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Write cmd like this: %s <BoatData.csv>\n", argv[0]);
        return 1;
    }


    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Can't open file %s\n", argv[1]);
        return 1;
    }


    Boat *boat_Array[MAX_BOATS];
    int boatCount = 0;


    readBoatDataFromFile(file, boat_Array, &boatCount);
    sortBoatsByName(boat_Array, boatCount);
    boatManagementSystem(boat_Array, &boatCount);
    writeBoatDataToFile(argv[1], boat_Array, boatCount);


    return 0;
}
