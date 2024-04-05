#include "tdmm.h"
#include "tmalloc.h"
#include <assert.h>


// Main ~ tester
extern block *freeLinkedList;


int main(int argc, char *argv[])
{
    int a;


    /* Initialization */
    t_init(FIRST_FIT, &a);


    // void * p = t_malloc(10);


    int test_var = 5000;


    int *test[test_var];
    for (int i = 0; i < test_var; i++)
    {
        // t_malloc(4097);
        // t_free(test[i]);
        if (i == 273)
        {
            test[0] = test[0];
        }
        test[0] = t_malloc(28);
        *test[0] = i;
        // print pointers returned by malloc
        // t_free(test[i]);
        printf("SUCCESS at %d\n", (i));
    }


    // int test_var = 5;


    // int *test[test_var];
    // for (int i = 0; i < test_var; i++)
    // {
    //     t_malloc(10);
    //     testMalloc();
    //     // t_free(test[i]);
    //     // if (i == 271)
    //     // {
    //     //     test[0] = test[0];
    //     // }
    //     // test[0] = t_malloc(28);
    //     // *test[0] = i;
    //     // print pointers returned by malloc
    //     // t_free(test[i]);
    //     printf("SUCCESS at %d\n", (i));
    // }
    // t_gcollect();
    // testMalloc();
    // printf("SAAME ADDRESS CHECK!\n");
    // for (int i = 0; i < test_var; i++)
    // {
    //     t_malloc(10);
    //     testMalloc();
    //     // t_free(test[i]);
    //     // if (i == 271)
    //     // {
    //     //     test[0] = test[0];
    //     // }
    //     // test[0] = t_malloc(28);
    //     // *test[0] = i;
    //     // print pointers returned by malloc
    //     // t_free(test[i]);
    //     printf("SUCCESS at %d\n", (i));
    // }
    // for (int i = 0; i < test_var; i++)
    // {
    //     t_malloc(4097);
    //     testMalloc();
    //     // t_free(test[i]);
    //     // if (i == 271)
    //     // {
    //     //     test[0] = test[0];
    //     // }
    //     // test[0] = t_malloc(28);
    //     // *test[0] = i;
    //     // print pointers returned by malloc
    //     // t_free(test[i]);
    //     printf("SUCCESS at %d\n", (i));
    // }


    // t_gcollect();
    // testMalloc();


    // // testMalloc();
    // //t_gcollect();
    // // testMalloc();


    // // test[0] = t_malloc(30);
    // // test[1] = t_malloc(29);
    // // test[2] = t_malloc(35);
    // // test[3] = t_malloc(20);
    // // test[4] = t_malloc(40);


    // // t_free(test[1]);
    // // t_free(test[3]);


    // // test[5] = t_malloc(19);


    // // printf("Worked!\n");


    // // for (int i = 0; i < test_var; i++)
    // // {
    // //     test[i]
    // //     //assert(*test[i] == i);
    // //     printf("SUCCESS at %d\n", (i));
    // // }


    // char* test[1000000];
    // for(int i =0; i < 100000; i++) {
    //     test[i] = NULL;
    // }
    // for(int i=0; i < 20000; i++){
    //     test[i] = t_malloc(16);
    //     for(int j = 0; j < 16; j++) {
    //         test[i][j] = 99;
    //     }
    //     test[i + 50000] = t_malloc(112);
    //     for(int j = 0; j < 112; j++) {
    //         test[i + 50000][j] = 99;
    //     }
    //     // block* search = freeLinkedList;
    //     // if(i>84&&i<90){puts("newlist");}
    //     // while (search != NULL)
    //     // {
    //     //     if(i>84&&i<90){printf("pointer:%p, next:%p, free: %d, size:%d\n", search, search->next, search->free, search->size);}
    //     //     assert(search->free == 1);
    //     //     assert((unsigned long long)search->next != 0xDEADBEEFBEEFBEEF);
    //     //     assert((unsigned long long)search % 4 ==0);
    //     //     assert(search->next==NULL||(unsigned long long)search->next >= ((unsigned long long)search) + search->size);
    //     //     search= search->next;
    //     // }
    // }


    // for (int i = 0 ; i < 20000; i++) {
    //     t_free(test[i + 50000]);
    //     test[i + 50000] = NULL;
    // }
    // for (int i = 0 ; i < 20000; i++) {
    //     test[i + 50000] = t_malloc(128);
    //     for(int j = 0; j < 128; j++) {
    //         test[i + 50000][j] = 99;
    //     }
    // }


    // }
    // printf("made it!!");
}


// long timed_t_malloc(size_t size) {
//     clock_t start_t, end_t;
//    double total_t;
//    int i;


//    start_t = clock();
//    // replace w
//    printf("Starting of the program, start_t = %ld\n", start_t);


//    printf("Going to scan a big loop, start_t = %ld\n", start_t);
//    for(i=0; i< 10000000; i++) {
//    }
//    end_t = clock();


// }
