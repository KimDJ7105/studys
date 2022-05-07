#include "resource.h"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 4-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK Sate_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
int GetRad(int num);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

typedef struct _cir {
	RECT C;
	int Red;
	int Green;
	int Blue;
	int ColorSet;
	POINT C_center;
	int theta[3];
	int r;
	BOOL way;
	RECT sate;
	double sate_theta;
	BOOL sate_way;
	BOOL color_inv;
} Circle;

Circle Cir[20];
int cir_count;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hDC;
	static RECT rc;
	static int r;
	static POINT center,click;
	HBRUSH hbrush, oldbrush;
	static HDC hdc, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static BOOL run,Clink_in;


	switch (iMessage) {
	case WM_CREATE:
		re:
		GetClientRect(hWnd, &rc);

		for (int i = 0; i < 10; i++) {
			center.x = rand() % (rc.right- 25);
			center.y = rand() % (rc.bottom- 25);
			r = 10 + rand() % 50;

			Cir[i].C.left = center.x - r;
			Cir[i].C.right = center.x + r;
			Cir[i].C.top = center.y - r;
			Cir[i].C.bottom = center.y + r;
			Cir[i].ColorSet = 0;
			Cir[i].Red = rand();
			Cir[i].Blue = rand();
			Cir[i].Green = rand();
			Cir[i].C_center = center;
			Cir[i].r = r;
			Cir[i].theta[0] = 0;
			Cir[i].theta[1] = 45;
			Cir[i].theta[2] = 90;
			Cir[i].way = TRUE;

			Cir[i].sate_theta = 90;

			Cir[i].sate.left = (Cir[i].C_center.x - (r + 5) * cos(Cir[i].sate_theta)) - 5;
			Cir[i].sate.top = (Cir[i].C_center.y - (r + 5) * sin(Cir[i].sate_theta)) - 5;
			Cir[i].sate.right = (Cir[i].C_center.x - (r + 5) * cos(Cir[i].sate_theta)) + 5;
			Cir[i].sate.bottom = (Cir[i].C_center.y - (r + 5) * sin(Cir[i].sate_theta)) + 5;

			Cir[i].sate_way = TRUE;
			Cir[i].color_inv = FALSE;
		}

		SetTimer(hWnd, 1, 10, NULL);
		SetTimer(hWnd, 2, 90, Sate_Move);

		cir_count = 10;

		run = TRUE;
		Clink_in = FALSE;
		break;
	case WM_LBUTTONDOWN:
		
		click.x = LOWORD(lParam);
		click.y = HIWORD(lParam);

		for (int i = 0; i < cir_count;i++) {
			if (PtInRect(&Cir[i].C, click)) {
				if (Cir[i].sate_way) Cir[i].sate_way = FALSE;

				else if (!Cir[i].sate_way) Cir[i].sate_way = TRUE;

				Clink_in = TRUE;
			}
		}

		if (!Clink_in) {
			Cir[cir_count].C_center.x = LOWORD(lParam);
			Cir[cir_count].C_center.y = HIWORD(lParam);

			Cir[cir_count].r = 10 + rand() % 50;

			Cir[cir_count].C.left = Cir[cir_count].C_center.x - Cir[cir_count].r;
			Cir[cir_count].C.right = Cir[cir_count].C_center.x + Cir[cir_count].r;
			Cir[cir_count].C.top = Cir[cir_count].C_center.y - Cir[cir_count].r;
			Cir[cir_count].C.bottom = Cir[cir_count].C_center.y + Cir[cir_count].r;

			Cir[cir_count].ColorSet = 0;
			Cir[cir_count].Red = rand();
			Cir[cir_count].Blue = rand();
			Cir[cir_count].Green = rand();

			Cir[cir_count].theta[0] = 0;
			Cir[cir_count].theta[1] = 45;
			Cir[cir_count].theta[2] = 90;
			Cir[cir_count].way = TRUE;

			Cir[cir_count].sate_theta = 90;

			Cir[cir_count].sate.left = (Cir[cir_count].C_center.x - (r + 5) * cos(Cir[cir_count].sate_theta)) - 5;
			Cir[cir_count].sate.top = (Cir[cir_count].C_center.y - (r + 5) * sin(Cir[cir_count].sate_theta)) - 5;
			Cir[cir_count].sate.right = (Cir[cir_count].C_center.x - (r + 5) * cos(Cir[cir_count].sate_theta)) + 5;
			Cir[cir_count].sate.bottom = (Cir[cir_count].C_center.y - (r + 5) * sin(Cir[cir_count].sate_theta)) + 5;

			Cir[cir_count].sate_way = TRUE;
			Cir[cir_count].color_inv = FALSE;

			cir_count++;
		}
		break;
	case WM_TIMER:

		for (int i = 0; i < cir_count; i++) {
			if (Cir[i].way) {
				Cir[i].theta[0] += 2;
				Cir[i].theta[1] += 2;
				Cir[i].theta[2] += 2;
			}

			else if (!Cir[i].way) {
				Cir[i].theta[0] -= 2;
				Cir[i].theta[1] -= 2;
				Cir[i].theta[2] -= 2;
			}

		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MOVE_1:
			for (int i = 0; i < cir_count; i++) {
				if (Cir[i].way) Cir[i].way = FALSE;

				else if(!Cir[i].way) Cir[i].way = TRUE;
			}
			break;
		case ID_MOVE_2:
			for (int i = 0; i < cir_count; i++) {
				if (Cir[i].sate_way) Cir[i].sate_way = FALSE;

				else if (!Cir[i].sate_way) Cir[i].sate_way = TRUE;
			}
			break;
		case ID_MOVE_3:
			if (run) {
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);

				run = FALSE;
			}

			else if (!run) {
				SetTimer(hWnd, 1, 10, NULL);
				SetTimer(hWnd, 2, 90, Sate_Move);

				run = TRUE;
			}
			break;
		case ID_CHANGE_C:
			for (int i = 0; i < cir_count;i++) {
				if (rand() % 2 == 0) {
					if (Cir[i].color_inv) Cir[i].color_inv = FALSE;

					else if (!Cir[i].color_inv) Cir[i].color_inv = TRUE;
				}
			}
			break;
		case ID_CHANGE_RED:
			for (int i = 0; i < cir_count; i++) {
				Cir[i].ColorSet = 1;
			}
			break;
		case ID_CHANGE_GREEN:
			for (int i = 0; i < cir_count; i++) {
				Cir[i].ColorSet = 3;
			}
			break;
		case ID_CHANGE_BLUE:
			for (int i = 0; i < cir_count; i++) {
				Cir[i].ColorSet = 2;
			}
			break;
		case ID_CHANGE_RANDOM:
			for (int i = 0; i < cir_count; i++) {
				Cir[i].ColorSet = 0;
			}
			break;
		case ID_GAME_QUIT:
			exit(1);
			break;
		case ID_GAME_RESET:
			goto re;
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		//여기까지가 시작 밑은 출력

		for (int i = 0; i < cir_count; i++) {

			Cir[i].sate.left = (Cir[i].C_center.x - (Cir[i].r + 5) * cos(Cir[i].sate_theta)) - 5;
			Cir[i].sate.top = (Cir[i].C_center.y - (Cir[i].r + 5) * sin(Cir[i].sate_theta)) - 5;
			Cir[i].sate.right = (Cir[i].C_center.x - (Cir[i].r + 5) * cos(Cir[i].sate_theta)) + 5;
			Cir[i].sate.bottom = (Cir[i].C_center.y - (Cir[i].r + 5) * sin(Cir[i].sate_theta)) + 5;

			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

			Ellipse(hdc, Cir[i].sate.left, Cir[i].sate.top, Cir[i].sate.right, Cir[i].sate.bottom);

			SelectObject(hdc, oldbrush);
			DeleteObject(hbrush);

			if (Cir[i].ColorSet == 0) {
				if (!Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(Cir[i].Red, Cir[i].Green, Cir[i].Blue));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				else if (Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(255-Cir[i].Red, 255-Cir[i].Green, 255-Cir[i].Blue));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}
			}

			else if (Cir[i].ColorSet == 1) {
				if (!Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(255, 0, 0));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				else if (Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(0, 255, 255));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}
			}

			else if (Cir[i].ColorSet == 2) {
				if (!Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(0, 255, 0));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				else if (Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(255, 0, 255));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}
			}

			else if (Cir[i].ColorSet == 3) {
				if (!Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(0, 0, 255));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				else if (Cir[i].color_inv) {
					hbrush = CreateSolidBrush(RGB(255, 255, 0));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Ellipse(hdc, Cir[i].C.left, Cir[i].C.top, Cir[i].C.right, Cir[i].C.bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}
			}
			
			MoveToEx(hdc,(Cir[i].C_center.x - Cir[i].r * cos(Cir[i].theta[0])),(Cir[i].C_center.y - Cir[i].r * sin(Cir[i].theta[0])),NULL);
			LineTo(hdc, (Cir[i].C_center.x + Cir[i].r * cos(Cir[i].theta[0])), (Cir[i].C_center.y + Cir[i].r * sin(Cir[i].theta[0])));

			MoveToEx(hdc, (Cir[i].C_center.x - Cir[i].r * cos(Cir[i].theta[1])), (Cir[i].C_center.y - Cir[i].r * sin(Cir[i].theta[1])), NULL);
			LineTo(hdc, (Cir[i].C_center.x + Cir[i].r * cos(Cir[i].theta[1])), (Cir[i].C_center.y + Cir[i].r * sin(Cir[i].theta[1])));

			MoveToEx(hdc, (Cir[i].C_center.x - Cir[i].r * cos(Cir[i].theta[2])), (Cir[i].C_center.y - Cir[i].r * sin(Cir[i].theta[2])), NULL);
			LineTo(hdc, (Cir[i].C_center.x + Cir[i].r * cos(Cir[i].theta[2])), (Cir[i].C_center.y + Cir[i].r * sin(Cir[i].theta[2])));
		}

		Clink_in = FALSE;

		//여기서부터는 종료
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		GetClientRect(hWnd, &bufferRT);
		BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int GetRad(int num) {
	return num * (PI / 180);
}

void CALLBACK Sate_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = 0; i < cir_count; i++) {
		if (Cir[i].sate_way) {
			Cir[i].sate_theta += 0.3;
		}

		else if (!Cir[i].sate_way) {
			Cir[i].sate_theta -= 0.3;
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}