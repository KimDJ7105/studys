#include <windows.h>
#include <tchar.h>
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

	srand(time(NULL));

	PAINTSTRUCT ps;
	HDC hDC;
	static RECT* rect;
	static int x;
	static int y;
	static int part_x;
	static int part_y;
	static int selecter;
	static int Red;
	static int Green;
	static int Blue;
	static int count;

	HFONT font, oldfont;

	LPCWSTR shape1 = TEXT("AAAAAAAAA\nAAAAAAA\nAAAAA\nAAA\nA");	//역삼
	LPCWSTR shape2 = TEXT("BBBBB\nBBB\nB\nBBB\nBBBBB");	//모래시계
	LPCWSTR shape3 = TEXT("C\nCCC\nCCCCC\nCCC\nC");	//마름모
	LPCWSTR shape4 = TEXT("");	//X
	LPCWSTR shape5 = TEXT("EEEEE\nEEEEE\nEEEEE\nEEEEE\nEEEEE");	//사각형
	LPCWSTR shape6 = TEXT("");	//나비

	static SIZE size;

	switch (iMessage) {
	case WM_CREATE:
		part_x = 0;
		part_y = 0;
		
		x = 2 + rand() % 9;
		y = 2 + rand() % 9;

		rect = (RECT*)malloc(x * y * sizeof(RECT));

		for (int i = 0; i < x*y;i++) {
			rect[i].left = (770 / x) * part_x;
			rect[i].right = rect[i].left + (770 / x);
			rect[i].top = (550 / y) * part_y;
			rect[i].bottom = rect[i].top + (550 / y);
			
			part_x++;
			
			if (part_x == x) { 
				part_x = 0; 
				part_y++; 
			}
		};

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		font = CreateFont(12, 4, 0, 0, 0, 0, 0, 0, NULL, 0, 0, 0, 0, NULL);
		oldfont = (HFONT)SelectObject(hDC, font);
		
		for (int i = 0; i < x*y; i++) {
			count = 0;
			selecter = rand() % 6;

			Red = 1 + rand() & 255;
			Green = 1 + rand() & 255;
			Blue = 1 + rand() & 255;

			SetTextColor(hDC, RGB(Red, Green, Blue));
			SetBkColor(hDC, RGB(Red, Green, Blue));

			if (selecter == 0) {
				//역삼각형
				DrawText(hDC, shape1, lstrlen(shape1), &rect[i], DT_CENTER | DT_WORDBREAK);
			}

			if (selecter == 1) {
				//모래시계
				DrawText(hDC, shape2, lstrlen(shape2), &rect[i], DT_CENTER | DT_WORDBREAK);
			}

			if (selecter == 2) {
				//마름모
				DrawText(hDC, shape3, lstrlen(shape3), &rect[i], DT_CENTER | DT_WORDBREAK);
			}

			if (selecter == 3) {
				//X
				DrawText(hDC, shape4, lstrlen(shape4), &rect[i],DT_CENTER | DT_WORDBREAK);
			}

			if (selecter == 4) {
				//사각형
				DrawText(hDC, shape5, lstrlen(shape5), &rect[i], DT_CENTER | DT_WORDBREAK);
			}

			if (selecter == 5) {
				//나비

			}
			
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}