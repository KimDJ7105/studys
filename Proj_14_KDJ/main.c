#include <stdio.h>
#include <stdlib.h>

typedef struct _TREENODE {
	int data;
	struct Treenode* Left, * Right;
} TreeNode;

#define SIZE 100

int top = -1;
TreeNode* stack[SIZE];
//스택 구현 함수

void push(TreeNode* p) {
	if (top < SIZE - 1) stack[++top] = p;
}

TreeNode* pop() {
	TreeNode* p = NULL;

	if (top >= 0) p = stack[top--];

	return p;
}

void init_stack() {
	top = -1;

	for (int i = 0; i < SIZE; i++) {
		stack[i] = NULL;
	}
}

// Full Binary Tree node number 1~15(root : 1)
TreeNode n15 = { 15, NULL, NULL };
TreeNode n14 = { 14, NULL, NULL };
TreeNode n13 = { 13, NULL, NULL };
TreeNode n12 = { 12, NULL, NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL, NULL };
TreeNode n8 = { 8, NULL, NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;

//재귀 함수
void inorder_rec(TreeNode* root);
void preorder_rec(TreeNode* root);
void postorder_rec(TreeNode* root);
//반복 함수
void inorder_iter(TreeNode* root);
void preorder_iter(TreeNode* root);
void postorder_iter(TreeNode* root);



int main() {


	printf("중위 순회(rec)=");
	inorder_rec(root);	//재귀
	printf("\n");
	printf("중위 순회(itr)=");
	inorder_iter(root);	//반복
	printf("\n");

	printf("전위 순회(rec)=");
	preorder_rec(root);	//재귀
	printf("\n");
	printf("전위 순회(itr)=");
	preorder_iter(root);	//반복
	printf("\n");

	printf("후위 순회(rec)=");
	postorder_rec(root);	//재귀
	printf("\n");
	printf("후위 순회(itr)=");
	postorder_iter(root);	//반복
	printf("\n");
	return 0;

}

void inorder_rec(TreeNode* root) {
	if (root) {
		inorder_rec(root->Left);
		printf(" [%d]", root->data);
		inorder_rec(root->Right);
	}

	return;
}

void preorder_rec(TreeNode* root) {
	if (root) {
		printf(" [%d]", root->data);
		preorder_rec(root->Left);
		preorder_rec(root->Right);
	}

	return;
}

void postorder_rec(TreeNode* root) {
	if (root) {
		postorder_rec(root->Left);
		postorder_rec(root->Right);
		printf(" [%d]", root->data);
	}

	return;
}

void inorder_iter(TreeNode* root) {
	init_stack();

	while (1) {
		for (;root; root = root->Left) push(root); //루트의 왼쪽node 를 전부 스택에 넣기

		root = pop();	//하나를 빼서 root 에 넣음

		if (!root) break; //stack이 비어있었으면 반복 종료

		printf(" [%d]", root->data);	//데이터 출력 후
		root = root->Right;
	}
}

void preorder_iter(TreeNode* root) {
	init_stack();

	while(1) {
		for(; root; root = root->Left) {
			printf(" [%d]",root->data);
			push(root);
		}

		root = pop();

		if(!root) break;

		root = root->Right;
	}

}

void postorder_iter(TreeNode* root) {
	init_stack();

	while(1) {
		for(;root;root = root->Left) {
			push(root);
			push(root);
		}

		if (top != -1) {
			root = pop();
			if (top != -1 && root == stack[top]) {
				root = root->Right;
			}

			else {
				printf(" [%d]", root->data);
				root = NULL;
			}
		}

		else {
			break;
		}
		
	}

}