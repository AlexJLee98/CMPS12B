# include "aes.h"
# include "hash.h"
# include "ll.h"
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

static inline int realLength(int l)
{
	return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

hashTable *newHT(uint32_t length, uint32_t salt [] ) //Make a new hash table 
{
    hashTable *myHash = calloc(1, sizeof(hashTable));
    myHash->h = calloc(length, sizeof(hashTable));
    myHash->l = length;
    memcpy(myHash->s, salt, sizeof(uint32_t) * 4);
    return myHash;
}

void delHT(hashTable *myHash) { //Delete hash table
     for (uint32_t i = 0; i < myHash -> l; i++) 
     {
        free(myHash->h[i]);
    }
}

listNode *findHT(hashTable *myHash, const char *oldspeak) //Find corresponding node for the word
{
    uint32_t position = 0;
    position = hash(myHash, oldspeak) % myHash->l;
    return findLL(&myHash->h[position], oldspeak);
}

void insertHT (hashTable *myHash, const char *oldspeak, const char *newspeak) //Insert something
{
    uint32_t position =  0;
    position = hash(myHash, oldspeak) % myHash->l;
    if (myHash->h[position] == NULL) 
    {
        listNode *myNode = newNode(oldspeak, newspeak);
        myHash->h[position] = myNode;
    } else 
    {
        myHash->h[position] = insertLL(&myHash->h[position], oldspeak, newspeak);
    }  
}

uint32_t hash (hashTable *h, const char *key) //Hash function
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum       = 0x0;
	int keyL           = strlen(key);
	uint8_t *realKey   = (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t));

	memcpy(realKey, key, keyL);

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) h -> s,// Salt
                   (uint8_t *) realKey + i,	// Input
				   (uint8_t *) output);	    // Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}

void printHT (const hashTable *myHash) //Print stuff of hash table
{
    printf("Length : %d \n " , myHash -> l);
    printf("Salt : %d \n", *myHash -> s);
    for (uint32_t i = 0; i < myHash -> l; i++) 
    {
        if (myHash->h[i] != 0) 
        {
            printLL(myHash->h[i]);
       } 
    }
}

