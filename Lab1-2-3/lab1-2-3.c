// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain *chn);
void run(chain *chn);

int main()
{
    chain *chn = (chain *)malloc(sizeof(chain));
    chn->head = NULL;
    run(chn);
    print_chain(chn);
    free(chn);
    return 0;
}

// parse the input
void run(chain *chn)
{
    matrix *mat = (matrix *)malloc(sizeof(matrix));

    int rows;
    int columns = 0;
    scanf("%d\n", &rows);
    mat->num_rows = rows;
    char line[50];
    fgets(line, 50, stdin);
    char *token = strtok(line, " ");
    int *row = (int *)malloc(sizeof(int) * 50);

    while (token != NULL)
    {
        row[columns] = atoi(token);
        columns += 1;
        token = strtok(NULL, " ");
    }
    row = (int *)realloc(row, sizeof(int) * columns);
    int **data = (int **)malloc(rows * sizeof(int *));
    data[0] = row;
    for (int i = 1; i < rows; i++)
    {
        data[i] = (int *)calloc(columns, sizeof(int));
    }
    for (int i = 1; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            scanf("%d", &data[i][j]);
        }
    }
    matrix *temp;

    mat->data = data;
    mat->num_cols = columns;

    temp = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; i++)
    {
        for (int j = 0; j < mat->num_cols; j++)
        {
            temp->data[i][j] = mat->data[i][j];
        }
    }

    insert_node_before(chn, 0, temp);
    rows = chn->head->mat->num_rows;
    columns = chn->head->mat->num_cols;

    while (1)
    {
        int function;
        scanf("%d", &function);
        if (function == 0)
        {
            break;
        }

        int *row = (int *)malloc(sizeof(int) * columns);
        int *column = (int *)malloc(sizeof(int) * rows);
        int num;
        switch (function)
        {
        case 2:
            for (int i = 0; i < mat->num_cols; i++)
            {
                scanf("%d", &row[i]);
            }

            add_row(mat, row);
            break;
        case 3:
            for (int i = 0; i < mat->num_rows; i++)
            {
                scanf("%d", &column[i]);
            }
            add_col(mat, column);
            break;
        case 4:
            scanf("%d", &num);
            increment(mat, num);
            break;
        case 5:
            scanf("%d", &num);
            scalar_multiply(mat, num);
            break;
        case 6:
            scanf("%d", &num);
            scalar_divide(mat, num);
            break;
        case 7:
            scanf("%d", &num);
            scalar_power(mat, num);
            break;
        }

        temp = create_matrix(mat->num_rows, mat->num_cols);
        for (int i = 0; i < mat->num_rows; i++)
        {
            for (int j = 0; j < mat->num_cols; j++)
            {
                temp->data[i][j] = mat->data[i][j];
            }
        }
        insert_node_before(chn, 0, temp);
    }
}

//Print the chain
void print_chain(chain *chn)
{

    node *temp = chn->head;
    do
    {
        if (temp->next != chn->head)
        {
            print_matrix(temp->mat);
            printf("\n");
        }else
        {
            print_matrix(temp->mat);
        }
        
        temp = temp->next;
    } while (temp != chn->head);
}
