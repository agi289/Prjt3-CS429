#include "tdmm.h"
#include "tmalloc.h"
#include<assert.h>

// Main ~ tester
extern block* freeLinkedList;

int main(int argc, char *argv[])
{
    int a;

    /* Initialization */
    t_init(FIRST_FIT, &a);

    //void * p = t_malloc(10);

    int test_var = 6000;

    int *test[test_var];
    for (int i = 0; i < test_var; i++)
    {
       // t_malloc(4097);
        //t_free(test[i]);
        test[i] = t_malloc(4097);
        *test[i] = i;
        t_free(test[i]);
        printf("SUCCESS at %d\n", (i));
    }
    // testMalloc();
    //t_gcollect();
    // testMalloc();

    // test[0] = t_malloc(30);
    // test[1] = t_malloc(29);
    // test[2] = t_malloc(35);
    // test[3] = t_malloc(20);
    // test[4] = t_malloc(40);

    // t_free(test[1]);
    // t_free(test[3]);

    // test[5] = t_malloc(19);

    // printf("Worked!\n");

    // for (int i = 0; i < test_var; i++)
    // {
    //     test[i]
    //     //assert(*test[i] == i);
    //     printf("SUCCESS at %d\n", (i));
    // }

    // void* test[1000000];
    // for(int i=1; i < 500000; i++){
    //     test[i] = t_malloc(16);
    //     test[2*i] = t_malloc(112);
    //     block* search = freeLinkedList;
    //     if(i>84&&i<90){puts("newlist");}
    //     while (search != NULL)
    //     {   
    //         if(i>84&&i<90){printf("pointer:%p, next:%p, free: %d, size:%d\n", search, search->next, search->free, search->size);}
    //         assert(search->free == 1);
    //         assert((unsigned long long)search->next != 0xDEADBEEFBEEFBEEF);
    //         assert((unsigned long long)search % 4 ==0);
    //         assert(search->next==NULL||(unsigned long long)search->next >= ((unsigned long long)search) + search->size);
    //         search= search->next;
    //     }
        
    // }
    // printf("made it!!");
}