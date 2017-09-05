# include "aes.h"
# include "bf.h"
# include "hash.h"
# include "flextutorial.h"
# include "ll.h"
# include <ctype.h>
# include <fcntl.h>
# include <getopt.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>

# define BUFFER 255
uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; //Salt for BF1
uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; //Salt for BF2
uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; //Salt for HT
extern FILE* yyin;
extern char* yytext;
int bloomSize = 0;
int density = 0;
int newNum = 0;
int oldNum = 0;
int seeks = 0;
int numLL = 0;
uint32_t bitSet = 0;
bool moveToFront = false; //Default don't move to front
int numWords = 0;

void hashBloomF(bloomF *bloomFilter, char *badSpeak) //Badspeak and oldspeak in bloom filter
{ 
    FILE *fp0;
    fp0 = fopen("badspeak.txt", "r");
    while(fscanf(fp0, "%s", badSpeak) != EOF ) { 
        oldNum++;
        for (int i = 0; i < BUFFER; i++) {
            badSpeak[i] = tolower(badSpeak[i]);
        }
        setBF(bloomFilter , badSpeak);
        memset(badSpeak, 0, BUFFER); 
    }
    fclose(fp0);
}

void hashHT(hashTable *hashT, bloomF *bloomFilter, bloomF *bloomFilter2, char badSpeak[], char oldSpeak[], char newSpeak[]) //Oldspeak and newspeak in hash table
{ 
    FILE *fp1;
    fp1 = fopen("newspeak.txt", "r");
    while (fscanf(fp1,"%s %s", oldSpeak , newSpeak) == 2) {
        for (int i = 0; i < BUFFER; i++) {
            oldSpeak[i] = tolower(oldSpeak[i]);
        }
        for (int j = 0; j < BUFFER; j++) {
            newSpeak[j] = tolower(newSpeak[j]);
        }
        setBF(bloomFilter, oldSpeak);
        setBF(bloomFilter2, oldSpeak);
        if (findHT(hashT, oldSpeak) == NULL) { //Check for duplicates
            insertHT(hashT, oldSpeak, newSpeak);
        } else {
            int position = hash(hashT, oldSpeak) % hashT->l;
            listNode *oldNode = findLL(&hashT->h[position], oldSpeak);
            if (oldNode == NULL) {
                insertHT(hashT, oldSpeak, newSpeak);
            } else {
                oldNode->newspeak = strcpy(oldNode->newspeak, newSpeak);
            }
        }
        memset(badSpeak, 0, BUFFER); 
        memset(oldSpeak, 0, BUFFER); 
        memset(newSpeak, 0, BUFFER); 
        newNum++;
    }
    fclose(fp1);
}

void printStats(bloomF *BF1, bloomF *BF2) //Prints statistics 
{
    float lenBF1 = BF1->l; //BF length
    float lenBF2 = BF2->l;
    bitSet = countBF(BF1); //Num bits set
    float densityOne = bitSet/lenBF1; 
    float densityTwo =  bitSet/lenBF2; 
    float average = (float) seeks/(float) numLL; //Seeks divided by number of times you call 
    printf("\n");
    printf("Seeks %d, ", seeks);
    printf("Average %f, ", average);
    printf("Dictionary %d, ", oldNum/2);
    printf("Translations %d, ", newNum);
    printf("Text %d, ", numWords);
    printf("Densities %f %f \n", densityOne, densityTwo);
}

void printJoy(listNode *joyCamp) //Prints words that would get you sent to joycamp
{ 
    if (joyCamp == NULL)  //If no words don't print anything
    {
        return;
    }
    printf("Dear Comrade,\n");
    printf("\n");
    printf("You have chosen to use degenerate words that may cause hurt\n");
    printf("feelings or cause your comrades to think unpleasant thoughts.\n");
    printf("This is doubleplus bad. To correct your wrongthink and\n");
    printf("save community consensus we will be sending you to joycamp\n");
    printf("administered by Miniluv.\n");
    printf("\n");
    printf("Your errors:\n");
    printf("\n");
    while (joyCamp != NULL) {
        printf("%s\n", joyCamp->oldspeak); 
        joyCamp = joyCamp->next;
    }
    printf("\n");
}

void printOld(listNode *oldSpeak) //Prints oldspeak and translation
{ 
    if (oldSpeak == NULL) //If no words don't print anything
    { 
        return;
    }
    printf("Dear Comrade, \n");
    printf("\n");
    printf("Submitting your text helps to preserve feelings and prevent \n");
    printf("badthink. Some of the words that you used are not goodspeak. \n");
    printf("The list shows how to turn the oldspeak words into newspeak. \n");
    printf("\n");
    while (oldSpeak != NULL) {
        printf("%s -> %s\n", oldSpeak->oldspeak, oldSpeak->newspeak);
        oldSpeak = oldSpeak->next;
    }
}
               
