#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#define MAX_HASH_TABLE_SIZE 1024 
entry *hashTable[MAX_HASH_TABLE_SIZE];


unsigned long hashF(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return (hash&(MAX_HASH_TABLE_SIZE-1));
    }


entry *findName(char lastName[], entry *pHead)
{
    unsigned long hash = hashF(lastName);
    pHead  = hashTable[hash];
    while(pHead != NULL) {
        if(strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }   
    return NULL;
}

entry *append(char lastName[], entry *e) 
{
    unsigned long hash = hashF(lastName);
    entry *newEntry = (entry *)malloc(sizeof(entry));
    strcpy(newEntry->lastName, lastName);
    if(hashTable[hash] != NULL)
        newEntry->pNext = hashTable[hash];
    else
        newEntry->pNext = NULL;
    hashTable[hash] = newEntry;
    return e;
}
