#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROB 2

#if PROB == 1

#define SIZE 10000

typedef int element;

//힙 정의 함수들 시작
typedef struct _HEAPTYPE {
	element heap[SIZE + 1];
	int heap_size;
} HeapType;

void init_heap(HeapType *h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item ) {
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
		if(child < h->heap_size && h->heap[child] > h->heap[child +1]) {
			child++;
		}

		if(tmp <= h->heap[child]) break;

		h->heap[parent] = h->heap[child];

		parent = child;
		child *= 2;
	}

	h->heap[parent] = tmp;

	return item;
}
//힙 정의 함수 종료

//힙 정렬 함수
void heap_sort(element* list,element* sorted_list) {
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));

	init_heap(h);

	for(int i = 0 ; i < SIZE ; i++) insert_min_heap(h,list[i]);

	for(int i = 0 ; i < SIZE; i++) sorted_list[i] = delete_min_heap(h);

	if(SIZE < 100){
		for(int i = 0 ; i < SIZE ; i++) printf("%d  ", sorted_list[i]);

		printf("\n");
	}
}

//선택 정렬 함수
void selection_sort(element* list, element* sorted_list) {
	int i, j, least;
	element tmp;

	for (i = 0; i < SIZE; i++) {
		least = i;

		// 최솟값 탐색
		for (j = i + 1; j < SIZE; j++) {
			if (list[j] < list[least]) least = j;
		}
		
		if (i != least) {
			tmp = list[i];
			list[i] = list[least];
			list[least] = tmp;
		}
	}

	for (int i = 0; i < SIZE; i++) sorted_list[i] = list[i];

	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d  ", sorted_list[i]);

		printf("\n");
	}
}

int main() {
	element* list, *sorted_list;
	int i, s_time, e_time;

	srand(100);

	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);

	for (i = 0; i < SIZE; i++) list[i] = rand();

	printf("정수형 데이터 %d개 정렬\n", SIZE);

	s_time = clock();	//시작
	heap_sort(list, sorted_list);
	e_time = clock();	//종료
	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	
	s_time = clock();	//시작
	selection_sort(list, sorted_list);
	e_time = clock();	//종료
	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);
	return 0;
}

#elif PROB == 2

#include <string.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0을 저장하고 순환호출한다. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력한다. 
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

// 허프만 코드 생성 함수
TreeNode* make_huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++) { // 모든 문자에 대한 min heap 생성
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	printf("허프만 코드를 위한 트리 생성\n");

	for (i = 1; i < n; i++) {
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리

	printf("\n문자별 허프만 코드\n");
	print_codes(e.ptree, codes, top);
	printf("\n");
	free(heap);

	return e.ptree;
}

	
//허프만 디코드 함수
void huffman_decode(TreeNode* head, char code[]) {
	
	TreeNode* node = head;
	int i;
	int length = strlen(code);

	printf("%s", code);
	printf("\n");

	for (i = 0; i < length; i++) {
		if (!is_leaf(node)) {
			if (code[i] == '1') {
				node = node->left;
				printf("%d", 1);
			}

			if (code[i] == '0') {
				node = node->right;
				printf("%d", 0);
			}
		}

		if (is_leaf(node)) {
			printf(" ==> %c\n", node->ch);
			node = head;
		}
	}

}

int main() {
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	TreeNode* head;
	head = make_huffman_tree(freq, ch_list, 5);
	printf("디코딩 시작\n");
	huffman_decode(head, "1110101010000101");
	
	destroy_tree(head);
	return 0;
}

#endif
