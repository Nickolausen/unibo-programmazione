/* ALCUNI ESERCIZI IN PREPARAZIONE ALL'ESAME ORALE */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int row;
    int col;
    struct Node *next;
} Node;

typedef struct SecondNode {
    struct SecondNode *inner_list;
    struct SecondNode *next;
} SecondNode;

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

void inverti_lista(Node **lista) 
{
    Node *current_node = *lista;
    Node *prev_node = NULL;

    while (current_node != NULL) 
    {
        Node *prev_next = current_node->next;

        current_node->next = prev_node;
        prev_node = current_node;

        current_node = prev_next;
    }

    *lista = prev_node;
}

/* Crea una Linked List di nodi contenenti riga e colonna della matrice con corrispondente cella == 1 */
Node *crea_lista(int **matrix, int n_row, int n_col)
{
    Node *out_list = NULL;

    for (int row = 0; row < n_row; row++) 
    {
        for (int col = 0; col < n_col; col++) 
        {
            if (matrix[row][col] == 1)
            {
                Node *new_element = (Node *)malloc(sizeof(Node));
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

void free_list(Node **list)
{
    while (*list != NULL) 
    {
        Node *next = (*list)->next;

        free(*list);
        *list = next;
    }
}

void free_recursive_list(Node **list)
{
    if (*list == NULL) return;

    Node *next = (*list)->next;
    free(*list);

    free_recursive_list(&next);
}

/* 
 * Data una lista di liste, l'obiettivo è 'appiattire' tutta la struttura su un unico livello. 
 */
void flatten_list(SecondNode **list)
{
    
}

void merge_list(Node **list1, Node **list2) 
{
    Node *second_list = *list2;

    while (second_list != NULL) 
    {
        Node *current_first_list = *list1;
        Node *prev_first_list = NULL;

        while (current_first_list != NULL)
        {
            if (current_first_list->row < second_list->row || 
                (current_first_list->row == second_list->row && current_first_list->col < second_list->col)) 
                break;
            
            if (prev_first_list == NULL)
            {
                printf("");
            } else 
            {
                prev_first_list->next = second_list;
                second_list->next = current_first_list;
            }

            current_first_list = current_first_list->next;
        }


        second_list = second_list->next;
    }
}

int main() 
{
    int n_col = 10, n_row = 10;

    int **matrix = crea_matrice(n_row, n_col);
    print_matrix(matrix, n_row, n_col);

    return 0;
}