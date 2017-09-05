# include "encoder.h"
# include <getopt.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h> 

//Global variables
code *codeTable;
bitV *encodedTextBits;
int count[numSymbol];
queue histoQueue;
treeNode rootNode;
uint16_t leafCounter;
uint64_t inputFileSize;
uint16_t treeSize;
uint32_t existingBitVSize = 0;
FILE *fp;
int fpOut;


void encode(char *inputFileName, char *outFileName) //Encode a file 
{
    codeTable = (code *) calloc(256, sizeof(code)); //Create code table
    encodedTextBits = NIL;
    buildTree(inputFileName); //Build tree
    dumpNode(&rootNode); 
    code bitCode = newCode();
    buildCode(&rootNode, &bitCode, codeTable); //Build code
    encodeTextFile(inputFileName, outFileName, &rootNode); //Encode text file
}


void encodeTextFile(char *inFileName, char *outFileName, treeNode *rootTreeNode) //Encode text file
{
    char * line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen(inFileName, "r"); //Open input file
    bitV *bitMap = NIL;
    while ((read = getline(&line, &length, fp)) != EOF) //Read whole file 
    {
        for (int i = 0; i < read; i++) 
        {
            code myTable = codeTable[(uint8_t) line[i]]; //Create code table
            bitMap = appendBits(&myTable); //Append bits together
        }
    }
    fseek(fp, 0L, SEEK_END);
    inputFileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    fclose(fp);
    fpOut = open(outFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    
    if (fpOut == -1) //Get leaf count and tree size even if no output file
    {
        leafCounter = leafCount(rootTreeNode); 
        treeSize = (leafCounter * 3) - 1;
        return;
    }  
    
    write(fpOut, &magicNumber, sizeof(uint32_t)); //Write magic number
    write(fpOut, &inputFileSize, sizeof(inputFileSize)); //Write size of input file
    leafCounter = leafCount(rootTreeNode); 
    treeSize = (leafCounter * 3) - 1;
    write(fpOut, &treeSize, sizeof(treeSize)); //Write size of tree
    dumpTree(&rootNode, fpOut); //Dump tree
    int numDump = bitMap->l/8;
    if (bitMap->l % 8 != 0) 
    {
        numDump++;    
    }
    for (int i = 0; i < numDump; i++) //Append second half
    { 
        write(fpOut, bitMap->v+i, sizeof(uint8_t));        
    }
    fsync(fpOut); 
    close(fpOut); //Close file
}


bitV *appendBits(code *bitCode) // Append the bits from the bitCode to the encodedText bitV
{
    if (encodedTextBits != NIL) 
    {
        existingBitVSize = encodedTextBits->l; //Set bit length
    }
    uint32_t newBitVSize = existingBitVSize + bitCode->l;
    bitV* tempBits = newVec(newBitVSize); //Make a temporary bit vector
    uint32_t currentBitPos = 0;
    if (encodedTextBits != NIL) 
    {
        memcpy(tempBits->v, encodedTextBits->v, (encodedTextBits->l/ 8 + 1)); //Copy bits to new
        currentBitPos = currentBitPos + encodedTextBits->l;
    
    }
    
    for (uint32_t k = 0; k < bitCode->l; k++) //Iterate through bit vector 
    {
        uint8_t bitValue = getBitValue(bitCode, k); 
        if (bitValue == 1) { //Set second half
            setBit(tempBits, currentBitPos);
        } else 
        {
            clrBit(tempBits, currentBitPos);
        }
        currentBitPos = currentBitPos + 1;
    } 
    delVec(encodedTextBits); //Free bit vector
    encodedTextBits = tempBits;    
    return encodedTextBits;
}


uint8_t getBitValue(code *bitCode, int pos) //Get bit value
{

    uint32_t byteIndex = pos / 8;
    uint8_t n = bitCode->bits[byteIndex];
    int bitToPrint = pos - 8*byteIndex;  
    
    if (n == 0) 
    {
        return 0;
    } else 
    {
        for (int y = 0; y < bitToPrint; y++)
        {
            n >>= 1;
        }
        if (n & 1) 
        {
            return 1;
        } else 
        {
            return 0;
        }
    } 
}


void dumpNode(treeNode *node) //Dump empty node
{
    if (node == NIL) {
        return;
    }
}


void buildHistogram(char *inFile) { //Builds histogram
    for (int i = 0; i < numSymbol; i++) 
    {
        if (i == 0 || i == numSymbol - 1) //Set first and last to 0
        {
            count[i] = 1; 
        } else {
            count[i] = 0;
        }
    }
    
    FILE *fp = fopen(inFile, "r");
    int c;
    
    while((c = fgetc(fp))) //Read to end of file
    {
        if (c == EOF) 
        {
            break;
        }
        count[c] = count[c] + 1;
    }
    fclose(fp);
}


void buildPriorityQueue() //Builds priority queue
{ 
    histoQueue = *newQueue(numSymbol);
    treeNode myNode;
    
    for (int i = 0; i < numSymbol; i++) //Iterature through number of symbols used
    {
        if (count[i] > 0) 
        {
            myNode.symbol = i;
            myNode.count = count[i];
            myNode.leaf = true;
            enqueue(&histoQueue, myNode);
        }
    }
}


void buildingTree() //Builds priority queue
{ 
    treeNode queueNode;
    treeNode *internalNode;
    treeNode *leftNode;
    treeNode *rightNode;
    uint32_t boolT = false;
    
    while (1) //Infinite loop
    { 
        boolT = dequeue(&histoQueue, &queueNode); 
        if (boolT == true) 
        {
            leftNode = newNode(queueNode.symbol, queueNode.leaf, queueNode.count);
            leftNode->left = queueNode.left;
            leftNode->right = queueNode.right;
        } else 
        {
            break;
        }
        
        boolT = dequeue(&histoQueue, &queueNode);
        
        if (boolT == true) 
        {
            rightNode = newNode(queueNode.symbol, queueNode.leaf, queueNode.count);
            rightNode->left = queueNode.left;
            rightNode->right = queueNode.right;
            internalNode = join(leftNode, rightNode);
            enqueue(&histoQueue, *internalNode);
        } else 
        {
            rootNode.symbol = leftNode->symbol;
            rootNode.count = leftNode->count;
            rootNode.leaf = leftNode->leaf;
            rootNode.left = leftNode->left;
            rootNode.right = leftNode->right;
            break;
        }
    }
}


uint64_t leafCount(treeNode *root) //Counts number of leaves
{ 
    uint64_t count = 0;
    if (root->leaf == true) //Incrememnt leaf cpimt
    {
        count = count + 1;
    } else 
    {
        uint64_t leftCount = leafCount(root->left);
        uint64_t rightCount = leafCount(root->right);
        count = leftCount + rightCount;
    }
    return count;
}


void buildTree(char *inFile) //Builds entire tree
{
    buildHistogram(inFile);
    buildPriorityQueue();
    buildingTree();
}


void printStats() //Prints stas
{
    printf("Original %llu bits: %d leaves (%hu bytes) encoding %d bits" , inputFileSize * 8, leafCounter, treeSize, existingBitVSize);
}


int main(int argc, char * const argv[]) 
{
    int c = 0;
    int caseI = -1;
    int caseV = -1;
    char *inputFile = NULL;
    char *outputFile = NULL;
    while ((c = getopt(argc, argv, "vi:o:")) != -1) 
    {
         switch (c) {
            case 'v' : caseV = 0; //Print stats
                break;
            case 'i' : caseI = 0, inputFile = optarg; //Specify input file
                break;
            case 'o' : outputFile = optarg; //Specify output location
                break;
        }
    }
    if (caseI == -1) //Exit if no input file
    {
        printf("No input file specified. \n");
        exit(0);
    }
    encode(inputFile, outputFile);
    printf("Successfully encoded %s. Encoded file name is : %s \n", inputFile, outputFile);
    if (caseV == 0) {
        printStats();
    }
    return 0;
} 
