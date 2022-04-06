//-유니온 활용
#define _CRR_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define PROB 2
#define MAX_SIZE 6
#define MAX_STACK 101

#if PROB == 1
#include "stack_fx.h"

int check_pri(char item);

int main() {

	char* expr = "100 + 11 - 20 * ( 20 + 10 ) / 100 + 5 - 3";
	s_type s;
	char temp, top_on;
	char post[MAX_STACK_SIZE] = {0,};
	int count = 0;
	int len = strlen(expr);
	int data_num;
	char toi[3];
	int data1, data2;

	printf("후위 표기 수식 : ");

	init_stack(&s);

	for (int i = 0; i < len; i++) {
		temp = expr[i];

		switch (temp) {
		case '+': case '-':case '/':case '*':
			while (is_empty(&s) != 1 && (check_pri(temp) <= check_pri(peek_oper(&s)))) {
				top_on = pop_oper(&s);
				printf("%c", top_on);
				post[count++] = top_on;
			}

			push_oper(&s, temp);
			break;
		case '(':
			push_oper(&s, temp);
			break;
		case ')':
			top_on = pop_oper(&s);
			while (top_on != '(') {
				printf("%C", top_on);
				post[count++] = top_on;
				top_on = pop_oper(&s);
			}
			break;
		case ' ':
			if (expr[i - 1] == ' ' || expr[i + 1] == ' ') {
				printf("연속 공백 오류");
				exit(1);
			}

			post[count++] = temp;
			printf("%c", temp);
			break;
		default:
			printf("%c", temp);
			post[count++] = temp;
			break;
		}
	
	}

	while (is_empty(&s) != 1) {
		temp = pop_oper(&s);
		printf("%c", temp);
		post[count++] = temp;
	}

	len = strlen(post);

	init_stack(&s);

	for (int i = 0; i < len; i++) {
		temp = post[i];
		if (temp != '+' && temp != '-' && temp != '/' && temp != '*' && temp != ' ') {
			int n = 0;
			while (post[i] != ' ' && post[i] != '+' && post[i] != '-' && post[i] != '/' && post[i] != '*') {
				toi[n] = post[i];
				n++;
				i++;
			}

			data_num = atoi(toi);

			push_data(&s, data_num);
		}

		else if(temp != ' ') {
			data2 = pop_data(&s);
			data1 = pop_data(&s);

			switch (temp) {
			case '+': push_data(&s, data1 + data2); break;
			case '-': push_data(&s, data1 - data2); break;
			case '*': push_data(&s, data1 * data2); break;
			case '/': push_data(&s, data1 / data2); break;
			}
		}
	}
	
	printf("\n계산 결과 : %d", pop_oper(&s));

}

int check_pri(char item) {	//item은 +,-,/,*,(
	if (item == '('||item == ')') return 0;

	else if (item == '*' || item == '/') return 3;

	else if (item == '+' || item == '-') return 2;

	return -1;
}

#elif PROB == 2

typedef struct {
	short r;
	short c;
} element;

element here = { 1,0 };

typedef struct _player {
	element data[MAX_STACK];

	int top;
}player;

void init_stack(player* s);
void push(player* s, element item);
int loc_serch(int r, int c, char maze[MAX_SIZE][MAX_SIZE]);
element pop(player* s);
element peek(player* s);
int is_empty(player* s);
int is_full(player* s);
void print_maze(char maze[MAX_SIZE][MAX_SIZE]);
int check_wall(char maze[MAX_SIZE][MAX_SIZE], int r, int c);


int main() {	//무한 루프만 해결하면 됨
	char maze[MAX_SIZE][MAX_SIZE] = {
		{'1', '1', '1', '1', '1', '1'},
		{'e', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '1'},
		{'1', '0', '1', '0', '1', '1'},
		{'1', '0', '1', '0', '0', 'x'},
		{'1', '1', '1', '1', '1', '1'},
	};
	player s;
	int r, c, result = 0;
	element temp;

	init_stack(&s);

	temp = here;

	push(&s, temp);

	while (!is_empty(&s)) {

		temp = peek(&s);
		r = temp.r;
		c = temp.c;

		if (maze[r][c] == 'x') {
			printf("성공\n");
			result = 1;
			break;
		}

		else if (maze[r][c] != '.') {
			maze[r][c] = '.';
		}

		if (loc_serch(r, c - 1, maze) == 1) {
			--temp.c;
			push(&s, temp);
		}
		else if (loc_serch(r, c + 1, maze) == 1) {
			++temp.c;
			push(&s, temp);
		}

		else if (loc_serch(r - 1, c, maze) == 1) {
			--temp.r;
			push(&s, temp);
		}

		else if (loc_serch(r + 1, c, maze) == 1) {
			++temp.r;
			push(&s, temp);
		}

		else {
			pop(&s);
		}

	}

	if (result == 1) {
		print_maze(maze);

		printf("<row  col>\n");
		int s_size = s.top;
		element* route = (element*)malloc((s_size + 1) * sizeof(element));
		for (int i = s_size; i > -1; i--) {
			route[i] = pop(&s);
		}

		for (int i = 0; i < s_size + 1; i++) {
			temp = route[i];
			printf("  %d    %d\n", temp.r, temp.c);
		}
	}

	else printf("실패");

}

void init_stack(player* s) {
	s->top = -1;
}

void push(player* s, element item) {

	if (is_full(s) == 1) {
		printf("스택 포화 에러");
		exit(1);
	}

	else {
		s->data[++(s->top)] = item;
	}
}

int loc_serch(int r, int c,char maze[MAX_SIZE][MAX_SIZE]) {

	if (r < 0 || c < 0) return 0;
	if (r >= MAX_SIZE || c >= MAX_SIZE) return 0;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		return 1;
	}
	else return 0;
}

int is_empty(player* s) {
	if (s->top == -1) return 1;

	else return 0;
}

int is_full(player* s) {
	if (s->top == (MAX_STACK - 1)) return 1;

	else return 0;
}

element pop(player* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 오류");
		exit(1);
	}

	else return s->data[(s->top)--];
}

element peek(player* s) {
	if (is_empty(s) == 1) {
		printf("스택 공백 오류");
		exit(1);
	}

	else return s->data[s->top];
}

void print_maze(char maze[MAX_SIZE][MAX_SIZE]) {
	printf("\n");
	printf("=======MAZE======\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			printf(" %c ", maze[i][j]);
		}
		printf("\n");
	}
}

int check_wall(char maze[MAX_SIZE][MAX_SIZE], int r, int c) {
	if (maze[r][c + 1] != '0' && maze[r][c - 1] != '0' && maze[r + 1][c] != '0' && maze[r - 1][c] != '0') {

		if (maze[r][c + 1] != 'x' && maze[r][c - 1] != 'x' && maze[r + 1][c] != 'x' && maze[r - 1][c] != 'x') {
			return 0;
		}

		else return 1;
	}

	else return 1;
}

#endif
