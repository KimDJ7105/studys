#include <stdio.h>
#include <stdlib.h>

#define PROB 1

#if PROB == 1

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
    int n; //정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; //시작 정점으로부터의 최단경로 거리
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int path[MAX_VERTICES]; /* 경유 노드 */

int choose(int distance[], int n, int found[]);
void shortest_path(GraphType* g, int start);
void print_path(int start, int end);
void print_status(GraphType* g, int count);

int main() {
    
// test data 1
    GraphType g = { 7,
{{ 0, 7, INF, INF, 3, 10, INF },
{ 7, 0, 4, 10, 2, 6, INF },
{ INF, 4, 0, 2, INF, INF, INF },
{ INF, 10, 2, 0, 11, 9, 4 },
{ 3, 2, INF, 11, 0, INF, 5 },
{ 10, 6, INF, 9, INF, 0, INF },
{ INF, INF, INF, 4, 5, INF, 0 } }
    };

// 방향성 그래프에도 적용 가능

// test data 2
    /*
    GraphType g = {6,
{{ 0, 50, 45, 10, INF, INF},
{ INF, 0, 10, 15, INF, INF},
{ INF, INF, 0, INF, 30, INF},
{ 20, INF, INF, 0, 15, INF},
{ INF, 20, 35, INF, 0, INF},
{ INF, INF, INF, INF, 3, 0}}
    };
    */
// test data 3
    /*
    GraphType g = { 7,
        {{ 0, 7, INF, 5,INF, INF, INF},
        { 7, 0, 8, 9, 7, INF, INF},
        { INF, 8, 0, INF, 5, INF, INF},
        { 5, 9, INF, 0, 15, 6, INF },
        { INF, 7, 5, 15, 0, 8, 9},
        { INF, INF, INF, 6, 8, 0, 11 },
        { INF, INF, INF, INF, 9, 11, 0 } }
    };
    */
    shortest_path(&g, 0);
    printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 6);
    print_path(0, 6); // 정점 0에서 정점 6으로 가는 최단경로 출력
    printf("\n");
    return 0;
}

int choose(int distance[], int n , int found[]) {
    int i, min, minpos;

    min = INT_MAX;
    minpos = -1;

    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }

    return minpos;
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;

    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
        path[i] = start;
    }

    found[start] = TRUE;
    distance[start] = 0;

    for (i = 0; i < g->n; i++) {
        print_status(g, i);
        u = choose(distance, g->n, found);
        found[u] = TRUE;

        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                    path[w] = u;
                }
            }
        }
    }
}

void print_path(int start, int end) {
    int index;

    index = end;

    printf("%d ", end);

    while (path[index] != start) {
        printf("<= %d ", path[index]);

        index = path[index];
    }

    printf("<= %d", path[index]);
}

void print_status(GraphType* g, int count) {
    printf("<%d 단계> :\n");
    printf("distance :");

    for (int i = 0; i < g->n;i++) {
        if (distance[i] == INF) printf(" * ");
        else printf(" %d ", distance[i]);
    }

    printf("\n");
    printf("   found :");

    for (int i = 0; i < g->n;i++) printf(" %d ", found[i]);
    
    printf("\n");
}
#elif PROB == 2
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

void floyd(GraphType* g);
void print_path( int start, int end);
void printA(GraphType *g);

int main() {
    /*
// test data 1
GraphType g = { 7,
{{ 0, 7, INF, INF, 3, 10, INF },
{ 7, 0, 4, 10, 2, 6, INF },
{ INF, 4, 0, 2, INF, INF, INF },
{ INF, 10, 2, 0, 11, 9, 4 },
{ 3, 2, INF, 11, 0, INF, 5 },
{ 10, 6, INF, 9, INF, 0, INF },
{ INF, INF, INF, 4, 5, INF, 0 } }
};
// 방향성 그래프에도 적용 가능
// test data 2
GraphType g = { 6,
{{ 0, 50, 45, 10, INF, INF},
{ INF, 0, 10, 15, INF, INF},
{ INF, INF, 0, INF, 30, INF},
{ 20, INF, INF, 0, 15, INF},
{ INF, 20, 35, INF, 0, INF},
{ INF, INF, INF, INF, 3, 0}}
};
*/

// test data 3
    GraphType g = { 7,
    {{ 0, 7, INF, 5,INF, INF, INF},
    { 7, 0, 8, 9, 7, INF, INF},
    { INF, 8, 0, INF, 5, INF, INF},
    { 5, 9, INF, 0, 15, 6, INF },
    { INF, 7, 5, 15, 0, 8, 9},
    { INF, INF, INF, 6, 8, 0, 11 },
    { INF, INF, INF, INF, 9, 11, 0 } }
    };

    floyd(&g);

    printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 6);
    print_path(0, 6); // 정점 0에서 정점 3으로 가는 최단경로 출력

    //printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 5);
    //print_path(path, 0, 5); // 정점 0에서 정점 3으로 가는 최단경로 출력
    printf("\n");
    return 0;
}

