#include <stdio.h>
#include <string.h>

void noverlap(char str[]);	//중복되는 공백 없애기
void e(char str[]);	//e가 들어간 단어 대문자 출력
void f(char str[]);	//공백 특수문자 치환
void l(char str[]);	//문자열 길이
void c(char str[]);	//대소문자 치환
void a(char str[]);	//문자 이동


int main() {

	char str[60] = "example";
	char order;	//명령 입력

	printf("Enter the script\n");
	scanf("%[^\n]", &str); //문자열 전체 입력

	noverlap(str);	//중복된 공백 제거

	printf("Enter the order\n");
	

	while (true) {

		scanf("%c", &order);

		if (order == 'e' || order == 'E') {
			e(str);
		}

		if (order == 'f' || order == 'F') {
			f(str);
		}

		if (order == 'l' || order == 'L') {
			l(str);
		}

		if (order == 'c' || order == 'C') {
			c(str);
		}

		if (order == 'a' || order == 'A') {
			a(str);
		}

		if (order == 'q' || order == 'Q') {
			printf("Shuting down");
			return 0;
		}

	}
}

void noverlap(char str[]) {
	char temp[60];
	int i{0};
	int j{0};

	for (i = 0; str[i] != 0;i++) {	//연속된 공백을 제외한 문자열을 temp에 저장
		if (str[i] == ' ' && str[i + 1] == ' ') {}

		else {

			temp[j] = str[i];

			j++;
		}
	}

	temp[j] = 0;
	j = 0;
	for (i = 0; temp[i] != 0; i++) {	//temp에 저장된 문자열을 str에 다시 저장
		
		str[i] = temp[i];
		j++;
	}
	str[j] = 0;
}

void e(char str[]) {
	int i{ 0 };
	int j{ 0 };
	int k{ 0 };
	int t{ 0 };

	while (str[i]) {

		if (i == 0) {

			if (str[i] == 'E' || str[i] == 'e') {	//str[0]이 e일 경우 뒷부분 공백만 검사

				while (str[j] != ' ') {

					if (str[j] >= 'a' && str[j] <= 'z') {
						str[j] = str[j] - 32;
					}

					j++;
				}
			}
		}

		else {

			if (str[i] == 'E' || str[i] == 'e') {	//중간에 e가 나올경우 앞 뒤에 공백을 검사

				k = i;
				t = i;

				while (str[k] != ' ') {

					if (str[k] >= 'a' && str[k] <= 'z') {
						str[k] = str[k] - 32;
					}

					k++;
				}

				while (str[t] != ' ') {

					if (str[t] >= 'a' && str[t] <= 'z') {
						str[t] = str[t] - 32;
					}

					t--;
				}
			}
		}
		i++;
	}

	printf("%s\n", str);
}

void f(char str[]) {
	int i{0};

	while (str[i]) {
		if (str[i] == 32) {	//해당 문자열이 공백일경우 특수기호로 변경
			str[i] = 64;
		}

		else if (str[i] == 64) {	//해당 문자열이 특수기호일경우 공백으로 변경
			str[i] = 32;
		}

		i++;
	}

	printf("%s\n", str);
};

void l(char str[]) {
	int i{0};
	int j{ 0 };

	for (i; str[i] != 0; i++) {	//공백의 수만큼 j에 저장
		
		if (str[i] == ' ') {
			j++;
		}
	}

	printf("Result : %d", j + 1);

}

void c(char str[]) {
	
	int i{0};

	while (str[i]) {
		if (str[i] >= 'a' && str[i] <= 'z') {	//소문자일 경우
			str[i] = str[i] - 32;	//대문자로 전환
		}
		
		else if(str[i] >= 'A' && str[i] <= 'Z') {	//대문자일 경우
			str[i] = str[i] + 32;	//소문자로 전환
		}

		i++;
	}

	printf("%s\n", str);
}

void a(char str[]) {
	int i{0};
	int len{0}; //문자열 길이
	char temp{0}; // str[0] 저장할 매개체 선언

	len = strlen(str);

	temp = str[0];	//str[0] 변환

	for (i; i < len; i++) {

		str[i] = str[i + 1];

	}

	str[len-1] = temp;

	printf("%s\n", str);

};