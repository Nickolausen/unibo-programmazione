#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node {
    int value;
    struct node *next;
} node;

void push(node **list, int el) 
{
    node *new = (node *)malloc(sizeof(node));
    assert(new != NULL);

    /* init new node */
    new->value = el;

    new->next = *list;
    *list = new;
}

node* pop(node **list) 
{
    node *tmp = *list;
    *list = (*list)->next;

    /* 'stacco' l'elemento dallo stack */
    tmp->next = NULL;

    return tmp;
}

void print_list(node *list) 
{
    node *current = list;
    while (current != NULL) 
    {
        printf("Node value: %d\n", current->value);
        current = current->next;
    }
}

int main() 
{
    // node *list = NULL;
    // for (int i = 0; i < 10; i++) 
    // {
    //     push(&list, i);
    // }

    // print_list(list);
    // printf("== Pop: %d ==\n", pop(&list)->value);
    // printf("== Pop: %d ==\n", pop(&list)->value);
    // printf("== Pop: %d ==\n", pop(&list)->value);
    // print_list(list);

    int A[2][2] = {{1,2},{3,4}};
    int (*p)[1] = A;
    printf("%d %d %d %d", p[0][0], p[0][1], p[1][0], p[1][1]);

    return 0;
}