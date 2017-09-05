# include "minSort.h"
# include "bubbleSort.h"
# include "insertionSort.h"
# include "quickSort.h"
# include "mergeSort.h"
# include <getopt.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

void print(uint32_t sort[], uint32_t numPrint, uint32_t numNumbers) //Print function
{
    uint32_t printCount = 0;
    if (numPrint <= numNumbers) {
        for (uint32_t i = 0; i < numPrint; i++)
        {
            if (printCount != 6) //Print line every 7 num
            {
                printf(" %-10d", sort[i]); //Spacing
                printCount++;
            } else {
                printf(" %-10d \n", sort[i]);
                printCount = 0;
            }
        }
        printf(" \n");
    } else
    {
        numPrint = numNumbers;
        for (uint32_t i = 0; i < numPrint; i++)
        {
            if (printCount != 6)
            {
                printf(" %-10d", sort[i]);
                printCount++;
            } else {
                printf(" %-10d \n", sort[i]);
                printCount = 0;
                
            }
        }
         printf(" \n");
    }
}

int main(int argc, char * const argv[])
{
    int c = 0;
    int caseMin = -1;
    int caseB = -1;
    int caseI = -1;
    int caseQ = -1;
    int caseMerge = -1;
    uint32_t numPrint = 100; //Default numbers to print
    uint32_t numNumbers = 100; //Default
    int ranSeed = 8062022; //Default seed
    
    while ((c = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
    {
     switch (c)
        {
         case 'A' : caseMin = caseB = caseI = caseQ = caseMerge = 0; //Case all
             break;
         case 'm' : caseMin = 0; //Case minSort
             break;
         case 'b' : caseB = 0; //Case bubbleSort
             break;
         case 'i' : caseI = 0; //Case insertionSort
             break;
         case 'q' : caseQ = 0; //Case quickSort
             break;
         case 'M' : caseMerge = 0; //Case mergesort
             break;
         case 'p' : numPrint = atoi(optarg); //Specify numPrint
             break;
         case 'r' : ranSeed = atoi(optarg); //Specify randSeed
             break;
         case 'n' : numNumbers = atoi(optarg); //Specify numNumbers
             break;
        }
    }
   
    if (caseMin == 0) //Min sort
    {
        srand(ranSeed);
        uint32_t *sortM;
        sortM = (uint32_t*)calloc(numNumbers, sizeof(uint32_t)); //Allocate space
        for (uint32_t i = 0; i < numNumbers; i++)
        {
            sortM[i] = (rand() % 16777216);
        }
        minSort(sortM , numNumbers);
        print(sortM, numPrint, numNumbers);
        free(sortM);
    }
    if (caseB == 0) //Bubble sort
    {
        srand(ranSeed);
        uint32_t *sortB;
        sortB = (uint32_t*)calloc(numNumbers, sizeof(uint32_t)); //Allocate space
        for (uint32_t i = 0; i < numNumbers; i++)
        {
            sortB[i] = rand() % 16777216;
        }
        bubbleSort(sortB, numNumbers);
        print(sortB, numPrint, numNumbers);
        free(sortB);
    }
    if (caseI == 0) //Insertion Sort
    {
        srand(ranSeed);
        uint32_t *sortI;
        sortI = (uint32_t*)calloc(numNumbers, sizeof(uint32_t)); //Allocate space
        for (uint32_t i = 0; i < numNumbers; i++)
        {
            sortI[i] = rand() % 16777216;
        }
        insertionSort(sortI, numNumbers);
        print(sortI, numPrint, numNumbers);
        free(sortI);
        }
    if (caseQ == 0) //Quick sort
    {
        srand(ranSeed);
        uint32_t *sortQ;
        sortQ = (uint32_t*)calloc(numNumbers, sizeof(uint32_t)); //Allocate space
        for (uint32_t i = 0; i < numNumbers; i++)
        {
            sortQ[i] = rand() % 16777216;
        }
        quickSort(sortQ, 0 , numNumbers - 1, numNumbers);
        print(sortQ, numPrint, numNumbers);
        free(sortQ);
    }
    if (caseMerge == 0) //Merge sort
    {
        srand(ranSeed);
        uint32_t *sortMerge;
        uint32_t *temp;
        sortMerge = (uint32_t*)calloc(numNumbers, sizeof(uint32_t)); //Allocate space
        temp = (uint32_t*)calloc(numNumbers, sizeof(uint32_t));
        for (uint32_t i = 0; i < numNumbers; i++)
        {
            sortMerge[i] = rand() % 16777216;
        }
        mergeSort(sortMerge, temp, numNumbers, 0, numNumbers - 1);
        print(sortMerge, numPrint, numNumbers);
        free(sortMerge);
        free(temp);
    }
    return 0;
}
