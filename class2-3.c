#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect1;
	static int x, y, n, count;
	TCHAR str[100];

	switch (iMessage) {
	case WM_CREATE:
		srand(time(NULL));

		x = rand() % 700 +1;
		y = rand() % 500 +1;
		n = rand() % 10;
		count = rand() % 30;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < count; i++) {
			if (n == 0) str[i] = '0';
			if (n == 1) str[i] = '1'; 
			if (n == 2) str[i] = '2';
			if (n == 3) str[i] = '3';
			if (n == 4) str[i] = '4';
			if (n == 5) str[i] = '5';
			if (n == 6) str[i] = '6';
			if (n == 7) str[i] = '7';
			if (n == 8) str[i] = '8';
			if (n == 9) str[i] = '9';
		}
		str[count] = '\0';

		/*if (x1 >= x2) {
			rect.left = x2;
			rect.right = x1;
		}

		if (x1 < x2) {
			rect.left = x1;
			rect.right = x2;
		}

		if (y1 >= y2) {
			rect.top = y2;
			rect.bottom = y1;
		}

		if (y1 < y2) {
			rect.top = y1;
			rect.bottom = y2;
		}

		DrawText(hDC, str, wcslen(str), &rect, DT_LEFT | DT_WORDBREAK);
		*/	//범위 지정을 통해 출력 할 경우
		SetTextColor(hDC, RGB(rand()%256, rand() % 256, rand() % 256));
		SetBkColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
		
		for(int i = 0 ; i <count;i++) TextOut(hDC, x, y + 15*i, str, count);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}