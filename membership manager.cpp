#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class member {
private:
	char name[7] = {0,};
	int num { 0 };
	int day { 0 };
	int month { 0 };
	int atd[6] = {0,};

public:

	char* getname() { return name; };
	int getnum() { return num; };
	int getday() { return day; };
	int getmonth() { return month; };
	int* getatd() { return atd; };

	void chname(char n[7]) {


		for (int i = 0;i < 7; i++) name[i] = n[i];
	};

	void chnum(int n) { num = n; };
	void chday(int n) { day = n; };
	void chmonth(int n) { month = n; };

	void chatd(int n[6]) {

		for (int i = 0; i < 6; i++) {

			atd[i] = n[i];
		}
	}

	void showmember() {
		printf("이름 : %s\n", name);
		printf("회원번호 : %d\n", num);

		if (month < 10 && day < 10) {

			printf("생년월일 : 0%d0%d\n", month, day);
		}

		if (month >= 10 && day < 10) {

			printf("생년월일 : %d0%d\n", month, day);
		}

		if (month < 10 && day >= 10) {

			printf("생년월일 : 0%d%d\n", month, day);
		}

		if (month >= 10 && day >= 10) {

			printf("생년월일 : %d%d\n", month, day);
		}
		
		for (int i = 0; i < 6; i++) {

			switch (i) {

			case 0:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			case 1:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			case 2:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			case 3:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			case 4:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			case 5:
				printf("%d월 출석 : %d\n", i+1, atd[i]);

				break;
			}
		}
	}

};

void threem(class member m[15]);	//3명의 맴버를 채우는 함수
void a(class member m[15], int c);	//맴버 추가 함수
void p(class member m[15], int c);	//모든 맴버 출력
void max(class member m[15], int c);	//출석이 가장 많은 맴버 출력
void n(class member m[15], int c);	//출석이 가장 적은 맴버 출력
void v(class member m[15], int c, int k);	//1,2,3월 동안 출석이 가장 많은 맴버 출력
void j(class member m[15], int c);	//번호순으로 내림차순 정렬
void i(class member m[15], int c);	//안돼
void k(class member m[15], int c);	//생일순으로 오름차순 정렬
void change(class member *a, class member *b);

int c{ 2 };
void plus() { c++; };

int main() {

	class member m[15];
	char order;
	
	threem(m);



	while (true) {

		printf("Enter order below\n");
		printf("1.a 2.p 3.m 4.n 5.1/2/3 6.i 7.j 8.k 9.q\n");
		printf("to see manual, enter H\n");

		scanf("%c", &order);

		if (order == 'a' || order == 'A') {

			a(m, c);
		}

		if (order == 'p' || order == 'P') {

			p(m, c);
		}

		if (order == 'm' || order == 'M') {
			max(m, c);
		}

		if (order == 'n' || order == 'n') {
			n(m, c);
		}

		if (order == '1') {
			v(m, c, 1);
		}

		if (order == '2') {
			v(m, c, 2);
		}

		if (order == '3') {
			v(m, c, 3);
		}

		if (order == 'i' || order == 'I') {

			i(m, c);
		}

		if (order == 'j' || order == 'J') {
			j(m, c);
		}

		if (order == 'k' || order == 'K') {
			k(m, c);
		}

		if (order == 'h' || order == 'H') {
			printf("a : Save new member\n");
			printf("p : Show all member\n");
			printf("m : Show member which is most attandance\n");
			printf("n : Show member which is least attandance\n");
			printf("1/2/3 : Show member Which is most attandance on Jan/Feb/March\n");
			printf("i : rearrange member by name\n");
			printf("j : rearrange member by number\n");
			printf("k : rearrang member by birth\n");
			printf("q : turn off program\n");
		}

		if (order == 'q' || order == 'Q') {

			return 0;
		}

		getchar();
	}




}

