#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUE_SIZE 100

typedef struct ELEMENT {
	int id_num;
	char name[10];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}treenode;

//여기부터 큐 코드
typedef struct _Queue {
	treenode* data[MAX_QUE_SIZE];
	int front, rear;
} que;

void init_Que(que* q) {
	q->front = 0; q->rear = 0;

	for(int i = 0 ; i < MAX_QUE_SIZE ; i++) {
		q->data[i] = NULL;
	}
}

int is_full(que* q) {
	return ((q->rear + 1) % MAX_QUE_SIZE) == q->front;
}

int is_empty(que* q) {
	return q->front == q->rear;
}

void enqueue(que* q, treenode* item) {
	if (is_full(q)) {
		printf("큐 포화 오류");
		exit(1);
	}

	if(item == NULL) return;

	else {
		q->rear = (q->rear + 1) % MAX_QUE_SIZE;
		q->data[q->rear] = item;
	}
}

treenode* dequeue(que* q) {
	if (is_empty(q)) printf("큐 공백 오류");

	else {
		q->data[q->front] = NULL;

		q->front = (q->front + 1) % MAX_QUE_SIZE;
		return q->data[q->front];
	}
}

treenode* peek(que* q) {
	if(is_empty(q)) printf("큐 공백 오류");

	else {
		return q->data[((q->front + 1) % MAX_QUE_SIZE)];
	}
}
//여기까지 큐 코드


//새로운 노드를 추가하는 함수
treenode* insert_node(treenode* root, element item) {
	
	treenode* tmp = (treenode*)malloc(sizeof(treenode));

	tmp->data = item;
	tmp->left = NULL; tmp->right = NULL;

	if (root == NULL) root = tmp;

	else {
		treenode* p = root;

		while (1) {
			if (p->data.id_num < tmp->data.id_num) {
				if (p->right == NULL) {
					p->right = tmp;
					break;
				}

				else p = p->right;
			}

			else if (p->data.id_num > tmp->data.id_num) {
				if (p->left == NULL) {
					p->left = tmp;
					break;
				}

				else p = p->left;
			}

			else if (p->data.id_num == tmp->data.id_num) {
				free(tmp);
				printf("\n동일한 학번 존재\n");
				return root;
			}

			if (p == NULL) break;
		}

		return root;
	}
}

//중위순회 함수 (재귀)
void inorder(treenode* root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->data.id_num);
		inorder(root->right);
	}

	return;
}

//레벨순회 함수
void level_order(treenode* root) {
	que q;
	que tmp;
	treenode* temp;
	int level = 1;

	init_Que(&q);
	init_Que(&tmp);

	if(root == NULL) return;

	else {
		enqueue(&q,root);

		while(1) {
			while(!is_empty(&q)) enqueue(&tmp, dequeue(&q));
			
			if(is_empty(&tmp)) break;

			printf("LEVEL %d : ", level);

			while(!is_empty(&tmp)) {
				temp = dequeue(&tmp);

				printf("[%d] ",temp->data.id_num);

				enqueue(&q, temp->left);
				enqueue(&q, temp->right);
			}
			printf("\n");
			level++;
		}
	}
}

//노드의 총 갯수를 리턴하는 함수
int get_node_count(treenode* root) {
	int count = 0;

	if (root) {
		count += get_node_count(root->left);
		count++;
		count += get_node_count(root->right);
	}

	return count;
}

//리프 노드의 총 갯수를 리턴하는 함수
int get_leaf_count(treenode* root) {
	int count = 0;

	if (root) {
		if (root->left == NULL && root->right == NULL) return 1;

		else {
			count = get_leaf_count(root->left) + get_leaf_count(root->right);

			
		}
	}

	return count;
}

//트리의 높이를 리턴하는 함수
int get_height(treenode* root) {
	int height = 0;
	
	if (root) {
		if (get_height(root->left) > get_height(root->right)) height = 1 + get_height(root->left);

		else height = 1 + get_height(root->right);
	}

	return height;
}

//학번을 검색하는 함수
treenode* search(treenode* root, int num) {
	treenode* tmp = NULL;

	if(root->data.id_num == num) tmp = root;

	else if(root->left == NULL && root->right == NULL) tmp = NULL; 

	else if(root->data.id_num > num) tmp = search(root->left, num);

	else if(root->data.id_num < num) tmp = search(root->right, num);

	return tmp;
}

//가장 작은 값을 찾는 함수
treenode* min_value_node(treenode* node)
{
	treenode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}


//검색한 학번을 삭제하는 함수
treenode* delete_node(treenode* root, int key) {
	if (root == NULL) return root;

	if (key < root->data.id_num) root->left = delete_node(root->left, key);

	else if (key > root->data.id_num) root->right = delete_node(root->right, key);

	else {
		if (root->left == NULL) {
			treenode* tmp = root->right;
			free(root);
			return tmp;
		}

		else if (root->right == NULL) {
			treenode* tmp = root->left;
			free(root);
			return tmp;
		}

		treenode* tmp = min_value_node(root->right);

		root->data = tmp->data;

		root->right = delete_node(root->right, key);
	}

	return root;
}