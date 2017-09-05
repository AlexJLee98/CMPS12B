# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h> 
# include "huffman.h"


typedef treeNode item;


typedef struct stack
{
    int32_t size; // How big?
    int32_t top; // Where’s the top?
    item *entries; // Array to hold it (via calloc)
} stack;

stack *newStack(uint32_t);
void delStack(stack *); 

item pop (stack *);
void push(stack *, item);

bool empty(stack *); 
bool full (stack *);

# endif