void floyd(GraphType* g) {
    int i, j, k;

    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->weight[i][j];
            path[i][j] = i;
        }
    }

    printA(g);

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++) {
            for (j = 0; j < g->n; j++) {
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }

        printA(g);
    }
}

void print_path(int start, int end) {
    int index;

    index = end;

    printf("%d ", index);

    while (index != start) {
        index = path[start][index];

        printf("<= %d ", index);
    }
}

void printA(GraphType* g) {
    int i, j;
    
    printf("=================\n");
    for ( i = 0; i < g->n; i++) {
        for ( j = 0; j < g->n; j++) {
            if (A[i][j] == INF) printf(" * ");
            else printf(" %d ", A[i][j]);

            if (j == g->n - 1) printf("\n");
        }
    }
    printf("=================\n");
}

#elif PROB == 3
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100

typedef int element;

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef struct _Stack {
    int top;
    int data[MAX_VERTICES];
} StackType;

void init(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return s->top == -1;
}

int is_full(StackType* s) {
    return s->top == (MAX_VERTICES - 1);
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        printf("스택 포화 오류\n");
        return;
    }

    s->data[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        printf("스택 공백 오류\n");
        return;
    }

    return s->data[(s->top)--];
}

void graph_init(GraphType* g);
void set_vertex(GraphType* g, int vertex);
void insert_edge(GraphType* g, int start, int end);
int topo_sort(GraphType* g);
void delete_graph(GraphType* g);

int main() {
    GraphType g;
    graph_init(&g);

    //test data 1
    /*
    set_vertex(&g, 6);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 5);
    */

    //test data 2
    set_vertex(&g, 8);
    insert_edge(&g, 0, 1);
    insert_edge(&g, 1, 2);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 7);
    insert_edge(&g, 3, 6);
    insert_edge(&g, 4, 5);
    insert_edge(&g, 4, 6);
    insert_edge(&g, 5, 7);
    insert_edge(&g, 6, 7);

    //위상 정렬 
    topo_sort(&g);
    // 동적 메모리 반환 코드 생략
    delete_graph(&g);

    return 0;
}

void graph_init(GraphType* g) {
    g->n = 0;

    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

void set_vertex(GraphType* g, int vertex) {
    if ((g->n + vertex) >= MAX_VERTICES) {
        printf("정점 개수 오류\n");
        return;
    }

    g->n += vertex;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        printf("정점 번호 오류\n");
        return;
    }

    GraphNode* newnode = (GraphNode*)malloc(sizeof(GraphNode));
    GraphNode* tmp;

    tmp = g->adj_list[start];

    newnode->link = NULL;
    newnode->vertex = end;

    if (tmp == NULL) g->adj_list[start] = newnode;

    else {
        while (tmp->link != NULL) tmp = tmp->link;

        tmp->link = newnode;
    }
}

int topo_sort(GraphType* g) {
    int i;
    StackType s;
    GraphNode* node;

    int* in_degree = (int*)malloc(sizeof(int) * g->n);

    for (i = 0;i < g->n;i++) in_degree[i] = 0;

    for (i = 0; i < g->n;i++) {
        node = g->adj_list[i];

        while (node != NULL) {
            in_degree[(node->vertex)]++;
            node = node->link;
        }
    }

    init(&s);

    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0) push(&s, i);
    }

    while (!is_empty(&s)) {
        int w;

        w = pop(&s);

        printf("정점 %d ->", w);

        node = g->adj_list[w];

        while (node != NULL) {
            int u = node->vertex;
            in_degree[u]--;

            if (in_degree[u] == 0) push(&s, u);

            node = node->link;
        }
    }

    free(in_degree);

    printf("\n");

    return (i == g->n);
}

void delete_graph(GraphType* g) {
    GraphNode* tmp,*del;

    for (int i = 0; i < MAX_VERTICES; i++) {
        tmp = g->adj_list[i];

        while (tmp != NULL) {
            del = tmp;
            tmp = tmp->link;
            free(del);
        }
    }
}
#endif