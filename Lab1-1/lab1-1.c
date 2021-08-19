// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list *lst);
void run(list *lst);

int main()
{
    list *lst = (list *)malloc(sizeof(list));
    lst->head = NULL;
    run(lst);
    print_list(lst);
    free(lst);
    return 0;
}

// parse the input
void run(list *lst)
{
    char *str = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH);
    while (1)
    {
        scanf("%20[^,\n]", str);
        insert_node_before(lst, 0, str);
        char temp;
        scanf("%c", &temp);
        if (temp == '\n')
        {
            break;
        }
        str = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH);
    }

    while (1)
    {
        int command;
        scanf("%d", &command);
        if (command == 0)
        {
            break;
        }
        int index;
        char *parameters = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH) ;
        switch (command)
        {
        case INSERT_BEFORE:
            scanf("%d %s\n",&index,parameters);
            insert_node_before(lst,index,parameters);
            break;

        case INSERT_AFTER:
            scanf("%d %s\n",&index,parameters);
            insert_node_after(lst,index,parameters);
            break;
        case DELETE_NODE:
            scanf("%d\n",&index);
            delete_node(lst,index);
            break;
        case DELETE_LIST:
            delete_list(lst);
            break;
        default:
            break;
        }
       
    }

}

//Print the list contents
void print_list(list *lst)
{
    char * sentense = list_to_sentence(lst);
    printf("%s\n",sentense);
    free(sentense);
}
