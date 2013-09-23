#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */

void list_insert(const int i, struct node *head) {
	if ( head == NULL ) {
		// if the list is empty, malloc a new node and point head to it
		struct node *newnode = malloc(sizeof(struct node));
		newnode->n = i;
		newnode->next = NULL;

		head = newnode;
	} else {
		// else, insert the node in the list in order from least to greatest
		struct node *newnode = malloc(sizeof(struct node));
		newnode->n = i;
		
		// go through the list and find where the node should be inserted
		struct node *afterme = head;
		struct node *beforeme = head;
		while ( beforeme != NULL ) {
			if ( beforeme->n >= i ) {
			
			}
		}
	}
}
