#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


/*

명령어 입력할때 스페이스바 치고 입력해야 작동됨

*/
struct player {
	int x{0};
	int y{0};
	char shape = 'o';

	int* ptr_x = &x;
	int* ptr_y = &y;
	char* ptr_shape = &shape;

};

void move1(struct player p1, char o);	//플레이어 1의 이동 함수
void move2(struct player p1, char o);	//플레이어 2의 이동 함수
void make_shape(struct player p);	//말의 모습을 정하는 함수
void show_map(char map[10][10]);	//맵을 출력하는 함수

int main() {

	char map[10][10] = {0, };
	char order = 'a';

	struct player p1, p2;

	re:

	p1.x = 1;
	p1.y = 1;
	make_shape(p1);	//말의 위치와 모양을 초기화

	p2.x = 8;
	p2.y = 8;
	make_shape(p2);	//말의 위치와 모양을 초기화

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			map[i][j] = ' ';
		}
	}	//맵의 각 부분을 공백으로 지정

	map[p1.y][p1.x] = p1.shape;
	map[p2.y][p2.x] = p2.shape;	//맵의 각 위치에 말을 생성

	show_map(map);	//맵 출력

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			map[i][j] = ' ';
		}
	}	//맵의 각 부분을 공백으로 지정

	while (true) {

		getchar();
		scanf(" %c", &order);

		if (order == 'q') {
			return 0;
		}

		if (order == 'r') {
			goto re;
		}

		move1(p1,order);

		if (p1.x == p2.x && p1.y == p2.y) {
			Beep(340, 500);

			make_shape(p2);
			map[p1.y][p1.x] = p1.shape;

			show_map(map);
		}

		if (p1.x != p2.x || p1.y != p2.y) {
			map[p1.y][p1.x] = p1.shape;
			map[p2.y][p2.x] = p2.shape;

			show_map(map);
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {

				map[i][j] = ' ';
			}
		}	//맵의 각 부분을 공백으로 지정

		getchar();

		scanf(" %c", &order);

		if (order == 'q') {
			return 0;
		}

		if (order == 'r') {
			goto re;
		}


		move2(p2,order);

		if (p2.x == p1.x && p2.y == p1.y) {
			Beep(340, 500);

			make_shape(p1);
			map[p2.y][p2.x] = p2.shape;

			show_map(map);
		}

		if (p2.x != p1.x || p2.y != p1.y) {
			map[p1.y][p1.x] = p1.shape;
			map[p2.y][p2.x] = p2.shape;

			show_map(map);
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {

				map[i][j] = ' ';
			}
		}	//맵의 각 부분을 공백으로 지정

	}



}

void move1(struct player p1 , char o ) {

	if (o == 'w') {
		if (p1.y == 0) {

			*p1.ptr_y = 9;

			make_shape(p1);
		}

		else {
			*p1.ptr_y = *p1.ptr_y - 1;
		}
	}

	if (o == 's') {
		
		if (p1.y == 9) {
			*p1.ptr_y = 0;

			make_shape(p1);
		}

		else {
			*p1.ptr_y = *p1.ptr_y;
		}
	}

	if (o == 'a') {

		if (p1.x == 0) {

			*p1.ptr_x = 9;

			make_shape(p1);
		}

		else {
			*p1.ptr_x = *p1.ptr_x - 1;
		}
	}

	if (o == 'd') {
		
		if (p1.x == 9) {
			*p1.ptr_x = 0;

			make_shape(p1);
		}

		else {

			*p1.ptr_x = *p1.ptr_x + 1;
		}
	}	

}

void move2(struct player p1, char o) {


	if (o == 'i') {
		if (p1.y == 0) {

			*p1.ptr_y = 9;

			make_shape(p1);
		}

		else {
			*p1.ptr_y = *p1.ptr_y - 1;
		}
	}

	if (o == 'k') {

		if (p1.y == 9) {
			*p1.ptr_y = 0;

			make_shape(p1);
		}

		else {
			*p1.ptr_y = *p1.ptr_y + 1;
		}
	}

	if (o == 'j') {
		if (p1.x == 0) {

			*p1.ptr_x = 9;

			make_shape(p1);
		}

		else {
			*p1.ptr_x = *p1.ptr_x - 1;
		}
	}

	if (o == 'l') {

		if (p1.x == 9) {
			*p1.ptr_x = 0;

			make_shape(p1);
		}

		else {

			*p1.ptr_x = *p1.ptr_x + 1;
		}
	}

}

void make_shape(struct player p) {
	
	int temp{0};

	srand(time(NULL));

	temp = rand() % 5;

	if (temp == 0) {

		*p.ptr_shape = 'g';
	}

	if (temp == 1) {
		*p.ptr_shape = 'a';
	}

	if (temp == 2) {
		*p.ptr_shape = 'm';
	}

	if (temp == 3) {
		*p.ptr_shape = 'e';
	}

	if (temp == 4) {
		*p.ptr_shape = 'o';
	}
}

void show_map(char map[10][10]) {

	char map_border = '|';
	int c{0};

	for (int i = 0; i < 10; i++) {

		if (i < 9) {

			printf("---------------------\n");

			for (int j = 0; j < 10; j++) {

				if (j < 9) {
					printf("%c", map_border);
					printf("%c", map[i][j]);
				}

				if (j == 9) {
					printf("%c", map_border);

					printf("%c", map[i][j]);

					printf("%c\n", map_border);
				}
			}
		}

		if (i == 9) {
			printf("---------------------\n");

			for (int j = 0; j < 10; j++) {

				if (j < 9) {
					printf("%c", map_border);
					printf("%c", map[i][j]);
				}

				if (j == 9) {
					printf("%c", map_border);

					printf("%c", map[i][j]);

					printf("%c\n", map_border);
				}
			}
			printf("---------------------\n");

		}
	}
}