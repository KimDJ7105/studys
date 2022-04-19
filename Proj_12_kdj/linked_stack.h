#include <stdio.h>
#include <stdlib.h>

typedef struct _position {
	int x;
	int y;
	int z;
} element;

typedef struct _stack {
	element data;
	struct _stack* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStack;

void init_LinkedStack(LinkedStack* s) {
	s->top = NULL;
}

int is_empty(LinkedStack* s) {
	if (s->top == NULL) return 1;

	else return 0;
}

int is_full(LinkedStack* s) {
	return 0;
}

void error() {
	printf("메모리 할당 오류\n");

	exit(1);
}

void push(LinkedStack* s, element item) {
	StackNode* newnode;

	newnode = (StackNode*)malloc(sizeof(StackNode));

	if (newnode == NULL) error();

	else {
		newnode->data.x = item.x;
		newnode->data.y = item.y;
		newnode->data.z = item.z;
		newnode->link = NULL;
	}

	if (s->top == NULL) s->top = newnode;

	else {
		newnode->link = s->top;

		s->top = newnode;
	}
}

element pop(LinkedStack* s) {
	element temp;
	StackNode* prev_t;

	if (is_empty(s) == 1) {
		temp.x = INT_MIN;
		temp.y = INT_MIN;
		temp.z = INT_MIN;
	}

	else {
		temp = s->top->data;
		prev_t = s->top;

		s->top = s->top->link;

		free(prev_t);
	}

	return temp;
}

element peek(LinkedStack* s) {
	if (is_empty(s) == 1) {
		element temp = { INT_MIN, INT_MIN, INT_MIN };

		return temp;
	}

	else return s->top->data;
}

void print_stack(LinkedStack* s) {
	StackNode* temp;

	printf("=====스택 내용=====\n");

	if (s->top == NULL) printf("스택 공백상태\n");

	else {

		temp = s->top;

		while (temp->link != NULL) {
			printf("x : %d y: %d z : %d", temp->data.x, temp->data.y, temp->data.z);
			if (temp == s->top) printf("  <---top");

			printf("\n");
			temp = temp->link;
		}

		printf("x : %d y: %d z : %d", temp->data.x, temp->data.y, temp->data.z);
		if (temp == s->top) printf("  <---top");

		printf("\n");
	}

	printf("==================\n");
}

void clean_stack(LinkedStack* s) {
	if (s->top == NULL) printf("메모리 해제 완료\n");

	else {
		StackNode* temp;

		while (s->top != NULL) {
			temp = s->top;
			s->top = s->top->link;

			free(temp);
		}

		printf("메모리 해제 완료\n");
	}
}

