#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 101


typedef struct {
    int degree;
    float coef[MAX_NUM];
}Polynomial;

void print_poly(Polynomial p);

Polynomial read_poly();

Polynomial add_poly(Polynomial a, Polynomial b);

Polynomial mult_poly(Polynomial a, Polynomial b);

int main() {

    Polynomial x, y, a, b;
    printf("\t함수 X\n");
    x = read_poly();
    printf("\t함수 Y\n");
    y = read_poly();

    a = add_poly(x, y);
    b = mult_poly(x, y);

    print_poly(a);
    print_poly(b);

    return 0;

}

void print_poly(Polynomial p) {

    int i;

    printf("X + Y = ");

    for (i = 0; i < p.degree; i++) {

        printf("%5.1f x^%d ", p.coef[i], p.degree - i);

        if (p.coef[i + 1] > 0)

            printf("+");

    }

    printf("%4.1f\n", p.coef[p.degree]);

}

Polynomial read_poly() {

    int i;

    Polynomial p;



    printf("다항식의 최고 차수 입력: ");

    scanf_s("%d", &p.degree);

    printf("각 항의 계수를 입력하시오 :\n");

    for (i = 0; i <= p.degree; i++) {
        printf("%d차 : ", p.degree - i);
        scanf_s("%f", p.coef + i);
    }
    return p;

}


Polynomial add_poly(Polynomial a, Polynomial b) {

    int i;

    Polynomial p;

    if (a.degree > b.degree) {

        p = a;

        for (i = 0; i <= b.degree; i++) {
            p.coef[i + (p.degree - b.degree)] += b.coef[i];
        }
    }

    else {

        p = b;

        for (i = 0; i <= a.degree; i++) {
            p.coef[i + (p.degree - a.degree)] += a.coef[i];
        }
    }

    return  p;

}

Polynomial mult_poly(Polynomial a, Polynomial b) {

    int i, j;

    Polynomial p;

    for (i = 0; i < a.degree + b.degree + 1; i++) {
        p.coef[i] = 0;
    }

    p.degree = a.degree + b.degree;

    for (i = 0; i < a.degree + 1; i++) {
        for (j = 0; j < b.degree + 1; j++) {

            p.coef[i + j] = p.coef[i + j] + a.coef[i] * b.coef[j];
        }
    }

    return p;

}