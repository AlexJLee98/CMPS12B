# include "swap.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

static uint64_t moves = 0; //Keep track of moves and compares
static uint64_t compares = 0;

void insertionSort(uint32_t sort[], uint32_t numNumbers)
{
    uint32_t temp = 0;
    uint32_t length = numNumbers;
    for (uint32_t i = 1; i < length; i++)
    {
        if (sort[i - 1] > sort[i]) //If previous element greater than current
        {
            temp = sort[i]; //Move to temp as it may move more than one spot
            moves++;
            compares++;
            for (uint32_t j = i; j > 0; j--) //Check how many spots it can move back
            {
                if (temp < sort[j - 1] && j == 1) //Check if it is less than previous element and j is within bound
                {
                    sort[j] = sort[j - 1]; //Continue as they're equal
                    sort[j - 1] = temp;
                    moves++;
                    compares++;
                } else if (temp < sort[j - 1]) //Move back
                {
                    sort[j] = sort[j - 1];
                    moves++;
                    compares++;
                    
                } else //Stop as it can't move back any further
                {
                    sort[j] = temp;
                    moves++;
                    compares++;
                    break;
                }        
            }
        } else //Can't move back further than one
            moves++;
        {
            continue;
        }
    }
    printf("Insertion Sort \n"); //Print stuff
    printf("%d elements \n", numNumbers);
    printf("%lu moves \n", moves);
    printf("%lu compares \n", compares);
}
