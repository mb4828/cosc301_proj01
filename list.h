#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */

struct node {
	int n;
	struct node *next;
};

/* your function declarations associated with the list */

void list_insert(const int i, struct node *head);

void list_print(struct node *head);

void list_clear(struct node *list);

#endif // __LIST_H__
