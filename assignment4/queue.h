# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

typedef treeNode item;

typedef struct queue
{
    int32_t size; // How big is it?
    int32_t head, tail; // Front and rear locations
    item *Q; // Array to hold it (via calloc)
} queue;

queue *newQueue(uint32_t size); // Constructor
void delQueue(queue *); //Destructor

bool emptyQueue (queue *);
bool fullQueue (queue *);

bool enqueue(queue *, item ); // Add an item
bool dequeue(queue *, item *); // Remove from the rear

void printQueue(queue *);

# endif
