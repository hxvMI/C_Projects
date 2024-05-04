#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <ctype.h> 


// Function Prototype
int numOfWords(const char *string);


// Function to count the number of words in a sentence
int numOfWords(const char *string) {
    int count = 0;
    char *token = strtok((char *)string, " ");


    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }


    return count;
}


int main() {
    // variables
    char input_string[1000];
    char regex_pattern[50];
    char *rest;
    char *sentence;
    char delimiter[] = ".!?";


    // Get sentence from user input 
    printf("\n\nPlease enter the string to analyze: ");
    fgets(input_string, sizeof(input_string), stdin);
    input_string[strcspn(input_string, "\n")] = '\0'; // Remove the trailing newline character


    // Ask for Regex
    printf("Please enter the regular expression: ");
    scanf("%s", regex_pattern);


    // Check if Regex is valid
    regex_t regex;
    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        printf("Error: Regex is not valid\n");
        return 1;
    }


    // Split each sentence and print output
    sentence = strtok_r(input_string, delimiter, &rest);
    while (sentence != NULL) {


        // Skip whitespace at start if in a sentence
        while (isspace(*sentence)) {
            sentence++;
        }


        // Print the current sentence
        printf("%s\n", sentence);


        // Check if Regex matches
        if (regexec(&regex, sentence, 0, NULL, 0) == 0) {
            printf("Yes   ");
        } 
        else {
            printf("No    ");
        }


        // Pritn number of words in the current sentence and move to next sentence
        printf("%d words\n", numOfWords(sentence));
        sentence = strtok_r(NULL, delimiter, &rest);
    }


    // Free the memory
    regfree(&regex);


    return 0;
}

