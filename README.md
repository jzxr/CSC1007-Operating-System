# 1. CSC1007 Operating System

## 1.1. Banker's Algorithm

---

Given six processes to be allocated and four resources types (A, B, C, D), the values of the allocation matrix of the processes for Allocation[6][4] and the values of the Max matrix of the processes is Max[6][4].

The user can input the total instances of each type, has the options to enter the allocation matrix and max matrix of the program. It shows the process of the whole safe state and unsafe state based on the calculation using Banker's Algorithm.

We have included some libraries, define some variable as well as function prototype.

```C
#include <stdio.h>
#include <stdlib.h>
#define RESOURCE 4
#define PROCESS 6
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
```

---

### 1.1.1. Main Function for Banker's Algorithm

---
Description
User can enter choice 1 for hardcoded and choice 2 for user input based on assignment question 1.

```C
int main(){
    // Defining Variables 
    int choice;
    int need[PROCESS][RESOURCE];
    
    printf("Select Choice: \n1) Hardcoded  \n2) User input\n");
    printf("User Choice: ");
    scanf("%d", &choice);

    // Follows assignment requirement
    if (choice == 1){
        // Allocation and Max resources stated in the specification
        // initializing variables 
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

        // Set each process flag to FALSE, indicating resources has not been allocated 
        // before calling Banker's Algorithm 
        int flag[PROCESS] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
        bankerAlgo(max, need, available, flag, 0, PROCESS, RESOURCE);
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
```

---

### 1.1.2. Function for Banker's Algorithm

---
This is the calculation part for our Banker's Algorithm

```C
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
            printf("\n\nNEEDED RESOURCE FOR UNALLOCATED PROCESSES \n");
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
                printf("Available Resource after Allocation to process P%d: [", processIndex);
                for (int i = 0; i < noOfResources; i++){
                     printf("%d, ", available[i]);
                }
                printf("]\n");

                // Process return all held resource back to the system
                for (int resourceIndex = 0; resourceIndex < noOfResources; resourceIndex++){
                    available[resourceIndex] += max[processIndex][resourceIndex];
                }

                // Display available resources after the process return the resource to the system
                printf("Available Resource after Retrieving resource from process P%d: [", processIndex);
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
```

---

### 1.1.3. Read the total instances of resources

---
Description
This function ask the users to enter the total number of instances and check if the number of instances hits the minimum requirement for the resources for question 1 hardcoded part.

```C
//Functon to read the total instance of resources 
void readResource(int total[], int noOfResources, int choice){
    for (int i = 0; i < noOfResources; i++){
        printf("Enter total number of instances %c: ", resourcetype[i]);
        scanf("%d", &total[i]);
        // Resource A, B, C, D needs to be larger than 14, 11, 14, 18 respectively 
        if (choice == 1){
            int check[RESOURCE] = {14,11,14,18};
            if (total[i] < check[i]){
                printf("Minimum number of instance for resource %c must be %d or above \n", resourcetype[i], check[i]);
                exit(0);
            }
        }
    }   
    printf("\n");
}
```

---

### 1.1.4. Read the max instances of the process needs

---
This function ask the users to enter the number of MAX allocation instances for the resources in the process and check if the number of instances allocate to the resources is more than the one they defined earlier on.

```C
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
```

---

### 1.1.5. Read the allocation resources for a process

---
This function ask the users to enter the number of allocation instances for resources in the process and check if the allocateed resources is more than the number of resources.

```C
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
```

---

### 1.1.6. Calculate need matrix

---
This function calculates the need matrix

```C
// Function to read the allocation resource for a process
// Function to calculate Need matrix
// Need = Allocation - Need
void calculateNeed(int allocation[][noOfResources], int max[][noOfResources], int need[][noOfResources], int noOfProcess, int noOfResources){
    for (int i = 0; i < noOfProcess; i++){
        for (int j = 0; j < noOfResources; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}
```

---

### 1.1.7. Calculate the available vector

---
This function calculate the available vector and check if the total number of allocated instances is more than the total number of instances.

```C
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
```

---

## 1.2. Memory Management in Operating System

---
Given with 12 memory partitions available: 160 KB, 350 KB, 650 KB, 80 KB, 410 KB, 50 KB, 720 KB, 905 KB, 570 KB, 130 KB, 260 KB, and 830 KB (in order). We would use the different algorithms to allocate 10 input processes with different sizes (in order).

---

### 1.2.1. Main Function for Memory Management

---

Function to allow user to enter the options and execute the functions.

```C
//Libaries
#include <stdio.h>
#include "Q2.h"

//Main function
int main()
{
    int choice;
    bool exit_condition = true;
    printf("\nDynamic memory Allocation demonstration program\n");
    getMaxSize();
    getMinSize();
    getInput();
    while (exit_condition)
    {
        printf("\nPlease Enter one of the options: 1.First-fit, 2.Best-fit, 3.Worst-fit 4.Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            firstFit();
            break;
        case 2:
            bestFit();
            break;
        case 3:
            worstFit();
            break;
        case 4:
            exit_condition = false;
            break;
        default:
            printf("Invalid options entered.\n");
        }
    }
    return 0;
}

```

