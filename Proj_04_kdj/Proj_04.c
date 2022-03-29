#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define PROB 1
#define MAX_NUM 101

#if PROB == 1

typedef struct _node {

    double coef;
    int expon;
    struct _node*  next;

} node;

node* createNode(double coef, int expon);   //새로운 노드를 생성하는 함수
void deleteNode(node** root);   //노드를 자유롭게 해주는 함수
void polyPrint(node* poly); //함수를 출력해주는 함수
void addNode(node** root, double coef, int expon);  //새로운 node를 link시켜주는 함수
node* polyAdd(node* poly1, node* poly2);    //함수 덧셈
node* polyMult(node* poly1, node* poly2);   //함수 곱셈
node* createPoly(); //함수를 만드는 함수

int main() {

    node* p1 = NULL;
    node* p2 = NULL;
    node* p3 = NULL;
    node* p4 = NULL;

    printf("\tP1(x) 입력\n");

    p1 = createPoly();

    printf("P1(x) = ");
    polyPrint(p1);

   
    printf("\tP2(x) 입력\n");
       
    p2 = createPoly();

    printf("P2(x) = ");
    polyPrint(p2);
        
    p3 = polyAdd(p1, p2);
    printf("P1(x) + p2(x) = ");
    polyPrint(p3);

    p4 = polyMult(p1, p2);
    printf("P1(x) * p2(x) = ");
    polyPrint(p4);

    deleteNode(&p1);
    deleteNode(&p2);
    deleteNode(&p3);
    deleteNode(&p4);

    return 0;
}

node* createNode(double coef, int expon) {

    node* p = (node*)malloc(sizeof(node));
    p->coef = coef;
    p->expon = expon;
    p->next = NULL;

    return p;
}

void deleteNode(node** root) {

    node* p = *root;
    node* next;
    while (p) {

        next = p->next;
        free(p);
        p = next;
    }
    *root = NULL;
}

void polyPrint(node* poly) {

    node* p = poly;

    if (p->expon >= 1) {
        if (p->coef == 1) printf("x^%d", p->expon);

        else if (p->coef != 0) printf("%gx^%d", p->coef, p->expon);
    }

    else printf("%g", p->coef);

    p = p->next;

    while (p) {
        while (p->coef == 0) {  //p의 계수가 0이면 넘기기
            p = p->next;
        }

        if (p->coef > 0) printf("+");

        if (p->expon > 1) {
            if (p->coef == 1) printf("x^%d", p->expon);

            else if (p->coef != 0) printf("%gx^%d", p->coef, p->expon);
        }

        else if (p->expon == 1) {
            if (p->coef == 1) printf("x");

            else printf("%gx", p->coef);
        }

        else printf("%g", p->coef);

        p = p->next;
    }

    printf("\n");
}



void addNode(node** root, double coef, int expon) {

    node* p = *root;
    node* prev = NULL;

    if (*root == NULL) {
        *root = createNode(coef, expon);

        return;
    }

    while (p) {
        if (p->expon == expon) {
            p->coef += coef;

            break;
        }

        else if (p->expon < expon) {
            node* newnode = createNode(coef, expon);
            newnode->next = p;

            if (prev) prev->next = newnode;

            else *root = newnode;

            break;
        }

        if (p->next == NULL) {
            node* newnode = createNode(coef, expon);
            p->next = newnode;

            break;
        }

        prev = p;
        p = p->next;
    }
}

node* polyAdd(node* poly1, node* poly2) {

    node* p = NULL;
    node* p1 = poly1;
    node* p2 = poly2;

    while (p1) {
        addNode(&p, p1->coef, p1->expon);
        p1 = p1->next;
    }

    while (p2) {
        addNode(&p, p2->coef, p2->expon);
        p2 = p2->next;
    }

    return p;
}

