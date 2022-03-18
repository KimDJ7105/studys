#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linkedlist.h"

int main() {

	int c;
	int seed;
	int start;
	int done;
	int num1;
	int num2;

	printf("Data size : ");
	scanf("%d", &c);
	printf("rand함수의 seed 값 : ");
	scanf("%d", &seed);

	
	start = time(NULL);

	creatnum(c, seed);

	done = time(NULL);

	num1 = done - start;

	printf("배열을 이용한 경우의 실행 시간 : %d\n", num1);

	start = time(NULL);

	creatnode(c, seed);

	done = time(NULL);

	num2 = done - start;

	printf("연결리스트를 이용한 경우의 실행 시간 : %d", num2);
	
}