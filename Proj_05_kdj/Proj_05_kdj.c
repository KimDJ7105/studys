#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 101

typedef char element;

typedef struct _stack {
	element data[MAX_STACK_SIZE];
	int top;
	int pos[MAX_STACK_SIZE];
} ST;

int is_full(ST* s);
int is_empty(ST* s);
void init_stack(ST* s);
void push(ST* s, element item,int i);
element pop(ST* s);
int check_str(ST* s, element str[]);

int main() {
	ST *s;
	element* str;

	s = (ST*)malloc(sizeof(ST));

	init_stack(s);

	printf("수식을 입력해주세요 :");
	scanf("%s", str);

	if(check_str(s, str) == 0) printf("문제 없음");

	
}

int is_full(ST* s) {
	if (s->top == MAX_STACK_SIZE) return 1;

	else return 0;
}

int is_empty(ST* s) {
	if (s->top == -1) return 1;

	else return 0;
}

void init_stack(ST* s) {
	s->top = -1;
}

void push(ST* s, element item, int i) {
		s->data[++(s->top)] = item;
		s->pos[(s->top)] = i;
}

element pop(ST* s) {
	if (is_empty(s) == 1) {
		return 'E';
	}

	else return s->data[(s->top)--];
}

int check_str(ST* s, element str[]) {

	element check;
	int n = 0;

	for (int i = 0; i < strlen(str);i++) {
		if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
			push(s, str[i], i+1);
		}

		else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
			check = pop(s);

			if (check == 'E') {
				printf("%d번째 : 스택에 데이터가 없음\n",i+1);
				n++;
			}

			else if (check  == '(' && str[i] != ')') {
				printf("%d번째, %d번째 : 괄호가 짝이 맞지 않음\n",s->pos[s->top + 1], i+1);
				n++;
			}

			else if (check == '{' && str[i] != '}') {
				printf("%d번째, %d번째 : 괄호가 짝이 맞지 않음\n", s->pos[s->top + 1], i + 1);
				n++;
			}

			else if (check == '[' && str[i] != ']') {
				printf("%d번째, %d번째 : 괄호가 짝이 맞지 않음\n", s->pos[s->top + 1], i + 1);
				n++;
			}
		}
	}

	if (is_empty(s) == 0) {
		while (is_empty(s) == 0) {
			printf("%d번째 : 페어가 되는 괄호가 없음\n", s->pos[s->top]);
			n++;
			pop(s);
		}
	}

	return n;
}