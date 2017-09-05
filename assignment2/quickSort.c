# include "swap.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

uint32_t left = 0; //Global variable so it doesn't reset to 0 every time I call Quick Sort
uint32_t right = 0;
static uint64_t moves = 0; //Keep track of moves and compares
static uint64_t compares = 0;

void partition (uint32_t sort[], uint32_t start, uint32_t end, uint32_t numNumbers)
{
    left = start;
    right = end;
    uint32_t pivot = sort[right];
    moves++;
    
    while (left <= right)
    {
        while (1)
        {
            if (sort[left] >= pivot) //Find value greater or equal to pivot on left on pivot
            {
                compares++;
                break;
            } else
            {
                left++;
            }
        }
        
        while(1)
        {
            if (sort[right] <= pivot) //Find value lesser or equal to pivot on right of pivot
            {
                compares++;
                break;
            } else
            {
                compares++;
                right--;
            }
        }
        if (left <= right) //Swap values if left less than or equal to right
        {
            SWAP(sort[left], sort[right]);
            moves++;
            left++;
            right--;
        }
    }
    if (end == 1) //Print stuff
    {
        printf("Quick Sort \n");
        printf("%d elements \n", numNumbers);
        printf("%lu moves \n", moves * 3);
        printf("%lu compares \n", compares);
    }
}

void quickSort(uint32_t sort[], uint32_t start, uint32_t end, uint32_t numNumbers)
{
    if (end >= 1)
    {
        partition(sort, start , end, numNumbers);
        if (left < end) //Recursion
        {
            quickSort(sort, left, end, numNumbers);
            moves++;
        }
        if (start < right) //Recursion
        {
            quickSort(sort, start, right, numNumbers);
            moves++;
        }
    }
}




