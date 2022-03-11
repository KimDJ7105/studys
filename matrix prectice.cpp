#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void a(int num[4][5]);	//1행 1열에서 행으로 오름차순
void d(int num[4][5]);	//1행 5열에서 열을 따라 내림차순
void e(int num[4][5]);	//짝수만 출력
void o(int num[4][5]); //홀수만 출력
void m(int num[4][5]);	//최대값 출력
void n(int num[4][5]);	//최솟값 출력
void p(int num[4][5]);	//한 행의 값을 모두 더해 행의 1열에 저장
void r(int num[4][5]);	//랜덤하게 재정렬 < 실패
void s(int num[4][5]);	//다시 입력받기
void show(int num[4][5]);	//행렬을 출력하는 함수
//종료용 q

int main() {

	int num[4][5] = { 0, };
	char order = ' ';

	s(num);
	
	printf("generated random number :\n");

	show(num);

	printf("Enter the order\n");
	printf("please choose order form the list below\n");
	printf("1. a\t2. d\t3. e\t4. o\t5. m\t6. n\t7. p\t8. r\t9. s\t10. q\n");

	while (true) {

		scanf("%c", &order);

		if (order == 'a' || order == 'A') {

			a(num);
			show(num);
		}

		if (order == 'd' || order == 'D') {

			d(num);
			show(num);
		}

		if (order == 'e' || order == 'E') {
			
			e(num);
		}

		if (order == 'o' || order == 'O') {

			o(num);
		}

		if (order == 'm' || order == 'M') {

			m(num);
		}

		if (order == 'n' || order == 'N') {

			n(num);
		}

		if (order == 'p' || order == 'P') {

			p(num);
			show(num);
		}

		if (order == 's' || order == 'S') {

			s(num);
			show(num);
		}

		else if (order == 'r' || order == 'R') {
			r(num);
			show(num);
		}

		if (order == 'q' || order == 'Q') {

			return 0;
		}

		
	}

}

void a(int num[4][5]) {
	int temp_num[20] = { 0, };
	int temp{ 0 };
	int i{ 0 };
	int j{ 0 };
	int n{ 0 };

	for (i;i < 4;i++) { //2차원 배열을 1차원 배열에 저장
		for (j = 0; j < 5;j++) {
			temp_num[n] = num[i][j];
			n++;
		}
	}

	for (i = 0;i < 19;i++) {

		for (j = 0; j < 19 - i;j++) {	//1차원 배열을 오름차순으로 정렬

			if (temp_num[j] > temp_num[j + 1]) {
				temp = temp_num[j];
				temp_num[j] = temp_num[j+1];
				temp_num[j + 1] = temp;

			}
		}
	}

	n = 0;

	for (i = 0;i < 4;i++) {	//정렬된 1차원 배열을 2차원 배열에 저장
		for (j = 0; j < 5;j++) {
			num[i][j] = temp_num[n];
			n++;
		}
	}


};

void d(int num[4][5]) {

	int temp_num[20] = { 0, };
	int temp{ 0 };
	int i{ 0 };
	int j{ 0 };
	int n{ 0 };

	for (i;i < 4;i++) {	//2차원 배열을 1차원 배열에 저장
		for (j = 0; j < 5;j++) {
			temp_num[n] = num[i][j];
			n++;
		}
	}

	for (i = 0;i < 19;i++) {

		for (j = 0; j < 19 - i;j++) {	//1차원 배열을 내림차순 정렬

			if (temp_num[j] < temp_num[j + 1]) {
				temp = temp_num[j];
				temp_num[j] = temp_num[j + 1];
				temp_num[j + 1] = temp;

			}
		}
	}

	n = 0;

	for (i = 4;i >=0 ;i--) {	//1차원 배열의 값을 2차원 배열에 저장
		for (j = 0; j <4;j++) {
			num[j][i] = temp_num[n];
			n++;
		}
	}

}

void e(int num[4][5]) {
	int i{ 0 }, j{ 0 };
	int temp_num[4][5] = { 0, };

	for (i; i < 4;i++) {

		for (j=0;j < 5;j++) {

			if (num[i][j] % 2 == 0) {
				temp_num[i][j] = num[i][j];
			}

			else {

				temp_num[i][j] = 0;
			}
		}
	}

	i = 0;

	for (i; i < 4;i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", temp_num[i][0], temp_num[i][1], temp_num[i][2], temp_num[i][3], temp_num[i][4]);
	}


}

