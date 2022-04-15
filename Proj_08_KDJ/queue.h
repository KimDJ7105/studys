#include <stdio.h>

#define MAX_QUE_SIZE 10000

typedef int element;

typedef struct _queue {
	element data[MAX_QUE_SIZE];
	int front;
	int rear;
} que;

void init_que(que* q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty(que* q) {
	if (q->front == q->rear) return 1;

	else return 0;
}

int is_full(que* q) {
	if ((q->rear + 1) % MAX_QUE_SIZE == q->front) return 1;

	else return 0;
}

void enque(que* q, element item) {
	if (is_full(q) == 1) {
		printf("큐 포화상태\n");
	}

	else {
		q->rear = (q->rear + 1) % MAX_QUE_SIZE;
		q->data[q->rear] = item;
	}
}

element deque(que* q) {
	if (is_empty(q) == 1) {
		printf("큐 공백상태\n");
	}

	else {
		q->front = (q->front + 1) % MAX_QUE_SIZE;
		return q->data[q->front];
	}
}

typedef struct _stack{
	element data[MAX_QUE_SIZE];
	int top;
} stk;

int is_stk_full(stk* s) {
	return s->top == (MAX_QUE_SIZE -1);
}

int is_stk_empty(stk* s) {
	return s->top == -1;
}

void init_stk(stk* s) {
	s->top = -1;
}

void push(stk* s, element item) {
	if(is_stk_full(s)) printf("스택 포화 오류");

	else {
		++s->top;

		s->data[s->top] = item;
	}

}

element pop(stk* s) {
	if(is_stk_empty(s)) {
		printf("스택 공백 오류");
		return 0;
	}

	else {
		return s->data[(s->top)--];
	}
}

element peek(stk* s) {
	if(is_stk_empty(s)){
		printf("스택 공백 오류");
		return 0;
	}

	else return s->data[s->top];
}