#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>

/* Structs */
typedef struct block{
    size_t size;    // size of the block
    struct block * next;    // pointer to next block
    int free;               // value to tell if the block has been freed or not, 1 if free 0 if not
    int mark;               // garbage collect marker, 1 is in use, 0 if not
    long magicNumber;        // set to DEADBEEF if in use for corroborating garabeg collect
} block;


/* Linked List Functions */
void insertListModified(block * * pointerToAList, block * insertBlock);


/* Helper Functions */

void putBlock(block * change, size_t size, block * nextAdd, int freeAdd);

size_t align(size_t size);

size_t alignForExtension(size_t size);


/* Function declarations  part of malloc */

block * split(block * blockToSplit, size_t size);

block * firstFit(size_t size);

block * bestFit(size_t size);

block * worstFit(size_t size);

block * buddy(size_t size);

block * extend(size_t size);


/*Functions part of free*/
void coalesce();



void testMalloc();