void a(class member m[15], int c) {

	char nn[7] = { 0, };
	int nnum{ 0 };
	int month{ 0 };
	int day{ 0 };
	int natd[6] = { 0, };
	int j{ 0 };

	for (int i = 0; i < 5; i++) {

		re:

		switch (i) {

		case 1:

			printf("Enter name : ");
			scanf("%s", &nn);

			if (strlen(nn) <= 5) {

				m[c+1].chname(nn);

				break;
			}

			if (strlen(nn) > 5) {

				printf("Error : name must be lass than 5 later\n");

				goto re;
			}

		case 2:

			printf("Enter membership number : ");
			scanf("%d", &nnum);

			if (nnum > 99 && nnum < 1000) {
				m[c+1].chnum(nnum);

				break;
			}

			if (nnum <= 99 || nnum >= 1000) {
				
				printf("Error : membership number must in between 100 to 999\n");

				goto re;
			}

		case 3:

			printf("Enter month : ");
			scanf("%d", &month);

			if (month > 0 && month < 13) {
				m[c+1].chmonth(month);

				break;
			}

			if (month <= 0 || month >= 13) {

				printf("Error : month must in between 1 to 12\n");

				goto re;
			}

		case 4:
			printf("Enter day : ");
			scanf("%d", &day);

			switch (m[c].getmonth()) {
			case 4:

			case 6:

			case 9:

			case 11:

				if (day > 0 && day < 31) {
					m[c+1].chday(day);

					break;
				}

				if (day <= 0 || day >= 31) {
					printf("Error : day is wrong\n");

					goto re;
				}

			case 2:

				if (day > 0 && day < 29) {
					m[c+1].chday(day);

					break;
				}

				if (day <= 0 || day >= 29) {
					printf("Error : day is wrong\n");

					goto re;
				}
				
			default:

				if (day > 0 && day < 32) {
					m[c+1].chday(day);

					break;
				}

				if (day <= 0 || day >= 32) {
					printf("Error : day is wrong\n");

					goto re;
				}

			}

		case 5:

			for (j; j < 6; j++) {

				printf("Enter attendance per month(%d) : ", j+1);

				switch (j) {

				case 0:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 32) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}
				case 1:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 29) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}

				case 2:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 32) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}

				case 3:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 31) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}

				case 4:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 32) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}
					
				case 5:
					scanf("%d", &natd[j]);

					if (natd[j] > 0 && natd[j] < 31) {
						break;
					}

					else {
						printf("Error : worng number\n");

						goto re;
					}
				}
			}

			m[c+1].chatd(natd);
		}
	}

	plus();
}

void threem(class member m[15]) {
	
	char n1[7] = "brosy";
	char n2[7] = "albis";
	char n3[7] = "cammy";
	
	int temnum[3] = {451,487,165};

	int temmonth[3] = {6,11,5};

	int temday[3] = {14,7,24};

	int tematd[6] = { 15,12,16,18,15,19 };



	m[0].chname(n1);
	m[1].chname(n2);
	m[2].chname(n3);

	for (int i = 0; i < 3; i++) {

		m[i].chnum(temnum[i]);
		m[i].chmonth(temmonth[i]);
		m[i].chday(temday[i]);
		m[i].chatd(tematd);
	}
}

void p(class member m[15], int c) {

	for (int i = 0; i < c + 1;i++) {
		
		m[i].showmember();
	}
}

void max(class member m[15], int c) {

	int* temp;
	int* Max = (int*)malloc(sizeof(int) * c);
	int Mtemp;
	int f{ 0 };
	int e{0};

	for (int i = 0; i < c + 1; i++) {
		temp = m[i].getatd();

		e = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5];

		Max[i] = e;
	}

	for (int i = 0;i < c + 1;i++) {	//최대값 찾기

		for (int j = 0; j < c + 1 - i;j++) {

			if (Max[j] < Max[j + 1]) {
				f = j + 1;
				Mtemp = Max[j];
				Max[j] = Max[j + 1];
				Max[j + 1] = Mtemp;

			}
		}
	}

	m[f].showmember();

}

