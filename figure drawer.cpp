#include < stdio.h>

void square(int n);
void inver(int n);
void rhombus(int n);
void X(int n);
void butter(int n);
void hour(int n);

int main() {
	int hight{ 0 };
	int o{ 0 };

	while (true) {

		printf("select order below\n");
		printf("1.X 2.inverted triangle 3.rhombus 4.butterfly 5.hourglass 6.square 7.turn off\n");

		scanf("%d", &o);

	re:

		switch (o) {

		case 1:


			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				X(hight);
			}

			break;

		case 2:

			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				inver(hight);

			}

			break;

		case 3:

			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				rhombus(hight);

			}

			break;
		case 4:


			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				butter(hight);
			}

			break;

		case 5:

			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				hour(hight);
			}

			break;

		case 6:

			printf("Enter hight\n");

			scanf("%d", &hight);

			if (hight % 2 != 0) {
				printf("Error : hight must be even\n");

				goto re;
			}

			if (hight % 2 == 0) {

				square(hight);
			}

			break;

		case 7:

			return 0;

		default:
			printf("Error Wrong order\n");
			break;

		}
	}

}

void inver(int n) {

	for (int i = 0;i < n;i++) {

		for (int j = 0;j < i;j++) {

			printf(" ");
		}

		for (int j = 2 * n - 1;j > 2 * i;j--) {

			printf("*");
		}

		printf("\n");
	}
}

void rhombus(int n) {

	int num = n / 2;

	for (int i = 0;i < num;i++) {
		for (int j = num - 1;j > i;j--) {
			printf(" ");
		}

		for (int j = 0;j < 2 * i + 1;j++) {
			printf("*");
		}
		printf("\n");
	}

	for (int i = 0;i < num;i++) {
		for (int j = 0;j < i;j++) {
			printf(" ");
		}

		for (int j = 2 * num - 1;j > 2 * i;j--) {
			printf("*");
		}
		printf("\n");
	}

}

void square(int n) {

	for (int i = 1; i <= n; i++) {

		for (int j = 1; j <= n; j++) {

			if (i == 1 || i == n || j == 1 || j == n) {
				printf("*");
			}

			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void X(int n) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			if (i == j || i + j == n - 1) {

				printf("*");

			}

			else {

				printf(" ");
			}

			
		}

		printf("\n");
	}
}

void butter(int n) {

	for (int i = 0; i < n/2; i++)
	{
		for (int j = 0; j <= i; j++)
			printf("*");
		for (int k = 1; k < n/2 - i; k++)
			printf(" ");
		for (int l = 1; l < n/2 - i; l++)
			printf(" ");
		for (int m = 0; m <= i; m++)
			printf("*");
		printf("\n");
	}

	for (int i = 1; i < n/2; i++)
	{
		for (int j = 0; j < n/2 - i; j++)
			printf("*");
		for (int k = 1; k <= i; k++)
			printf(" ");
		for (int l = 1; l <= i; l++)
			printf(" ");
		for (int m = 0; m < n/2 - i; m++)
			printf("*");

		printf("\n");
	}
}

void hour(int n) {

	int N = n / 2;

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < i; j++) {
			
			printf(" ");
		}

		for (int k = 0; k < 2 * (N - i) - 1; k++) {
		
			printf("*");
		}

		printf("\n");
	}

	for (int i = 1; i < N; i++) {

		for (int j = 0; j < N - i - 1; j++) {

			printf(" ");
		}

		for (int k = 0; k < 2 * i + 1; k++) {
		
			printf("*");
		}

		printf("\n");
	}
}