//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef int* IntPtr;
//-----------------------------------------------------------------------------
void initializeIntArray(int array[], int size){
    srand(getpid()); // Use before using rand()


    for (int i = 0; i < size; i++){
        array[i] = rand();
    }
}


void initializeIntPtrArray(IntPtr array[], int intArray[], int size){
    for (int i = 0; i < size; i++){
        array[i] = &intArray[i];
    }
}


void printIntArray(int array[], int size){
    for (int i = 0; i < size; i++){
        printf("%2d : %10d\n", i, array[i]);
    }
}


void printIntPtrArrayValues(IntPtr array[], int size){
    for (int i = 0; i < size; i++){
        printf("%2d : %10d\n", i, *array[i]);
    }
}


void bubbleSortIntArray(int* array, int size){
    int swap, temp;
    

    for (int i = 0; i < size - 1; i++){
        swap = 0;
        for (int j = 0; j < size - i - 1; j++){
            if (*(array + j) > *(array + j + 1)){
                temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
                swap = 1;
            }
        }
        if (swap == 0){
            break;
        }
    }
}


void bubbleSortIntPtrArray(IntPtr* array, int size){
    IntPtr temp;
    int swap;
    

    for (int i = 0; i < size - 1; i++){
        swap = 0;
        for (int j = 0; j < size -i - 1; j++){
            if (*array[j] > *array[j + 1]){
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swap = 1;
            }
        }
        if (swap == 0){
            break;
        }
    }
}


int main(void){
    // Define variables
    int intArray[5];
    IntPtr pointArray[5];


    // Initialize arrays
    initializeIntArray(intArray, 5);
    initializeIntPtrArray(pointArray, intArray, 5);


    // Print array of integers
    printf("---- Initialized array of integers ----\n");
    printIntArray(intArray, 5);


    // Sort array of pointers and print them
    bubbleSortIntPtrArray(pointArray, 5);
    printf("---- Sorted array of pointers ----\n");
    printIntPtrArrayValues(pointArray, 5);


    // Sort array of integers and print them
    bubbleSortIntArray(intArray, 5);
    printf("---- Sorted array of integers ----\n");
    printIntArray(intArray, 5);


    // Print integers array
    printf("---- Array of pointers ----\n");
    printIntPtrArrayValues(pointArray, 5);


    return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
