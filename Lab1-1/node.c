// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h>	// includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:
node *find(list *lst, int index);
// implementation
void insert_node_before(list *lst, int index, char *word)
{
	
	node *newNode = (node *)malloc(sizeof(node));
	newNode->word = word;

	if (lst->head == NULL)
	{
		lst->head = newNode;
		newNode->prev = newNode;
		newNode->next = newNode;
	}
	else
	{
		node *current = (node*) find(lst,index);


		current->prev->next = newNode;
		newNode->prev = current->prev;
		current->prev = newNode;
		newNode->next = current;
		
		
	}
}

void insert_node_after(list *lst, int index, char *word)
{
	node *newNode = (node *)malloc(sizeof(node));
	newNode->word = word;

	if (lst->head == NULL)
	{
		lst->head = newNode;
		newNode->prev = lst->head;
		newNode->next = lst->head;
	}
	else
	{
		node *current = (node*) find(lst,index);
		
		current->next->prev = newNode;
		newNode->next = current->next;
		current->next = newNode;
		newNode->prev = current;
	}
}
node *find(list *lst, int index)
{
	node *current = lst->head;
	if (index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
	}
	else if (index<0)
	{
		for (int i = 0; i < index * (-1); i++)
		{
			current = current->prev;
		}
	}

	return current;
}

char *list_to_sentence(list *lst)
{
	char * sentense = (char*) malloc(sizeof(char)* 100);
	strcpy(sentense,"");
	node * temp = lst->head;
	do{
		if (temp->next != lst->head){
			// printf("%s ",temp->word);
			strcat(sentense,temp->word);
			strcat(sentense," ");
		}else
		{
			// printf("%s",temp->word);
			strcat(sentense,temp->word);
			strcat(sentense,"");
		}
		
		
		temp = temp->next;
	} while(temp != lst->head);
	return sentense; // Change this line accordingly
}

void delete_node(list *lst, int index)
{
	node *current = (node*)find(lst,index);
	current->prev->next = current->next;
	current->next->prev = current->prev;

	free(current->word);
	free(current);

}

void delete_list(list *lst)
{
	node *head_next = lst -> head->next;
	node *temp;
	while(head_next!= lst->head){
		temp = head_next->next;
		free(head_next);
		head_next = temp;
	}

	free(lst->head);
	lst->head = NULL;
}
