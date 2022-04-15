#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 2-10";

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

void utoi(TCHAR str[30], int order[6]);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	HPEN hpen, oldpen;
	HBRUSH hbrush, oldbrush;
	static TCHAR str[100];
	static TCHAR error1[30] = L"이전 도형이 없습니다.";
	static TCHAR error2[30] = L"마지막 도형입니다.";
	static int count;
	static RECT rect;
	static int order[6];
	static int Red,Green,Blue,b_Red,b_Green,b_Blue;
	static int rememb[10][6];
	static int num,now,last;
	switch (iMessage) {
	case WM_CREATE:
		str[0] = '\0';
		count = 0;
		num = 0;
		last = 0;
		rect.left = 0;
		rect.top = 535;
		rect.right = 700;
		rect.bottom = 560;
		for (int i = 0; i < 5; i++) {
			order[i] = 0;
		}

		Red = rand() % 256;
		Green = rand() % 256;
		Blue = rand() % 256;

		b_Red = rand() % 256;
		b_Green = rand() % 256;
		b_Blue = rand() % 256;

		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			order[1] -= 10;
			order[3] -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_RIGHT) {
			order[1] += 10;
			order[3] += 10;
			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_UP) {
			order[2] -= 10;
			order[4] -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_DOWN) {
			order[2] += 10;
			order[4] += 10;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN) {
			utoi(str, order);
			for (int i = 0; i < 6;i++) {
				rememb[num][i] = order[i];
			}
			now = num;
			last = num;
			num++;
			count = 0;
		}

		else if (wParam == 'p') {
			if (now == 0) {
				TextOut(hDC, 0, 0, error1, lstrlen(error1));
			}

			else if (now > 0) {
				now--;
				for (int i = 0;i < 6;i++) {
					order[i] = rememb[now][i];
				}
			}
		}

		else if (wParam == 'n') {
			if (now == 9) {
				TextOut(hDC, 0, 0, error2, lstrlen(error2));
			}

			else if (now < 9) {
				now++;
				if (now > last) {
					TextOut(hDC, 0, 0, error2, lstrlen(error2));
					now--;
				}

				else {
					for (int i = 0; i < 6;i++) {
						order[i] = rememb[now][i];
					}
				}
			}
		}

		else if (wParam == '+') {
			if (order[5] != 10) {
				order[5]++;
			}
			else if (order[5] == 10) {
				order[3] += 10;
				order[4] += 10;
			}
		}

		else if (wParam == '-') {
			if (order[5] != 1) {
				order[5]--;
			}
			else if (order[5] == 1) {
				order[3] -= 10;
				order[4] -= 10;
			}
		}

		else if (wParam == 'k') {
			Red = rand() % 256;
			Green = rand() % 256;
			Blue = rand() % 256;

			b_Red = rand() % 256;
			b_Green = rand() % 256;
			b_Blue = rand() % 256;
		}

		else {
			str[count++] = wParam;
			str[count] = '\0';
		}

		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
		TextOut(hDC, 0, 535, str, lstrlen(str));

		if (order[0] == 1) {
			hpen = CreatePen(PS_SOLID, order[5], RGB(Red,Green,Blue));
			oldpen = (HPEN)SelectObject(hDC, hpen);

			MoveToEx(hDC, order[1], order[2], NULL);
			LineTo(hDC, order[3], order[4]);

			SelectObject(hDC, oldpen);
			DeleteObject(hpen);
		}

		else if (order[0] == 2) {
			hpen = CreatePen(PS_SOLID, order[5], RGB(Red, Green, Blue));
			oldpen = (HPEN)SelectObject(hDC, hpen);
			hbrush = CreateSolidBrush(RGB(b_Red, b_Green, b_Blue));
			oldbrush = (HBRUSH)SelectObject(hDC, hbrush);

			POINT tr[3] = {{order[1],order[4]},{order[3],order[4]},{(order[1]+order[3])/2,order[2]}};
			Polygon(hDC, tr, 3);

			SelectObject(hDC, oldbrush);
			SelectObject(hDC, oldpen);
			DeleteObject(hpen);
			DeleteObject(hbrush);
		}

		else if (order[0] == 3) {
			hpen = CreatePen(PS_SOLID, order[5], RGB(Red, Green, Blue));
			oldpen = (HPEN)SelectObject(hDC, hpen);
			hbrush = CreateSolidBrush(RGB(b_Red, b_Green, b_Blue));
			oldbrush = (HBRUSH)SelectObject(hDC, hbrush);

			Rectangle(hDC, order[1], order[2], order[3], order[4]);

			SelectObject(hDC, oldbrush);
			SelectObject(hDC, oldpen);
			DeleteObject(hpen);
			DeleteObject(hbrush);
		}

		else if (order[0] == 4) {
			hpen = CreatePen(PS_SOLID, order[5], RGB(Red, Green, Blue));
			oldpen = (HPEN)SelectObject(hDC, hpen);
			hbrush = CreateSolidBrush(RGB(b_Red, b_Green, b_Blue));
			oldbrush = (HBRUSH)SelectObject(hDC, hbrush);
			
			Ellipse(hDC, order[1], order[2], order[3], order[4]);

			SelectObject(hDC, oldbrush);
			SelectObject(hDC, oldpen);
			DeleteObject(hpen);
			DeleteObject(hbrush);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void utoi(TCHAR str[30], int order[6]) {
	TCHAR nstr[2];
	TCHAR x1_str[4];
	TCHAR y1_str[4];
	TCHAR x2_str[4];
	TCHAR y2_str[4];
	TCHAR line[3];

	nstr[0] = str[0];
	nstr[1] = '\0';

	for (int i = 0; i < 3; i++) {
		x1_str[i] = str[i + 2];
	}
	x1_str[3] = '\0';

	for (int i = 0; i < 3; i++) {
		y1_str[i] = str[i + 6];
	}
	y1_str[3] = '\0';

	for (int i = 0; i < 3; i++) {
		x2_str[i] = str[i + 10];
	}
	x2_str[3] = '\0';

	for (int i = 0; i < 3;i++) {
		y2_str[i] = str[i + 14];
	}
	y2_str[3] = '\0';

	for (int i = 0; i < 2; i++) {
		line[i] = str[i + 18];
	}
	line[2] = '\0';

	order[0] = _wtoi(nstr);
	order[1] = _wtoi(x1_str);
	order[2] = _wtoi(y1_str);
	order[3] = _wtoi(x2_str);
	order[4] = _wtoi(y2_str);
	order[5] = _wtoi(line);
}