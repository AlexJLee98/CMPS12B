# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "swap.h"

static uint64_t moves = 0;
static uint64_t compares = 0;

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last)
{
    uint32_t smallest = first;
    for (uint32_t i = first; i < last; i++)
    {
        smallest = a[i] < a[smallest] ? i : smallest;
        compares++;
    }
    return smallest;
}

void minSort(uint32_t a[], uint32_t length)
{
    for (uint32_t i = 0; i < length - 1; i++) 
    {
        uint32_t smallest = minIndex(a, i, length);
        if (smallest != i)
        {
            SWAP(a[smallest], a[i]);
            moves++;
        }
    }
    printf("Min Sort \n");
    printf("%d elements \n", length);
    printf("%lu moves \n", moves * 3);
    printf("%lu compares \n", compares);
    return;
}
