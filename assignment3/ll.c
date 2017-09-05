# include "ll.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

extern bool moveToFront;
extern int seeks;
extern int numLL;

listNode *newNode(const char *oldspeak, const char *newspeak) //Make new node
{
    listNode *myNode = malloc(sizeof(listNode));
    if (oldspeak != NULL) 
    {
        myNode->oldspeak = malloc(sizeof(char) * strlen(oldspeak));
        myNode->oldspeak = strcpy(myNode->oldspeak, oldspeak);
    }
    if (newspeak != NULL) 
    {
        myNode->newspeak = malloc(sizeof(char) * strlen(newspeak));
        myNode->newspeak = strcpy(myNode->newspeak, newspeak);
    }
    myNode->next = NULL;
    return myNode;
}

void delNode(listNode *myNode) //Delete node
{
    free (myNode->oldspeak);
    free (myNode->newspeak);  
    free (myNode);  
}

void delLL(listNode *myNode) //Delete linked list
{
    while (myNode != NULL) 
    {
        delNode(myNode);
        myNode = myNode -> next;
        
    }
}

listNode *insertLL(listNode **headNode, const char *oldspeak, const char *newspeak) //Insert
{
    listNode *myNode = newNode(oldspeak, newspeak);
    myNode->next = *headNode;
    *headNode = myNode;
    return myNode;
}

listNode *findLL(listNode **headNode, const char *oldspeak) 
{
    listNode *myNode = *headNode;
    listNode *previousNode = NULL;
    listNode *nextNode = NULL;
    numLL = numLL + 1;
    int compare = 1;
    int counter = 0;
    while (myNode != NULL)  
    {   
        compare = strcmp(oldspeak, myNode->oldspeak); //Compare oldspeak
        if (compare == 0 && counter == 0) 
        {
            *headNode = myNode;
            seeks++;
            return myNode;
        } else if (compare == 0 && counter != 0 && moveToFront == true) 
        {
            nextNode = myNode->next; //Move accessed one to front
            myNode->next = *headNode;
            *headNode = myNode;
            previousNode->next = nextNode;
            seeks++;
            return myNode;
        } else if (compare == 0 && counter != 0 && moveToFront == false) 
        {
            return myNode; //Return node
        } else 
        {   
            previousNode = myNode;
            myNode = myNode->next;
            seeks++;
            counter++;
        }
    }
    return NULL; //Return null if can't find a match
}

void printLL(listNode *myNode) //Print linked list
{
    while (myNode != NULL) 
    {
        printf("Oldspeak value: %s \n", myNode->oldspeak);
        printf("Newspeak value: %s \n", myNode->newspeak);
        myNode = myNode->next;
    }
}
