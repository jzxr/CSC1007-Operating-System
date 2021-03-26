#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// Global variable
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
    
    printf("Select Choice: \n1) Question 1  \n2) Question 1 with user input\n");
    printf("User Choice: ");
    scanf("%d", &choice);

    // Follows assignment requirement
    if (choice == 1){
        // Allocation and Max resources stated in the specification
        // initializing variables 
        noOfProcess = 6;
        noOfResources = 4;

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

        int need[noOfProcess][noOfResources];
        int available[noOfResources];
        int total[noOfResources];

        readResource(total, noOfResources, choice);
        calculateNeed(allocation, max, need, noOfProcess, noOfResources);
        calculateAvailable(allocation, total, available, noOfProcess, noOfResources);

        // Set each process flag to FALSE, indicating resources has not been allocated 
        // before calling Banker's Algorithm 
        int flag[noOfProcess];
        for (int i = 0; i < noOfProcess; i++){
            flag[i] = FALSE;
        }
        bankerAlgo(max, need, available, flag, 0, noOfProcess, noOfResources);
        // System is in safe state if Banker's Algorithm is able to run till completion
        printf("\n--- SYSTEM IS IN SAFE STATE ---\n");
    }
    // User is able to dymanically insert value of process and resources
    else if (choice == 2){

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

        // initializing variables 
        int allocation[noOfProcess][noOfResources];
        int max[noOfProcess][noOfResources];
        int need[noOfProcess][noOfResources];
        int available[noOfResources];
        int total[noOfResources];
        
        readResource(total, noOfResources, choice);
        readMax(max, noOfProcess, noOfResources, total);
        printf("\n");
        readAllocation(allocation, noOfProcess, noOfResources, max);
        calculateNeed(allocation, max, need, noOfProcess, noOfResources);
        calculateAvailable(allocation, total, available, noOfProcess, noOfResources);
        printf("\n");

        // Set each process flag to FALSE, indicating resources has not been allocated 
        // before calling Banker's Algorithm 
        int flag[noOfProcess];
        for (int i = 0; i < noOfProcess; i++){
            flag[i] = FALSE;
        }

        bankerAlgo(max, need, available, flag, 0, noOfProcess, noOfResources);
        // System is in safe state if Banker's Algorithm is able to run till completion
        printf("\n--- SYSTEM IS IN SAFE STATE ---\n");
        
    } else {
        printf("Entered Invalid option. \n");
        exit(0);
    }
}

// Function for Banker's Algorithm 
void bankerAlgo(int max[][noOfResources], int need[][noOfResources], int available[], int flag[], int processIndex, int noOfProcess, int noOfResources){ 
    int counterFlag = 0;
    // Base Case 
    // Check if all the process has been allocated resources
    for (int i = 0; i < noOfProcess; i ++){
        if (flag[i] == TRUE){
            counterFlag += 1;
        }
    }
    // If all process flag are TRUE; function will terminate
    if (counterFlag == noOfProcess){
        return;
    }
    // Recursive Case
    else {
        // Unsafe Safe: The available resource is not able to satisfy any of the process request
        if (processIndex > noOfProcess){
            printf("--- SYSTEM IS IN UNSAFE STATE ---\n");
            printf("Available instances: ");
            // display the number of available resource
            for (int i = 0; i < noOfResources; i++){
                printf("%d ", available[i]);
            }
            // display the number of resources needed by the processes that has not receive the max resources 
            printf("\n\nNEEDED INSTANCES FOR UNALLOCATED PROCESSES \n");
            for (int i = 0; i < noOfProcess; i++){
                if (flag[i] == FALSE){
                    printf("Process %d: ", i);
                    for (int j = 0; j < noOfResources; j++){
                        printf("%d ", need[i][j]);
                    }
                    printf("\n");
                }
            }
            exit(0);
        } else {
            int availableCounter = 0;
            // counter for (available - need) condition
            for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                if (available[resourceIndex] - need[processIndex][resourceIndex] >= 0){
                    availableCounter += 1;
                }
            }
            // Check if there's enough available resource to satisfy process need
            // Check if the process flag is in FALSE state
            if ((availableCounter == noOfResources) && (flag[processIndex] == FALSE)){
                for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                    available[resourceIndex] -= need[processIndex][resourceIndex];
                }
                flag[processIndex] = TRUE;

                // Display available resource after allocating resource to the process
                printf("Available Instance after Allocation to process P%d: [", processIndex);
                for (int i = 0; i < noOfResources; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                // Process return all held resource back to the system
                for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                    available[resourceIndex] += max[processIndex][resourceIndex];
                }

                // Display available resources after the process return the resource to the system
                printf("Available Instance after Retrieving resource from process P%d: [", processIndex);
                for (int i = 0; i < noOfResources; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                // Continue to call itself recursive until all process flag is set to TRUE
                bankerAlgo(max, need, available, flag, 0, noOfProcess, noOfResources);
            } else {
                // Check not enough available rsource or process state is set to TRUE
                // increment process Index and call itself recursivly
                bankerAlgo(max, need, available, flag, processIndex + 1, noOfProcess, noOfResources);
            }
        }
    }
}

//Functon to read the total instance of resources 
void readResource(int total[], int noOfResources, int choice){
    for (int i = 0; i < noOfResources; i++){
        printf("Enter total number of instances %c: ", resourcetype[i]);
        scanf("%d", &total[i]);
        // Resource A, B, C, D needs to be larger than 14, 11, 14, 18 respectively 
        if (choice == 1){
            int check[4] = {14,11,14,18};
            if (total[i] < check[i]){
                printf("Minimum number of instance for resource %c must be %d or above \n", resourcetype[i], check[i]);
                exit(0);
            }
        }
    }   
    printf("\n");
}

// Function to read the max instances a process needs
void readMax(int max[][noOfResources], int noOfProcess, int noOfResources, int total[]){
    for (int i = 0; i < noOfProcess; i++){
        printf("Enter number of MAX allocation instances for resources in process %d\n", i+1);
        for (int j = 0; j < noOfResources; j++){
            printf("Resource %c: ", resourcetype[j]);
            scanf("%d", &max[i][j]);
            // the max number of instance a process needs cannot be more than the total number of instance
            if (max[i][j] > total[j]){
                printf("Process instance number cannot be more than the number of total instance. \n");
                exit(0);
            }
        }
    }
}

// Function to read the allocation resource for a process
void readAllocation(int allocation[][noOfResources], int noOfProcess, int noOfResources, int max[][noOfResources]){
    for (int i = 0; i < noOfProcess; i++){
        printf("Enter number of allocation instances for resources in process %d\n", i+1);
        for (int j = 0; j < noOfResources; j++){
            printf("Resource %c: ", resourcetype[j]);
            scanf("%d", &allocation[i][j]);
            // the allocation resource cannot be more than the number of resources
            if (allocation[i][j] > max[i][j]){
                printf("Process Allocation value cannot be more than process Max value. \n");
                exit(0);
            }
        }
    }
}

// Function to calculate Need matrix
// Need = Allocation - Need
void calculateNeed(int allocation[][noOfResources], int max[][noOfResources], int need[][noOfResources], int noOfProcess, int noOfResources){
    for (int i = 0; i < noOfProcess; i++){
        for (int j = 0; j < noOfResources; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to calculate available vector
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
    // Total number of allocated instances cannot be more than the total number of instances
    for (int i = 0; i < noOfResources; i++){
        available[i] = total[i] - totalAllocation[i];
        if(available[i] < 0){
            printf("Total Allocation of Instances cannot be more then total instances. \n");
            exit(0);
        }
    }
}
