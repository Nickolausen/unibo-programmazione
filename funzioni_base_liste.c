/* ALCUNI ESERCIZI IN PREPARAZIONE ALL'ESAME ORALE */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node1 {
    int row;
    int col;
    struct Node1 *next;
} Node1;

typedef struct Node2 {
    int element;
    struct Node2 *next;
} Node2;

typedef struct SecondNode {
    struct SecondNode *inner_list;
    struct SecondNode *next;
} SecondNode;

bool is_empty(Node2 *list)
{
    return list == NULL;
}

int **crea_matrice(int nr_righe, int nr_colonne) 
{
    int **matrix = (int **)malloc(sizeof(int *) * nr_righe);
    assert(matrix != NULL);

    for (int row = 0; row < nr_righe; row++) 
    {
        matrix[row] = (int *)calloc(nr_colonne, sizeof(int));
        assert(matrix[row] != NULL);
    }

    return matrix;
}

void print_matrix(int **matrix, int nr_righe, int nr_col)
{
    for (int row = 0; row < nr_righe; row++) 
    {
        for (int col = 0; col < nr_col; col++) 
        {
            printf("%d ", matrix[row][col]);
        }
        puts("");
    }
}

void free_matrix(int **matrix, int nr_righe) 
{
    for (int row = 0; row < nr_righe; row++) 
    {
        free(matrix[row]);
    }

    free(matrix);
}

void free_recursive_matrix(int **matrix, int nr_righe) 
{
    static int idx = 0;
    if (idx >= nr_righe) 
    {
        idx = 0;
        free(matrix);
        return;
    }

    free(matrix[idx++]);

    free_recursive_matrix(matrix, nr_righe);
}

void inverti_lista(Node1 **lista) 
{
    Node1 *current_node = *lista;
    Node1 *prev_node = NULL;

    while (current_node != NULL) 
    {
        Node1 *prev_next = current_node->next;

        current_node->next = prev_node;
        prev_node = current_node;

        current_node = prev_next;
    }

    *lista = prev_node;
}

void recursive_inverti_lista(Node1 **list) 
{
   
}

/* Crea una Linked List di nodi contenenti riga e colonna della matrice con corrispondente cella == 1 */
Node1 *crea_lista(int **matrix, int n_row, int n_col)
{
    Node1 *out_list = NULL;

    for (int row = 0; row < n_row; row++) 
    {
        for (int col = 0; col < n_col; col++) 
        {
            if (matrix[row][col] == 1)
            {
                Node1 *new_element = (Node1 *)malloc(sizeof(Node1));
                assert(new_element != NULL);

                new_element->row = row;
                new_element->col = col;

                /* HEAD INSERT linked list */
                new_element->next = out_list;
                out_list = new_element;
            }
        }
    }

    return out_list;
}

void free_list(Node1 **list)
{
    while (*list != NULL) 
    {
        Node1 *next = (*list)->next;

        free(*list);
        *list = next;
    }
}

void free_recursive_list(Node1 **list)
{
    if (*list == NULL) return;

    Node1 *next = (*list)->next;
    free(*list);

    free_recursive_list(&next);
}

/* 
 * Data una lista di liste, l'obiettivo è 'appiattire' tutta la struttura su un unico livello. 
 */
void flatten_list(SecondNode **list)
{
    /* ... */
}

void aggiungi_nodo(Node2 **list, Node2 *node) 
{
    if (*list == NULL) {
        *list = node;
        return; 
    }

    Node2 *current_node = *list;
    Node2 *prev_node = NULL;

    while (current_node != NULL) 
    {
        if (node->element <= current_node->element)
            break;
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    node->next = current_node;

    if (prev_node != NULL)
        prev_node->next = node;
    else
        *list = node;
}

void tail_insert(Node2 **list, Node2 *node)
{
    if (is_empty(*list))
    {
        *list = node;
        return;
    }

    Node2 *current_node = *list;
    Node2 *prev_node = NULL;

    while (current_node != NULL) 
    {
        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = node;
}

Node2 *genera_lista_esempio(int nr_nodi) 
{
    static int idx = 0;
    idx++;
    srand(time(NULL));
    Node2 *out_list = NULL;

    for (int i = 0; i < nr_nodi; i++) 
    {
        Node2 *new_node = (Node2 *)malloc(sizeof(Node2));
        assert(new_node != NULL);

        if (idx % 2 == 0)
            new_node->element = 2 * i + 1;
        else
            new_node->element = 2 * i;

        new_node->next = NULL;

        aggiungi_nodo(&out_list, new_node);
    }

    return out_list;
}

void print_list(Node2 *list) 
{
    if (is_empty(list)) 
    {
        printf("List is empty!\n");
        return;
    }    

    Node2 *current_node = list;
    int idx = 0;
    while (current_node != NULL) 
    {
        printf("[%d], Value: %d\n", idx++, current_node->element);
        current_node = current_node->next;
    }

    putchar('\n');
}

/* Date due linked list ORDINATE per 'elemento' CRESCENTE, effettuare il merge sulla lista1 */
void merge_list(Node2 **list1, Node2 *list2) 
{
    /* Il merge funziona!! Manca solo l'ordinamento */
    Node2 *p_first_list = *list1;
    Node2 *p_second_list = list2; 

    while (p_first_list != NULL && p_second_list != NULL) 
    {
        if (p_first_list->element <= p_second_list->element)
        {
            Node2 *prev_next = p_first_list->next;
            Node2 *prev_next2 = p_second_list->next;

            p_first_list->next = p_second_list;
            p_second_list->next = prev_next;

            p_first_list = prev_next;
            p_second_list = prev_next2;
        }
        else 
        {
            p_first_list = p_first_list->next;
        }
    }
}

Node2 *create_node(int value) 
{
    Node2 *output = (Node2 *)malloc(sizeof(Node2));
    output->element = value;
    output->next = NULL;

    return output;
}

int main() 
{
    int n_col = 10, n_row = 10;

    int **matrix = crea_matrice(n_row, n_col);
    // print_matrix(matrix, n_row, n_col);

    Node2 *list1 = genera_lista_esempio(5);
    // aggiungi_nodo(&list1, create_node(1));
    // aggiungi_nodo(&list1, create_node(3));
    // aggiungi_nodo(&list1, create_node(4));
    // aggiungi_nodo(&list1, create_node(5));

    Node2 *list2 = genera_lista_esempio(10);
    // aggiungi_nodo(&list2, create_node(2));
    // aggiungi_nodo(&list2, create_node(3));
    // aggiungi_nodo(&list2, create_node(7));

    printf("=== BEFORE merge:\n\n");
    printf("> LIST 1: \n");
    print_list(list1);
    printf("> LIST 2: \n");
    print_list(list2);

    merge_list(&list1, list2);

    printf("=== AFTER merge:\n\n");
    printf("> LIST 1: \n");
    print_list(list1);
    printf("> LIST 2: \n");
    print_list(list2);

    return 0;
}