#include "tmalloc.h"
#include "tdmm.h"

void insertListModified(block * * pointerToAList, block * insertBlock)
{
    // dereference pointer to check if list is null or the block inserted is before first elem (cause add at start)
    if (*(pointerToAList) == NULL || *(pointerToAList) > insertBlock)
    {
        // set the values
        insertBlock->next = *pointerToAList;
        * pointerToAList = insertBlock;
    }
    else
    {
        block * previous = *pointerToAList;
        block * curr = previous->next;

        while (curr != NULL && curr < insertBlock)
        {
            previous = curr;
            curr = curr->next;
        }

        insertBlock->next = curr;
        previous->next = insertBlock;
    }
}