void o(int num[4][5]) {
	int i{ 0 }, j{ 0 };
	int temp_num[4][5] = { 0, };

	for (i; i < 4;i++) {

		for (j = 0;j < 5;j++) {

			if (num[i][j] % 2 != 0) {
				temp_num[i][j] = num[i][j];
			}

			else {

				temp_num[i][j] = 0;
			}
		}
	}

	i = 0;

	for (i; i < 4;i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", temp_num[i][0], temp_num[i][1], temp_num[i][2], temp_num[i][3], temp_num[i][4]);
	}

}

void m(int num[4][5]) {
	int temp_num[20] = { 0, };
	int temp{ 0 };
	int i{ 0 };
	int j{ 0 };
	int n{ 0 };

	for (i;i < 4;i++) { //2차원 배열을 1차원 배열에 저장
		for (j = 0; j < 5;j++) {
			temp_num[n] = num[i][j];
			n++;
		}
	}

	for (i = 0;i < 19;i++) {	//최대값 찾기

		for (j = 0; j < 19 - i;j++) {

			if (temp_num[j] < temp_num[j + 1]) {
				temp = temp_num[j];
				temp_num[j] = temp_num[j + 1];
				temp_num[j + 1] = temp;

			}
		}
	}

	n = 1;

	for (i = 0; i < 4; i++) {

		for (j = 0;j < 5;j++) {

			if (n % 5 != 0) {

				if (num[i][j] == temp_num[0]) {
					printf("%d\t", num[i][j]);

					n++;
				}

				else {
					printf("%d\t", 0);

					n++;
				}
			}

			else {

				if (num[i][j] == temp_num[0]) {
					printf("%d\n", num[i][j]);

					n++;
				}

				else {
					printf("%d\n", 0);

					n++;
				}
			}
		}
	}

}

void n(int num[4][5]) {
	int temp_num[20] = { 0, };
	int temp{ 0 };
	int i{ 0 };
	int j{ 0 };
	int n{ 0 };

	for (i;i < 4;i++) { //2차원 배열을 1차원 배열에 저장
		for (j = 0; j < 5;j++) {
			temp_num[n] = num[i][j];
			n++;
		}
	}

	for (i = 0;i < 19;i++) {	//최솟값 찾기

		for (j = 0; j < 19 - i;j++) {

			if (temp_num[j] < temp_num[j + 1]) {
				temp = temp_num[j];
				temp_num[j] = temp_num[j + 1];
				temp_num[j + 1] = temp;

			}
		}
	}

	n = 1;

	for (i = 0; i < 4; i++) {

		for (j = 0;j < 5;j++) {
			if (n % 5 != 0) {

				if (num[i][j] == temp_num[19]) {
					printf("%d\t", num[i][j]);

					n++;
				}

				else {
					printf("%d\t", 0);

					n++;
				}
			}

			else {

				if (num[i][j] == temp_num[19]) {
					printf("%d\n", num[i][j]);

					n++;
				}

				else {
					printf("%d\n", 0);

					n++;
				}
			}
		}
	}
}

void p(int num[4][5]) {

	for (int i = 0; i < 4; i++) {
		num[i][0] = num[i][1] + num[i][2] + num[i][3] + num[i][4];
	}
}


void r(int num[4][5]) {

	int temp_num[4][5];

	for (int i = 0; i < 4;i++) {

		for (int j = 0; j < 5;j++) {
			temp_num[i][j] = num[4][5];
		}
	}

	for (int i = 0; i < 4;i++) {
		num[i][0] = temp_num[i][4];
		num[i][1] = temp_num[i][3];
		num[i][2] = temp_num[i][2];
		num[i][3] = temp_num[i][1];
		num[i][4] = temp_num[i][0];
	}


}

void s(int num[4][5]) {

	int i{ 0 };
	int	j{ 0 };
	int n{ 0 };
	int ranum[20] = { 0, };

	srand(time(NULL));

	for (i; i < 4;i++) {

		for (j = 0; j < 5;j++) {

			ranum[n] = (rand() % 50) + 1;

			num[i][j] = ranum[n];

			n++;

		}

	}

};

void show(int num[4][5]) {

	int i{ 0 };

	for (i; i < 4;i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", num[i][0], num[i][1], num[i][2], num[i][3], num[i][4]);
	}

};