void readInput(int hashSize, int bloomSize, int printTrue) //Reads from input with lex
{
    char badTalk[BUFFER]; 
    char oldTalk[BUFFER];
    char newTalk[BUFFER];
    char *tempText; 
    tempText = malloc(sizeof(char) * BUFFER);
    uint32_t filter0 = 0;
    uint32_t filter1 = 0;
    listNode *replacement = NULL; 
    listNode *joyCamp = NULL;
    hashTable *hashT = newHT(hashSize, initH);
    bloomF *bloomF0 = newBF(bloomSize, initA);
    bloomF *bloomF1 = newBF(bloomSize, initB); 
    hashBloomF(bloomF0,badTalk); //Hash words into bloom filter
    hashBloomF(bloomF1,badTalk); //Hash words into second bloom filter
    listNode *hashNode = NULL;
    hashHT(hashT, bloomF0, bloomF1, badTalk, oldTalk, newTalk); //Hash words into hash table
    int yylex(void);
    int tokenID = 0;
	while (tokenID != TOKEN_EOF) //While not EOF
    {
        tokenID = yylex();
        memset(tempText,0,BUFFER);
        strcpy(tempText, yytext);
        for (uint64_t i = 0; i < strlen(tempText); i++) //Read text and convert to lowercase
        {
            tempText[i] = tolower(tempText[i]);
        }
		switch (tokenID) 
        {
			case TOKEN_WORD:  
                numWords++;
                filter0 = memBF(bloomF0, tempText); //Checks to see if in first BF
                if (filter0 == 0) 
                {
                   continue;
                }
                filter1 = memBF(bloomF1, tempText);
                if (filter1 == 1) //If in both bloom filter check if it has a replacement
                {
                    hashNode = findHT(hashT, tempText);
                    if (hashNode != NULL) 
                    {
                        if (replacement == NULL) //Give the person a warning
                        {
                            replacement = newNode(hashNode->oldspeak, hashNode->newspeak);
                        } else 
                        {
                            if (findLL(&replacement, tempText) == NULL) {
                                insertLL(&replacement, hashNode->oldspeak, hashNode->newspeak);
                            }
                        }
                    } else 
                    {
                        if (joyCamp == NULL) //Send to joy camp
                        {          
                            joyCamp = newNode(tempText, NULL);                            
                        } else 
                        {
                            if (findLL(&joyCamp, tempText) == NULL) {
                                insertLL(&joyCamp, tempText, NULL);
                            }
                        }
                    }
                }
                break;
            default:
				break;   
        }
    }
    if (printTrue == 0) 
    {
        printJoy(joyCamp); //Print joy
    }
    if (printTrue == 0) 
    {
        printOld(replacement); //Print old
    }
    if (printTrue == -1) 
    {
        printStats(bloomF0, bloomF1); //Print stats
    }
    delLL(replacement);
    delLL(joyCamp);
    delHT(hashT);
    delBF(bloomF0);
    delBF(bloomF1);
}

int main(int argc, char * const argv[]) 
{
    bloomSize = pow(2,20); //Default bloom filter size
    int c = 0;
    int caseS = -1;
    int caseM = -1;
    int caseB = -1;
    int hashSize = 10000;
    int printTrue = 0;
    while ((c = getopt(argc, argv, "smbh:f:")) != -1) 
    {
        switch (c) 
        {
            case 's' : caseS = 0; //Supress letter from censor and print stats
                break;
            case 'm' : caseM = 0; //Use move to front rule
                break;
            case 'b' : caseB = 0; //Don't use move to front rule
                break;
            case 'h' : hashSize = atoi(optarg); //Specify number of hash entries
                break;
            case 'f' : bloomSize = atoi(optarg); //Specify number of bloom filter entries
                break;
        }
    }
    if (caseS == 0) //Print stats
    {
        printTrue = -1;
    }
    
    if (caseM == 0) //Move to front is true
    {
        moveToFront = true;
    }
    
    if (caseB == 0) //Move to front is false
    {
        moveToFront = false;
    }

    if (argc == 1) //Read from standard input
    {
        yyin = stdin;
        readInput(hashSize, bloomSize, printTrue);
        return 0;
    } else 
    {
        yyin = fopen(argv[1],"r"); //Read from text file
        readInput(hashSize, bloomSize, printTrue);
        return 0;
    }
}

    

