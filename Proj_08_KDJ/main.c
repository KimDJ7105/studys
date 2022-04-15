#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "queue.h"

#define PROB 1

#if PROB == 1

int check_mul(int ch[MAX_QUE_SIZE], int n, int item);

int main() {
	que q;
	int num;	//바이러스 마리수를 저장할 인수
	int tm = 1;		//시간을 저장할 인수
	int taget_num,result = 0;		//구하고자 하는 바이러스의 마리수
	int check[MAX_QUE_SIZE] = {0,}, n = 0;
	int save[MAX_QUE_SIZE];
	int temp, j = 0,what;
	
	init_que(&q);
	enque(&q, 1);
	printf("목표 바이러스 수 입력 : ");
	scanf("%d", &taget_num);

	while (is_full(&q) == 0) {

		while (is_empty(&q) == 0) {
			temp = deque(&q);
			what = check_mul(check, n, temp);
			if (what == 1) {
				++n;
				if (n == MAX_QUE_SIZE) {
					printf("큐가 포화상태입니다.\n");
					return 0;
				}
				check[n] = temp;
				save[j++] = temp;
			}
		}

		for (int i = 0; i < j; i++) {
			temp = save[i] * 2;
			enque(&q, temp);
			
			if (temp == taget_num) {
				result = 1;
			}

			temp = save[i] / 3;
			enque(&q, temp);

			if (temp == taget_num) {
				result = 1; 
			}
		}

		if (result == 1) break;

		else {
			j = 0;
			++tm;
		}	
	}

	if (result == 1) printf("%d마리가 되는데 필요한 시간 : %d", taget_num, tm);

	else printf("큐가 포화상태입니다.\n");

}

int check_mul(int ch[MAX_QUE_SIZE], int n, int item) {

	int count = 0;

	for (int i = 0; i < n + 1 ;i++) {
		if (item == ch[i]) {
			++count;
		}
	}

	if (count == 0) return 1;

	else return 0;
}

#elif PROB == 2

int main() {	//사람의 숫자만큼 큐에 집어넣고 전부 뺀 뒤에 k번째를 죽이고, 다시 넣기를 반복

	que q;
	int n, k, count = 0,k_count = 1, remeber;
	int num[MAX_QUE_SIZE];

	init_que(&q);

re:

	printf("참여하는 사람 수 n과 선택하는 k값 입력 :");
	scanf("%d %d", &n, &k);

	if (n < 1) {
		printf("n은 1보다 크거나 같아야 합니다.\n");
		goto re;
	}
	if (k<1 || k>n) {
		printf("k는 1보다 크거나 같고 n보다 작거나 같아야 합니다.\n");
		goto re;
	}
	
	for (int i = 1; i <= n; i++) { //큐에 사람을 순서대로 넣음
		enque(&q, i);
	}
	printf("선택된 사람의 번호 : ");
	while (!is_empty(&q)) {

		for (int i = 0; i < k - 1;i++) {
			enque(&q, deque(&q));
		}
		
		remeber = deque(&q);

		printf("%d ", remeber);
		count = 0;
		k_count = 1;
	}

	printf("\n최종 살아남은 사람은 %d 위치에 줄을 선 사람임", remeber);
}

#elif PROB == 3

int main() {
	int n = 10, count = 0;
	int testNumberSquence[MAX_QUE_SIZE] = { 3, 4, 6, 7, 8, 5, 10, 2, 1, 9 };
	que qR,qL;
	stk s;
	element temp;

	init_que(&qR);
	init_que(&qL);
	init_stk(&s);

	for(int i = 1 ; i <= n ;i++) {
		enque(&qR,i);
	}	//right queque에 1부터 n까지 집어넣기

	printf("%d개의 테스트 수열\n", n);
	for (int i = 0; i < n;i++) {
		printf("%d ", testNumberSquence[i]);
	}

	printf("\n생성가능 여부 : ");

	while(!is_empty(&qR)) {	

		if (!is_stk_empty(&s) && testNumberSquence[count] == peek(&s)) {
			enque(&qL, pop(&s));
			count++;
		}

		else {
			temp = deque(&qR);

			if (temp == testNumberSquence[count]) {
				enque(&qL, temp);
				count++;
			}

			else {
				push(&s, temp);
			}
		}

	}

	while (!is_stk_empty(&s) && testNumberSquence[count] == peek(&s)) {
		enque(&qL, pop(&s));
		count++;
	}	//stack에 있는게 마지막으로 들어갈 경우 위 while문에서 해결 x, 따라서 이 while문 필요

	if (is_stk_empty(&s)) {
		printf("가능");
	}

	else printf("불가능");

}
#endif