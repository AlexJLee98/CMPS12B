#include <stdio.h>
#include <stdlib.h>
#include "bv.h"


bitV *newVec(uint32_t l) //Creates a new bit vector 
{
    bitV *v = (bitV *) malloc(sizeof(bitV));
    v->v = (uint8_t *) calloc(l / 8 + 1, sizeof(uint8_t));
    v->l = l;
    return v;
}

void delVec(bitV *myBit)  //Deletes a vector 
{
    if (myBit != 0) 
    {
        if (myBit->v != 0)
        {
            free(myBit->v);
        }
        free(myBit);
    }
}

void oneVec(bitV *myBit) //Creates a vector of all 1
{ 
    uint32_t length = myBit->l*8;
    
    for (uint32_t i = 0; i < length; i++) 
    {
        setBit(myBit, i);
    }
}

void setBit(bitV *m, uint32_t s) //Set a specified bit
{
    *(m -> v + (s / 8)) |= (01 << (s & 07));
}

void clrBit(bitV *m, uint32_t s) //Clears a specified bit
{ 
    *(m -> v + (s / 8)) &= ~(01 << (s & 07));
}

uint8_t valBit(bitV *m, uint32_t s)  //Return the value of a specified bit 
{
    return (*(m -> v + (s / 8)) & (01 << (s & 07))) >> (s & 07);
}

uint32_t lenVec(bitV *m) //Return the length of the vector
{ 
    return m -> l;
}