### 1.2.2. Biggest Partition Size

---

Function to get the biggest partition size

```C
//Get Biggest Partition size.
void getMaxSize()
{
    int partitionCount = sizeof(memoryPartitions) / sizeof(memoryPartitions[0]);
    Max = memoryPartitions[0];
    int count;
    for (count = 1; count < partitionCount; count++)
    {
        if (memoryPartitions[count] > Max)
        {
            Max = memoryPartitions[count];
        }
    }
}
```

---

### 1.2.3. Smallest Partition Size

---

Gettign the smallest partition size for the worst fit algorithm.

Function to get the smallest partition size

```C
//Get Smallest Partition size.
void getMinSize()
{
    int partitionCount = sizeof(memoryPartitions) / sizeof(memoryPartitions[0]);
    Min = memoryPartitions[0];
    int count;
    for (count = 1; count < partitionCount; count++)
    {
        if (memoryPartitions[count] < Min)
        {
            Min = memoryPartitions[count];
        }
    }
}
```

---

### 1.2.4. User Input

---

User can input 10 process sizes to allow the system to compute the different algorithms.

Function to allow user to input

```C
//Input Function
void getInput()
{
    int count;
    printf("\nMaximum Partition Size avaliable: %d KB\n", Max);
    for (count = 0; count < 10; count++)
    {
        printf("Enter size of processes: %d in KB\n", count + 1);
        scanf("%d", &userInput[count]);

        if (userInput[count] > Max)
        {
            printf("The size of procees entered exceeded the Maximum avaliable partition of: %d KB, Please re-enter\n", Max);
            count--;
        }
    }

    printf("\nProcess No. \tProcess Size\n");
    for (count = 0; count < 10; count++)
    {
        printf("\t%d \t%d KB\n", count + 1, userInput[count]);
    }
}
```

---

### 1.2.5. Reset Partition Size

---

User can re-select their options for algorithm, the function will reset the partition size.

Function to reset the partition size to the original size

```C
//Reset Memory partition function.
void resetPartition()
{
    memoryPartitions[0] = 160;
    memoryPartitions[1] = 350;
    memoryPartitions[2] = 650;
    memoryPartitions[3] = 80;
    memoryPartitions[4] = 410;
    memoryPartitions[5] = 50;
    memoryPartitions[6] = 720;
    memoryPartitions[7] = 905;
    memoryPartitions[8] = 570;
    memoryPartitions[9] = 130;
    memoryPartitions[10] = 260;
    memoryPartitions[11] = 830;
}
//End
```

---

### 1.2.6. First Fit Algorithm

---

First Fit Algorithm is to allocate the process size to the first suitable block size.

Function to allocate the memory partitions

```C
void firstFit()
{
    int processID, processSize, partitionID, partitionSize, count = 0;
    int assign = -1;
        
    //Match all process to suitable memory partition
    for (processID = 0; processID < 10; processID++){
        processSize = userInput[processID];
        for (partitionID = 0; partitionID < 12; partitionID++){
            partitionSize = memoryPartitions[partitionID];
                
            //assign memory partiton to process.
            if (partitionSize >= processSize){
                    assignPartitions[processID] = partitionSize;
                    partitionSize -= processSize;
                    assign = partitionID;
                    break;
                }
                //do not need to display if partition is not allocated
                else{
                    assignPartitions[processID] = 0;
                } 
            }

            //Check if memorypartition is assigned to a process. if so empty it from array.
            if (assign >= 0){
                memoryPartitions[assign] = 0;
            }
            else{
                unassignProcess[processID] = 0;
            }
        }

        //Print allocated process
        printf("\nAllocated Process");
        printf("\nProcess No.\tProcess Size.\tAllocated Memory Size.\n");
        for (processID = 0; processID < 10; processID++)
        {
            if (assignPartitions[processID] != 0)
            {
                printf("%d \t\t%d KB \t\t%d KB\n", processID + 1, userInput[processID], assignPartitions[processID]);
            }
        }

        //Print unallocated process
        printf("\nUnallocated Process");
        printf("\nProcess No.\tProcess Size.\n");
        for (processID = 0; processID < 10; processID++)
        {
            if (assignPartitions[processID] == 0)
            {
                printf("%d \t\t%d KB\n", processID + 1, userInput[processID]);
            }
        }

        //Print available memory parition.
        printf("\nAvaliable Memory Partition");
        printf("\nParition Size.\n");
        for (count = 0; count < 12; count++)
        {
            if (memoryPartitions[count] != 0)
            {
                printf("%d KB\n", memoryPartitions[count]);
            }
        }

    //Reset memoryPartition array to default state at start.
    resetPartition();
}
```

