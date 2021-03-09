
/* Input */
// Total instance of resource A
// Total instance of resource B
// Total instance of resource C
// Total instance of resource D
// Allocation and Max 

/* Output */
// Safe or Unsafe 
    // Safe State (Allocate resource up to the max amount in some order)
    // Print out the execution sequence in which these processes may complete
// UnSafe State (Cycle entails unsafe state)
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
#define TRUE 1
#define FALSE 0

//Function Prototype
void readResource(int total[]);
void calculateNeed(int allocation[][RESOURCE], int max[][RESOURCE], int need[][RESOURCE]);
void calculateAvailable(int allocation[][RESOURCE], int total[], int available[]);
void bankerAlgo(int max[][RESOURCE], int need[][RESOURCE], int available[], int flag[], int processIndex);

int main(){
    // Defining Variables 
    int allocation[PROCESS][RESOURCE] = {{2, 1, 3, 3},{2, 3, 1, 2},{3, 3, 3, 1},{2, 1, 3, 4},{3, 2, 2, 5},{2, 1, 2, 3}};
    int max[PROCESS][RESOURCE] = {{7, 3, 4, 5},{8, 6, 2, 5},{9, 5, 5, 6},{6, 4, 6, 5},{8, 3, 2, 8},{8, 3, 2, 3}};
    int need[PROCESS][RESOURCE];
    int available[RESOURCE];
    int total[RESOURCE];
    int sequence[PROCESS];

    readResource(total);
    calculateNeed(allocation, max, need);
    calculateAvailable(allocation, total, available);

    //To Be Continued Here

    int flag[PROCESS] = {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};
    bankerAlgo(max, need, available, flag, 0);
    printf("\n--- SYSTEM IS IN SAFE STATE ---");
}

// Code quite messy, maybe there's a better solution?
void bankerAlgo(int max[][RESOURCE], int need[][RESOURCE], int available[], int flag[], int processIndex){ //First call is alwaays 0 for processIndex
    // if all Flag = False then break
        // if available - need >= 0 and flag[i] = true
            // then available = available - need
            // set flag[i] = False 
            // print some stuff here 
            // available = avilable + max
            // print some stuff
            // append i to sequence array
            // set counter to 0
            // bankerAlgo(max, need, available, flag)
        // else increment counter by 1 and repeat steps

    // Count number of False in Flag array
    int counterFlag = 0;
    // Base Case: Once all process has been allocated, return to main function
    for (int i = 0; i < PROCESS; i ++){
        if (flag[i] == FALSE){
            counterFlag += 1;
        }
    }
    // Recursive case
    if (counterFlag == PROCESS){
        return;
    } else {
        if (processIndex > PROCESS){
            printf("--- SYSTEM IS IN UNSAFE STATE ---\n");
            printf("Available resources: ");
            for (int i = 0; i < RESOURCE; i++){
                printf("%d ", available[i]);
            }
            printf("\n\nNEEDED RESOURCE FOR UNALLOCATED PROCESSES \n");
            for (int i = 0; i < PROCESS; i++){
                if (flag[i] == TRUE){
                    printf("Process %d: ", i);
                    for (int j = 0; j < RESOURCE; j++){
                        printf("%d ", need[i][j]);
                    }
                    printf("\n");
                }
            }
            exit(0);
        } else {
            // Count resource type: available is more then need
            int availableCounter = 0;
            for (int resourceIndex = 0; resourceIndex < RESOURCE; resourceIndex++){
                if (available[resourceIndex] - need[processIndex][resourceIndex] > 0){
                    availableCounter += 1;
                }
            }
            if ((availableCounter == RESOURCE) && (flag[processIndex] == TRUE)){
                for (int resourceIndex = 0; resourceIndex < RESOURCE; resourceIndex++){
                    available[resourceIndex] -= need[processIndex][resourceIndex];
                }
                flag[processIndex] = FALSE;

                // Print out the available resource here after allocating max resource to process
                printf("Available Resource after Allocation to process P%d: [", processIndex);
                for (int i = 0; i < RESOURCE; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                for (int resourceIndex = 0; resourceIndex < RESOURCE; resourceIndex++){
                    available[resourceIndex] += max[processIndex][resourceIndex];
                }
                // Print out the available resource after retreiving resource by from process
                printf("Available Resource after Retrieving resource from process P%d: [", processIndex);
                for (int i = 0; i < RESOURCE; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                // append process to string or something

                bankerAlgo(max, need, available, flag, 0);
            } else {
                bankerAlgo(max, need, available, flag, processIndex + 1);
            }
        }
    }
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
    printf("\n");
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
