# 1. CSC1007 Operating System

<!-- TOC -->autoauto- [1. CSC1007 Operating System](#1-csc1007-operating-system)auto    - [1.1. Banker's Algorithm](#11-bankers-algorithm)auto        - [1.1.1. Header for your function](#111-header-for-your-function)auto    - [1.2. Memory Management in Operating System](#12-memory-management-in-operating-system)auto        - [1.2.1. Biggest Partition Size](#121-biggest-partition-size)auto        - [1.2.2. Smallest Partition Size](#122-smallest-partition-size)auto        - [1.2.3. User Input](#123-user-input)auto        - [1.2.4. Reset Partition Size](#124-reset-partition-size)auto        - [1.2.5. First Fit Algorithm](#125-first-fit-algorithm)auto        - [1.2.6. Best Fit Algorithm](#126-best-fit-algorithm)auto        - [1.2.7. Worst Fit Algorithm](#127-worst-fit-algorithm)autoauto<!-- /TOC -->

## 1.1. Banker's Algorithm

---

Description for banker's algorithm

---

### 1.1.1. Header for your function

---
Description of your function

The function below is used to open the file. It will display an error message with an exit status set to 1 if file is not found.

```C
    //Read in Data from text file
   FILE *input_fp;
   if ((input_fp = fopen("fertility_Diagnosis_Data_Group1_4.txt", "r")) == NULL){
       printf("\nError in opening the file.");
       exit(1);
   }
```

---

## 1.2. Memory Management in Operating System

---
Given with 12 memory partitions available: 160 KB, 350 KB, 650 KB, 80 KB, 410 KB, 50 KB, 720 KB, 905 KB, 570 KB, 130 KB, 260 KB, and 830 KB (in order). We would use the different algorithms to allocate 10 input processes with different sizes (in order).

---

### 1.2.1. Biggest Partition Size

---

Description

Function to get the biggest partition size

```C
```

---

### 1.2.2. Smallest Partition Size

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

### 1.2.3. User Input

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

### 1.2.4. Reset Partition Size

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

### 1.2.5. First Fit Algorithm

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

### 1.2.6. Best Fit Algorithm

---
Best Fit Algorithm is to allocate the process size to the smallest

Function to allocate the memory partitions

```C
```

---

### 1.2.7. Worst Fit Algorithm

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
