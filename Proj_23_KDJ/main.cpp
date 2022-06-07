#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TABLE_SIZE 10000 // 해싱 테이블의 크기=소수 
typedef struct {
	int key;
} element;

struct list {
	element item;
	struct list* link;
};

// 제산 함수를 사용한 해싱 함수
int hash_function(int key) {
	return key % TABLE_SIZE;
}

#define SIZE TABLE_SIZE/10
#define SEARCH_COUNT 1000000

struct list* Chash_table[TABLE_SIZE];
element Lhash_table[TABLE_SIZE];


void init() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		Lhash_table[i].key = INT_MAX;
		Chash_table[i]->item.key = INT_MAX;
	}
}

int get_prime_number(int input);
void hash_linear_add(element e, element table[], int prime);
void hash_chain_add(element e, struct list* table[TABLE_SIZE]);
void hash_linear_search(element e, element table[], int prime);
void hash_chain_search(element e, struct list* table[]);

int main() {
	int s_time, e_time;
	int h_prime;
	element e;

	srand(100);
	h_prime = get_prime_number(TABLE_SIZE); 
	//이중 해시법을 적용하기 위한 버킷 사이즈보다 작은 가장 큰 소수 구하기

	for (int i = 0; i < SIZE; i++) {
		e.key = rand();
		//printf("%d, %d\n", i, e.key);
		hash_linear_add(e, Lhash_table, h_prime);
		hash_chain_add(e, Chash_table);
		//hash_chain_print(Chash_table);
	}

	srand(200);

	s_time = clock();

	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_linear_search(e, Lhash_table, h_prime);
	}

	e_time = clock();

	printf("선형기법\n");
	printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d \n", (float)SIZE / TABLE_SIZE, SEARCH_COUNT, e_time - s_time);
	
	srand(200);
	s_time = clock();
	for (int i = 0; i < SEARCH_COUNT; i++) {
		e.key = rand();
		hash_chain_search(e, Chash_table);
	}
	e_time = clock();

	printf("체인기법\n");
	printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d \n", (float)SIZE /TABLE_SIZE, SEARCH_COUNT, e_time - s_time);

	return 0;
}

int get_prime_number(int input) {
	int prime = 2;
	int num = 3;

	while (1) {
		int max = (int)sqrt(num);

		for (int i = 0;i <= max; i++) {
			if (i != 0 && num % i == 0) break;

			if (i == max) prime = num;
		}

		num++;

		if (num > input) break;
	}

	return prime;
}

void hash_linear_add(element e, element table[], int prime) {
	int index = hash_function(e.key);

	if(table[index].key == NULL) table[index] = e;

	else {
		int tmp_index = index + 1;

		while (tmp_index != index) {
			if (table[tmp_index].key == NULL) {
				table[tmp_index] = e;
				break;
			}

			tmp_index++;

			if (tmp_index == TABLE_SIZE) tmp_index = 0;
		}
	}
}

void hash_chain_add(element e, struct list* table[TABLE_SIZE]) {
	int index = hash_function(e.key);

	struct list* newnode = (struct list*)malloc(sizeof(struct list));

	newnode->item = e;
	newnode->link = NULL;

	if (table[index] == NULL) table[index] = newnode;

	else {
		struct list* tmp = table[index];

		while (tmp->link != NULL) tmp = tmp->link;

		tmp->link = newnode;
	}
}


void hash_linear_search(element e, element table[], int prime) {
	int index, hash;
	hash = index = hash_function(e.key);

	while (table[index].key != INT_MAX) {
		if (e.key == table[index].key) {
			//printf("탐색 위치 = %d\n", index);
			
			return;
		}

		index = (index + 1) % TABLE_SIZE;

		if (index == hash) {
			return;
		}
	}
}

void hash_chain_search(element e, struct list* table[]) {
	struct list* node;

	int hash_index = hash_function(e.key);

	for (node = table[hash_index]; node; node = node->link) {
		if (node->item.key == e.key) {
			//printf("탐색 성공 = %d\n", node->item);

			return;
		}
	}
}