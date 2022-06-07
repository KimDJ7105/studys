#include<stdio.h>
#include <stdlib.h>

#define PROB 2

#if PROB == 1

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

struct Edge { // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int en; // 간선의 개수
    int vn; // 정점의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;


//union-find 프로그램 구현 
int parent[MAX_VERTICES];

void set_init(int n) {
    for(int i = 0 ; i < n ; i++) {
        parent[i] = -1;
    }
}

int set_find(int curr){
    if(parent[curr] == -1) return curr;

    while(parent[curr] != -1) curr = parent[curr];

    return curr;
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);

    if(root1 != root2) parent[root1] = root2;
}

//그래프 관련 함수
void graph_init(GraphType* g);
void set_nodes(GraphType* g, int n);
void insert_edge(GraphType* g, int start, int end, int w);
//qsort에 필요한 함수
int compare(const void* a, const void* b); 
//kruskal함수
void kruskal(GraphType* g);


int main() {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    // test data 1 
    set_nodes(g, 7);
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);
/*
// test data 2
    set_nodes(g, 8);
    insert_edge(g, 0, 1, 10);
    insert_edge(g, 0, 3, 6);
    insert_edge(g, 0, 7, 1);
    insert_edge(g, 1, 2, 4);
    insert_edge(g, 1, 5, 2);
    insert_edge(g, 2, 3, 11);
    insert_edge(g, 2, 5, 7);
    insert_edge(g, 3, 7, 3);
    insert_edge(g, 4, 5, 5);
    insert_edge(g, 4, 7, 8);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 6, 7, 12);
*/
    kruskal(g);
    free(g);
    return 0;
}

void graph_init(GraphType* g) {
    g->vn = 0;
    g->en = 0;
    for(int i = 0 ; i <2*MAX_VERTICES ; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void set_nodes(GraphType* g,int n) {
    g->vn =n;
}

void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->en].start = start;
    g->edges[g->en].end = end;
    g->edges[g->en].weight = w;
    g->en++;
}

int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;

    return (x->weight - y->weight);
}

void kruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset, min_w = 0;
    struct Edge e;

    set_init(g->vn);
    qsort(g->edges,g->en,sizeof(struct Edge), compare);

    printf("크루스칼 최소 신장 트리 알고리즘\n");
    int i = 0;
    while(edge_accepted < (g->vn - 1)) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);

        if(uset != vset) {
            printf("간선 (%d,%d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            min_w += e.weight;
            set_union(uset,vset);
        }
        i++;
    }

    printf("\n최소 비용  = %d\n", min_w);
}

#elif PROB == 2

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L
#define N_NODE 7

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n);
void prim(GraphType*, int);


int main() {
    int i;
    //test data1
    GraphType g = { N_NODE,
    {{ 0, 29, INF, INF, INF, 10, INF },
    { 29, 0, 16, INF, INF, INF, 15 },
    { INF, 16, 0, 12, INF, INF, INF },
    { INF, INF, 12, 0, 22, INF, 18 },
    { INF, INF, INF, 22, 0, 27, 25 },
    { 10, INF, INF, INF, 27, 0, INF },
    { INF, 15, INF, 18, 25, INF, 0 } }
    };

    //test data2
    /*
    GraphType g = { N_NODE,
    { { 0, 10, INF, 6, INF, INF, INF, 1 },
    { 10, 0, 4, INF, INF, 2, INF, INF },
    { INF, 4, 0, 11, INF, 7, INF, INF },
    { 6, INF, 11, 0, INF, INF, INF, 3 },
    { INF, INF, INF, INF, 0, 5, INF, 8},
    { INF, 2, 7, INF, 5, 0, 9, INF },
    { INF, INF, INF, INF, INF, 9, 0, 12 },
    { 1, INF, INF, 3, 8, INF, 12, 0 }
    }
    };
    */

    prim(&g, 0);
    return 0;
}

int get_min_vertex(int n) {
    int v, i;
    for (i = 0; i < n; i++) {
        if (!selected[i]) {     //i를 방문한적이 없다면
            v = i;
            break;
        }
    }

    for (i = 0; i < n; i++) {
        if (!selected[i] && (distance[i] < distance[v])) v = i;
    }

    return (v);
}

void prim(GraphType* g, int s) {
    int i, u, v, min_vlue = 0;

    for (u = 0; u < g->n; u++) distance[u] = INF;

    distance[s] = 0;

    for (i = 0; i < g->n; i++) {
        u = get_min_vertex(g->n);

        selected[u] = TRUE;
        if (distance[u] == INF) return;

        printf("정점 %d 추가, distance = %d\n", u, distance[u]);
        min_vlue += distance[u];

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF) {
                if (!selected[v] && g->weight[u][v] < distance[v]) distance[v] = g->weight[u][v];
            }
        }
    }

    printf("\n최소 비용 = %d", min_vlue);
}


#endif