#include <stdio.h>
#include <stdlib.h>

#define MAX_QUE_SIZE 1000

// AVL 트리 노드 정의
typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

AVLNode* AVL_make_balance(AVLNode* root);
AVLNode* AVL_insert(AVLNode* root, int item);
AVLNode* AVL_remove(AVLNode* root, int item);
void level_order(AVLNode* root);
int Get_balance_factor(AVLNode* root);
int Get_level(AVLNode* root);
int Max(int a, int b);
AVLNode* min_value_node(AVLNode* node);
AVLNode* rotate_left(AVLNode* root);
AVLNode* rotate_right(AVLNode* root);
AVLNode* LL_rotate(AVLNode* root);
AVLNode* RR_rotate(AVLNode* root);
AVLNode* LR_rotate(AVLNode* root);
AVLNode* RL_rotate(AVLNode* root);

typedef struct _Queue {
	AVLNode* data[MAX_QUE_SIZE];
	int front, rear;
} que;

void init_Que(que* q) {
	q->front = 0; q->rear = 0;

	for (int i = 0; i < MAX_QUE_SIZE; i++) {
		q->data[i] = NULL;
	}
}

int is_full(que* q) {
	return ((q->rear + 1) % MAX_QUE_SIZE) == q->front;
}

int is_empty(que* q) {
	return q->front == q->rear;
}

void enqueue(que* q, AVLNode* item) {
	if (is_full(q)) {
		printf("큐 포화 오류");
		exit(1);
	}

	if (item == NULL) return;

	else {
		q->rear = (q->rear + 1) % MAX_QUE_SIZE;
		q->data[q->rear] = item;
	}
}

AVLNode* dequeue(que* q) {
	if (is_empty(q)) printf("큐 공백 오류");

	else {
		q->data[q->front] = NULL;

		q->front = (q->front + 1) % MAX_QUE_SIZE;
		return q->data[q->front];
	}
}

AVLNode* peek(que* q) {
	if (is_empty(q)) printf("큐 공백 오류");

	else {
		return q->data[((q->front + 1) % MAX_QUE_SIZE)];
	}
}

int main() {
	AVLNode* root = NULL;
	// 예제 트리 구축

	printf("Insert %d\n", 5); root = AVL_insert(root, 5);
	printf("Insert %d\n", 4); root = AVL_insert(root, 4);
	printf("Insert %d\n", 3); root = AVL_insert(root, 3);
	level_order(root);
	printf("\nInsert %d\n", 2); root = AVL_insert(root, 2);
	level_order(root);
	printf("\nInsert %d\n", 1); root = AVL_insert(root, 1);
	level_order(root);
	printf("\nRemove %d\n", 5); root = AVL_remove(root, 5);
	level_order(root);
	printf("\nInsert %d\n", 6); root = AVL_insert(root, 6);
	level_order(root);
	printf("\nInsert %d\n", 7); root = AVL_insert(root, 7);
	level_order(root);
	printf("\nInsert %d\n", 8); root = AVL_insert(root, 8);
	level_order(root);
	printf("\nInsert %d\n", 9); root = AVL_insert(root, 9);
	level_order(root);
	printf("\nInsert %d\n", 10); root = AVL_insert(root, 10);
	level_order(root);
	printf("\nInsert %d\n", 15); root = AVL_insert(root, 15);
	level_order(root);
	printf("\nInsert %d\n", 14); root = AVL_insert(root, 14);
	level_order(root);
	printf("\nInsert %d\n", 13); root = AVL_insert(root, 13);
	level_order(root);
	printf("\nInsert %d\n", 12); root = AVL_insert(root, 12);
	level_order(root);
	printf("\nInsert %d\n", 11); root = AVL_insert(root, 11);
	level_order(root);
	printf("\nInsert %d\n", 12); root = AVL_insert(root, 12);
	level_order(root);
	printf("\nRemove %d\n", 11); root = AVL_remove(root, 11);
	level_order(root);
	printf("\nRemove %d\n", 9); root = AVL_remove(root, 9);
	level_order(root);

	return 0;

}

