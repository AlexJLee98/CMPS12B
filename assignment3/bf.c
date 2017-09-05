# include "aes.h"
# include "bf.h"
# include "bv.h"
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

extern int bitSet;

uint32_t hashBF (uint8_t *oldspeak, uint32_t salt []) //Hash function for bloom filter
{
	uint32_t output[4];
	uint32_t sum = 0;
	size_t   keyLength = strlen((const char *) oldspeak);

	for (uint64_t i = 0; i < keyLength; i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) salt, oldspeak + i, (uint8_t *) output);
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	return sum;
}

bloomF *newBF (uint32_t length, uint32_t salt []) //Make a new bloom filter
{
    bloomF *myBF = calloc(1, sizeof(bloomF));
    myBF->l = length;
    myBF->bitVec = malloc(sizeof(myBF->bitVec));
    myBF->bitVec->l = length;
    myBF->bitVec->v = calloc(length/8, sizeof(uint8_t));
    memcpy(myBF->s, salt, sizeof(uint32_t) * 4);
    return myBF;
}

void delBF (bloomF *myBF) //Delete bloom filter
{
    delVec(myBF->bitVec);
    free(myBF);
}

uint32_t valBF (bloomF *myBF, uint32_t position) //Return 0 or 1 if a bit is set or not
{
    return valBit(myBF->bitVec, position);
}

uint32_t lenBF (bloomF *myBF) //Return length of bloom filter
{
    return myBF->l;
}

uint32_t countBF (bloomF *myBF) //Counts number of bits set
{
    uint32_t bitValue = 0;
    uint32_t counter = 0;
    uint32_t length = myBF->l;
    uint32_t position = 0;
    while (position < length) {
         position++;
         bitValue = valBit(myBF->bitVec, position);
         if (bitValue == 1) {
            counter++;
        }
    }
      return counter;
}

void setBF (bloomF *myBF, char *oldspeak) //Sets a word in bloom filter
{
    uint32_t position = hashBF((uint8_t *) oldspeak, myBF->s);
    position = position % myBF->l;
    setBit(myBF->bitVec, position);
}

void clrBF (bloomF *myBF, char *oldspeak) //Clears entry
{
    uint32_t position = hashBF((uint8_t *) oldspeak, myBF->s);
    position = position % myBF->l;
    clrBit(myBF->bitVec, position);
}

uint32_t memBF (bloomF *myBF, char *oldspeak) //Check if that word is in the bloom filter
{
    uint32_t position = hashBF((uint8_t *) oldspeak, myBF->s);
    position = position % myBF->l;
    uint8_t val = (valBit(myBF->bitVec, position));
        if (val > 0)  {
            return 1;
        } else {
            return 0;   
        }
}

void printBF (bloomF *myBF) //Print bloom filter
{
    uint32_t length = myBF->l;
    printf("Length :%d \n", length);
    uint32_t position = 0;
    uint8_t val = (valBit(myBF->bitVec, position));
    while (length < position) {
        val = (valBit(myBF->bitVec, position));
        if (val > 0) {
            printf("Val: %d \n", val);
        }
    }
}