node* polyMult(node* poly1, node* poly2) {

    node* p = NULL;
    node* p1 = poly1;
    node* p2;

    while (p1) {

        p2 = poly2;

        while (p2) {
            addNode(&p, p1->coef * p2->coef, p1->expon + p2->expon);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return p;
}

node* createPoly() {

    node* p = NULL;
    double coef;
    int i, n, expon;

    printf("다항식의 항의 갯수: ");
    scanf("%d", &n);

    for (i = 0 ; i < n ; ++i) {

        printf("계수와 지수: ");
        scanf("%lf%d", &coef, &expon);

        addNode(&p, coef, expon);
    }

    return p;
}

#elif PROB == 2

#pragma pack(push, 1)
typedef struct _namecard {
    char name[10];
    int company;
    int pnum;
} NC;
#pragma pack(pop)

void print_menu();  //명령어 출력
void get_NC(NC a[], int count);    //명함 저장
void show_NC(NC a[], int count);    //명함 전체 출력
void serch_NC(NC a[], int count);   //이름으로 명함 검색
void delete_NC(NC a[], int count, char name[]);   //이름과 일치하는 명함 삭제
void save_fp(FILE* fp , NC a[],int count);  //파일에 저장
void read_fp(FILE* fp, NC a[], int* count);     //파일을 읽어오기

int main() {

    FILE* fp;
    int menu_item;
    NC namecard[MAX_NUM];
    int count = 0;
    int n;
    int serch[10];
    
    fp = fopen("namecard.txt", "a");
    fclose(fp);

    read_fp(fp, namecard, &count);

    while (1) {
        print_menu();
        printf("명령 입력 ------>");
        scanf("%d", &menu_item);

        switch (menu_item) {
        case 1:
            printf("명함 입력\n");
            get_NC(namecard, count);
            count = count + 1;
            printf("--------------------------\n");
            break;
        case 2:
            printf("모든 명함 출력\n");
            show_NC(namecard, count);
            printf("--------------------------\n");
            break;
        case 3:
            printf("이름 검색\n");
            serch_NC(namecard, count);
            printf("--------------------------\n");
            break;
        case 4:
            printf("명함 삭제\n");
            printf("삭제할 이름을 입력하세요 :");
            scanf("%s", &serch);
            delete_NC(namecard, count, serch);
            count = count - 1;
            printf("--------------------------\n");
            break;
        case 5:
            printf("프로그램 종료");
            save_fp(fp, namecard, count);
            return 0;
            break;
        default :
            printf("잘못된 명령어 입니다\n");
        }
    }

}

void print_menu() {

    printf("============Name Card============\n");
    printf("명령어를 입력하세요\n");
    printf("1. 명함 입력\n");
    printf("2. 모든 명함 출력\n");
    printf("3. 명함 검색\n");
    printf("4. 명함 삭제\n");
    printf("5. 종료\n");
}

void get_NC(NC a[], int count) {

    int b, c;
    char str[5];
    char n[10];
    char* str2 = "yes";

    printf("이름 :");
    scanf("%s", &n);
    printf("회사 :");
    scanf("%d", &b);
    printf("전화 :");
    scanf("%d", &c);

    for (int i = 0; i < 10;i++) {
            a[count + 1].name[i] = n[i];
    }
        
    a[count + 1].company = b;    
    a[count + 1].pnum = c;
}

void show_NC(NC a[], int count) {

    for (int i = 0; i <= count; i++) {
        printf("%d. 이름 :%s 회사 :%d 전화 :%d\n", i, a[i].name, a[i].company, a[i].pnum);
    }

    printf("%d개의 명함이 존재함\n", count+1);
}

void serch_NC(NC a[], int count) {

    char key[4];
    printf("검색할 이름을 입력하세요. : ");
    scanf("%s", key);

    int searchCount = 0;

    for (int i = 0; i < count; ++i)
    {
        if (strstr(a[i].name, key) != NULL)
        {
            printf("검색한 명함 이름 : ");
            printf("이름:%s, 회사:%d, 전화:%d\n", a[i].name, a[i].company, a[i].pnum);
            ++searchCount;
        }
    }
}

void delete_NC(NC a[], int count, char name[]) {
    for (int i = 0; i <= count; i++) {
        if (a[i].name == name) {
            for (int j = i; j < count; j++) {
                a[j] = a[j + 1];
            }
        }
    }
}

void save_fp(FILE* fp, NC a[],int count) {

    if (count == 0)
        return;

    fp = fopen("namecard.txt", "wb");
    if (fp == NULL)
    {
        printf("파일 오픈 실패\n");
        exit(-1);
    }
    fwrite(a, sizeof(NC), count, fp);
    fclose(fp);
}

void read_fp(FILE* fp, NC a[], int* count) {
   
    FILE* fp = fopen("namecard.txt", "rb");
    if (fp == NULL)
    {
        fp = fopen("namecard.txt", "w+");
        fclose(fp);
        return 0;
    }
    int count = 0;
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(NC);
    fseek(fp, 0, SEEK_SET);             
    fread(a, sizeof(NC), count, fp);
    fclose(fp);
    return count;
}
#endif