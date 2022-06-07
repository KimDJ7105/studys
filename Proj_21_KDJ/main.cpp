#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define DATA 802

int seqsearch(int list[], int low, int high, int data, int* count);
int binsearch(int list[], int low, int high, int data, int* count);
int search_interpolation(int list[], int low, int high, int data, int* count);

int main() {
	int i, s_time, e_time, count, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);

	list[0] = 0;

	for (i = 1; i < SIZE; i++) list[i] = list[i - 1] + (rand() % 3);

	printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");
	s_time = clock();

	result = seqsearch(list, 0, SIZE - 1, DATA, &count); // 순차탐색 호출 

	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");

	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	s_time = clock();

	result = binsearch(list, 0, SIZE - 1, DATA, &count); // 이진탐색 호출 

	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");

	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	s_time = clock();

	result = search_interpolation(list, 0, SIZE - 1, DATA, &count); //보간탐색 호출 

	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");

	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	free(list);
	return 0;

}


int seqsearch(int list[], int low, int high, int data, int* count) {
	int i;
	*count = 0;

	for (i = low; i <= high; i++) {
		*count += 1;
		if (list[i] == data) return i;
	}

	return -1;
}

int binsearch(int list[], int low, int high, int data, int* count) {
	int middle;
	*count = 0;

	while (low <= high) {
		*count += 1;

		middle = (low + high) / 2;

		if (data == list[middle]) return middle;

		else if (data > list[middle]) low = middle + 1;

		else high = middle - 1;
	}

	return -1;
}

int search_interpolation(int list[], int low, int high, int data, int* count) {
	int j;

	*count = 0;

	while ((list[high] >= data) && (data > list[low])) {
		*count += 1;

		j = ((float)(data - list[low]) / (list[high] - list[low]) * (high - low)) + low;

		if (data > list[j]) low = j + 1;

		else if (data < list[j]) high = j - 1;

		else low = j;
	}

	if (list[low] == data) return low;

	else return -1;
}