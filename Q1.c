#include <stdio.h>
#include <stdlib.h>
#define RESOURCE 4
#define PROCESS 6
#define TRUE 1
#define FALSE 0

int noOfProcess;
int noOfResources;
int maxOfResources;
char resourcetype[] = {'A', 'B', 'C', 'D', 'E', 'F'};

//Function Prototype
void readResource(int total[], int noOfResources, int choice);
void readMax(int max[][noOfResources], int noOfProcess, int noOfResources, int total[]);
void readAllocation(int allocation[][noOfResources], int noOfProcess, int noOfResources, int max[][noOfResources]);
void calculateNeed(int allocation[][noOfResources], int max[][noOfResources], int need[][noOfResources], int noOfProcess, int noOfResources);
void calculateAvailable(int allocation[][noOfResources], int total[] ,int available[], int noOfProcess, int noOfResources);
void bankerAlgo(int max[][noOfResources], int need[][noOfResources], int available[], int flag[], int processIndex, int noOfProcess, int noOfResource);

int main(){
    // Defining Variables 
    int choice;
    int need[PROCESS][RESOURCE];
    
    printf("Select Choice: \n1) Hardcoded  \n2) User input\n");
    scanf("%d", &choice);

    if (choice == 1){
        // Double check here
        int allocation[6][4] = {{2, 1, 3, 3},
                                {2, 3, 1, 2},
                                {3, 3, 3, 1},
                                {2, 1, 3, 4},
                                {3, 2, 2, 5},
                                {2, 1, 2, 3}};
        int max[6][4] = {{7, 3, 4, 5},
                         {8, 6, 2, 5},
                         {9, 5, 5, 6},
                         {6, 4, 6, 5},
                         {8, 3, 2, 8},
                         {8, 3, 2, 3}};

        int need[PROCESS][RESOURCE];
        int available[RESOURCE];
        int total[RESOURCE];

        readResource(total, RESOURCE, choice);
        calculateNeed(allocation, max, need, PROCESS, RESOURCE);
        calculateAvailable(allocation, total, available, PROCESS, RESOURCE);

        int flag[PROCESS] = {TRUE, TRUE, TRUE, TRUE, TRUE, TRUE};
        bankerAlgo(max, need, available, flag, 0, PROCESS, RESOURCE);
        printf("\n--- SYSTEM IS IN SAFE STATE ---\n");
    }

    else if (choice = 2){

        printf("Enter the number of process(between 1-6): ");
        scanf("%d", &noOfProcess);
        
        if (noOfProcess < 1 || noOfProcess > 6){
            printf("Invalid number of process. \n");
            exit(0);
        }

        printf("Enter the number of resources(between 1-6): ");
        scanf("%d", &noOfResources);

        if (noOfResources < 1 || noOfResources > 6){
            printf("Invalid number of resources \n");
            exit(0);
        }

        int allocation[noOfProcess][noOfResources];
        int max[noOfProcess][noOfResources];
        int need[noOfProcess][noOfResources];
        int available[noOfResources];
        int total[noOfResources];
        
        readResource(total, noOfResources, choice);
        readMax(max, noOfProcess, noOfResources, total);
        readAllocation(allocation, noOfProcess, noOfResources, max);
        calculateNeed(allocation, max, need, noOfProcess, noOfResources);
        calculateAvailable(allocation, total, available, noOfProcess, noOfResources);

        int flag[noOfProcess];
        for (int i = 0; i < noOfProcess; i++){
            flag[i] = TRUE;
        }

        bankerAlgo(max, need, available, flag, 0, noOfProcess, noOfResources);
        printf("\n--- SYSTEM IS IN SAFE STATE ---\n");
        
    } else {
        printf("Enter Invalid option. \n");
        exit(0);
    }
}

