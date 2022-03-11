#include <stdio.h>

int month_days(int year, int month);	//각 달의 전체 일수를 리턴
int leap(int year);	//윤년일 경우 1을 리턴
int firstday(int year, int month);	//각 달의 시작일을 계산
void show_calendar(int days, int first);	//달력을 출력
void show_Fri(int year, int month, int first);	//13일의 금요일을 출력
void show_sev(int year, int month, int day);	//입력된 날의 요일을 출력



int main(void) {

	int year{ 0 };
	int month{ 0 };
	int days{ 0 };
	int first{ 0 };
	int order{ 0 };
	int day{ 0 };

re:

	printf("Enter number below\n");
	printf("1. print calender\t2. show Friday 13\t3. turn off the program\n");

	scanf("%d", &order);

	switch(order) {

	case 1:

		printf("Input year, month and day to make calender\n");

		scanf("%d%d%d", &year, &month,&day);

		if (month <= 0 || month > 12) {
			printf("Month must between 1 to 12\n");

			goto re;
		}

		if (day > month_days(year, month) || day <= 0) {
			printf("wrong day\n");

			goto re;
		}

		days = month_days(year, month);

		first = firstday(year, month);

		show_sev(year, month, day);

		show_calendar(days, first);

		goto re;

	case 2:

		for (year = 2020; year < 2031; year++) {

			for (month = 1; month < 13; month++) {

				first = firstday(year, month);

				show_Fri(year, month, first);
			}
		}

		goto re;

	case 3:

		break;

	default:

		printf("wrong number, please enter again\n");

	}

	return 0;
}

int month_days(int year, int month) {

	switch (month)
	{
	case 4:

	case 6:

	case 9:

	case 11:
		return(30);
		break;

	case 2: 
		if (leap(year) == 1) {
			return (29);
		}

		else {
			return (28);
		}

		break;

	default: 
		
		return (31);
	}
}

int leap(int year) {

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int firstday(int year, int month) {

	int i{ 0 };
	int TotalDay{ 0 };
	int leapyearcnt{ 0 };

	for (i = 1; i < year; i++) {

		if (leap(i) == 1) {

			leapyearcnt++;
		}
	}

	TotalDay = (year - 1) * 365 + leapyearcnt;

	for (i = 1; i < month; i++) {
		TotalDay += month_days(year, i);
	}

	TotalDay += 1;

	return TotalDay % 7;
}

void show_calendar(int days, int first) {

	int i{ 0 };

	printf("  -Sun- -Mon- -Tus- -Wen- -Thu- -Fri- -Sat-\n");

	for (i = 0; i < first; i++) {

		printf("      ");
	}

	for (i = 1; i <= days; i++) {

		printf("%6d", i);
		if ((first + i) % 7 == 0)
			printf("\n");
	}

	printf("\n");
}

void show_Fri (int year, int month, int first) {

	if (first == 0) {

		printf("%d/%d is Friday 13\n", year, month);
	}
}

void show_sev(int year, int month, int day)
{
	int n = firstday(year, month);

	switch (n) {
	case 0:
		printf("%d %d %d = Sun\n", year, month, day);
		break;
	case 1:
		printf("%d %d %d = Mon\n", year, month, day);
		break;
	case 2:
		printf("%d %d %d = Tus\n", year, month, day);
		break;
	case 3:
		printf("%d %d %d = Wen\n", year, month, day);
		break;
	case 4:
		printf("%d %d %d = Thu\n", year, month, day);
		break;
	case 5:
		printf("%d %d %d = Fri\n", year, month, day);
		break;
	case 6:
		printf("%d %d %d = Sat\n", year, month, day);
		break;
	}


}