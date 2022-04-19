#include <stdio.h>
#include <stdlib.h>

typedef struct _position {
	int x;
	int y;
	int z;
} element;

typedef struct _Queue {
	element data;
	struct _Queue* link;
} QueNode;

typedef struct {
	QueNode* front;
	QueNode* rear;
} LinkedQue;

void init_LinkedQue(LinkedQue* q) {
	q->front = NULL;
	q->rear = NULL;
}

int is_empty(LinkedQue* q) {
	if (q->front == q->rear&& q->front == NULL) return 1;

	else return 0;
}

int is_full(LinkedQue* q) {
	return 0;
}

void error() {
	printf("메모리 할당 오류\n");

	exit(1);
}

void enqueue(LinkedQue* q, element item) {
	QueNode* newnode;

	newnode = (QueNode*)malloc(sizeof(QueNode));

	if (newnode == NULL) error();

	else {
		newnode->data.x = item.x;
		newnode->data.y = item.y;
		newnode->data.z = item.z;
		newnode->link = NULL;
	}

	if (is_empty(q) == 1) {
		q->rear = newnode;
		q->front = newnode;
	}

	else {
		q->rear->link = newnode;

		q->rear = q->rear->link;
	}
}

element dequeue(LinkedQue* q) {
	element temp;
	QueNode* prev_t;

	if (is_empty(q) == 1) {

		temp.x = INT_MIN;
		temp.y = INT_MIN;
		temp.z = INT_MIN;
	}

	else {
		temp = q->front->data;
		prev_t = q->front;

		q->front = q->front->link;

		if (q->front == NULL) q->rear = NULL;

		free(prev_t);
	}

	return temp;
}

element peek(LinkedQue* q) {
	if (is_empty(q) == 1) {
		element temp = { INT_MIN, INT_MIN, INT_MIN };

		return temp;
	}

	else return q->front->data;
}

void print_queue(LinkedQue* q) {
	QueNode* temp;

	printf("=====큐 내용=====\n");

	if (is_empty(q) == 1) printf("큐 공백상태\n");

	else {

		temp = q->front;

		while (temp->link != NULL) {
			printf("x : %d y: %d z : %d", temp->data.x, temp->data.y, temp->data.z);

			if (temp == q->front && temp == q->rear) printf("  <----front,rear");

			else if (temp == q->front) printf(" <----front");

			else if (temp == q->rear) printf("  <----rear");

			printf("\n");

			temp = temp->link;
		}

		printf("x : %d y: %d z : %d", temp->data.x, temp->data.y, temp->data.z);

		if (temp == q->front && temp == q->rear) printf("  <----front,rear");

		else if (temp == q->front) printf(" <----front");

		else if (temp == q->rear) printf("  <----rear");

		printf("\n");
	}

	printf("==================\n");
}

void clean_Que(LinkedQue* q) {
	if (is_empty(q) == 1) printf("메모리 해제 완료\n");

	else {
		QueNode* temp;

		while (q->front != NULL) {
			temp = q->front;
			q->front = q->front->link;

			free(temp);
		}

		printf("메모리 해제 완료\n");
	}
}

