//1007-Assigment-Q2

//Std libary
#include <stdio.h>

//Function Declaration
void getMaxSize();
void getInput();
void resetPartition();
void firstFit();
void bestFit();

//Array for the user input
int userInput[10];

//Array for 12 memory Partitions
int memoryPartitions[12] = {160, 350, 650, 80, 410, 50, 720, 905, 570, 130, 260, 830};

//Array for storing given partitions. //Use to store process number and size of partition assign to it.
int assignPartitions[10];

//Array for unassign process //Use to store process number and size of unassign process.
int unassignProcess[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//Max Value
int Max = 0;

//Main function
int main()
{
    int choice;
    bool exit_condition = true;
    printf("\nDynamic memory Allocation demonstration program\n");
    getMaxSize();
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
            //worst-fit
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
//End

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
//End

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

//Firstfit Function
//need display unallocated blocks and process.
void firstFit()
{
    int processID, processSize, partitionID, partitionSize, smallID, differences, count = 0;
    int assign = -1;
    processSize = userInput[processID];
    for (processID = 0; processID < 10; processID++)
    {
        for (partitionID = 0; partitionID < 12; partitionID++)
        {
            partitionSize = memoryPartitions[partitionID];
            if (partitionSize != 0)
            {
                differences = partitionSize - processSize;

                //Check if difference is negative.
                if (differences >= 0)
                {
                    //assign memory partiton to process.

                    assignPartitions[processID] = partitionSize;
                    assign = partitionID;
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

//Bestfit function
void bestFit()
{
    int processID, processSize, partitionID, partitionSize, smallID, differences, count = 0;

    //Match All process to memory partition
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

//Worstfit function
