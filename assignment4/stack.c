# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "stack.h"
# include "huffman.h"

stack *newStack(uint32_t length) //Create new stack
{
    stack *myStack = calloc(1, sizeof(stack)); //One stack
    myStack->size = length;
    myStack->entries = calloc(length, sizeof(item)); 
    myStack->top = -1; 
    return myStack;
}


void delStack (stack *myStack) //Delete stack
{
    free(myStack->entries); //Free entries
    free(myStack); //Free stack
}


item pop (stack *myStack) //Pop entry
{
    if (empty(myStack) == true) //Cannot pop an empty stack
    { 
        printf("Can't pop an empty stack \n");
        return myStack->entries[0];
    } else 
    {
        return myStack->entries[myStack->top--];
    }
}


void push (stack *myStack, item myNode) //Push entry
{
    if (full(myStack) == true) { //Cannot insert into a full stack
        return;
    } else 
    {
        myStack->top++;
        myStack->entries[myStack->top].count = myNode.count;
        myStack->entries[myStack->top].leaf = myNode.leaf;
        myStack->entries[myStack->top].symbol = myNode.symbol;
        myStack->entries[myStack->top].left = myNode.left; 
        myStack->entries[myStack->top].right = myNode.right; 
    }
}


bool empty (stack *myStack) //Checks if stack is empty
{ 
    int32_t top = myStack->top;
    
    if (top == -1) //Empty condition 
    {
        return true;
    } else {
        return false;
    }
}

bool full (stack *myStack) //Checks if stack is full
{
    int32_t top = myStack->top;
    
    if (top == myStack->size - 1) {
        return true;
    } else {
        return false;
    }
}

