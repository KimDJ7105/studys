#include "binary_Tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	treenode* root = NULL;
	treenode* tmp = NULL;

	element item;

	item.id_num = 2021006; strcpy(item.name, "name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy(item.name, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy(item.name, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy(item.name, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy(item.name, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy(item.name, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy(item.name, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy(item.name, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy(item.name, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy(item.name, "name10");
	root = insert_node(root, item);

	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021009 검색\n");
	if (search(root, 2021009) != NULL)
		printf("이진 탐색 트리에서 2021009을 발견함 \n");
	else
		printf("이진 탐색 트리에서 2021009을 발견못함 \n");
	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	return 0;
}