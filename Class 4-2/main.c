#include "resource.h"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 4-2";

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 700, 700, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

typedef struct _Rect {
	RECT r;
	int Red;
	int Green;
	int Blue;
	BOOL show;
	BOOL choose;
} RectType;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	static RECT* broad;
	static RECT rc;
	static int start_x, start_y, new_x, new_y, old_x, old_y;
	static int x, y, part_X, part_y, count_R, P_R, P_G, P_B;
	static RectType R[10];
	static RectType cap[20];
	static int cap_count;
	HBRUSH hbrush, oldbrush;
	HPEN hpen, oldpen;
	static BOOL Drag,Dotted,Border,R_Drag;

	switch (iMessage) {
	case WM_CREATE:
		x = 25;
		y = 25;
		part_X = 0;
		part_y = 0;
		broad = (RECT*)malloc(sizeof(RECT) * x * y);

		GetClientRect(hWnd, &rc);

		for (int i = 0; i < x * y; i++) {
			broad[i].left = part_X * (rc.right - rc.left) / x;
			broad[i].right = (part_X + 1) * (rc.right - rc.left) / x;
			broad[i].top = part_y * (rc.bottom - rc.top) / y;
			broad[i].bottom = (part_y + 1) * (rc.bottom - rc.top) / y;

			part_X++;

			if (part_X == x) {
				part_X = 0;
				part_y++;
			}
		}

		for (int i = 0; i < 10; i++) {
			R[i].show = FALSE;
			R[i].choose = FALSE;
		}

		count_R = 0;
		P_R = 255;
		P_G = 0;
		P_B = 0;

		Drag = FALSE;
		R_Drag = FALSE;
		Dotted = FALSE;
		Border = TRUE;

		cap_count = 0;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GRID_DOTTED : 
			Dotted = TRUE;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_GRID_SOLID :
			Dotted = FALSE;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_COLOR_RED:
			P_R = 255;
			P_G = 0;
			P_B = 0;
			break;
		case ID_COLOR_GREEN:
			P_R = 0;
			P_G = 255;
			P_B = 0;
			break;
		case ID_COLOR_BLUE:
			P_R = 0;
			P_G = 0;
			P_B = 255;
			break;
		case ID_COLOR_MAGENTA :
			P_R = 200;
			P_G = 0;
			P_B = 200;
			break;
		case ID_COLOR_CYAN:
			P_R = 0;
			P_G = 200;
			P_B = 200;
			break;
		case ID_COLOR_YELLOW:
			P_R = 200;
			P_G = 200;
			P_B = 0;
			break;
		case ID_BORDER_OFF:
			Border = FALSE;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_BORDER_ON:
			Border = TRUE;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_LBUTTONDOWN:

		for (int i = 0; i < x * y; i++) {
			if (broad[i].left < LOWORD(lParam) && broad[i].right > LOWORD(lParam) && broad[i].top < HIWORD(lParam) && broad[i].bottom > HIWORD(lParam)) {
				R[count_R].r.left = broad[i].right;
				R[count_R].r.top = broad[i].bottom;
			}
		}

		start_x = LOWORD(lParam);
		start_y = HIWORD(lParam);
		old_x = LOWORD(lParam) + 1;
		old_y = HIWORD(lParam) + 1;
		Drag = TRUE;
		break;
	case WM_RBUTTONDOWN:
		R_Drag = TRUE;

		POINT spot = { LOWORD(lParam), HIWORD(lParam) };

		for (int i = 0; i < 10; i++) {
			if (PtInRect(&R[i].r, spot)) R[i].choose = TRUE;

			old_x = LOWORD(lParam);
			old_y = HIWORD(lParam);
		}
		
		break;
	case WM_MOUSEMOVE:
		hDC = GetDC(hWnd);
		if (Drag) {

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, start_x, old_y, NULL);

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, old_x, start_y, NULL);

			MoveToEx(hDC, start_x, old_y, NULL);
			LineTo(hDC, old_x, old_y, NULL);

			MoveToEx(hDC, old_x, start_y, NULL);
			LineTo(hDC, old_x, old_y, NULL);


			SetROP2(hDC, R2_XORPEN);
			SelectObject(hDC, (HPEN)GetStockObject(WHITE_PEN));

			new_x = LOWORD(lParam);
			new_y = HIWORD(lParam);

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, start_x, old_y, NULL);

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, old_x, start_y, NULL);

			MoveToEx(hDC, start_x, old_y, NULL);
			LineTo(hDC, old_x, old_y, NULL);

			MoveToEx(hDC, old_x, start_y, NULL);
			LineTo(hDC, old_x, old_y, NULL);

			//================================

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, start_x, new_y, NULL);

			MoveToEx(hDC, start_x, start_y, NULL);
			LineTo(hDC, new_x, start_y, NULL);

			MoveToEx(hDC, start_x, new_y, NULL);
			LineTo(hDC, new_x, new_y, NULL);

			MoveToEx(hDC, new_x, start_y, NULL);
			LineTo(hDC, new_x, new_y, NULL);

			old_x = new_x;
			old_y = new_y;

		}

		if (R_Drag) {
			new_x = LOWORD(lParam);
			new_y = HIWORD(lParam);

			for (int i = 0; i < 10; i++) {
				if (R[i].choose) {
					R[i].r.left += (new_x - old_x);
					R[i].r.right += (new_x - old_x);
					R[i].r.top += (new_y - old_y);
					R[i].r.bottom += (new_y - old_y);
				}
			}

			old_x = new_x;
			old_y = new_y;

			InvalidateRect(hWnd, NULL, TRUE);
		}
		ReleaseDC(hWnd, hDC);
		break;
	case WM_LBUTTONUP:

		for (int i = 0; i < x * y; i++) {
			if (broad[i].left < LOWORD(lParam) && broad[i].right > LOWORD(lParam) && broad[i].top < HIWORD(lParam) && broad[i].bottom > HIWORD(lParam)) {
				R[count_R].r.right = broad[i].left;
				R[count_R].r.bottom = broad[i].top;
			}
		}

		R[count_R].Red = P_R;
		R[count_R].Green = P_G;
		R[count_R].Blue = P_B;
		R[count_R].show = TRUE;
		count_R++;

		Drag = FALSE;

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONUP:
		R_Drag = FALSE;
		for (int i = 0; i < 10; i++) {
			if (R[i].choose) {
				for (int j = 0; j < x * y; j++) {
					if (broad[j].left < R[i].r.left && broad[j].right > R[i].r.left && broad[j].top < R[i].r.top && broad[j].bottom > R[i].r.top) {
						R[i].r.left = broad[j].left;
						R[i].r.top = broad[j].top;
					}

					if (broad[j].left < R[i].r.right && broad[j].right > R[i].r.right && broad[j].top < R[i].r.bottom && broad[j].bottom > R[i].r.bottom) {
						R[i].r.right = broad[j].left;
						R[i].r.bottom = broad[j].top;
					}
				}

				R[i].choose = FALSE;
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < x * y; i++) {
			if(!Dotted) Rectangle(hDC, broad[i].left, broad[i].top, broad[i].right, broad[i].bottom);

			else if (Dotted) {
				hpen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
				oldpen = (HPEN)SelectObject(hDC, hpen);

				Rectangle(hDC, broad[i].left, broad[i].top, broad[i].right, broad[i].bottom);

				SelectObject(hDC, oldpen);
				DeleteObject(hpen);
			}
		}

		for (int i = 0; i < 10; i++) {
			if (R[i].show == TRUE) {
				hbrush = CreateSolidBrush(RGB(R[i].Red, R[i].Green, R[i].Blue));
				oldbrush = (HBRUSH)SelectObject(hDC, hbrush);

				if(Border) Rectangle(hDC, R[i].r.left, R[i].r.top, R[i].r.right, R[i].r.bottom);
				
				else if (!Border) {
					hpen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
					oldpen = (HPEN)SelectObject(hDC, hpen);

					Rectangle(hDC, R[i].r.left, R[i].r.top, R[i].r.right, R[i].r.bottom);

					SelectObject(hDC, oldpen);
					DeleteObject(hpen);
				}

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}
		}

		for (int i = 0; i < 10; i++) {
			if (R[i].show == TRUE) {
				for (int j = i + 1; j < 10; j++ ) {
					if (R[j].show == TRUE) {
						if (IntersectRect(&cap[cap_count].r, &R[i].r, &R[j].r)) {
							cap[cap_count].Red = R[j].Red + R[i].Red;
							cap[cap_count].Green = R[j].Green + R[i].Green;
							cap[cap_count].Blue = R[j].Blue + R[i].Blue;
							cap[cap_count].show = TRUE;
							cap_count++;
						}
					}
				}
			}
		}

		for (int i = 0; i < 20; i++) {
			if (cap[i].show == TRUE) {
				hbrush = CreateSolidBrush(RGB(cap[i].Red, cap[i].Green, cap[i].Blue));
				oldbrush = (HBRUSH)SelectObject(hDC, hbrush);

				if (Border) Rectangle(hDC, cap[i].r.left, cap[i].r.top, cap[i].r.right, cap[i].r.bottom);

				else if (!Border) {
					hpen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
					oldpen = (HPEN)SelectObject(hDC, hpen);

					Rectangle(hDC, cap[i].r.left, cap[i].r.top, cap[i].r.right, cap[i].r.bottom);

					SelectObject(hDC, oldpen);
					DeleteObject(hpen);
				}

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}
		}

		cap_count = 0;
		for (int i = 0; i < 20; i++) cap[i].show = FALSE;

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		free(broad);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}