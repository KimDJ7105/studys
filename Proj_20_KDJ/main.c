#define SIZE 100000
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "Que.h"
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

#define BUCKETS 10
#define DIGITS 4


void selection_sort(int* list, int size);
void insertion_sort(int* list, int size);
void bubble_sort(int* list, int size);
int inc_insertion_sort(int list[], int first, int last, int gap);
void shell_sort(int* list, int size);
void merge_sort(int* list, int left, int right);
int partition(int* list, int low, int high);
void quick_sort(int* list, int low, int high);
void heap_sort(int* list, int size);
void radix_sort(int* list, int size);

typedef int element;

//힙 정의 함수들 시작
typedef struct _HEAPTYPE {
	element heap[SIZE + 1];
	int heap_size;
} HeapType;

void init_heap(HeapType* h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while (i != 1 && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
	int parent = 1, child = 2;
	element	item, tmp;

	item = h->heap[1];
	tmp = h->heap[(h->heap_size)--];

	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child] > h->heap[child + 1]) {
			child++;
		}

		if (tmp <= h->heap[child]) break;

		h->heap[parent] = h->heap[child];

		parent = child;
		child *= 2;
	}

	h->heap[parent] = tmp;

	return item;
}


int main() {
	int i, s_time, e_time;

	int* list = (int*)malloc(sizeof(int) * SIZE);
	int* data = (int*)malloc(sizeof(int) * SIZE);
	int* sorted = (int*)malloc(sizeof(int) * SIZE);

	printf("Data 크기 : %d \n", SIZE);
	srand(100);
	for (i = 0; i < SIZE; i++) {// 난수 생성 및 출력 
		data[i] = rand(); // 난수 발생
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	selection_sort(list, SIZE); // 선택정렬 호출 
	e_time = clock();
	printf("선택정렬 시간 : %d\n", e_time - s_time);

	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	insertion_sort(list, SIZE);	//삽입정렬 호출
	e_time = clock();
	printf("삽입정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}
	
	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	bubble_sort(list, SIZE); //버블정렬 호출
	e_time = clock();
	printf("버블정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	shell_sort(list, SIZE); //셀 정렬 호출
	e_time = clock();
	printf("셸정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	merge_sort(list, 0, SIZE - 1);	//병합정렬 호출
	e_time = clock();
	printf("병합정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	quick_sort(list, 0, SIZE - 1);	//퀵 정렬 호출
	e_time = clock();
	printf("퀵정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	heap_sort(list, SIZE);	//힙 정렬 호출
	e_time = clock();
	printf("힙정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	memcpy(list, data, sizeof(int) * SIZE);

	s_time = clock();
	radix_sort(list, SIZE); // 기수정렬 호출 
	e_time = clock();
	printf("기수정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n");
	}

	free(data); free(list); free(sorted);

	return 0;
}

void selection_sort(int* list, int size) {
	int i, j, least, tmp;

	for (i = 0; i < size - 1; i++) {
		least = i;
		for (j = i + 1 ; j < size; j++) {
			if (list[j] < list[least]) least = j;
		}

		SWAP(list[i], list[least], tmp);
	}
}

void insertion_sort(int* list, int size) {
	int i, j, key;

	for (i = 1; i < size ; i++) {
		key = list[i];
		
		for (j = i - 1; j >= 0 && list[j] > key; j--) list[j + 1] = list[j]; 		// 레코드의 오른쪽 이동
		
		list[j + 1] = key;
	}

}

void bubble_sort(int* list, int size) {
	int i, j, tmp;

	for (i = size - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) SWAP(list[j], list[j + 1], tmp);
		}
	}
}

int inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;

	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];

		for (j = i - gap; j >= first && key < list[j];j = j - gap) list[j + gap] = list[j];

		list[j + gap] = key;
	}
}


void shell_sort(int* list, int size) {
	int i, gap;

	for (gap = size / 2; gap > 0; gap /= 2) {
		if (gap % 2 == 0) gap++;

		for (i = 0;i < gap; i++) inc_insertion_sort(list,i, size-1, gap);
	}
}

void merge_sort(int* list, int left, int right) {
	int i, j, k, l, mid;
	int sorted[SIZE];

	mid = (left + right) / 2;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {

		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}

	if (i > mid) {	// 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++) sorted[k++] = list[l];
	}

	else { 	// 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++) sorted[k++] = list[l];
	}

	memcpy(list, sorted, sizeof(int) * SIZE);
}

int partition(int* list, int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;

}

void quick_sort(int* list, int low, int high) {
	if (low < high) {
		int q = partition(list, low, high);

		quick_sort(list, low, q - 1);
		quick_sort(list, q + 1, high);
	}
}

void heap_sort(int* list, int size) {
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));

	init_heap(h);

	for (int i = 0; i < SIZE; i++) insert_min_heap(h, list[i]);

	for (int i = 0; i < SIZE; i++) list[i] = delete_min_heap(h);

}

void radix_sort(int* list, int size) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0;b < BUCKETS;b++) init(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0;i < size;i++)				// 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0;b < BUCKETS;b++)			// 버켓에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;				// 그 다음 자리수로 간다.
	}

}