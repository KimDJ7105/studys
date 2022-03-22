#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROB 1

#if PROB == 1

int rec_Bino(int n, int k) {

	if (k == 0 || k == n)
		return 1;

	if (0 < k && k < n)
		return rec_Bino(n - 1, k - 1) + rec_Bino(n - 1, k);
}

int itr_Bino(int n, int k) {

	int i, j;
	int c[50][50];

	for (i = 1; i <= n; i++) {

		for (j = 0;j < i;j++) {

			if (j == 0 || j == 1) c[i][j] = 1;
			else c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
}

int main() {

	int n, k;

	int start, end, done;

	printf(" Enter n and k :");
	scanf("%d %d", &n, &k);

	start = time(NULL);

	rec_Bino(n, k);

	end = time(NULL);

	done = end - start;

	printf("순환으로 걸린 시간 : %d\n", done);

	start = time(NULL);

	itr_Bino(n, k);

	end = time(NULL);

	done = end - start;

	printf("반복으로 걸린 시간 : %d\n", done);
}

#elif PROB == 2 

int rec_Ackerman(int m, int n) {
	if (m == 0)
		return n + 1;
	if (m != 0 && n == 0)
		return rec_Ackerman(m - 1, 1);
	else
		return rec_Ackerman(m - 1, rec_Ackerman(m, n - 1));
}

int itr_Ackerman(int m, int n) {
	int A_num[10000];
	int idx = 0;

	A_num[idx++] = m; //m값을 첫 idx에 저장
	A_num[idx] = n;	//n값을 다음 idx에 저장

	while (1) {
		if (idx == 0) {
			return A_num[idx];	//idx 값이 0이 될 경우 해당 값을 리턴하고 루프 종료
		}

		else if (A_num[idx - 1] == 0) {	//m부분이 0이 될 때
			A_num[idx - 1] = A_num[idx] + 1;	// m = n+1
			idx = idx - 1;	//n이 해소되었으니 idx -1
		}

		else if (A_num[idx] == 0) {	//n이 0이 될 때
			A_num[idx - 1] = A_num[idx - 1] - 1;	// m 을 m-1로 변경
			A_num[idx] = 1;	//n을 1로 변경
		}

		else {	//그 외의 경우
			A_num[idx + 1] = A_num[idx] - 1;	//새 아커만 함수 속 함수에 n-1
			A_num[idx] = A_num[idx - 1];	//새 아커만 함수속 함수에 m값을 넣기
			A_num[idx - 1] = A_num[idx - 1] - 1;	//새 아커만 함수 m 자리에 m-1넣기

			idx = idx + 1;	//아커만 함수의 재기 횟수가 늘었으니 +1
		}
	}
}

int main() {

	int m, n;

	int start, end, done;

	long long int num;

	printf(" Enter m and n :");
	scanf("%d %d", &m, &n);

	start = time(NULL);

	num = rec_Ackerman(m,n);

	end = time(NULL);

	done = end - start;

	printf("순환으로 걸린 시간 : %d\n", done);

	start = time(NULL);

	num = itr_Ackerman(m, n);

	end = time(NULL);

	done = end - start;

	printf("반복으로 걸린 시간 : %d\n", done);
}

#elif PROB == 3

int rec_fib(int n) {
	if (n == 0 || n == 1)
		return n;
	else
		return rec_fib(n - 2) + rec_fib(n - 1);
}

int itr_fib(int n) {

	int arr[100];

	if (n == 0 || n == 1)
		return n;
	else 
		for (int i = 0; i < n; i++) {
			if (i == 0 || i == 1) arr[i] = i;

			if (i > 1) arr[i] = arr[i - 1] + arr[i - 2];
		}

}

int main() {

	int start, end, done;
	int n;

	printf("n을 입력하세요 :");
	scanf("%d", &n);

	start = time(NULL);
	rec_fib(n);
	end = time(NULL);

	done = end - start;

	printf("순환으로 걸린 시간 : %d\n", done);

	start = time(NULL);

	itr_fib(n);

	end = time(NULL);

	done = end - start;

	printf("반복으로 걸린 시간 : %d\n", done);
}

#elif PROB == 4

#define SIZE 1000

void serch(int x, int data[], int i, int j) {

	int n = (i + j) / 2;

	if (x == data[n])
		printf("x는 %d번째 데이터 입니다.\n", n);
	if (x > data[n])
		serch(x, data, i, n);
	if (x < data[n])
		serch(x, data, n, j);

}


int main() {
	int x;
	int i = SIZE;
	int j = 0;
	int* data = (int*)malloc(SIZE * sizeof(int));

	for (int idx = 0; idx < SIZE; idx++) data[idx] = idx;

	serch(x, data, i, j);
}

#endif
