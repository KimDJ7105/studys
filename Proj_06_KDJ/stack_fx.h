#define MAX_STACK_SIZE 101
#include <stdio.h>
#include <stdlib.h>


typedef union mod {
	int data;
	char oper;
}element;

typedef struct _stack {

	element slot[MAX_STACK_SIZE];
	int top;
} s_type;

void init_stack(s_type* s);
int is_empty(s_type* s);
int is_full(s_type* s);
char pop_oper(s_type* s);
int pop_data(s_type* s);
char peek_oper(s_type* s);
int pop_data(s_type* s);
void push_oper(s_type* s, char item);
void push_data(s_type* s, int item);

void init_stack(s_type* s) {
	s->top = -1;
}

int is_empty(s_type* s) {
	if (s->top == -1) return 1;

	else return 0;
}

int is_full(s_type* s) {
	if (s->top == MAX_STACK_SIZE - 1) return 1;

	else return 0;
}

char pop_oper(s_type* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 에러\n");
		exit(1);

		return 0;
	}

	else return s->slot[(s->top)--].oper;
}

int pop_data(s_type* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 에러\n");
		exit(1);

		return 0;
	}

	else return s->slot[(s->top)--].data;
}

char peek_oper(s_type* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 에러\n");
		exit(1);
		return 0;
	}

	else return s->slot[s->top].oper;
}

int peek_data(s_type* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 에러\n");
		exit(1);
		return 0;
	}

	else return s->slot[s->top].data;
}

void push_oper(s_type* s, char item) {
	if (is_full(s) == 1) {
		printf("스택 포화 에러\n");
		exit(1);
	}

	else {
		s->slot[++(s->top)].oper = item;
	}
}

void push_data(s_type* s, int item) {
	if (is_full(s) == 1) {
		printf("스택 포화 에러\n");
		exit(1);
		return 0;
	}

	else {
		s->slot[++(s->top)].data = item;
	}
}