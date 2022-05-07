#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 3-3";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK Game(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void Make_three_del();

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

typedef struct _Board {
	RECT board[6][12];
	int check[6][12];
	int link[6][12];
	BOOL move[6][12];
} Board;

Board B;
RECT rc;
int con_x, con_y,dis, c_dis;
int score;
int s_count = 0, d_count = 0,l_count = 1;
BOOL block_move = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	srand(time(NULL));

	PAINTSTRUCT ps;
	HDC hDC;
	static int x,y,part_x,part_y;
	static BOOL run;
	static TCHAR text[20] = L"press 'S' to start";
	static TCHAR over[20] = L"Game Over!";
	static TCHAR next[4] = L"NEXT";
	TCHAR sc[20];
	HBRUSH hbrush, oldbrush;

	static HDC hdc, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd,&rc);
		rc.right -= 300;

		score = 0;

		dis = 1 + rand() % 3;
		c_dis = 1 + rand() % 4;

		x = 6;
		y = 12;
		part_x = 0;
		part_y = 0;

		con_x = rc.right / x;
		con_y = rc.bottom / y;
		
		for(int i = 0 ; i < y ; i++) {
			for (int j = 0; j < x; j++) {
				B.board[j][i].left = part_x * (rc.right / x);
				B.board[j][i].right = (part_x + 1) * (rc.right / x);
				B.board[j][i].top = (part_y) * (rc.bottom / y);
				B.board[j][i].bottom = (part_y + 1) * (rc.bottom / y);
				B.check[j][i] = 0;
				B.link[j][i] = 0;
				B.move[j][i] = FALSE;

				part_x++;
			}
			part_x = 0;
			part_y++;
		}


		run = FALSE;
		break;
	case WM_CHAR:
		if(wParam == 's' || wParam == 'S') {
			if(!run) {
			SetTimer(hWnd,1,500,Game);
			run = TRUE;
			}
		}

		if (wParam == 'p' || wParam == 'P') {
			if(run) {
				KillTimer(hWnd,1);
				run = FALSE;
			}
		}
			
		InvalidateRect(hWnd, NULL, FALSE);
		break;	
	case WM_KEYDOWN:
		if(wParam == VK_LEFT) {
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					if (B.move[i][j]) {
						if (i != 0 && B.check[i - 1][j] == 0) {
							B.check[i - 1][j] = B.check[i][j];
							B.link[i - 1][j] = B.link[i][j];
							B.move[i - 1][j] = B.move[i][j];

							B.check[i][j] = 0;
							B.link[i][j] = 0;
							B.move[i][j] = FALSE;
						}
					}
				}
			}
		}

		if(wParam == VK_RIGHT) {
			for (int i = 5; i >= 0; i--) {
				for (int j = 0; j < y; j++) {
					if (B.move[i][j]) {
						if (i != 5 && B.check[i + 1][j] == 0) {
							B.check[i + 1][j] = B.check[i][j];
							B.link[i + 1][j] = B.link[i][j];
							B.move[i + 1][j] = B.move[i][j];

							B.check[i][j] = 0;
							B.link[i][j] = 0;
							B.move[i][j] = FALSE;
						}
					}
				}
			}
		}

		if(wParam == VK_DOWN) {
			for (int i = 0; i < x ; i++) {
				for (int j = 11; j >= 0; j--) {
					if (B.move[i][j]) {
						if (j != 11 && B.check[i][j + 1] == 0) {
							B.check[i][j + 1] = B.check[i][j];
							B.link[i][j + 1] = B.link[i][j];
							B.move[i][j + 1] = B.move[i][j];

							B.check[i][j] = 0;
							B.link[i][j] = 0;
							B.move[i][j] = FALSE;
						}
					}
				}
			}
		}

		if (wParam == VK_SPACE) {
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					if (B.move[i][j]) {	//가끔 이상한 블럭이 사라짐, 이것만 고치면 끝
						//link가 좌 우일때, 아래일때 나눠서 변환
						if (B.link[i][j] == B.link[i + 1][j]) {	//link 가 우측과 같을 때
							B.check[i][j - 1] = B.check[i + 1][j];
							B.link[i][j - 1] = B.link[i + 1][j];
							B.move[i][j - 1] = B.move[i + 1][j];

							B.check[i + 1][j] = 0;
							B.link[i + 1][j] = 0;
							B.move[i + 1][j] = FALSE;

						}


						else if (B.link[i][j] == B.link[i][j - 1]) {
							if (i != 5) {
								B.check[i + 1][j] = B.check[i][j - 1];
								B.link[i + 1][j] = B.link[i][j - 1];
								B.move[i + 1][j] = B.move[i][j - 1];

								B.check[i][j - 1] = 0;
								B.link[i][j - 1] = 0;
								B.move[i][j - 1] = FALSE;

							}

							else if (i == 5) {
								B.check[i - 1][j] = B.check[i][j - 1];
								B.link[i - 1][j] = B.link[i][j - 1];
								B.move[i - 1][j] = B.move[i][j - 1];

								B.check[i][j - 1] = 0;
								B.link[i][j - 1] = 0;
								B.move[i][j - 1] = FALSE;
							}
						}
					}
				}
			}
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

		
		for(int i = 0 ; i < x ; i++) {
			for (int j = 0; j < y; j++) {
				if (B.check[i][j] == 0) {
					Rectangle(hdc, B.board[i][j].left, B.board[i][j].top, B.board[i][j].right, B.board[i][j].bottom);
				}

				if (B.check[i][j] == 1) {
					hbrush = CreateSolidBrush(RGB(255, 255, 150));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Rectangle(hdc, B.board[i][j].left, B.board[i][j].top, B.board[i][j].right, B.board[i][j].bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				if (B.check[i][j] == 2) {
					hbrush = CreateSolidBrush(RGB(255, 150, 255));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Rectangle(hdc, B.board[i][j].left, B.board[i][j].top, B.board[i][j].right, B.board[i][j].bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				if (B.check[i][j] == 3) {
					hbrush = CreateSolidBrush(RGB(150, 255, 255));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Rectangle(hdc, B.board[i][j].left, B.board[i][j].top, B.board[i][j].right, B.board[i][j].bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}

				if (B.check[i][j] == 4) {
					hbrush = CreateSolidBrush(RGB(150, 255, 150));
					oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

					Rectangle(hdc, B.board[i][j].left, B.board[i][j].top, B.board[i][j].right, B.board[i][j].bottom);

					SelectObject(hdc, oldbrush);
					DeleteObject(hbrush);
				}
			}
		}

		if(!run) DrawText(hdc, text, lstrlen(text), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		TextOut(hdc, 620, 80, next, lstrlen(next));

		if (dis == 1) {
			
			if (c_dis == 1) {
				hbrush = CreateSolidBrush(RGB(255, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
				
			}

			if (c_dis == 2) {
				hbrush = CreateSolidBrush(RGB(255, 150, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 3) {
				hbrush = CreateSolidBrush(RGB(150, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 4) {
				hbrush = CreateSolidBrush(RGB(150, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}
		}

		if (dis == 2) {

			if (c_dis == 1) {
				hbrush = CreateSolidBrush(RGB(255, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 550, 120, 550 + con_x, 120 + con_y);
				Rectangle(hdc, 550 + con_x, 120, 550 + con_x*2, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);

			}

			if (c_dis == 2) {
				hbrush = CreateSolidBrush(RGB(255, 150, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 550, 120, 550 + con_x, 120 + con_y);
				Rectangle(hdc, 550 + con_x, 120, 550 + con_x * 2, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 3) {
				hbrush = CreateSolidBrush(RGB(150, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 550, 120, 550 + con_x, 120 + con_y);
				Rectangle(hdc, 550 + con_x, 120, 550 + con_x * 2, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 4) {
				hbrush = CreateSolidBrush(RGB(150, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 550, 120, 550 + con_x, 120 + con_y);
				Rectangle(hdc, 550 + con_x, 120, 550 + con_x * 2, 120 + con_y);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}
		}

		if (dis == 3) {

			if (c_dis == 1) {
				hbrush = CreateSolidBrush(RGB(255, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);
				Rectangle(hdc, 600, 120 + con_y, 600 + con_x, 120 + con_y*2);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);

			}

			if (c_dis == 2) {
				hbrush = CreateSolidBrush(RGB(255, 150, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);
				Rectangle(hdc, 600, 120 + con_y, 600 + con_x, 120 + con_y * 2);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 3) {
				hbrush = CreateSolidBrush(RGB(150, 255, 255));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);
				Rectangle(hdc, 600, 120 + con_y, 600 + con_x, 120 + con_y * 2);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}

			if (c_dis == 4) {
				hbrush = CreateSolidBrush(RGB(150, 255, 150));
				oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

				Rectangle(hdc, 600, 120, 600 + con_x, 120 + con_y);
				Rectangle(hdc, 600, 120 + con_y, 600 + con_x, 120 + con_y * 2);

				SelectObject(hdc, oldbrush);
				DeleteObject(hbrush);
			}
		}
		wsprintf(sc, L"SCORE : %d", score);
		TextOut(hdc, 550, 280, sc, lstrlen(sc));

		for (int i = 0; i < x; i++) {
			if (B.check[i][0] > 0 && !B.move[i][0]) {
				KillTimer(hWnd, 1);

				DrawText(hdc, over, lstrlen(over), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}

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

void CALLBACK Game(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (!block_move) {

		Make_three_del();

		if (dis == 1) {		// 블럭 하나
			B.check[2][0] = c_dis;
			B.link[2][0] = l_count++;
			B.move[2][0] = TRUE;
		}

		else if (dis == 2) {	//블럭 양 옆
			B.check[2][0] = c_dis;
			B.link[2][0] = l_count;
			B.move[2][0] = TRUE;
			B.check[3][0] = c_dis;
			B.link[3][0] = l_count;
			B.move[3][0] = TRUE;
			l_count++;

		}

		else if (dis == 3) {	//블럭 위 아래
			B.check[2][0] = c_dis;
			B.link[2][0] = l_count;
			B.move[2][0] = TRUE;
			B.check[2][1] = c_dis;
			B.link[2][1] = l_count;
			B.move[2][1] = TRUE;
			l_count++;
		}

		dis = -1;
		c_dis = -1;

		block_move = TRUE;
	}

	if (block_move) {
		block_move = FALSE;

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 12; j++) {
				if (B.move[i][j]) block_move = TRUE;
			}
		}

		if (dis == -1) dis = 1 + rand() % 3;
		if (c_dis == -1) c_dis = 1 + rand() % 4;
	}

	for (int i = 5; i >= 0; i--) {
		for (int j = 11; j >= 0; j--) {
			if (B.move[i][j]) {
				if (j == 11 || B.check[i][j + 1] > 0) {
					if (B.link[i][j] == B.link[i][j + 1]) {
						if (!B.move[i][j + 1]) B.move[i][j] = FALSE;
					}
					
					else {
						B.move[i][j] = FALSE;
					}
				}

				else if (i != 5 && B.link[i][j] == B.link[i + 1][j]) {
					if (!B.move[i + 1][j]) B.move[i][j] = FALSE;
					
					else {
						B.check[i][j + 1] = B.check[i][j];
						B.link[i][j + 1] = B.link[i][j];
						B.move[i][j + 1] = B.move[i][j];

						B.check[i][j] = 0;
						B.link[i][j] = 0;
						B.move[i][j] = TRUE;

						Make_three_del();
					}
				}

				else if (i != 0 && B.link[i][j] == B.link[i - 1][j]) {
					if (B.check[i - 1][j + 1] > 0) {
						B.move[i][j] = FALSE;
					}

					else {
						B.check[i][j + 1] = B.check[i][j];
						B.link[i][j + 1] = B.link[i][j];
						B.move[i][j + 1] = B.move[i][j];

						B.check[i][j] = 0;
						B.link[i][j] = 0;
						B.move[i][j] = TRUE;

						Make_three_del();
					}
				}

				else {
					B.check[i][j + 1] = B.check[i][j];
					B.link[i][j + 1] = B.link[i][j];
					B.move[i][j + 1] = B.move[i][j];

					B.check[i][j] = 0;
					B.link[i][j] = 0;
					B.move[i][j] = TRUE;

					Make_three_del();
				}
			}

			else if (!B.move[i][j]) {
				if (j == 11) {

				}

				else if (B.check[i][j + 1] == 0) {
					if (B.link[i][j] != B.link[i + 1][j] && B.link[i][j] != B.link[i - 1][j]) {
						B.check[i][j + 1] = B.check[i][j];
						B.link[i][j + 1] = B.link[i][j];

						B.check[i][j] = 0;
						B.link[i][j] = 0;

						Make_three_del();
					}

					else if (B.link[i][j] == B.link[i + 1][j]) {
						if (B.check[i + 1][j + 1] == 0) {
							B.check[i][j + 1] = B.check[i][j];
							B.link[i][j + 1] = B.link[i][j];

							B.check[i][j] = 0;
							B.link[i][j] = 0;

							Make_three_del();
						}
					}

					else if (B.link[i][j] == B.link[i - 1][j]) {
						if (B.check[i - 1][j + 1] == 0) {
							B.check[i][j + 1] = B.check[i][j];
							B.link[i][j + 1] = B.link[i][j];
							 
							B.check[i][j] = 0;
							B.link[i][j] = 0;

							Make_three_del();
						}
					}
				}
			}
		}
	}

	InvalidateRect(hWnd,NULL,FALSE);
}

void Make_three_del() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {
			if (!B.move[i][j]) {
				if (B.check[i][j] != 0) {
					if (i < 4 && B.check[i + 1][j] == B.check[i][j] && B.check[i + 2][j] == B.check[i][j]) {
						if (!B.move[i + 1][j] && !B.move[i + 2][j]) {
							B.check[i][j] = 0;
							B.check[i + 1][j] = 0;
							B.check[i + 2][j] = 0;
							B.link[i][j] = 0;
							B.link[i + 1][j] = 0;
							B.link[i + 2][j] = 0;
							B.move[i][j] = FALSE;
							B.move[i + 1][j] = FALSE;
							B.move[i + 2][j] = FALSE;

							score += 100;
						}
					}

					if (j > 1 && B.check[i][j - 1] == B.check[i][j] && B.check[i][j - 2] == B.check[i][j]) {
						B.check[i][j] = 0;
						B.check[i][j - 1] = 0;
						B.check[i][j - 2] = 0;
						B.link[i][j] = 0;
						B.link[i][j - 1] = 0;
						B.link[i][j - 2] = 0;
						B.move[i][j] = FALSE;
						B.move[i][j - 1] = FALSE;
						B.move[i][j - 2] = FALSE;

						score += 100;
					}
				}
			}
		}
	}
}
