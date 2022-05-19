#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUE_SIZE 100

typedef int element;

typedef struct _Queque {
	element data[MAX_QUE_SIZE];
	int front, rear;
} QueueType;

void init_Queue(QueueType* q) {
	q->front = 0; q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		printf("큐 포화 오류\n");
		return;
	}

	q->rear = (q->rear + 1) % MAX_QUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q)) {
		printf("큐 공백 오류\n");
		return;
	}

	q->front = (q->front + 1) % MAX_QUE_SIZE;
	return q->data[q->front];
}