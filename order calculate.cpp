#include <stdio.h>

int selec(char a);	//입력받은 연산자를 숫자로 치환해주는 함수
int cal(int n[5], char e[4]);	//계산하는 함수

int main() {

	int n[5] = {0, };
	char e[4] = { 0, };
	int result{ 0 };

	scanf("%d%c%d%c%d%c%d%c%d", &n[0], &e[0], &n[1], &e[1], &n[2], &e[2], &n[3], &e[3], &n[4]);

	printf("%d%c%d%c%d%c%d%c%d = ", n[0], e[0], n[1], e[1], n[2], e[2], n[3], e[3], n[4]);

	result = cal(n, e);

	printf("%d", result);

	

}

int selec(char a) {

	if (a == '+') {

		return 1;
	}

	if (a == '-') {

		return 2;
	}

	if (a == '*') {

		return 3;
	}

	if (a == '/') {

		return 4;
	}
}

int cal(int n[5], char e[4]) {

	int c[4] = {0, };

	int j{ 1 };

	for (int i = 0; i < 4; i++) {	//연산자를 숫자로 변환해 저장

		c[i] = selec(e[i]);
	}

	for (int i = 0; i < 4; i++) {	//곱하기, 나누기부터 실행

		switch (c[i]) {

		case 3:
			n[i + 1] = n[i] * n[i + 1];

			c[i] = 0;	//연산이 끝난 연산자는 구분

			break;

		case 4:

			n[i + 1] = n[i] / n[i + 1];

			c[i] = 0;

			break;

		default:

			break;
		}

	}

	for (int i = 0; i < 4; i++) {

		re:

		switch (c[i]) {

		case 1:

			if (c[i + j] == 0) {	//앞의 계산이 이미 시행된 경우

				j++;
				goto re;

			}

			n[i + j] = n[i] + n[i + j];	//곱하기 혹은 나누기의 결과값과 계산

			j = 1;
			c[i] = 0;
			break;

		case 2:

		    if (c[i + j] == 0) {

					j++;
					goto re;
		    }

			n[i + j] = n[i] - n[i + j];

			j = 1;
			c[i] = 0;

			break;

		default :
			break;
		}

	}

	return n[4];
}
