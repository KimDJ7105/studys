#include <windows.h>
#include <tchar.h>


HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming class 2-4";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void utoi(TCHAR str[100], int *x, int*y,int *n) {
	
	TCHAR xstr[4];
	TCHAR ystr[4];
	TCHAR nstr[3];

	for (int k = 0; k < 3; k++) {
		xstr[k] = str[k];
	}
	xstr[3] = '\0';
	for (int k = 0; k < 3; k++) {
		ystr[k] = str[4 + k];
	}
	ystr[3] = '\0';

	for (int k = 0; k < 2;k++) {
		nstr[k] = str[8 + k];
	}

	*x = _wtoi(xstr);
	*y = _wtoi(ystr);
	*n = _wtoi(nstr);
};

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
	static TCHAR str[100] = {0,};
	static int count;
	static SIZE size;
	static TCHAR ipOut[100];
	static int n = 5;
	static int i;
	static int x = NULL, y = NULL;
	static int num = 0;

	switch (iMessage) {
	case WM_CREATE:
		count = 0;
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN) {
			count = 0;

			utoi(str, &x, &y, &n);

			str[count] = '\0';

			InvalidateRect(hWnd, NULL, TRUE);
		}

		else {
			str[count++] = wParam;
			str[count] = '\0';

			InvalidateRect(hWnd, NULL, TRUE);
		}
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);


		TextOut(hDC, 0, 0, str, lstrlen(str));

		GetTextExtentPoint32(hDC, str, lstrlen(str), &size);

		SetCaretPos(size.cx, 0);
		
		if(x != NULL) {

		for (i = 0; i < 10; i++) {
			wsprintf(ipOut, L"%d*%d = %d", n, i, n * i);
			
			if (num >= 40) {
				x = x - 75 * i;
				y += 15;
				num = 0;
			}	//»Ï...
			TextOut(hDC, x + 75 * i, y, ipOut, lstrlen(ipOut));
			num += lstrlen(ipOut);
		}

		x = NULL;
		y = NULL;
		n = NULL;
		num = 0;
		SetCaretPos(0, 0);

	    }
		ShowCaret(hWnd);
		EndPaint(hWnd, &ps);
		break;
	case WM_SETFOCUS:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;
	case WM_KILLFOCUS:
		HideCaret(hWnd);
		break;
	case WM_DESTROY:
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}