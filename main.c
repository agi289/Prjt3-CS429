#include "tdmm.h"
#include "tmalloc.h"


// Main ~ tester

int main(int argc, char *argv[])
{
    int a;

    /* Initialization */
    t_init(FIRST_FIT, &a);

    void * p = t_malloc(10);
    ;

    // int test_var = 6000;

    // int *test[test_var];
    // for (int i = 0; i < test_var; i++)
    // {
    //    // t_malloc(4097);
    //     //t_free(test[i]);
    //     test[i] = t_malloc(4097);
    //     *test[i] = i;
    //     t_free(test[i]);
    //     printf("SUCCESS at %d\n", (i));
    // }
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
}