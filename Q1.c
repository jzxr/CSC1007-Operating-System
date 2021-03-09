
/* Input */
// Total instance of resource A
// Total instance of resource B
// Total instance of resource C
// Total instance of resource D
// Allocation and Max 

/* Output */
// Safe or Unsafe 
    // Safe State
    // Print out the execution sequence in which these processes may complete
// UnSafe State
    // Display the process at which it fails and 
    // Print out Available resource and Resources needed

/* Variables */
// Resource A, B, C, D
// Allocation[6][4]
// Max[6][4]
// Need[6][4] = Max[6][4] - Allocation[6][4]
// Available[4] = TotalResource[4] - SummationOfAllocation[4]


/* Algo */

#include <stdio.h>
#include <stdlib.h>
#define RESOURCE 4
#define PROCESS 6

//Function Prototype
void readResource(int total[]);
void calculateNeed(int allocation[][RESOURCE], int max[][RESOURCE], int need[][RESOURCE]);
void calculateAvailable(int allocation[][RESOURCE], int total[], int available[]);

int main(){
    // Defining Variables 
    int allocation[PROCESS][RESOURCE] = {{2, 1, 3, 3},{2, 3, 1, 2},{3, 3, 3, 1},{2, 1, 3, 4},{3, 2, 2, 5},{2, 1, 2, 3}};
    int max[PROCESS][RESOURCE] = {{7, 3, 4, 5},{8, 6, 2, 5},{9, 5, 5, 6},{6, 4, 6, 5},{8, 3, 2, 8},{8, 3, 2, 3}};
    int need[PROCESS][RESOURCE];
    int available[RESOURCE];
    int total[RESOURCE];

    readResource(total);
    calculateNeed(allocation, max, need);
    calculateAvailable(allocation, total, available);

    //To Be Continued Here
}

//Scan for total instance for resource A, B, C, D
void readResource(int total[]){
    int check[RESOURCE] = {14,11,14,18};
    char resourceType[RESOURCE] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < RESOURCE; i++){
        printf("Enter total number of Resource %c: ", resourceType[i]);
        scanf("%d", &total[i]);
        if (total[i] < check[i]){
            printf("Min number of instance for resource %c must be %d or above \n", resourceType[i], check[i]);
            exit(0);
        }
    }   
}

void calculateNeed(int allocation[][RESOURCE], int max[][RESOURCE], int need[][RESOURCE]){
    for (int i = 0; i < PROCESS; i++){
        for (int j = 0; j < RESOURCE; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void calculateAvailable(int allocation[][RESOURCE], int total[] ,int available[]){
    int totalAllocation[RESOURCE] = {0, 0, 0, 0};
    for (int i = 0; i < PROCESS; i++){
        totalAllocation[0] += allocation[i][0];
        totalAllocation[1] += allocation[i][1];
        totalAllocation[2] += allocation[i][2];
        totalAllocation[3] += allocation[i][3];
    }

    for (int i = 0; i < RESOURCE; i++){
        available[i] = total[i] - totalAllocation[i];
    }
}



/* Code for Checking */
// for (int i = 0; i < RESOURCE; i++){
//     printf("%d \n", total[i]);
// }

// for (int i = 0; i < PROCESS; i++){
//     for (int j = 0; j < RESOURCE; j++){
//         printf("%d ", need[i][j]);
//     }
//     printf("\n");
// }