//Check Error Here
void bankerAlgo(int max[][noOfResources], int need[][noOfResources], int available[], int flag[], int processIndex, int noOfProcess, int noOfResources){ //First call is alwaays 0 for processIndex
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

    // printf("No Of Resources: %d\n", noOfResources);
    // for (int i = 0; i < noOfResource; i++){
    //     printf("Test\n");
    //     printf("%d\n", available[i]);
    // }
    // Count number of False in Flag array
    int counterFlag = 0;
    // Base Case: Once all process has been allocated, return to main function
    for (int i = 0; i < noOfProcess; i ++){
        if (flag[i] == FALSE){
            counterFlag += 1;
        }
    }
    // Recursive case
    if (counterFlag == noOfProcess){
        return;
    } else {
        if (processIndex > noOfProcess){
            printf("--- SYSTEM IS IN UNSAFE STATE ---\n");
            printf("Available resources: ");
            for (int i = 0; i < noOfResources; i++){
                printf("%d ", available[i]);
            }
            printf("\n\nNEEDED RESOURCE FOR UNALLOCATED PROCESSES \n");
            for (int i = 0; i < noOfProcess; i++){
                if (flag[i] == TRUE){
                    printf("Process %d: ", i);
                    for (int j = 0; j < noOfResources; j++){
                        printf("%d ", need[i][j]);
                    }
                    printf("\n");
                }
            }
            exit(0);
        } else {
            // Count resource type: available is more then need
            int availableCounter = 0;
            for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                if (available[resourceIndex] - need[processIndex][resourceIndex] >= 0){
                    availableCounter += 1;
                }
            }
            if ((availableCounter == noOfResources) && (flag[processIndex] == TRUE)){
                for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                    available[resourceIndex] -= need[processIndex][resourceIndex];
                }
                flag[processIndex] = FALSE;

                // Print out the available resource here after allocating max resource to process
                printf("Available Resource after Allocation to process P%d: [", processIndex);
                for (int i = 0; i < noOfResources; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                    available[resourceIndex] += max[processIndex][resourceIndex];
                }
                // Print out the available resource after retreiving resource by from process
                printf("Available Resource after Retrieving resource from process P%d: [", processIndex);
                for (int i = 0; i < noOfResources; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                // append process to string or something

                bankerAlgo(max, need, available, flag, 0, noOfProcess, noOfResources);
            } else {
                bankerAlgo(max, need, available, flag, processIndex + 1, noOfProcess, noOfResources);
            }
        }
    }
}

//Scan for total instance for resource A, B, C, D
void readResource(int total[], int noOfResources, int choice){
    for (int i = 0; i < noOfResources; i++){
        printf("Enter total number of Resource %c: ", resourcetype[i]);
        scanf("%d", &total[i]);
        // Resource A, B, C, D needs to be larger than 14, 11, 14, 18 respectively 
        if (choice == 1){
            int check[RESOURCE] = {14,11,14,18};
            if (total[i] < check[i]){
                printf("Min number of instance for resource %c must be %d or above \n", resourcetype[i], check[i]);
                exit(0);
            }
        }
    }   
    printf("\n");
}

void readMax(int max[][noOfResources], int noOfProcess, int noOfResources, int total[]){
    for (int i = 0; i < noOfProcess; i++){
        printf("Enter number of max resource for process %d\n", i+1);
        for (int j = 0; j < noOfResources; j++){
            printf("Resource %c: ", resourcetype[j]);
            scanf("%d", &max[i][j]);
            if (max[i][j] > total[j]){
                printf("Process Max value cannot be more than number of total resource. \n");
                exit(0);
            }
        }
    }
}

void readAllocation(int allocation[][noOfResources], int noOfProcess, int noOfResources, int max[][noOfResources]){
    for (int i = 0; i < noOfProcess; i++){
        printf("Enter number of allocation resource for process %d\n", i+1);
        for (int j = 0; j < noOfResources; j++){
            printf("Resource %c: ", resourcetype[j]);
            scanf("%d", &allocation[i][j]);
            if (allocation[i][j] > max[i][j]){
                printf("Process Allocation value cannot be more than process Max value. \n");
                exit(0);
            }
        }
    }
}

void calculateNeed(int allocation[][noOfResources], int max[][noOfResources], int need[][noOfResources], int noOfProcess, int noOfResources){
    for (int i = 0; i < noOfProcess; i++){
        for (int j = 0; j < noOfResources; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void calculateAvailable(int allocation[][noOfResources], int total[] ,int available[], int noOfProcess, int noOfResources){

    int totalAllocation[noOfResources];
    for (int i = 0; i < noOfResources; i++){
        totalAllocation[i] = 0;
    }

    for (int i = 0; i < noOfResources; i++){
        for (int j = 0; j < noOfProcess; j++){
            totalAllocation[i] += allocation[j][i];
        }
    }

    for (int i = 0; i < noOfResources; i++){
        available[i] = total[i] - totalAllocation[i];
        if(available[i] < 0){
            printf("Total Allocation of Resource cannot be more then total resource. \n");
            exit(0);
        }
    }
}


// Replace number with alphbet for resource type 


//Test Code
/*
for (int i = 0; i < noOfResources; i++){
    printf("%d\n", total[i]);
}
*/

/*
for (int i = 0; i < noOfProcess; i++){  
            for (int j = 0; j < noOfResources; j++){
                printf("%d ", max[i][j]);
            }
            printf("\n");
        }
*/
