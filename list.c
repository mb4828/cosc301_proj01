#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void list_insert(const int i, struct node **head) {
	struct node *newnode = malloc(sizeof(struct node));
	newnode->n = i;
	newnode->next = NULL;

	if ( *head == NULL ) {
		*head = newnode;
	}
	else if ((*head)->next == NULL) {
		if (i < (*head)->n) {
			newnode->next = *head;
			*head = newnode;
		}
		else {
			(*head)->next = newnode;
		}

	} else {
		struct node *tmp = *head;
		while (tmp != NULL) {
			if (tmp->next == NULL) {
				tmp->next = newnode;
				break;
			}
			if (i >= tmp->n && i <= tmp->next->n) {
				newnode->next = tmp->next;
				tmp->next = newnode;
				break;
			}
			tmp = tmp->next;
		}
	}
}

void list_print(struct node *head) {
	while (head != NULL){
		printf("%i\n", head->n);
		head = head->next;
	}
}

void list_clear(struct node *list) {
	while (list != NULL) {
		struct node *tmp = list;
		list = list->next;
		free(tmp);
	}
}