---

### 1.2.7. Best Fit Algorithm

---
Best Fit Algorithm is to allocate the process size to the smallest

Function to allocate the memory partitions

```C
//Bestfit function
void bestFit()
{
    int processID, processSize, partitionID, partitionSize, smallID, differences, count = 0;

    //Match all process to memory partition
    for (processID = 0; processID < 10; processID++)
    {
        int assign = -1;
        getMaxSize();
        int smallest = Max;
        processSize = userInput[processID];

        //Find the best-fit memory partition to process size
        for (partitionID = 0; partitionID < 12; partitionID++)
        {
            partitionSize = memoryPartitions[partitionID];
            //Check if memory partition been allocated
            if (partitionSize != 0)
            {
                differences = partitionSize - processSize;

                //Check if difference is negative.
                if (differences >= 0)
                {
                    //assign memory partiton to process.
                    if (differences < smallest)
                    {
                        smallest = differences;
                        assignPartitions[processID] = partitionSize;
                        assign = partitionID;
                    }
                }
            }
        }

        //Check if memorypartition is assigned to a process. if so empty it from array.
        if (assign >= 0)
        {
            memoryPartitions[assign] = 0;
        }
        else
        {
            unassignProcess[processID] = 0;
        }
    }

    //print allocated process
    printf("\nAllocated Process");
    printf("\nProcess No.\tProcess Size.\tAllocated Memory Size.\n");
    for (processID = 0; processID < 10; processID++)
    {
        if (unassignProcess[processID] != 0)
        {
            printf("%d \t\t%d KB \t\t%d KB\n", processID + 1, userInput[processID], assignPartitions[processID]);
        }
    }

    //Print Unallocated Process
    printf("\nUnallocated Process");
    printf("\nProcess No.\tProcess Size.\n");
    for (processID = 0; processID < 10; processID++)
    {
        if (unassignProcess[processID] == 0)
        {
            printf("%d \t\t%d KB\n", processID + 1, userInput[processID]);
        }
    }

    //Print Avliable memory parition.
    printf("\nAvaliable Memory Partition");
    printf("\nParition Size.\n");
    for (count = 0; count < 12; count++)
    {
        if (memoryPartitions[count] != 0)
        {
            printf("%d KB\n", memoryPartitions[count]);
        }
    }

    //Reset memoryPartition array to default state at start.
    resetPartition();
}
```

---

### 1.2.8. Worst Fit Algorithm

---

Worst Fit Algorithm is to allocate the process size to the largest block size first.

Function to allocate the memory partitions

```C
//Worstfit function
void worstFit(){
    int processID, processSize, partitionID, partitionSize, smallID, differences, count = 0;

    //Match all process to memory partition
    for (processID = 0; processID < 10; processID++)
    {
        int assign = -1;
        getMinSize();
        int largest = Min;
        processSize = userInput[processID];

        //Find the best-fit memory partition to process size
        for (partitionID = 0; partitionID < 12; partitionID++)
        {
            partitionSize = memoryPartitions[partitionID];
            //Check if memory partition been allocated
            if (partitionSize != 0)
            {
                differences = partitionSize - processSize;

                //Check if difference is negative.
                if (differences >= 0)
                {
                    //assign memory partiton to process.
                    if (differences > largest)
                    {
                        largest = differences;
                        assignPartitions[processID] = partitionSize;
                        assign = partitionID;
                    }
                }
            }
        }

        //Check if memorypartition is assigned to a process. if so empty it from array.
        if (assign >= 0)
        {
            memoryPartitions[assign] = 0;
        }
        else
        {
            unassignProcess[processID] = 0;
        }
    }

    //print allocated process
    printf("\nAllocated Process");
    printf("\nProcess No.\tProcess Size.\tAllocated Memory Size.\n");
    for (processID = 0; processID < 10; processID++)
    {
        if (unassignProcess[processID] != 0)
        {
            printf("%d \t\t%d KB \t\t%d KB\n", processID + 1, userInput[processID], assignPartitions[processID]);
        }
    }

    //Print Unallocated Process
    printf("\nUnallocated Process");
    printf("\nProcess No.\tProcess Size.\n");
    for (processID = 0; processID < 10; processID++)
    {
        if (unassignProcess[processID] == 0)
        {
            printf("%d \t\t%d KB\n", processID + 1, userInput[processID]);
        }
    }

    //Print Avliable memory parition.
    printf("\nAvaliable Memory Partition");
    printf("\nParition Size.\n");
    for (count = 0; count < 12; count++)
    {
        if (memoryPartitions[count] != 0)
        {
            printf("%d KB\n", memoryPartitions[count]);
        }
    }

    //Reset memoryPartition array to default state at start.
    resetPartition();
}
```
