// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "tdmm.h"
// #include <time.h>
// #include "tmalloc.h"

// struct node
// {
//    int data;
//    struct node *next;
// };
// struct node *head = NULL;
// struct node *current = NULL;

// // display the list
// void printList()
// {
//    struct node *p = head;
//    printf("\n[");

//    // start from the beginning
//    while (p != NULL)
//    {
//       printf(" %d ", p->data);
//       p = p->next;
//    }
//    printf("]");
// }

// // insertion at the beginning
// void insertatbegin(int data)
// {

//    // create a link
//    struct node *lk = (struct node *)t_malloc(sizeof(struct node));
//    lk->data = data;

//    // point it to old first node
//    lk->next = head;

//    // point first to new first node
//    head = lk;
// }
// void insertatend(int data)
// {

//    // create a link
//    struct node *lk = (struct node *)t_malloc(sizeof(struct node));
//    lk->data = data;
//    struct node *linkedlist = head;

//    // point it to old first node
//    while (linkedlist->next != NULL)
//       linkedlist = linkedlist->next;

//    // point first to new first node
//    linkedlist->next = lk;
// }
// void insertafternode(struct node *list, int data)
// {
//    struct node *lk = (struct node *)t_malloc(sizeof(struct node));
//    lk->data = data;
//    lk->next = list->next;
//    list->next = lk;
// }
// void deleteatbegin()
// {
//    head = head->next;

//    // add tfree
//    t_free(head);
// }
// void deleteatend()
// {
//    struct node *linkedlist = head;
//    while (linkedlist->next->next != NULL)
//       linkedlist = linkedlist->next;

//    // add free
//    t_free(linkedlist->next);
//    linkedlist->next = NULL;
// }
// void deletenode(int key)
// {
//    struct node *temp = head, *prev;
//    if (temp != NULL && temp->data == key)
//    {
//       head = temp->next;
//       t_free(temp);
//       return;
//    }

//    // Find the key to be deleted
//    while (temp != NULL && temp->data != key)
//    {
//       prev = temp;
//       temp = temp->next;
//    }

//    // If the key is not present
//    if (temp == NULL)
//       return;

//    // Remove the node
//    prev->next = temp->next;
//    t_free(temp);
// }
// int searchlist(int key)
// {
//    struct node *temp = head;
//    while (temp != NULL)
//    {
//       if (temp->data == key)
//       {
//          return 1;
//       }
//       temp = temp->next;
//    }
//    return 0;
// }

// int main(int argc, char *argv[])
// {

//    clock_t start_time = clock();
//    // added intilization
//    int a;

//    t_init(BEST_FIT, &a);

//    int k = 0;
//    insertatbegin(12);
//    clock_t end_time = clock();

//    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertatbegin(22);

//    end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);

//    insertatbegin(1000);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertatend(7000);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertatend(30);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertatend(44);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertatbegin(50);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    insertafternode(head->next->next, 33);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    printf("Linked List: \n");

//    // print list
//    printList();
//    printf("\n");
//    deleteatbegin();
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    deleteatend();
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    deletenode(12);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    printf("\nLinked List after deletion: \n");

//    // print list
//    printList();
//    printf("\n");
//    insertatbegin(4);
//       end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
//    printList();
//    printf("\nUpdated Linked List: ");
//    printList();
//    printf("\n");

//    end_time = clock();

//    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

//    printf("Elapsed time: %f seconds\n", elapsed_time);
// }