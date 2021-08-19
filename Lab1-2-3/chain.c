#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int calculate_power(int b, int e);
node *find(chain *chn, int index);

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));
    int **temp = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++)
    {
        temp[i] = (int *)calloc(num_cols, sizeof(int));
    }

    mat->data = temp;
    mat->num_cols = num_cols;
    mat->num_rows = num_rows;
    return mat;
}

void add_row(matrix *mat, int *row)
{
    mat->data = (int **)realloc(mat->data, (mat->num_rows + 1) * sizeof(int *));
    mat->data[mat->num_rows] = row;
    mat->num_rows += 1;
}

void add_col(matrix *mat, int *col)
{
    int **temp_data = mat->data;
    for (int i = 0; i < mat->num_rows; i++)
    {
        temp_data[i] = (int *)realloc(temp_data[i], mat->num_cols + 1);
        temp_data[i][mat->num_cols] = col[i];
    }
    free(col);
    mat->num_cols += 1;
}

void increment(matrix *mat, int num)
{
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            mat->data[row_idx][col_idx] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            mat->data[row_idx][col_idx] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            mat->data[row_idx][col_idx] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    for (int row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (int col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            mat->data[row_idx][col_idx] = calculate_power(mat->data[row_idx][col_idx], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    for (int i = 0; i < mat->num_rows; i++)
    {
        free(mat->data[i]);
    }

    free(mat->data);
    free(mat);
}

int calculate_power(int b, int e)
{
    int power = 1;
    while (e > 0)
    {
        power = power * b;
        e--;
    }
    return power;
}
/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for (row_idx = 0; row_idx < mat->num_rows; ++row_idx)
    {
        for (col_idx = 0; col_idx < mat->num_cols; ++col_idx)
        {
            if (col_idx == mat->num_cols - 1)
            {
                printf("%d\n", mat->data[row_idx][col_idx]);
            }
            else
            {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below
void insert_node_before(chain *chn, int index, matrix *mat)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mat = mat;

    if (chn->head == NULL)
    {
        chn->head = newNode;
        newNode->prev = newNode;
        newNode->next = newNode;
    }
    else
    {
        node *current = (node *)find(chn, index);

        current->prev->next = newNode;
        newNode->prev = current->prev;
        current->prev = newNode;
        newNode->next = current;
    }
}

void insert_node_after(chain *chn, int index, matrix *mat)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mat = mat;

    if (chn->head == NULL)
    {
        chn->head = newNode;
        newNode->prev = chn->head;
        newNode->next = chn->head;
    }
    else
    {
        node *current = (node *)find(chn, index);

        current->next->prev = newNode;
        newNode->next = current->next;
        current->next = newNode;
        newNode->prev = current;
    }
}
node *find(chain *chn, int index)
{
    node *current = chn->head;
    if (index > 0)
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else if (index < 0)
    {
        for (int i = 0; i < index * (-1); i++)
        {
            current = current->prev;
        }
    }

    return current;
}

void delete_node(chain *chn, int index)
{
    node *current = (node *)find(chn, index);
    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current->mat);
    free(current);
}

void delete_list(chain *chn)
{
    node *head_next = chn->head->next;
    node *temp;
    while (head_next != chn->head)
    {
        temp = head_next->next;
        free(head_next);
        head_next = temp;
    }

    free(chn->head);
    chn->head = NULL;
}