AVLNode* AVL_insert(AVLNode* root, int item) {
	AVLNode* newnode = (AVLNode*)malloc(sizeof(AVLNode));

	newnode->key = item;
	newnode->left = NULL; newnode->right = NULL;

	if (root == NULL) {
		root = newnode;
		return root;
	}

	else {
		AVLNode* p = root;
		AVLNode* prev = root;

		while (1) {
			if (p->key > newnode->key) {
				if (p->left == NULL) {
					p->left = newnode;
					break;
				}

				p = p->left;
			}

			if (p->key < newnode->key) {
				if (p->right == NULL) {
					p->right = newnode;
					break;
				}

				p = p->right;
			}

			if (p->key == newnode->key) {
				printf("동일한 key 존재\n");

				free(newnode);
				return root;
			}
		}

		prev = AVL_make_balance(root);

		while (root != prev) {
			root = prev;

			prev = AVL_make_balance(root);
		}

		return root;
	}
}

void level_order(AVLNode* root) {
	que q;
	que tmp;
	AVLNode* temp;
	int level = 1;

	init_Que(&q);
	init_Que(&tmp);

	if (root == NULL) {
		return;
	}

	else {
		enqueue(&q, root);

		while (1) {
			while (!is_empty(&q)) enqueue(&tmp, dequeue(&q));

			if (is_empty(&tmp)) break;

			printf("LEVEL %d : ", level);

			while (!is_empty(&tmp)) {
				temp = dequeue(&tmp);

				printf("[%d] ", temp->key);

				enqueue(&q, temp->left);
				enqueue(&q, temp->right);
			}
			printf("\n");
			level++;
		}
	}
}

AVLNode* rotate_left(AVLNode* root)
{
	AVLNode* child = root->right;
	if (child != NULL)
		root->right = child->left;
	else
		root->right = NULL;
	child->left = root;
	return child;
}

AVLNode* rotate_right(AVLNode* root)
{
	AVLNode* child = root->left;
	if (child != NULL)
		root->left = child->right;
	else
		root->left = NULL;
	child->right = root;
	return child;
}

AVLNode* LL_rotate(AVLNode* root)
{
	return rotate_right(root);
}

AVLNode* RR_rotate(AVLNode* root)
{
	return rotate_left(root);
}

AVLNode* LR_rotate(AVLNode* root)
{
	root->left = rotate_left(root->left);
	return rotate_right(root);
}

AVLNode* RL_rotate(AVLNode* root)
{
	root->right = rotate_right(root->right);
	return rotate_left(root);
}

int Get_balance_factor(AVLNode* root) {
	if (root == NULL) {
		printf("트리가 없음\n");
		return 0;
	}

	else {
		int left_level = Get_level(root->left);
		int right_level = Get_level(root->right);

		return (left_level - right_level);
	}

}

int Max(int a, int b) {
	if (a >= b) return a;

	if (a < b) return b;
}

int Get_level(AVLNode* root) {
	
	if (root != NULL) {
		return 1 + Max(Get_level(root->left), Get_level(root->right));
	}

	else return 0;
}

AVLNode* AVL_make_balance(AVLNode* root) {
	if (root == NULL) {
		return NULL;
	}

	int balance_factor = Get_balance_factor(root);
	int sub_factor;

	//printf("%d 에서 탐색, BF = %d\n", root->key, balance_factor);

	if (balance_factor == 0 || balance_factor == 1 || balance_factor == -1) {
		root->left = AVL_make_balance(root->left);
		root->right = AVL_make_balance(root->right);
		return root;
	}

	else {
		if (balance_factor > 1) {
			sub_factor = Get_balance_factor(root->left);

			if (sub_factor > 0) {
				//printf("\nLL\n");
				return LL_rotate(root);
			}

			else if (sub_factor < 0) {
				//printf("\nLR\n");
				return LR_rotate(root);
			}
		}

		else if (balance_factor < 0) {
			sub_factor = Get_balance_factor(root->right);

			if (sub_factor > 0) {
				//printf("\nRL\n");
				return RL_rotate(root);
			}

			else if (sub_factor < 0) {
				//printf("\nRR\n");
				return RR_rotate(root);
			}
		}

	}
}

AVLNode* min_value_node(AVLNode* node) {
	AVLNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL) current = current->left;

	return current;
}


AVLNode* AVL_remove(AVLNode* root, int item) {
	if (root == NULL) return NULL;

	if (item > root->key) root->right = AVL_remove(root->right, item);

	else if (item < root->key) root->left = AVL_remove(root->left, item);

	else if (item == root->key) {
		AVLNode* tmp;

		if (root->left == NULL) {
			tmp = root->right;
			free(root);
			return tmp;
		}

		else if (root->right == NULL) {
			tmp = root->left;
			free(root);
			return tmp;
		}

		tmp = min_value_node(root->right);

		root->key = tmp->key;

		root->right = AVL_remove(root->right, item);


		root = AVL_make_balance(root);
	}

	return root;
}

