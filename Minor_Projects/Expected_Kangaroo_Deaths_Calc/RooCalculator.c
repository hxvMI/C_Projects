#include <stdio.h>

int main() {
    // Variables
    const double ROAD_KILL_PROB = 1.47;
    const double ROAD_WIDTH_AVERAGE = 0.01;
    double squareSideLength, roadLength, rooDensity, roadSurfaceArea, expectedKills, squareTotalArea;
    int rooCount;

    // Getting inputs
    printf("Enter side of square in km  : ");
    scanf("%lf", &squareSideLength);

    printf("Enter roads length in km    : ");
    scanf("%lf", &roadLength);

    printf("Enter number of 'roos       : ");
    scanf("%d", &rooCount);

    // Calculations
    squareTotalArea = squareSideLength * squareSideLength;
    rooDensity = rooCount / squareTotalArea;
    roadSurfaceArea = ROAD_WIDTH_AVERAGE * roadLength; 
    expectedKills = ROAD_KILL_PROB * rooDensity * roadSurfaceArea; 

    // Display the expected number of kills
    printf("Expected number of kills is : %0.1lf\n", expectedKills);

    return 0;
}
