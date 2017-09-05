# include "swap.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

//Psuedocode from "Data Abstraction & Problem Solving with Java Walls and Mirrors" (our textbook)

static uint64_t compares = 0;
static uint64_t moves = 0;
static uint32_t print = 0;

void merge (uint32_t sort[], uint32_t temp [], uint32_t start, uint32_t end)
{
    uint32_t tempI = 0; //Temp index
    uint32_t startOne = start; //First subarray element
    uint32_t endOne = (start + end) / 2; //Last subarray element
    uint32_t startTwo = endOne + 1; //First subarray element of 2nd subarray
    uint32_t endTwo = end; //Last subarray element of 2nd subarray
    
    while (startOne <= endOne && startTwo <= endTwo)
    {
        if (sort[startOne] < sort[startTwo])
        {
            temp[tempI++] = sort[startOne++]; //Sort first subarray into temp array
            compares++;
            moves++;
        } else
        {
            temp[tempI++] = sort[startTwo++]; //Sort second subarray into temp array
            compares++;
            moves++;
        }
    }
    for (uint32_t i = startOne; i <= endOne; i++, tempI++) //First part of subarray
    {
        temp[tempI] = sort[i];
        moves++;
    }
    for (uint32_t j = startTwo; j <= endTwo; j++, tempI++) //Second part of subarray
    {
        temp[tempI] = sort[j];
        moves++;
    }
    
    for (startOne = start, startTwo = 0; startOne <= endTwo; startOne++) //Transfer to original array
    {
        sort[startOne] = temp[startTwo++];
    }
}

void mergeSort (uint32_t sort[], uint32_t temp[], uint32_t numNumbers, uint32_t low, uint32_t high)
{
    if (low == numNumbers - 2 && print == 0) {
        printf("Merge Sort \n");
        printf("%d elements \n", numNumbers);
        printf("%lu moves \n", moves * 3);
        printf("%lu compares \n", compares);
        print = 1;
    }
    if (numNumbers > 1) //Only need to sort if more than one number
    {
        if (low < high)
        {
            int m = (low + high) / 2;
            mergeSort(sort, temp, numNumbers, low, m); //Merge Sort left half
            mergeSort(sort, temp, numNumbers, m + 1 , high); //Merge Sort right half
            merge(sort, temp, low, high); //Merge
        }
    }
}






