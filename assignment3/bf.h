# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include "bv.h"

typedef struct bloomF bloomF;


struct bloomF
{
       
    bitV *bitVec; //Vector
    uint32_t l; //Length
    uint32_t s[4]; //Salt
};

uint32_t hashBF (uint8_t *oldspeak, uint32_t salt []);

bloomF *newBF (uint32_t length, uint32_t salt []);

void delBF (bloomF *myBF);

uint32_t valBF (bloomF *myBF, uint32_t position);

uint32_t lenBF (bloomF *myBF);

uint32_t countBF (bloomF *myBF);

void setBF (bloomF *myBF, char *oldspeak);

void clrBF (bloomF *myBF, char *oldspeak);

uint32_t memBF (bloomF *myBF, char *oldspeak);

void printBF (bloomF *myBF);
# endif
