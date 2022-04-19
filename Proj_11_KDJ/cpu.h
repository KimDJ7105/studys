#include <stdio.h>
#include <stdlib.h>

#define MAX_CIR_QUE 10

typedef struct _Element {
	int job_id;		//작업 번호
	int priority;	//우선순위
	int arrival;	//시작 시간
	int run_time;	//필요 시간
	int remaining;	//지연 시간
	int run_count;	//실행 횟수
} element;

typedef struct Queque {
	element data[MAX_CIR_QUE];
	int fornt, rear;
} que;

int is_Cir_empty(que* q) {
	return (q->fornt == q->rear);
}

int is_Cir_full(que* q) {
	return ((q->rear + 1) % MAX_CIR_QUE == q->fornt);
}

void init_Cir(que* q) {
	q->fornt = 0;
	q->rear = 0;

	for (int i = 0;i < MAX_CIR_QUE; i++) {
		q->data[i].arrival = -1;
		q->data[i].job_id = -1;
		q->data[i].priority = -1;
		q->data[i].remaining = 0;
		q->data[i].run_count = -1;
		q->data[i].run_time = -1;
	}
}

void C_enque(que* q, element* item) {
	if (is_Cir_full(q)) {
		
	}

	else {
		q->rear = (q->rear + 1) % MAX_CIR_QUE;

		q->data[q->rear] = *item;
		free(item);
	}
}

element C_deque(que* q) {
	if (is_Cir_empty(q)) printf("원형 큐 공백 오류");

	else {
		
		q->fornt = (q->fornt + 1) % MAX_CIR_QUE;

		return q->data[q->fornt];
	}
}

typedef struct _LISTQUE {
	element data;
	struct _LISTQUE* link;
} L_que;

typedef struct LIST {
	L_que* front, *rear;
}que_ADT;

void enque(que_ADT* q, element item) {
	L_que* temp = (L_que*)malloc(sizeof(L_que));
	L_que* n;
	L_que* p;

	temp->data = item;
	temp->link = NULL;

	if (is_empty(q) == 1) {
		q->front = temp;
		q->rear = temp;
	}

	else {
		n = q->front;

		if (temp->data.priority > n->data.priority) {
			temp->link = n;
			q->front = temp;
		}

		else {
			while (n->link != NULL) {
				p = n->link;

				if (temp->data.priority >= p->data.priority) {
					temp->link = p;
					n->link = temp;

					break;
				}

				n = p;
			}

			if (n == q->rear) {
				q->rear->link = temp;
				q->rear = temp;
			}
		}
	}
}

element* deque(que_ADT* q) {
	L_que* temp = q->front;

	element* data;

	data = (element*)malloc(sizeof(element));

	if (is_empty(q) == 1) {
		printf("리스트 큐 공백 오류");
	}

	else {
		*data = temp->data;
		q->front = q->front->link;

		if (q->front == NULL) q->rear = NULL;

		free(temp);

		return data;
	}
}

int is_empty(que_ADT* q) {
	if (q->front == NULL) return 1;

	else return 0;
}

void w_free(que_ADT* q) {
	L_que* n,*temp;
	n = q->front;

	while (n != NULL) {
		temp = n;
		n = n->link;
		free(temp);
	}
}