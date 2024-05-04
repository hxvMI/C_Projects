/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*---------------------------------------------------------------------------*/


// Function Declarations
double *input_matrix(int *rows, int *columns, char *name);
int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2, int m2_rows, int m2_columns, double *m3);
void output_matrix(double *matrix, int rows, int columns);


// Read the two matrices by prompting the user for their dimensions
double *input_matrix(int *rows, int *columns, char *name) {
    double *matrix;


    // Scan input and dynamically set matrix
    printf("Enter the # of rows for %s:   ", name);
    scanf("%d", rows);
    printf("Enter the # of columns for %s:   ", name);
    scanf("%d", columns);


    // Dynamically set matrix
    matrix = (double *)malloc((*rows) * (*columns) * sizeof(double));
    

    // Test if input is valid and matrix is valid
    if (*rows <= 0 || *columns <= 0) {
        printf("Error in dimensions, please enter values greater than 0\n");
        return NULL;
    }
    if (matrix == NULL) {
        printf("Error allocating memory for %s\n", name);
        return NULL;
    }


    printf("Enter %s values using row-major ordering seperated by a space: ", name);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            scanf("%lf", &matrix[i * (*columns) + j]);
        }
    }
    return matrix;
}


// Multiply the two matrices together 
int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2, int m2_rows, int m2_columns, double *m3) {	
    // Check if dimensions are appropriate for matric multiplication
    if (m1_columns != m2_rows) {
        printf("Error in dimensions, m1 columns do not match m2 rows\n");
        return -1;
    }


    for (int i = 0; i < m1_rows; i++) {
        for (int j = 0; j < m2_columns; j++) {
            m3[i * m2_columns + j] = 0;
            for (int k = 0; k < m2_rows; k++) {
                m3[i * m2_columns + j] += m1[i * m1_columns + k] * m2[k * m2_columns + j];
            }
        }
    }
    return 1;
}


// Outputs the two input and the result matrice
void output_matrix(double *matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.2lf ", matrix[i * columns + j]);
        }
        printf("\n");
    }
}


/*---------------------------------------------------------------------------*/
int main(void) {
    double *m1, *m2, *m3;
    int m1_rows, m1_columns, m2_rows, m2_columns;


    if (((m1 = input_matrix(&m1_rows, &m1_columns, "Matrix 1")) != NULL) &&
        ((m2 = input_matrix(&m2_rows, &m2_columns, "Matrix 2")) != NULL) &&
        ((m3 = malloc(m1_rows * m2_columns * sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1, m1_rows, m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2, m2_rows, m2_columns);
        if (matrix_multiply(m1, m1_rows, m1_columns, m2, m2_rows, m2_columns, m3)) {
            printf("Product\n");
            output_matrix(m3, m1_rows, m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}
