#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creatnum(int c, int seed) {
	int* num = (int*)malloc(c * sizeof(int));
	int temp;

	srand(seed);

	for (int i = 0; i < c;i++) {

		num[i] = rand();
	}

	for (int i = 0; i < c; i++) {
		for (int j = 0; j < i;j++) {
			if (num[j] < num[i]) {
				temp = num[j];
				num[j] = num[i];
				num[i] = temp;
			}
		}
	}

	free(num);

}

void creatnode(int c, int seed) {
	node* p;
	node* next;
	node* newnode;
	node* head = NULL;
	
	
	srand(seed);

	for (int i = 0; i < c; i++) {

		newnode = (node*)malloc(sizeof(node));
		newnode->num = rand();

		if (head != NULL) {
			p = head;
			next = p->link;

			if (newnode->num > p->num) {
				newnode->link = p;
				head = newnode;

			}

			else if (p->link == NULL) {
				 if (p->num >= newnode->num) {
					p->link = newnode;
				 }
			}

			else if (p->link != NULL) {
				while (p->link != NULL) {
					if (p->num >= newnode->num && newnode->num >= next->num) {
						p->link = newnode;
						newnode->link = next;
						break;
					}
					else {
						p = p->link;
						next = p->link;
					}
				}
			}

		}

		if (head == NULL) {
			head = newnode;
			head->link = NULL;
		}

	}

	while (head != NULL) {
		next = head;
		head = head->link;
		free(next);
	}
}