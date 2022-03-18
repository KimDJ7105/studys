#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addNode(node** head, int id, char name[]) {	//head는 node **p->link

	node* p = *head;
	node* newnode = (node*)malloc(sizeof(node));


	if (newnode == NULL) {
		printf("동적할당 오류\n");
		exit(1);
	}


	newnode->id = id;
	strcpy(newnode->name, name);
	newnode->link = NULL;

	if (*head == NULL) {

		*head = newnode;
	}

	else {
		while (p->link != NULL) {

			p = p->link;
		}
		//while (p->link) p = p->link;

		p->link = newnode;
	}


}


node* searchNode(node* p, int id) {

	if (p->link == NULL) {

		if (p->id == id) {

			return p;
		}
	} //필요없는 공정

	else {
		while (p->link != NULL) {

			if (p->id == id) {

				return p;
			}

			p = p->link;

		}
	}
}


node* deleteNode(node* p, int id) { //첫번째 노드 삭제시에 head가 변동되므로 node **필요

	node* n = p;

	if (p->link == NULL) {
		if (p->id == id) {
			return p;
		}
	}

	else {
		while (p->link != NULL) {

			if (p->id == id) {

				if (p->link != NULL) {

					n->link = p->link;
				}

				return p;
			}

			else {
				n = p;
			}
			p = p->link;
		}

		if (p->link == NULL) {
			if (p->id == id) {
				n->link = NULL;
				return p;
			}
		}
	}
}

void printNode(node* p) {

	if (p->link == NULL) {
		printf("%d, %s\n", p->id, p->name);
	}

	else {
		printf("%d, %s\n", p->id, p->name);
		while (p->link != NULL) {
			p = p->link;
			printf("%d, %s\n", p->id, p->name);
		}

	}
}

void freeAllNode(node* p) {
	node* next;

	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
}