# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "huffman.h"
# include "queue.h"


queue *newQueue(uint32_t size) //Create a new queue
{
    queue *myQueue = calloc(1, sizeof(queue));
    myQueue->size = size;
    myQueue->Q = calloc(size, sizeof(item));
    myQueue->head = -1; //Set to -1 for empty condition
    myQueue->tail = -1; //Set to -1 for empty condition
    return myQueue;
}


void delQueue(queue *myQueue) //Delete a queue
{
    free(myQueue->Q);
    free(myQueue);
}


bool emptyQueue(queue *myQueue) //Check if queue is empty
{
    if (myQueue->tail == -1) 
    {
        return true;
    } else {
        return false;
    }
}


bool fullQueue (queue *myQueue) //Check if queue is full
{
    if (myQueue->head - myQueue->tail + 1 == myQueue->size) {
        return true;
    } else {
        return false;
    }
}


bool enqueue(queue *myQueue, item myItem) //Enqueue an item 
{
    if (fullQueue(myQueue) == true) //Can't enqueue full queue
    {
        return false;
    }
    if (myQueue->tail == -1) //First time case set head and tail to 0 and insert at 0
    { 
        myQueue->head = 0; //Set head and tail to 0
        myQueue->tail = 0;
        myQueue->Q[myQueue->head].symbol = myItem.symbol; //Copy stuff
        myQueue->Q[myQueue->head].leaf = myItem.leaf;
        myQueue->Q[myQueue->head].count = myItem.count;
        myQueue->Q[myQueue->head].left = myItem.left;
        myQueue->Q[myQueue->head].right = myItem.right;
        return true;
    }
    if (myItem.count >= myQueue->Q[myQueue->head].count) //If value is greater than head
    { 
        myQueue->head = (myQueue->head + 1) % myQueue->size; //Increment head
        myQueue->Q[myQueue->head].symbol = myItem.symbol; //Copy stuff
        myQueue->Q[myQueue->head].leaf = myItem.leaf;
        myQueue->Q[myQueue->head].count = myItem.count;
        myQueue->Q[myQueue->head].left = myItem.left;
        myQueue->Q[myQueue->head].right = myItem.right;
        return true;
    }

    int start = myQueue->head;
    int end = myQueue->tail;
    int i = start;
    for (i = start; i >= end; i--) 
    {
        if (myItem.count < myQueue->Q[i % myQueue->size].count) 
        {
            myQueue->Q[(i + 1) % myQueue->size] = myQueue->Q[i % myQueue->size];
        } else 
        {
            break;
        }  
    }
    i = i + 1;
    myQueue->Q[i] = myItem;
    if (i == myQueue->tail) 
    {
        myQueue->tail = i % myQueue->size;   
    }
    if (myQueue->head == myQueue->size - 1) 
    {
        myQueue->head++;
    } else 
    {
        myQueue->head++;
    }
    return true;
}


bool dequeue(queue *myQueue, item *myItem) { //Dequeue an item
    if (emptyQueue(myQueue) == true) //Can't dequeue an empty queue
    { 
        return false;
    } else 
    {
        myItem->symbol = myQueue->Q[myQueue->tail % myQueue->size].symbol; //Copy everything
        myItem->leaf = myQueue->Q[myQueue->tail % myQueue->size].leaf; 
        myItem->count = myQueue->Q[myQueue->tail % myQueue->size].count;
        myItem->left = myQueue->Q[myQueue->tail % myQueue->size].left;
        myItem->right = myQueue->Q[myQueue->tail % myQueue->size].right; 
        if (myQueue->head == myQueue->tail) //Set to empty condition if last one
        { 
            myQueue->tail = -1;    
        } else 
        {
            myQueue->tail = (myQueue->tail + 1) ;
        }
        return true;
    }
}


void printQueue(queue *myQueue) //Print queue
{ 
    for (int i = 0; i < myQueue->size; i++) 
    {
        if (myQueue->Q[i].count > 0) 
        {
            printf("Pos : %d Queue value : %llu Char : %c \n", i, myQueue->Q[i].count, myQueue->Q[i].symbol);
        }
    }
}
