#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "tmalloc.h"
#include "tdmm.h"
#include <sys/mman.h>
#include <assert.h>
#include <bits/mman-linux.h>

// Global variables
block *freeLinkedList = NULL;
block *allocatedLinkedList = NULL;
alloc_strat_e policy = FIRST_FIT;
char *stackBottomPtr;

/* Helper functions */
void putBlock(block *change, size_t size, block *nextAdd, int freeAdd)
{
    assert(change != NULL);
    change->size = size;
    change->next = nextAdd;
    change->free = freeAdd;
    change->mark = 0;
    change->magicNumber = 0xDEADBEEFBEEFBEEF;
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
    // return (((size) + (4096 - 1)) & ~(4096 - 1));
    //  keep doubling a number till it's greater than or equal to value
    size_t x = 4096;
    while (x < size)
    {
        x = x * 2;
    }
    return x;
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

// Splits in half each
// BUDDY CHANGE
block *splitBuddy(block *blockToSplit)
{
    size_t sizeOfBlock = blockToSplit->size;
    size_t whatsLeft = sizeOfBlock / 2;
    // changed from < size *3 to <= size

    // Keeping the top-half free
    putBlock(blockToSplit, whatsLeft, blockToSplit->next, 1);
    block *allocatedPortion = (block *)((char *)blockToSplit + whatsLeft);

    // Allocated bottom half
    putBlock(allocatedPortion, whatsLeft, NULL, 0);
    return allocatedPortion;
}

/* Main functions */

void t_init(alloc_strat_e mode, void *stack_bot)
{
    block *initial = (block *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (initial != MAP_FAILED)
    {
        putBlock(initial, 4096, NULL, 1);
        freeLinkedList = initial;
    }
    policy = mode;
    stackBottomPtr = stack_bot;
}

/* Policies or 4 implementations (first, best, worst, buddy)*/

// BUDDY CHANGE
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

size_t calcSize(block *check, size_t size)
{
    return check->size - size;
}

block *bestFit(size_t size)
{
    block *curr = freeLinkedList;
    block *toReturn = NULL;
    size_t sizeDiff = __SIZE_MAX__;

    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            size_t replaceS = calcSize(curr, size);
            if (replaceS < sizeDiff)
            {
                sizeDiff = replaceS;
                toReturn = curr;
            }
        }
        curr = curr->next;
    }

    return toReturn;
}

block *worstFit(size_t size)
{
    block *curr = freeLinkedList;
    block *toReturn = NULL;
    size_t sizeDiff = 0;

    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            size_t replaceS = calcSize(curr, size);
            if (replaceS > sizeDiff)
            {
                sizeDiff = replaceS;
                toReturn = curr;
            }
        }
        curr = curr->next;
    }

    return toReturn;
}

// BUDDY CHANGE
block *buddyFit(size_t size)
{
    block *curr = freeLinkedList;
    block *toReturn = NULL;
    size_t sizeDiff = __SIZE_MAX__;

    while (curr != NULL)
    {
        if (curr->free == 1 && curr->size >= size)
        {
            size_t replaceS = calcSize(curr, size);
            if (replaceS < sizeDiff)
            {
                sizeDiff = replaceS;
                toReturn = curr;
            }
        }
        curr = curr->next;
    }

    // buddy fit with the best fit block found
    if (toReturn == NULL)
    {
        return toReturn;
    }

    while (toReturn->size >= size * 2)
    {
        toReturn = splitBuddy(toReturn);
    }

    return toReturn;
}

block *policyChoose(alloc_strat_e strat, size_t size)
{
    block *use;
    switch (strat)
    {
    case FIRST_FIT:
        use = firstFit(size);
        return use;
    case BEST_FIT:
        use = bestFit(size);
        return use;
    case WORST_FIT:
        use = worstFit(size);
        return use;
    case BUDDY:
        // BUDDY CHANGE
        use = buddyFit(size);
        return use;
    default:
        fprintf(stderr, "Malloc error.");
        exit(EXIT_FAILURE);
    }
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

    use = policyChoose(policy, size);

    if (use == NULL)
    {
        // t_gcollect();
        // use = policyChoose(policy, size);
    }

    // If tgcollect doesn't work
    if (use == NULL)
    {
        // mmmap extension function
        use = extend(size);

        // BUDDY CHANGE
        if (policy == BUDDY)
        {
            use = buddyFit(size);
        }
    }

    // split a block
    // BUDDY CHANGE
    if (policy != BUDDY)
    {
        use = split(use, size);
    }

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

    // if the pointer hasn't been allocted / is free or isn't valid
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

void t_gcollect(void)
{
    // Marking phase
    long a;
    char *ptr = (char *)&a; // current stack ptr

    // sweep
    block *currStart = allocatedLinkedList;
    while (currStart != NULL)
    {
        block *nextStart = currStart->next;
        currStart->mark = 0;
        currStart = nextStart;
    }

    while ((uint64_t)stackBottomPtr - (uint64_t)ptr >= 8) // stack_bot is ptr of main so going up to main
    {
        void **reference = (void **)ptr;
        void *trial = *reference;

        block *allocCurr = allocatedLinkedList;
        while (allocCurr != NULL)
        {
            if (((uint64_t)allocCurr + sizeof(block) <= (uint64_t)trial) && ((uint64_t)trial < (uint64_t)allocCurr + allocCurr->size))
            {
                allocCurr->mark = 1;
            }
            allocCurr = allocCurr->next;
        }
        ptr += 1;
    }

    // sweep
    block *curr = allocatedLinkedList;
    while (curr != NULL)
    {
        block *next = curr->next;
        if (curr->mark == 0)
        {
            t_free(curr + 1);
        }
        curr = next;
    }
}

/*Tester functions*/

void testMalloc()
{
    printf("Testing malloc\n");
    block *currAllocTest = allocatedLinkedList;
    while (currAllocTest != NULL)
    {
        printf("The memory address is %p\n", currAllocTest);
        currAllocTest = currAllocTest->next;
    }
}