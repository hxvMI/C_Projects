#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXIMAL_PEOPLE 10
#define MAXIMAL_STRING_LENGTH 128


/*----Define data types */
typedef char string[MAXIMAL_STRING_LENGTH];
typedef struct personTag {
    string name;
    int age;
    struct personTag *bestFriend;
} personType;
typedef personType *personPointer;
typedef personPointer peoplePointers[MAXIMAL_PEOPLE];


// Function prototypes
personPointer findPerson(int currPerson, peoplePointers people, const string name);
void readBestFriends(peoplePointers people, int currPerson);
void printPeopleInfo(peoplePointers people, int currPerson);


// Function to find a person by name
personPointer findPerson(int currPerson, peoplePointers people, const string name) {
    int i;
 

    for (i = 0; i < currPerson; i++) {
        if (strcmp(people[i]->name, name) == 0) {
            return people[i];
        }
    }
    return NULL;
}


// Function to read and set best friend information
void readBestFriends(peoplePointers people, int currPerson) {
    int i;
    string bestFriendName;
  

    for (i = 0; i < currPerson; i++) {
        printf("Who is %s's best friend? ", people[i]->name);
        scanf("%s", bestFriendName);


        // Find the best friend and set the pointer
        // if not found set value to NULL
        personPointer bestFriend = findPerson(currPerson, people, bestFriendName);
        if (bestFriend != NULL) {
            people[i]->bestFriend = bestFriend;
        } 
        else {
            printf("Best friend not found in the list.\n");
            people[i]->bestFriend = NULL;
        }
    }
}


// Function to print people's information
void printPeopleInfo(peoplePointers people, int currPerson) {
    int i;


    for (i = 0; i < currPerson; i++) {
        printf("%-10s is %d", people[i]->name, people[i]->age);
        if (people[i]->bestFriend != NULL) {
            printf(", and his/her best friend is %s\n", people[i]->bestFriend->name);
        } 
        else {
            printf(", and he/she has no best friend\n");
        }
    }
}


int main() {
    peoplePointers people;
    int currPerson = 0;
    string name;
    int age;
    int i;


    // Read in the names and ages of people
    while (currPerson < MAXIMAL_PEOPLE) {
        

        printf("Please enter person name, 'exit' to exit : ");
        scanf("%s", name);


        if (strcmp(name, "exit") == 0) break;


        printf("Please enter %s's age : ", name);
        scanf("%d", &age);


        // Allocate memory for the new person
        personPointer newPersonPointer = (personPointer)malloc(sizeof(personType));
        if (newPersonPointer == NULL) {
            printf("Memory allocation failed in main while loop\n");
            return 1;
        }
        else {
            // Copy name, age, and set currPerson
            strcpy(newPersonPointer->name, name);
            newPersonPointer->age = age;
            newPersonPointer->bestFriend = NULL;
            people[currPerson] = newPersonPointer;
            
            // Increase index
            currPerson++;
        }
    }


    // Read and set best friend info
    readBestFriends(people, currPerson);


    // Print info
    printPeopleInfo(people, currPerson);


    // Free memory
    for (i = 0; i< currPerson; i++) {
        free(people[i]);
    }


    return 0;
}

