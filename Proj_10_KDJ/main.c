#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct _sparse_matrix {
    element data;
    int row;
    int col;
    struct _spaese_matrix* link;
} node;

typedef struct _Head {
    int m_row,m_col;
    node* h_link;
} head;

void add_data(head* h,element data, int row, int col,int offer);
int is_empty(head* h);
void print_matrix(head* h);
void print_list(head* h);
head* add_mat(head* a, head* b);
head* sub_mat(head* a,head* b);
head* mat_trans(head* h);
void free_matrix(head* h);

//속성페이지 디버그 탭에서 명령인수에 <test.txt를 입력시 test.txt 에서 명령을 받음 
//>result.txt 를 하면 결과를 result.txt 에 결과를 저장
int main() {
    head mat_a, mat_b;
    head* mat_c,* mat_d,* mat_e;
    int row,col,item = 0;

    scanf("%d %d", &row,&col);

    mat_a.m_row = row;
    mat_b.m_row = row;

    mat_a.m_col = col;
    mat_b.m_col = col;

    mat_a.h_link = NULL;
    mat_b.h_link = NULL;

    for (int i = 1; i <= row; i++) {
        for(int j = 1 ; j <= col ; j++ ) {
            scanf("%d", &item);
            
            if(item != 0) {
                add_data(&mat_a,item,i,j,0);
            }
        }
    }

    for (int i = 1; i <= row; i++) {
        for(int j = 1 ; j <= col ; j++ ) {
            scanf("%d", &item);
            if(item != 0) {
                add_data(&mat_b,item,i,j,0);
            }
        }
    }
    printf("\n행렬 A 리스트\n\n");
    print_list(&mat_a);
    printf("\n행렬 B 리스트\n\n");
    print_list(&mat_b);

    printf("\n행렬 A\n\n");
    print_matrix(&mat_a);
    printf("\n행렬 B\n\n");
    print_matrix(&mat_b);

    printf("\n행렬 C = A + B\n\n");
    mat_c = add_mat(&mat_a, &mat_b);
    print_matrix(mat_c);
    printf("\n행렬 C 리스트\n\n");
    print_list(mat_c);

    printf("\n행렬 D = A - B\n\n");
    mat_d = sub_mat(&mat_a, &mat_b);
    print_matrix(mat_d);
    printf("\n행렬 D 리스트\n\n");
    print_list(mat_d);

    printf("\n행렬 E = TRANCEPOSE(A)\n\n");
    mat_e = mat_trans(&mat_a);
    print_matrix(mat_e);
    printf("\n행렬 E 리스트\n\n");
    print_list(mat_e);

    free_matrix(&mat_a);
    free_matrix(&mat_b);
    free_matrix(mat_c);
    free_matrix(mat_d);
    free_matrix(mat_e);
}

void add_data(head* h,element item, int row, int col, int offer) {
    node* newnode;
    node* p, *q;
    newnode = (node*)malloc(sizeof(node));
    int check = 0;
    
    newnode->data = item;
    if (offer == 2) newnode->data = 0 - item;
    newnode->row = row;
    newnode->col = col;
    
    if(h->h_link == NULL) {
        h->h_link = newnode;
        newnode->link = NULL;
    }
    
    else {
        p = h->h_link;
        if (p->row > row) {
            newnode->link = p;
            h->h_link = newnode;
        }

        else if (p->row == row && p->col > col) {
            newnode->link = p;
            h->h_link = newnode;
        }

        else if (p->row == row && p->col == col) {
                p->data += newnode->data;
                free(newnode);
        }

        else {

            while (p->link != NULL) {
                q = p->link;
                if (q->row > row) {
                    newnode->link = q;
                    p->link = newnode;
                    check = 1;
                    break;
                }

                else if (q->row == row && q->col > col) {
                    newnode->link = q;
                    p->link = newnode;
                    check = 1;
                    break;
                }

                else if (q->row == row && q->col == col) {
                        q->data += newnode->data;
                        free(newnode);
                        check = 1;
                    break;
                }

                else {
                    p = p->link;
                }
            }

            if (check == 0) {
                p->link = newnode;
                newnode->link = NULL;
            }
        }
    }
}

int is_empty(head* h) {
    if(h->h_link == NULL) return 1;

    else return 0;
}

void print_matrix(head* h) {
    int x = h->m_row;
    int y = h->m_col;
    node* p = h->h_link;

    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            if (p->row == i && p->col == j) {
                printf("%d ", p->data);
                if (p->link != NULL) {
                    p = p->link;
                }
            }

            else printf("%d ", 0);

            if (j == y) printf("\n");
        }
    }
}

void print_list(head* h) {
    node* p;
    p = h->h_link;

    while (p->link != NULL) {
        printf("(%d %d) = %d\n", p->row, p->col, p->data);
        p = p->link;
    }

    printf("(%d %d) = %d\n", p->row, p->col, p->data);
}

head* add_mat(head* a, head* b) {
    head* result;
    node* n_a;
    node* n_b;

    result = (head*)malloc(sizeof(head));

    n_a = a->h_link;
    n_b = b->h_link;

    result->m_row = a->m_row;
    result->m_col = a->m_col;
    result->h_link = NULL;

    while (n_a->link != NULL) {
        add_data(result, n_a->data, n_a->row, n_a->col,1);
        n_a = n_a->link;
    }

    add_data(result, n_a->data, n_a->row, n_a->col,1);
    
    while (n_b->link != NULL) {
        add_data(result, n_b->data, n_b->row, n_b->col,1);
        n_b = n_b->link;
    }

    add_data(result, n_b->data, n_b->row, n_b->col,1);
    
    return result;
}

head* sub_mat(head* a,head* b) {
    head* result;
    node* n_a;
    node* n_b;

    result = (head*)malloc(sizeof(head));

    n_a = a->h_link;
    n_b = b->h_link;

    result->m_row = a->m_row;
    result->m_col = a->m_col;
    result->h_link = NULL;

    while (n_a->link != NULL) {
        add_data(result, n_a->data, n_a->row, n_a->col,1);
        n_a = n_a->link;
    }

    add_data(result, n_a->data, n_a->row, n_a->col,1);

    while (n_b->link != NULL) {
        add_data(result, n_b->data, n_b->row, n_b->col,2);
        n_b = n_b->link;
    }

    add_data(result, n_b->data, n_b->row, n_b->col,2);


    return result;
}

head* mat_trans(head* h) {
    head* result;
    node* n;

    result = (head*)malloc(sizeof(head));

    result->m_row = h->m_row;
    result->m_col = h->m_col;
    result->h_link = NULL;

    n = h->h_link;

    while (n->link != NULL) {
        add_data(result, n->data, n->col, n->row,1);
        n = n->link;
    }

    add_data(result, n->data, n->col, n->row,1);

    return result;
}

void free_matrix(head* h) {
    node* n,* p;

    n = h->h_link;

    while(n->link != NULL) {
        p = n->link;
        free(n);
        n = p;
    }
}