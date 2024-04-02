#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include "tmalloc.h"
#include "tdmm.h"
#include <sys/mman.h>
#include <assert.h>
#include <bits/mman-linux.h>

// Global variables
block *freeLinkedList = NULL;
block *allocatedLinkedList = NULL;
int policy = 0;

/* Helper functions */
void putBlock(block *change, size_t size, block *nextAdd, int freeAdd)
{
    assert(change != NULL);
    change->size = size;
    change->next = nextAdd;
    change->free = freeAdd;
}

/* Aligns to a multiple of 4  ~ done */
size_t align(size_t size)
{
    int ALIGNMENT = 4;
    return (size + (ALIGNMENT - 1) & ~(ALIGNMENT - 1));
}

/* Aligns to a multiple of 4  ~ done */
size_t alignForExtension(size_t size)
{
    return (((size) + (4096 - 1)) & ~(4096 - 1));
}

/* Split & coalesce */

block *split(block *blockToSplit, size_t size)
{
    size_t sizeOfBlock = blockToSplit->size;
    size_t whatsLeft = sizeOfBlock - size;
    // changed from < size *3 to <= size
    if (blockToSplit->size <= size)
    {
        return blockToSplit;
    }
    // Keeping the top-half free
    putBlock(blockToSplit, whatsLeft, blockToSplit->next, 1);
    block *allocatedPortion = (block *)((char *)blockToSplit + whatsLeft);
    // Allocated bottom half
    putBlock(allocatedPortion, size, NULL, 0);
    return allocatedPortion;
}

/* Main functions */

void t_init(int strategy)
{
    block *initial = (block *)mmap(NULL, 4096 * 4, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (initial != MAP_FAILED)
    {
        putBlock(initial, 4096 * 4, NULL, 1);
        freeLinkedList = initial;
    }
    policy = strategy;
}

/* Policies or 4 implementations (first, best, worst, buddy)*/


block *extend(size_t size)
{
    // Calculate expansion
    size = alignForExtension(size);
    block *newLength = (block *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Nothing in free list, means linked list is NULL, if not puts free linked list as next pointer
    putBlock(newLength, size, NULL, 1);
    insertListModified(&freeLinkedList, newLength);
    return newLength;
}

block *firstFit(size_t size)
{
    // get the first block
    block *curr = freeLinkedList;

    // do a while loop to iterate by going to next with condition curr isn't null
    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            return curr;
        }
        else
        {
            curr = curr->next;
        }
    }

    // No suitable block found return NULL
    return NULL;
}


size_t calcSize(block * check, size_t size)
{
    return check->size - size;
}

block * bestFit(size_t size)
{
    block * curr = freeLinkedList;
    block * toReturn = NULL;
    size_t sizeDiff = __SIZE_MAX__;

    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            size_t replaceS = calcSize(curr, size);
            if (replaceS<sizeDiff)
            {
                sizeDiff = replaceS;
                toReturn = curr;
            }
        }
        curr = curr->next;
    }

    return toReturn;
}


block * worstFit(size_t size)
{
    block * curr = freeLinkedList;
    block * toReturn = NULL;
    size_t sizeDiff = 0;

    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            size_t replaceS = calcSize(curr, size);
            if (replaceS>sizeDiff)
            {
                sizeDiff = replaceS;
                toReturn = curr;
            }
        }
        curr = curr->next;
    }

    return toReturn;
}

/* Malloc */

void *t_malloc(size_t size)
{
    // size 0 check
    if (size == 0)
    {
        return NULL;
    }

    // Align size to a multiple of 4, so we do not have to worry later
    size = align(size) + sizeof(block);
    block *use;

    switch (policy)
    {
    case 1:
        use = firstFit(size);
        break;
    case 2:
        use = bestFit(size);
        break;
    case 3:
        use = worstFit(size);
        break;
    case 4:
        //  return buddy(size);
        // do the entire code in here cause have to call buddy after extend, not same as rest
    default:
        fprintf(stderr, "Malloc error.");
        exit(EXIT_FAILURE);
    }

    if (use == NULL)
    {
        // mmmap extension function
        use = extend(size);
    }

    // split a block
    use = split(use, size);

    if (use == freeLinkedList)
    {
        // remove first node by simply changing ptr of freehead to next of usefinal
        freeLinkedList = freeLinkedList->next;
    }
    else
    {
        // get temp ref to free_head
        block *tempFreehead = freeLinkedList;

        while (tempFreehead->next != NULL && tempFreehead->next < use)
        {
            tempFreehead = tempFreehead->next;
        }

        // removes
        tempFreehead->next = use->next;
    }

    // we need to set block as allocated
    use->free = 0;
    // now put the node (via tempRef) into the allocated list
    insertListModified(&allocatedLinkedList, use);
    return ((char *)use + sizeof(block));
}

/* Free components */

void t_free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    block *beforeDataPtr = (block *)ptr - 1;

    // if the pointer hasn't been allocted / is free
    if (beforeDataPtr->free == 1)
    {
        return;
    }

    // Flips the free value of the allocated block to 1 meaning now free
    beforeDataPtr->free = 1;

    if (beforeDataPtr == allocatedLinkedList)
    {
        allocatedLinkedList = allocatedLinkedList->next;
    }
    else
    {
        // get temp ref to free_head
        block *tempAlloc = allocatedLinkedList;

        while (tempAlloc->next != NULL && tempAlloc->next < beforeDataPtr)
        {
            tempAlloc = tempAlloc->next;
        }

        // removes
        tempAlloc->next = beforeDataPtr->next;
    }

    insertListModified(&freeLinkedList, beforeDataPtr);

    coalesce(freeLinkedList);
}

void coalesce(block *curr)
{
    block *after = curr->next;
    while (after != NULL)
    {
        if (curr->free == 1 && after->free == 1)
        {
            // Calculate memory address ending of first block
            size_t thisEndingAddress = (size_t)curr + curr->size;

            // Check if these are contiguous blocks, meaning
            if ((block *)thisEndingAddress == after)
            {
                int sizeOfMergedBlock = curr->size + after->size;
                putBlock(curr, sizeOfMergedBlock, after->next, 1);
            }
        }
        curr = after;
        after = after->next;
    }
}