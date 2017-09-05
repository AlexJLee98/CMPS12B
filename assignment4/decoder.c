# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <getopt.h>
# include "huffman.h"
# include "bv.h"

//Global variables
FILE *in, *out;
uint32_t magicNum;
uint64_t outputSize;
uint32_t fileSize;
uint16_t treeSize;
bitV *myBitV;
uint8_t *savedTree;
treeNode *rootNode;

void readFileSize(char *inputFile) //Get total file size
{ 
    in = fopen(inputFile, "rb");
    fseek(in, 0L, SEEK_END); 
    fileSize = ftell(in);
    fseek(in, 0L, SEEK_SET);
}


void readMagicNum() //Read magic number 
{ 
    fread(&magicNum, sizeof(uint32_t), 1, in); 
    if (magicNum != 0xdeadd00d) //Exit if not a compressed file
    { 
        printf("Not a compressed file. \n");
        fclose(in);
        exit(-1);
    }
}


void readOutputSize() //Get output file size
{ 
    fread(&outputSize, sizeof(outputSize), 1, in);
}
 

void readTreeSize() //Read tree size
{
    fread(&treeSize, sizeof(treeSize), 1, in);  
}


void loadTreeInfo() //Get tree information
{    
    savedTree = (uint8_t *) calloc(treeSize, sizeof(uint8_t)); //Create saved tree array
    fread(savedTree, sizeof(uint8_t), treeSize, in); //Read bits into array
    rootNode = loadTree(savedTree, treeSize); //Load tree from array
}


void readBits() //Read bits
{ 
    uint32_t totalRead = 0;
    uint32_t bitValue = 0;
    int buffSize = 1024;
    int numRead = buffSize;
    uint8_t buf[buffSize];
    uint32_t readLength = fileSize - sizeof(magicNum) - sizeof(in) - sizeof(treeSize) - treeSize;
    myBitV = newVec(readLength * 8); 
    while (numRead == buffSize) 
    {
        numRead = fread(buf, sizeof(uint8_t), buffSize, in);
        memcpy(myBitV->v + totalRead, buf, numRead);
        totalRead = totalRead + numRead;
    }
    if (totalRead == readLength) //Exit condition
    { 
        printf("Total read : %d \n", totalRead);
    } else //They have to equal or something is incorrect 
    { 
        exit(1);
    }
}


void decompressInput(char* outputFile) //Decompress input 
{
    uint32_t bitVal;
    uint32_t counter = 0;
    uint32_t length = outputSize;
    uint8_t buffer[length];
    treeNode *startNode = rootNode;
    treeNode *searchNode;
    for (uint32_t i = 0; i < lenVec(myBitV); i++) //Iterate through bit vector
    {
        bitVal = valBit(myBitV, i);
        if (stepTree(startNode, &searchNode, bitVal) == -1) 
        {
            startNode = searchNode;
        } else if (counter < length) 
        {
            buffer[counter] = searchNode->symbol;
            startNode = rootNode;
            counter++;
        } else 
        {
            break;
        }
    }
    if (outputFile != NULL) //Write to file if one is specified
    {
        out = fopen(outputFile, "w+");
        fwrite(buffer, sizeof(uint8_t), length, out);
        fclose(out);
    } else //Write to standard input if no file specified 
    {
        fwrite(buffer, sizeof(uint8_t), length, stdout);
    }
}


void decode(char* inputFile, char* outputFile) //Decode main
{
    readFileSize(inputFile);
    readMagicNum();
    readOutputSize();
    readTreeSize();
    loadTreeInfo();
    readBits();
    decompressInput(outputFile);
}


void printStats() //Print statistics  
{ 
    printf("Original %llu bits: tree (%d) \n", outputSize * 8, treeSize);
}


int main(int argc, char * const argv[]) 
{
    char* inputFile = NULL;
    char* outputFile = NULL;
    int c = 0;
    int caseI = -1;
    int caseV = -1;
    int caseO = -1;
    while ((c = getopt(argc, argv, "vi:o:")) != -1) 
    {
         switch (c) 
         {
            case 'v' : caseV = 0; //Print stats
                break;
            case 'i' : caseI = 0, inputFile = optarg; //Specify input file
                break;
            case 'o' : caseO = 0, outputFile = optarg; //Specify output location
                break;
        }
    }
    if (caseI == -1) //Exit if no input file
    {
        printf("No input file specified. \n");
        exit(0);
    }
    
    decode(inputFile, outputFile);
    
    if (caseV == 0) //Print stats if -v flag is specified
    { 
        printStats();
    }
}
