#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 50
#define WORK_TIME 10000

typedef int element;

typedef struct _queue {
	element order[MAX_QUEUE_SIZE];
	int rear;
	int front;
} queue;

typedef struct prosser {
	int working;
	int busy;
	int task;
} server;

void init_queue(queue* q);
int is_full(queue* q);
int is_empty(queue* q);
void enqueue(queue* q, element item);
element dequeue(queue* q);


void init_server(server* s);
int is_busy(server* s);
void make_working(server* s, int tm);


int main() {
	int _time = 0;
	server serv1, serv2;
	queue q;
	element menu;
	int temp_menu;
	int cancled = 0;
	int menu_counter[5] = {0,0,0,0,0};
	int menu_timer[5] = {0,0,0,0,0};
	int server1_playtime = 0;
	int server2_playtime = 0;

	srand(time(NULL));

	init_server(&serv1);
	init_server(&serv2);

	init_queue(&q);

	while (_time < WORK_TIME) {
		if (serv1.busy == 0) server1_playtime++;
		if (serv2.busy == 0) server2_playtime++;

		if (_time % 5 == 0) {

			if (is_full(&q) == 1) {
				cancled++;
			}

			else {
				menu = rand() % 5;

				menu_counter[menu]++;

				menu_timer[menu] += _time;

				enqueue(&q, menu);
			}
		}

		if (is_busy(&serv1) == 0 && is_empty(&q) == 0) {
			temp_menu = dequeue(&q);

			make_working(&serv1, temp_menu);
			serv1.task = temp_menu;
			serv1.busy = 1;
		}

		else if (is_busy(&serv1) == 1 && serv1.working == 0) {
			menu_timer[serv1.task] -= _time;
			serv1.busy = 0;
		}

		if (is_busy(&serv2) == 0 && is_empty(&q) == 0) {
			temp_menu = dequeue(&q);

			make_working(&serv2, temp_menu);
			serv2.task = temp_menu;
			serv2.busy = 1;
		}

		else if (is_busy(&serv2) == 1 && serv2.working == 0) {
			menu_timer[serv2.task] -= _time;
			serv2.busy = 0;
		}

		_time++;
		serv1.working--;
		serv2.working--;
	}

	printf("=========== Results ============\n");
	for (int i = 0; i < 5; i++) {
		float f = (float)menu_timer[i]/ menu_counter[i];
		printf("MENU %d : %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f\n", i,menu_counter[i],menu_timer[i],f);
	}
	printf("취소된 횟수 : %d\n", cancled);
	printf("서버1과 서버2 휴식시간 : %d %d\n", server1_playtime, server2_playtime);

}

void init_queue(queue* q) {
	q->rear = 0;
	q->front = 0;
}

int is_full(queue* q) {
	if (q->front == (q->rear + 1) % MAX_QUEUE_SIZE) return 1;
	
	else return 0;
}

int is_empty(queue* q) {
	if (q->front == q->rear) return 1;

	else return 0;
}

void enqueue(queue* q, element item) {
	
	if (is_full(q) == 1) {
		printf("큐 포화 오류");
		exit(1);
	}

	if (q->rear < (MAX_QUEUE_SIZE - 1) ) {
		q->order[++(q->rear)] = item;
	}

	else if (q->rear == (MAX_QUEUE_SIZE - 1)) {
		q->rear = 1;
		q->order[q->rear] = item;
	}
}

element dequeue(queue* q) {
	if (is_empty(q) == 1) {
		printf("큐 공백 오류");
		exit(1);
	}

	if (q->front < (MAX_QUEUE_SIZE - 1)) return q->order[++(q->front)];

	else if (q->front == (MAX_QUEUE_SIZE - 1)) {
		q->front = 1;
		return q->order[q->front];
	}
}

void init_server(server* s) {
	s->working = 0;
	s->busy = 0;
}

int is_busy(server* s) {
	return s->busy;
}

void make_working(server* s, int tm) {
	if (tm == 0) {
		s->working = 5;
	}

	else if (tm == 1) {
		s->working = 10;
	}

	else if (tm == 2) {
		s->working = 15;
	}

	else if (tm == 3) {
		s->working = 20;
	}

	else if (tm == 4) {
		s->working = 25;
	}
}
