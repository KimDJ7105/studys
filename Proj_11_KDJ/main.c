#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_JOBS 1000
#define TIME_SLOT 10
int job_wait(element item[], que_ADT* q, int t);
void job_dispatch(que_ADT* wq, que* rq);
void job_pross(que_ADT* wq, que* rq, int t,element* temp);

int done = 0;

int main() {
	que rq;	//준비 큐
	que_ADT wq;	//대기 큐
	element jobs[NUM_JOBS];
	int p_time = 1;
	int remain_job = NUM_JOBS;
	element operater;

	operater.job_id = -1;
	operater.arrival = -1;
	operater.priority = -1;
	operater.remaining = -1;
	operater.run_count = -1;
	operater.run_time = - 1;

	for (int i = 0; i < NUM_JOBS; i++) {
		jobs[i].priority = rand() % 10;
		jobs[i].arrival = rand();
		jobs[i].run_time = (rand() % 10 + 5) * 10;
		jobs[i].job_id = i;
		jobs[i].remaining = 0;
		jobs[i].run_count = 0;
	}

	init_Cir(&rq);

	wq.front = NULL;
	wq.rear = NULL;

	while (1) {
		
		remain_job -= job_wait(jobs, &wq, p_time);
		job_dispatch(&wq, &rq);
		job_pross(&wq, &rq, p_time, &operater);
		p_time++;
		if (remain_job == 0 && is_empty(&wq) == 1 && is_Cir_empty(&rq) == 1) break;
	}

	printf("완료\n");

	w_free(&wq);
}

int job_wait(element item[], que_ADT* q, int t) {
	int num = 0;
	
	for (int i = 0; i < NUM_JOBS; i++) {
		if (item[i].arrival == t) {
			enque(q, item[i]);
			num++;
		}
	}

	return num;
}

void job_dispatch(que_ADT* wq, que* rq) {
	int temp;
	L_que* n;

	if (is_empty(wq) != 1 && is_Cir_empty(rq)) {
		n = wq->front;
		temp = n->data.priority;

		while (n != NULL && n->data.priority == temp) {
			if (is_Cir_full(rq)) break;

			C_enque(rq, deque(wq));
			n = wq->front;
		}
	}
}

void job_pross(que_ADT* wq, que* rq, int t, element* temp) {

	if (is_Cir_empty(rq)) return;

	else {
		if (temp->job_id == -1) *temp = C_deque(rq);

		if (temp->run_time != 0) {
			temp->run_time--;
			temp->remaining++;
		}
		
		if (temp->run_time == 0) {
			printf("시간 : %d 작업 : %d 종료 (도착시간 : %d, 실행시간 : %d, 실행횟수 : %d, 지연시간 : %d, 최종우선순위 : %d )\n", t, temp->job_id, temp->arrival, temp->run_count * TIME_SLOT, temp->run_count, t - temp->arrival, temp->priority);
			*temp = C_deque(rq);
		}

		else if (temp->remaining == TIME_SLOT) {
			if (temp->priority > 0) --temp->priority;
			temp->run_count++;
			temp->remaining = 0;
			enque(wq, *temp);
			*temp = C_deque(rq);
		}
	}
}