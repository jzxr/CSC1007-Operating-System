//1007-Assigment-Q2

//Std libary
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
