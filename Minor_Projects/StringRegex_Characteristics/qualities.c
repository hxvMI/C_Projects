#include <string.h>
#include <stdio.h>


// Constants
#define FILE_NAME "MyQualities.txt"
#define BUFF_SIZE 1024


// Function prototyps
void writeQualitiesToFile(FILE *file);
void readQualitiesFromFile(FILE *file);


// Function to write qualities to a file
void writeQualitiesToFile(FILE *file) {
    char quality[BUFF_SIZE];
    char inputBuffer[BUFF_SIZE];
    char qualities[BUFF_SIZE] = "";

    
    printf("\nPlease enter sentences, . to end:\n");


    // Read input til '.' is input
    while (fgets(inputBuffer, sizeof(inputBuffer), stdin)) {
        // Remove newline from input 
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0'; 


        // Check if '.' is input to end
        if (strcmp(inputBuffer, ".") == 0) break;


       // Check if sentence starts with "I am"
        if (strstr(inputBuffer, "I am ") == inputBuffer) {
            // store quality substring
            strncpy(quality, inputBuffer + 5, sizeof(quality) - 1); 


            // add comma
            if (qualities[0] != '\0') {
                strncat(qualities, ", ", sizeof(qualities) - strlen(qualities) - 1); 
            }


            // add quality to qualities string and write to file with a new line at end
            strncat(qualities, quality, sizeof(qualities) - strlen(qualities) - 1); 
            fprintf(file, "%s\n", quality);
        }
    }

    
    // print all qualities
    printf("The qualities are, %s.\n\n", qualities); 
}


// Function to read and print qualities from a file
void readQualitiesFromFile(FILE *file) {
    char buffer[BUFF_SIZE];
    

    printf("Confirming the saved qualities ...\n");


    // Read and print from file
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }


    printf("\n");
}



int main() {
    // Open file and check if its made
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Can't create file [%s] in main.\n", FILE_NAME);
        return 1;
    }


    // Call file writing function and then close file
    writeQualitiesToFile(file);
    fclose(file); 


    // ReOpen file to read and check that it can be read
    file = fopen(FILE_NAME, "r"); 
    if (file == NULL) {
        printf("Error: Can't read file [%s] in main.\n", FILE_NAME);
        return 1;
    }


    // Call file reading function then close file
    readQualitiesFromFile(file);
    fclose(file); 


    // Check if file can be deleted then delete it file
    if (remove(FILE_NAME) != 0) {
        printf("Error: Can't delete file [%s] in main.\n", FILE_NAME);
        return 1;
    }


    return 0;
}

