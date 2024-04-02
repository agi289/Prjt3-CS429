// #include "tmalloc.h"
// #include <limits.h>
// #include "tdmm.h"

// block *freeLinkedList = NULL;
// block *allocatedLinkedList = NULL;


// size_t calcSize(block * check, size_t size)
// {
//     return check->size - size;
// }

// block * bestFit(size_t size)
// {
//     block * curr = freeLinkedList;
//     block * toReturn = freeLinkedList;
//     size_t sizeDiff = __SIZE_MAX__;

//     while (curr != NULL)
//     {
//         if (curr->free == 1 && curr->size >= size)
//         {
//             size_t replaceS = calcSize(curr, size);
//             if (replaceS<sizeDiff)
//             {
//                 sizeDiff = replaceS;
//                 toReturn = curr;
//             }
//         }
//         curr = curr->next;
//     }

//     return toReturn;
// }





































/// LInked list stuf



// // void t_free(void *ptr)
// // {
// //     if (ptr == NULL)
// //     {
// //         return;
// //     }
// //     block * tempAllocAhead;
// //     // WHAT IF WE ARE FREEING FROM EMPTY LIST (unsure if correct)
// //     if (freeLinkedList == NULL)
// //     {
// //         // block *tempAllocAhead = allocatedLinkedList;
// //         // while (tempAllocAhead->next != NULL && tempAllocAhead != ptr)
// //         // {
// //         //     tempAllocAhead = tempAllocAhead->next;
// //         // }
// //         // tempAllocAhead->free = 1;
// //         // freeLinkedList = tempAllocAhead;
// //     }
// //     // if ptr is the first in list
// //     if (ptr == allocatedLinkedList)
// //     {
// //         allocatedLinkedList = allocatedLinkedList->next;
// //     }
// //     else
// //     {
// //         // CREATE TEMP FOR STARTING LEFT POINT i.e. tempAllocAhead
// //         // then forward tempAllocHead like you have done
// //         // save the tempAllocHead->next as a temp pointer
// //         tempAllocAhead = allocatedLinkedList;
// //         while (tempAllocAhead->next != NULL && tempAllocAhead != ptr)
// //         {
// //             tempAllocAhead = tempAllocAhead->next;
// //         }
// //     }

// //     // DEALLOCATE -- ste block back from 0 to 1 (have)
// //     tempAllocAhead->free = 1;
// //     insertListModified(&freeLinkedList, tempAllocAhead);

// //     // COALESCE, prev and this, this and temp right ptr
// //     coalesce(freeLinkedList);
// //     coalesce(freeLinkedList->next);
// // }





// version 1 add






//     // is linked list is null do linked list null thing
//     // loop through using freehead and freehead next

//     block *allocCurr = allocatedLinkedList;
//     block *allocPrev = NULL;

//     if (ptr == allocatedLinkedList) // change?
//     {
//         allocatedLinkedList = allocatedLinkedList->next;
//     }
//     else
//     {
//         while (allocCurr != NULL && allocCurr != ptr)
//         {
//             allocPrev = allocCurr;
//             allocCurr = allocCurr->next;
//         }

//         // wasn't found
//         if (allocCurr == NULL)
//         {
//             return;
//         }
//     }

//     allocCurr->free = 1;
//     if (freeLinkedList == NULL)
//     {
//         freeLinkedList = allocCurr;
//     }
//     else
//     {
//         insertListModified(&freeLinkedList, allocCurr);
//     }

//     coalesce(allocPrev);
//     coalesce(allocCurr);
// }



















// Old split
   // if (blockToSplit->size > size + sizeof(block))
    // {
    //     block *nextBlock = blockToSplit->next;
    //     // Get remaining size
    //     size_t newSize = size + sizeof(block);
    //     blockToSplit->size -= newSize;

    //     block *newBlock = (block *)((char *)blockToSplit + blockToSplit->size + sizeof(block));
    //     // putBlock function
    //     return newBlock;
    // }
    // else
    // {
    //     return blockToSplit;
    // }



    ////// More
    

// void insertList(block * currBlock, size_t size, block * blockInsert, block * prevBlock)
// {
//     while (currBlock != NULL && currBlock < blockInsert)
//     {
//         prevBlock = currBlock;
//         currBlock = currBlock-> next;
//     }
//     // add to beginning of list
//     if (prevBlock == NULL)
//     {
//         blockInsert->next = currBlock;
//         currBlock = blockInsert;
//     }
//     else
//     {
//         prevBlock->next = blockInsert;
//         blockInsert->next = currBlock;
//     }
// }


// // put on tmalloc
// void tfree(void * ptr)
// {
//     if (ptr == NULL)
//     {
//         return;
//     }
    // block block = getBlock(block)
    // if (freeLinkedList == NULL)
    // {
    //     freeLinkedList = block;
    //     block-> prev = NULL;
    //      block-> next = NULL;

    // }
    // 
    // use insert method
// }