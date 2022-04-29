#include "resource.h"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 3-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK Block_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK Cir_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 700, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}	

typedef struct _block {
	RECT* Block;
	int stat[60];
	int way;
	int life[60];
	int Red[60];
	int Green[60];
	int Blue[60];
	BOOL item[60];
} B;

typedef struct _player {
	RECT Cir[3];
	RECT Bar;
	int x_way[3];
	int y_way[3];
	int Cir_show[3];
	int Cir_x_size;
	int Cir_y_size;
} plyer;

B b;
plyer p;
RECT rc;
int Block_break;
int Max_y;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	int x, y;
	HBRUSH y_brush1,y_brush2,y_brush3,y_brush4,ball_brush,hbrush, oldbrush;
	static BOOL fuze;
	static TCHAR messege[20];
	static int Cir_speed,C_red,C_green,C_blue;
	static int color_set;
	static int size;
	static HDC hdc, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	switch (iMessage) {
	case WM_CREATE:
	re:
		Max_y = 3;
		size = 0;

		x = 0;
		y = 0;

		p.Cir_x_size = 20;
		p.Cir_y_size = 20;

		b.Block = (RECT*)malloc((Max_y * 10) * sizeof(RECT));

		for (int i = 0; i < 10*Max_y ; i++) {
			b.Block[i].left = 100 + x * 80;
			b.Block[i].right = 100 + (x + 1) * 80;
			b.Block[i].top = y * 30;
			b.Block[i].bottom = (y + 1) * 30;
			y++;
			if (y == Max_y) y = 0;
			x++;
			if (x == 10) x = 0;
			b.stat[i] = 0;
			b.life[i] = 1 + rand() % 4;
			b.item[i] = FALSE;
		}

		b.way = 1;

		GetClientRect(hWnd, &rc);

		for (int i = 0; i < 3;i++) {
			p.Cir[i].left = (rc.right / 2) - p.Cir_x_size;
			p.Cir[i].right = (rc.right / 2) + p.Cir_x_size;
			p.Cir[i].top = rc.bottom - (50 + p.Cir_y_size*2);
			p.Cir[i].bottom = rc.bottom - 50;
		}

		p.Cir_show[0] = 1;
		p.Cir_show[1] = 0;
		p.Cir_show[2] = 0;

		for (int i = 0; i < 3;i++) {
			p.x_way[i] = 0;
			p.y_way[i] = 5;
		}

		Cir_speed = 30;
		color_set = 0;

		p.Bar.left = (rc.right / 2) - 100;
		p.Bar.right = (rc.right / 2) + 100;
		p.Bar.top = rc.bottom - 35;
		p.Bar.bottom = rc.bottom - 1;

		Block_break = 0;

		C_red = 255;
		C_green = 255;
		C_blue = 0;

		fuze = FALSE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START:
			SetTimer(hWnd, 1, 500, Block_Move);
			SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			fuze = TRUE;
			break;
		case ID_GAME_RESET:
			goto re;
			break;
		case ID_GAME_END:
			exit(1);
			break;
		case ID_SPEED_FAST:
			Cir_speed = 15;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			break;
		case ID_SPEED_MIDDLE:
			Cir_speed = 30;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			break;
		case ID_SPEED_SLOW:
			Cir_speed = 45;
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			break;
		case ID_COLOR_CYAN:
			C_red = 0;
			C_green = 255;
			C_blue = 255;
			color_set = 2;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_COLOR_MAGENTA:
			C_red = 255;
			C_green = 0;
			C_blue = 255;
			color_set = 1;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_COLOR_YELLOW:
			C_red = 255;
			C_green = 255;
			C_blue = 0;
			color_set = 0;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_BALL_BIG:
			p.Cir_x_size = 20;
			p.Cir_y_size = 20;
			if (size == 1) {
				for (int i = 0; i < 3;i++) {
					p.Cir[i].left -= 10;
					p.Cir[i].right += 10;
					p.Cir[i].top -= 10;
					p.Cir[i].bottom += 10;
				}
				size = 0;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_BALL_SMALL:
			p.Cir_x_size = 10;
			p.Cir_y_size = 10;
			if (size == 0) {
				for (int i = 0; i < 3;i++) {
					p.Cir[i].left += 10;
					p.Cir[i].right -= 10;
					p.Cir[i].top += 10;
					p.Cir[i].bottom -= 10;
				}
				size = 1;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_BREAK_3LINE:
			Max_y = 3;
			free(b.Block);

			x = 0;
			y = 0;

			b.Block = (RECT*)malloc((Max_y * 10) * sizeof(RECT));

			for (int i = 0; i < 10 * Max_y; i++) {
				b.Block[i].left = 100 + x * 80;
				b.Block[i].right = 100 + (x + 1) * 80;
				b.Block[i].top = y * 30;
				b.Block[i].bottom = (y + 1) * 30;
				y++;
				if (y == Max_y) y = 0;
				x++;
				if (x == 10) x = 0;
				b.stat[i] = 0;
				b.life[i] = 1 + rand() % 4;
				b.item[i] = FALSE;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_BREAK_4LINE:
			Max_y = 4;
			free(b.Block);

			x = 0;
			y = 0;

			b.Block = (RECT*)malloc((Max_y * 10) * sizeof(RECT));

			for (int i = 0; i < 10 * Max_y; i++) {
				b.Block[i].left = 100 + x * 80;
				b.Block[i].right = 100 + (x + 1) * 80;
				b.Block[i].top = y * 30;
				b.Block[i].bottom = (y + 1) * 30;
				
				x++;
				if (x == 10) {
					x = 0;
					y++;
				}
				b.stat[i] = 0;
				b.life[i] = 1 + rand() % 4;
				b.item[i] = FALSE;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_BREAK_5LINE:
			Max_y = 5;
			free(b.Block);

			x = 0;
			y = 0;

			b.Block = (RECT*)malloc((Max_y * 10) * sizeof(RECT));

			for (int i = 0; i < 10 * Max_y; i++) {
				b.Block[i].left = 100 + x * 80;
				b.Block[i].right = 100 + (x + 1) * 80;
				b.Block[i].top = y * 30;
				b.Block[i].bottom = (y + 1) * 30;
				
				x++;
				if (x == 10) {
					x = 0;
					y++;
					if (y == Max_y) y = 0;
				}
				b.stat[i] = 0;
				b.life[i] = 1 + rand() % 4;
				b.item[i] = FALSE;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == 's' || wParam == 'S') {
			SetTimer(hWnd, 1, 500, Block_Move);
			SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			fuze = TRUE;
		}

		if (wParam == 'p' || wParam == 'P') {
			if (fuze == TRUE) {
				KillTimer(hWnd, 1);
				KillTimer(hWnd, 2);
				wsprintf(messege, L"부순 블럭의 수 : %d", Block_break);
				DrawText(hDC, messege, lstrlen(messege), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				fuze = FALSE;
			}

			else if (fuze == FALSE) {
				SetTimer(hWnd, 1, 500, Block_Move);
				SetTimer(hWnd, 2, Cir_speed, Cir_Move);
				fuze = TRUE;
			}
		}

		if (wParam == 'n' || wParam == 'N') {
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			goto re;
		}

		if (wParam == '+') {
			if (Cir_speed > 15) {
				Cir_speed -= 15;
				KillTimer(hWnd, 2);
				SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			}
		}

		if (wParam == '-') {
			if (Cir_speed < 60) {
				Cir_speed += 15;
				KillTimer(hWnd, 2);
				SetTimer(hWnd, 2, Cir_speed, Cir_Move);
			}
		}

		ReleaseDC(hWnd, hDC);
		break;
	case WM_MOUSEMOVE:
		if (wParam == MK_LBUTTON) {
			p.Bar.left = LOWORD(lParam) - 100;
			p.Bar.right = LOWORD(lParam) + 100;
			InvalidateRect(hWnd, NULL, FALSE);
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

		if (color_set == 0) {
			C_red = 255;
			C_green = 255;
			C_blue = 0;
		}

		if (color_set == 1) {
			C_red = 255;
			C_green = 0;
			C_blue = 255;
		}

		if (color_set == 2) {
			C_red = 0;
			C_green = 255;
			C_blue = 255;
		}

		y_brush1 = CreateSolidBrush(RGB(C_red, C_green, C_blue));
		oldbrush = (HBRUSH)SelectObject(hdc, y_brush1);

		for (int i = 0; i < 10 * Max_y; i++) {
			if (b.stat[i] != 1 && b.life[i] == 1) {
				Rectangle(hdc, b.Block[i].left, b.Block[i].top, b.Block[i].right, b.Block[i].bottom);
			}
		}

		Rectangle(hdc, p.Bar.left, p.Bar.top, p.Bar.right, p.Bar.bottom);
		SelectObject(hdc, oldbrush);

		if (C_red != 0) C_red -= 55;
		if (C_green != 0) C_green -= 55;
		if (C_blue != 0) C_blue -= 55;

		y_brush2 = CreateSolidBrush(RGB(C_red, C_green, C_blue));
		oldbrush = (HBRUSH)SelectObject(hdc, y_brush2);

		for (int i = 0; i < 10 * Max_y; i++) {
			if (b.stat[i] != 1 && b.life[i] == 2) {
				Rectangle(hdc, b.Block[i].left, b.Block[i].top, b.Block[i].right, b.Block[i].bottom);
			}
		}

		SelectObject(hdc, oldbrush);

		if (C_red != 0) C_red -= 50;
		if (C_green != 0) C_green -= 50;
		if (C_blue != 0) C_blue -= 50;

		y_brush3 = CreateSolidBrush(RGB(C_red, C_green, C_blue));
		oldbrush = (HBRUSH)SelectObject(hdc, y_brush3);

		for (int i = 0; i < 10 * Max_y; i++) {
			if (b.stat[i] != 1 && b.life[i] == 3) {
				Rectangle(hdc, b.Block[i].left, b.Block[i].top, b.Block[i].right, b.Block[i].bottom);
			}
		}

		SelectObject(hdc, oldbrush);

		if (C_red != 0) C_red -= 100;
		if (C_green != 0) C_green -= 100;
		if (C_blue != 0) C_blue -= 100;

		y_brush4 = CreateSolidBrush(RGB(C_red, C_green, C_blue));
		oldbrush = (HBRUSH)SelectObject(hdc, y_brush4);

		for (int i = 0; i < 10 * Max_y; i++) {
			if (b.stat[i] != 1 && b.life[i] == 4) {
				Rectangle(hdc, b.Block[i].left, b.Block[i].top, b.Block[i].right, b.Block[i].bottom);
			}
		}

		SelectObject(hdc, oldbrush);

		ball_brush = CreateSolidBrush(RGB(0, 0, 255));
		oldbrush = (HBRUSH)SelectObject(hdc, ball_brush);

		for (int i = 0; i < 3;i++) {
			if (p.Cir_show[i] == 1) {
				Ellipse(hdc, p.Cir[i].left, p.Cir[i].top, p.Cir[i].right, p.Cir[i].bottom);
			}
		}
		SelectObject(hdc, oldbrush);

		for (int i = 0; i < 10 * Max_y; i++) {
			if (b.stat[i] == 1) {
				hbrush = CreateSolidBrush(RGB(b.Red[i], b.Green[i], b.Blue[i]));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
				Rectangle(hdc, b.Block[i].left, b.Block[i].top, b.Block[i].right, b.Block[i].bottom);
				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}
		}

		if (p.Cir_show[0] == 0 && p.Cir_show[1] == 0 && p.Cir_show[2] == 0) {
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			fuze = FALSE;

			wsprintf(messege, L"GAME OVER");

			DrawText(hdc, messege, lstrlen(messege), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		DeleteObject(y_brush1);
		DeleteObject(y_brush2);
		DeleteObject(y_brush3);
		DeleteObject(y_brush4);
		DeleteObject(ball_brush);
		DeleteObject(oldbrush);

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

void CALLBACK Block_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	POINT mid;
	if (b.way == 1) {
		for (int i = 0; i < 10*Max_y; i++) {
			if (b.stat[i] != 1) {

				b.Block[i].left += 10;
				b.Block[i].right += 10;

				if (b.Block[i].right >= rc.right) {
					b.way = 2;
				}
			}
		}
	}

	else if (b.way == 2) {
		for (int i = 0; i < 10 * Max_y; i++) {

			if (b.stat[i] != 1) {
				b.Block[i].left -= 10;
				b.Block[i].right -= 10;

				if (b.Block[i].left <= rc.left) {
					b.way = 1;
				}
			}
		}
	}

	for (int i = 0; i < 10 * Max_y; i++) {
		if (b.stat[i] == 1) {
			mid.x = b.Block[i].left + (b.Block[i].right - b.Block[i].left);
			mid.y = b.Block[i].top + (b.Block[i].bottom - b.Block[i].top);

			if ((b.Block[i].right - b.Block[i].left) > 0) {
				b.Block[i].left += 16;
				b.Block[i].right -= 16;
			}

			if ((b.Block[i].bottom - b.Block[i].top) > 0) {
				b.Block[i].top += 6;
				b.Block[i].bottom -= 6;
			}
			
			b.Block[i].top += 20;
			b.Block[i].bottom += 20;
			if(b.item[i] == FALSE) {
				if (PtInRect(&p.Bar, mid)) {

					if (p.Cir_show[0] == 0) {
						p.Cir_show[0] = 1;
						p.Cir[0].top = rc.bottom - (50 + p.Cir_y_size*2);
						p.Cir[0].bottom = rc.bottom - 50;
						p.Cir[0].left = p.Bar.left + (100 - p.Cir_x_size);
						p.Cir[0].right = p.Bar.left + (100 + p.Cir_x_size);
						b.item[i] = TRUE;
					}

					else if (p.Cir_show[1] == 0) {
						p.Cir_show[1] = 1;
						p.Cir[1].top = rc.bottom - (50 + p.Cir_y_size * 2);
						p.Cir[1].bottom = rc.bottom - 50;
						p.Cir[1].left = p.Bar.left + (100 - p.Cir_x_size);
						p.Cir[1].right = p.Bar.left + (100 + p.Cir_x_size);
						b.item[i] = TRUE;
					}
					else if (p.Cir_show[2] == 0) {
						p.Cir_show[2] = 1;
						p.Cir[2].top = rc.bottom - (50 + p.Cir_y_size * 2);
						p.Cir[2].bottom = rc.bottom - 50;
						p.Cir[2].left = p.Bar.left + (100 - p.Cir_x_size);
						p.Cir[2].right = p.Bar.left + (100 + p.Cir_x_size);
						b.item[i] = TRUE;
					}
				}
			}
			
		}
	}

	InvalidateRect(hWnd, NULL, FALSE);
}

void CALLBACK Cir_Move(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = 0; i < 3;i++) {
		if (p.Cir_show[i] == 1) {
			int mid = p.Cir[i].left + 20;

			POINT spot[8];
			spot[0].x = p.Cir[i].left + 20;
			spot[0].y = p.Cir[i].top;

			spot[1].x = p.Cir[i].left + 30;
			spot[1].y = p.Cir[i].top + 10;

			spot[2].x = p.Cir[i].right;
			spot[2].y = p.Cir[i].top + 20;

			spot[3].x = p.Cir[i].left + 30;
			spot[3].y = p.Cir[i].top + 30;

			spot[4].x = p.Cir[i].left + 20;
			spot[4].y = p.Cir[i].bottom;

			spot[5].x = p.Cir[i].left + 10;
			spot[5].y = p.Cir[i].top + 30;

			spot[6].x = p.Cir[i].left;
			spot[6].y = p.Cir[i].top + 20;

			spot[7].x = p.Cir[i].left + 10;
			spot[7].y = p.Cir[i].top + 10;


			if (p.Cir[i].left <= rc.left) {
				p.x_way[i] = -1 * p.x_way[i];
			}

			if (p.Cir[i].right >= rc.right) {
				p.x_way[i] = -1 * p.x_way[i];
			}

			if (p.Cir[i].top <= rc.top) {
				p.y_way[i] = -1 * p.y_way[i];
			}

			if (p.Cir[i].top >= rc.bottom) {
				p.Cir_show[i] = 0;
			}

			if (mid >= p.Bar.left && mid <= p.Bar.right && p.Cir[i].bottom >= p.Bar.top) {
				p.y_way[i] = -5;
				if (0 <= (mid - p.Bar.left) && (mid - p.Bar.left) < 50) {
					p.x_way[i] = -10;
				}

				else if (50 <= (mid - p.Bar.left) && (mid - p.Bar.left) < 100) {
					p.x_way[i] = -5;
				}

				else if (100 <= (mid - p.Bar.left) && (mid - p.Bar.left) < 150) {
					p.x_way[i] = 5;
				}

				else if (150 <= (mid - p.Bar.left) && (mid - p.Bar.left) < 200) {
					p.x_way[i] = 10;
				}
			}

			for (int j = 0; j < 10 * Max_y; j++) {

				if (b.stat[j] != 1) {
					if (PtInRect(&b.Block[j], spot[0])) {
						p.y_way[i] = -1 * p.y_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[1])) {
						p.y_way[i] = -1 * p.y_way[i];
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[2])) {
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[3])) {
						p.y_way[i] = -1 * p.y_way[i];
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[4])) {
						p.y_way[i] = -1 * p.y_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[5])) {
						p.y_way[i] = -1 * p.y_way[i];
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[6])) {
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}

					if (PtInRect(&b.Block[j], spot[7])) {
						p.y_way[i] = -1 * p.y_way[i];
						p.x_way[i] = -1 * p.x_way[i];
						b.life[j]--;
						if (b.life[j] == 0) {
							b.stat[j] = 1;
							b.Red[j] = rand();
							b.Green[j] = rand();
							b.Blue[j] = rand();
							Block_break++;
						}
						break;
					}
				}
			}

			p.Cir[i].left += p.x_way[i];
			p.Cir[i].right += p.x_way[i];
			p.Cir[i].top += p.y_way[i];
			p.Cir[i].bottom += p.y_way[i];
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}