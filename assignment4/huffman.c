# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "stack.h"
# include "huffman.h"

treeNode *newNode(uint8_t s, bool l, uint64_t c) //Create a new tree node 
{
    treeNode *myNode = calloc(1 , sizeof(treeNode));
    myNode->symbol = s;
    myNode->leaf = l;
    myNode->count = c;
    myNode->left = NIL;
    myNode->right = NIL;
    return myNode;
}


void *delTree(treeNode *myTree) //Delete tree
{
    if (myTree) 
    {
        delTree(myTree->left);
        delTree(myTree->right);
        delTree(myTree);   
    }
    return 0;
}


void delNode(treeNode *myNode) //Delete node
{ 
    free(myNode); 
}


void dumpTree(treeNode *myTree, int file) //Dump tree contents
{
    if (file == -1) //If no file specified
    {
        printf("Error opening file when dumping tree. \n");
        exit(1);
    }
    
    if (myTree->leaf == true) //Dump leaf
    {
        write(file, "L", 1);
        write(file, &(myTree->symbol), 1);
        return;
    }
    
    dumpTree(myTree->left, file); //Traverse post order
    dumpTree(myTree->right, file);
    write(file, "I", 1);
    return;
}


treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes) //Load tree from array
{
    treeNode leafNode;
    treeNode popNode;
    treeNode interiorNode;
    treeNode *leftNode;
    treeNode *rightNode;
    treeNode *rootNode;
    int leafCount = 0;
    stack *myStack = newStack(treeBytes);
    
    leafNode.count = 0;
    leafNode.leaf = true;
    leafNode.left = NIL;
    leafNode.right = NIL;
    interiorNode.leaf = false;
    interiorNode.symbol = '$';
    
    for (uint16_t i = 0; i < treeBytes; i++) 
    {
        if (savedTree[i] == 'L') //Push if leaf
        {
            leafNode.symbol = savedTree[++i];
            push(myStack, leafNode);
            leafCount++;
        } else if (savedTree[i] == 'I') //Pop if internal node
        {
            popNode = pop(myStack);
            rightNode = newNode(popNode.symbol, popNode.leaf, popNode.count);
            rightNode->left = popNode.left;
            rightNode->right = popNode.right;
            popNode = pop(myStack);
            leftNode = newNode(popNode.symbol, popNode.leaf, popNode.count);
            leftNode->left = popNode.left;
            leftNode->right = popNode.right;
            interiorNode.count = leftNode->count + rightNode->count;
            interiorNode.left = leftNode;
            interiorNode.right = rightNode;
            push(myStack, interiorNode);       
        } else 
        {
            //printf("Error : %c \n", savedTree[i]);
        }
    }
    popNode = pop(myStack);
    free(myStack);
    rootNode = newNode(popNode.symbol, popNode.leaf, popNode.count);
    rootNode->left = popNode.left;
    rootNode->right = popNode.right;
    return rootNode;
}


int32_t stepTree(treeNode *root, treeNode **myTree, uint32_t code) //Step tree
{
    
    if (code == 0) //Go left if bit value 0
    {
        *myTree = root->left;    
    } else 
    {
        *myTree = root->right;
    }
    if ((*myTree)->leaf == true) //Return 0 if its a leaf
    {
        return 0;
    } else {
        return -1;
    }
}


void buildCode(treeNode *t, code *bitCode, code *codeTable) 
{    
    pushCode (bitCode, 0); //Traverse post order
    traverseEncoderTree(t->left, bitCode, codeTable);
    pushCode (bitCode, 1); 
    traverseEncoderTree(t->right, bitCode, codeTable);
}


void traverseEncoderTree(treeNode *node, code *bitCode, code *codeTable) 
{
    uint32_t k;
    if (node->leaf == true) //Make a copy of the code and save it in the code table
    { 
        codeTable[node->symbol].l = bitCode->l;
        memcpy(codeTable[node->symbol].bits, bitCode->bits, 32*sizeof(uint8_t));
        popCode (bitCode, &k);
        return;
    }
    pushCode (bitCode, 0);  //Traverse post order
    traverseEncoderTree(node->left, bitCode, codeTable);
    pushCode (bitCode, 1);
    traverseEncoderTree(node->right, bitCode, codeTable);
    popCode (bitCode, &k); 
}


bool compare(treeNode *left, treeNode *right) //Compare nodes
{
    return left->count - right->count;
}


treeNode *join(treeNode *left, treeNode *right) //Joins two nodes together
{ 
    uint64_t leftCount = left->count;
    uint64_t rightCount = right->count;
    treeNode *myInternalNode = newNode('$', false, leftCount + rightCount);
    myInternalNode->left = left; //Set left of internal node
    myInternalNode->right = right; //Set right of internal node
    return myInternalNode;
}
