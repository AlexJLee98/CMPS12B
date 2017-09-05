# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "swap.h"

static uint64_t moves = 0;  //Keep track of moves and compares
static uint64_t compares = 0;

void bubbleSort(uint32_t sort[], uint32_t numNumbers)
{
    uint32_t length = numNumbers;
    uint32_t swapCount = 0;
    if (length > 1) //Don't do anything if array is only a number
    {
        for (uint32_t i = 1; i <= length - 1; i++)
        {
            if (sort[i - 1] > sort[i])
            {
                SWAP(sort[i - 1], sort[i]); //Swap if previous element is greater
                swapCount++;
                compares++;
                moves++;
            }
        }
        if (swapCount > 0) //If no swaps in current iteration we're done
        {
            compares++;
            bubbleSort(sort, numNumbers);
        } else
        {
            printf("Bubble Sort \n"); //Print stuff if length is not greater than 1
            printf("%d elements \n", numNumbers);
            printf("%lu moves \n", moves * 3);
            printf("%lu compares \n", compares);
        }
    } else
    {
        printf("Bubble Sort \n"); //Print stuff if length is greater than 1
        printf("%d elements \n", numNumbers);
        printf("%lu moves \n", moves * 3);
        printf("%lu compares \n", compares);
    }
}

