#include "Que.h"
#include <stdio.h>
#include <stdlib.h>

#define PROB 2

#if PROB == 1
#define MAX_VERTICES 50

typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g);
void insert_edge(GraphType* g, int start, int end);
void set_vertex(GraphType* g, int num);
void dfs_mat(GraphType* g, int num);
void bfs_mat(GraphType* g, int num);

int main() {
	GraphType* g;
	int i;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0);
	printf("\n");
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);
	printf("\n");
	free(g);
	return 0;
}

void init(GraphType* g) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->adj_mat[i][j] = 0;
		}
	}

	g->n = 0;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		printf("그래프 : 정점의 번호 오류\n");
		return;
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void set_vertex(GraphType* g, int num) {
	if ((g->n + num) > MAX_VERTICES) {
		printf("그래프 : 정점 개수 초과\n");
		return;
	}

	g->n += num;
}

//깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = 1;
	printf("%d 방문->", v);
	for (w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !visited[w]) dfs_mat(g, w);
	}
}

//넓이 우선 탐색
void bfs_mat(GraphType* g, int v) {
	int w;

	QueueType q;
	init_Queue(&q);
	visited[v] = 1;

	printf("%d 방문->", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);

		for (w = 0;w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%d 방문->", w);
				enqueue(&q, w);	
			}
		}
	}
}

#elif PROB == 2

#define MAX_VERTICES 50
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g);
void set_vertex(GraphType* g, int v);
void insert_edge(GraphType* g, int start, int end);
void dfs_list(GraphType* g, int num);
void bfs_list(GraphType* g, int num);

int main() {
	GraphType* g;
	int i;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_list(g, 0);
	printf("\n");
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_list(g, 0);
	printf("\n");
	free(g);
	return 0;

}

void init(GraphType* g) {
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adj_list[i] = NULL;
	}
}

void set_vertex(GraphType* g, int v) {
	if ((g->n + v) > MAX_VERTICES) {
		printf("그래프 : 정점 개수 초과\n");
		return;
	}

	g->n += v;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		printf("그래프 : 정점 번호 오류\n");
		return;
	}

	GraphNode* tmp;
	GraphNode* newnode = (GraphNode*)malloc(sizeof(GraphNode));
	GraphNode* newnode2 = (GraphNode*)malloc(sizeof(GraphNode));

	newnode->link = NULL;	newnode2->link = NULL;
	newnode->vertex = end;	newnode2->vertex = start;

	tmp = g->adj_list[start];
	
	if (tmp == NULL) g->adj_list[start] = newnode;

	else {
		while (tmp->link != NULL) tmp = tmp->link;

		tmp->link = newnode;
	}

	tmp = g->adj_list[end];

	if (tmp == NULL) g->adj_list[end] = newnode2;

	else {
		while (tmp->link != NULL) tmp = tmp->link;

		tmp->link = newnode2;
	}

}

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = 1;
	printf("%d 방문->", v);

	for (w = g->adj_list[v]; w != NULL; w = w->link) {
		if (visited[w->vertex] == 0) dfs_list(g, w->vertex);
	}
}

void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;

	init_Queue(&q);
	visited[v] = 1;
	printf("%d 방문->", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);

		for (w = g->adj_list[v]; w; w = w->link) {
			if (visited[w->vertex] == 0) {
				visited[w->vertex] = 1;
				printf("%d 방문->", w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}
#endif


