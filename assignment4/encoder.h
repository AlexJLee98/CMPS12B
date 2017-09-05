# ifndef _ENCODER_H
# define _ENCODER_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# include "queue.h"
# include "huffman.h"
# include "code.h"
# include "bv.h"

void encode(char *inputFileName, char *outFileName);
//void traverseEncoderTree(treeNode *node, code *bitCode);
void dumpNode(treeNode *node) ;
void dumpCodeBits(code *bitCode);
void encodeTextFile(char *inFileName, char *outFileName, treeNode *rootNode);
bitV *appendBits(code *bitCode);
uint8_t getBitValue(code *bitCode, int pos);
void dumpVectorBits(bitV *bitVector);

void buildTree(char *inFile);
uint64_t leafCount(treeNode *root);

uint32_t magicNumber = 0xdeadd00d;
# define numSymbol 256

# endif