void n(class member m[15], int c) {

	int* temp;
	int* min = (int*)malloc(sizeof(int) * c);
	int Mtemp;
	int f{ 0 };
	int e{0};

	for (int i = 0; i < c + 1; i++) {
		temp = m[i].getatd();

		e = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5];

		min[i] = e;
	}

	for (int i = 0;i < c+1;i++) {	//최솟값 찾기

		for (int j = 0; j < c+1 - i;j++) {

			if (min[j] < min[j + 1]) {
				f = j;
				Mtemp = min[j];
				min[j] = min[j + 1];
				min[j + 1] = Mtemp;

			}
		}
	}

	m[f].showmember();

}

void v(class member m[15], int c, int k) {

	int* temp;
	int* Max = (int*)malloc(sizeof(int) * c + 1);
	int Mtemp;
	int f{ 0 };

	for (int i = 0; i < c + 1; i++) {
		temp = m[i].getatd();

		Max[i] = temp[k];
	}

	for (int i = 0;i < c + 1;i++) {	//최대값 찾기

		for (int j = 0; j < c + 1 - i;j++) {

			if (Max[j] < Max[j + 1]) {
				f = j + 1;
				Mtemp = Max[j];
				Max[j] = Max[j + 1];
				Max[j + 1] = Mtemp;

			}
		}
	}

	m[f].showmember();
}

void j(class member m[15], int c) {

	class member* a;
	class member* b;

	for (int i = 0;i < c + 1;i++) {	//최대값 찾기

		for (int j = 0; j < c + 1 - i;j++) {

			if (m[j].getnum() < m[j + 1].getnum()) {

				a = &m[j];
				b = &m[j + 1];

				change(a, b);

			}
		}
	}
}

void i(class member m[15], int c) {

	class member* a;
	class member* b;

	for (int i = 0 ; i < c + 1 ; i++) {

		for (int j = 0; j < c + 1 - i; j++) {

			if (m[j].getname()[0] > m[j+1].getname()[0]) {
				
				a = &m[j];
				b = &m[j + 1];

				change(a, b);
			}

			if (m[j].getname()[0] == m[j + 1].getname()[0]) {

				if (m[j].getname()[1] > m[j + 1].getname()[1]) {

					a = &m[j];
					b = &m[j + 1];

					change(a, b);
				}

				if (m[j].getname()[1] == m[j + 1].getname()[1]) {

					if (m[j].getname()[2] > m[j + 1].getname()[2]) {

						a = &m[j];
						b = &m[j + 1];

						change(a, b);
					}
				}
			}
		}
	}
}

void k(class member m[15], int c) {

	class member* a;
	class member* b;

	for (int i = 0;i < c + 1;i++) {	//최대값 찾기

		for (int j = 0; j < c + 1 - i;j++) {

			if (m[j].getmonth() < m[j + 1].getmonth()) {

				a = &m[j];
				b = &m[j + 1];

				change(a, b);

			}

			if(m[j].getmonth() == m[j + 1].getmonth()) {

				if (m[j].getday() < m[j + 1].getday()) {

					a = &m[j];
					b = &m[j + 1];

					change(a, b);

				}
		    }
	    }
    }
}

void change(class member* a, class member* b) {

	char tem_name[7];

	for (int i = 0;i < 7; i++) {

		tem_name[i] =  a->getname()[i];
	}

	int tem_num = a->getnum();
	int tem_mon = a->getmonth();
	int tem_day = a->getday();
	int tem_atd[6];

	for (int i = 0; i < 6; i++) {

		tem_atd[i] = a->getatd()[i];
	}

	a->chnum(b->getnum());
	a->chmonth(b->getmonth());
	a->chday(b->getday());

	for (int i = 0;i < 7; i++) {

		a->getname()[i] = b->getname()[i];
	}

	for (int i = 0; i < 6; i++) {

		a->getatd()[i] = b->getatd()[i];
	}

	b->chnum(tem_num);
	b->chmonth(tem_mon);
	b->chday(tem_day);

	for (int i = 0;i < 7; i++) {

		b->getname()[i] = tem_name[i];
	}

	for (int i = 0; i < 6; i++) {

		b->getatd()[i] = tem_atd[i];
	}
}