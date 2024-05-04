#include <stdio.h>

int main() {
    // Constants
    const int FEET_PER_ATMOSPHERE = 33;
    const double RECOMMENDED_PPO2  = 1.4;
    const double CONTINGENCY_PPO2 = 1.6;

    // Variables
    int depth, o2Percentage;
    double ambientPressure, o2Pressure;
    char o2Group;

    // Getting depth from input
    printf("Enter depth and percentage O2   : ");
    scanf("%d %d", &depth, &o2Percentage);

    // Calculations
    ambientPressure = (double)depth / FEET_PER_ATMOSPHERE + 1;
    o2Pressure = ambientPressure * o2Percentage / 100;
    o2Group = 'A' + ((int)(o2Pressure * 10));

    // Output Calculations
    printf("\nAmbient pressure                : %.1f", ambientPressure);
    printf("\nO2 pressure                     : %.2f\n", o2Pressure);
    printf("O2 group                        : %c\n\n", o2Group);

    // Check if Recommended Maximal PPO is 1.4
    if(o2Pressure > RECOMMENDED_PPO2) {
        printf("Exceeds maximal O2 pressure     : true\n");
    }
    else{
        printf("Exceeds maximal O2 pressure     : false\n");
    }

    // Check if Contingency Maximal PPO is 1.6
    if(o2Pressure > CONTINGENCY_PPO2) {
        printf("Exceeds contingency O2 pressure : true\n");
    }
    else{
        printf("Exceeds contingency O2 pressure : false\n");
    }

    return 0;
}

