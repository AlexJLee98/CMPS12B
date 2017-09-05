# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

#include "code.h"

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode;

struct DAH
{
    uint8_t symbol;
    uint64_t count;
    bool leaf;
    treeNode *left, *right;
};

treeNode *newNode(uint8_t, bool, uint64_t);
                  
void delNode(treeNode *);

void *delTree(treeNode *);

void dumpTree(treeNode *, int);

treeNode *loadTree(uint8_t [], uint16_t);

int32_t stepTree(treeNode *, treeNode **, uint32_t);

void buildCode(treeNode *t, code *bitCode, code *codeTable);

void traverseEncoderTree(treeNode *node, code *bitCode, code *codeTable);

bool compare(treeNode *, treeNode *);

treeNode *join(treeNode *, treeNode *);

void printTree(treeNode *);

void printNode(treeNode *);

# endif
