#include <windows.h>
#include <tchar.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming class 2-9";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
//말이 어느 칸 위에 있는지 확인해서 효과만 적용하면 끝
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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 900, 700, NULL, (HMENU)NULL, hInstance, NULL);

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
	HBRUSH make_Red, make_Green, make_Blue, make_rand, oldBrush, p1_Brush, p2_Brush;
	static RECT p1 = { 3,2,18,13 };
	static RECT p2 = { 23,18,38,29 };
	static LPRECT temp;
	static int turn = 0;
	static int player1_shape = 0;
	static int player2_shape = 0;
	static int player1_size = 0;
	static int player2_size = 0;
	static int *place;
	static int p1_pos;
	static int p2_pos;
	static int p1_R = 150, p1_G = 150, p1_B = 0, p2_R = 0, p2_G = 150, p2_B = 150;
	static TCHAR str[15] = L"Player 1 WIN!";
	HPEN mesege;

	switch (iMessage) {
	case WM_CREATE:
		part_x = 0;
		part_y = 0;

		x = 40;
		y = 40;

		p1_pos = 0;
		p2_pos = 41;

		rect = (RECT*)malloc(x * y * sizeof(RECT));
		place = (int*)malloc(x * y * sizeof(int));

		for (int i = 0; i < x * y;i++) {
			rect[i].left = (800 / x) * part_x;
			rect[i].right = rect[i].left + (800 / x);
			rect[i].top = (640 / y) * part_y;
			rect[i].bottom = rect[i].top + (640 / y);

			part_x++;

			if (part_x == x) {
				part_x = 0;
				part_y++;
			}
		};

		
		srand(time(NULL));
		break;
	case WM_CHAR:
		if (wParam == 'Q' || wParam == 'q') exit(1);

		if (wParam == 'w' || wParam == 'W') {
			if (turn == 0) {
				
				if (p1.top == 2) {
					p1.top = 626;
					p1.bottom = 637;
					p1_pos += 1560;

					if (place[p1_pos] == 1) {
						p1.top = 2;
						p1.bottom = 13;
						p1_pos -= 1560;
						Beep(560, 300);
						Beep(460, 300);
					}

					if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}

				else if (p1.top != 2) {
					p1.top -= 16;
					p1.bottom -= 16;
					p1_pos -= 40;

					if (place[p1_pos] == 1) {
						p1.top += 16;
						p1.bottom += 16;
						p1_pos += 40;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}
				turn++;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 's' || wParam == 'S') {
			if (turn == 0) {
				if (p1.top == 626) {
					int n = 
					p1.top = 2;
					p1.bottom = 13;
					p1_pos -= 1560;

					if (place[p1_pos] == 1) {
						p1.top = 626;
						p1.bottom = 637;
						p1_pos += 1560;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}

				else if (p1.top != 626) {
					p1.top += 16;
					p1.bottom += 16;
					p1_pos += 40;

					if (place[p1_pos] == 1) {
						p1.top -= 16;
						p1.bottom -= 16;
						p1_pos -= 40;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}
				turn++;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'a' || wParam == 'A') {
			if (turn == 0) {
				if (p1.left == 3) {
					p1.left = 783;
					p1.right = 798;
					p1_pos += 39;

					if (place[p1_pos] == 1) {
						p1.left = 3;
						p1.right = 18;
						p1_pos -= 39;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}

				else if (p1.left != 3) {
					p1.left -= 20;
					p1.right -= 20;
					p1_pos--;

					if (place[p1_pos] == 1) {
						p1.left += 20;
						p1.right += 20;
						p1_pos++;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}
				turn++;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'd' || wParam == 'D') {
			if (turn == 0) {
				if (p1.left == 783) {
					p1.left = 3;
					p1.right = 18;
					p1_pos -= 39;

					if (place[p1_pos] == 1) {
						p1.left = 783;
						p1.right = 798;
						p1_pos += 39;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}

				else if (p1.left != 783) {
					p1.left += 20;
					p1.right += 20;
					p1_pos++;

					if(place[p1_pos] == 1) {
						p1.left -= 20;
						p1.right -= 20;
						p1_pos--;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p1_pos] == 2) {
						if (player1_size == 0) player1_size++;

						else if (player1_size == 1) player1_size--;
					}

					else if (place[p1_pos] == 3) {
						if (player1_shape == 0) player1_shape++;

						else if (player1_shape == 1) player1_shape++;

						else if (player1_shape == 2) player1_shape = 0;
					}
				}
				turn++;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'i' || wParam == 'I') {
			if (turn == 1) {
				if (p2.top == 2) {
					p2.top = 626;
					p2.bottom = 637;
					p2_pos += 1560;

					if (place[p2_pos] == 1) {
						p2.top = 2;
						p2.bottom = 18;
						p2_pos -= 1560;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}

				else if (p2.top != 2) {
					p2.top -= 16;
					p2.bottom -= 16;
					p2_pos -= 40;

					if (place[p2_pos] == 1) {
						p2.top += 16;
						p2.bottom += 16;
						p2_pos += 40;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}
				turn--;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'k' || wParam == 'K') {
			if (turn == 1) {
				if (p2.top == 626) {
					p2.top = 2;
					p2.bottom = 13;
					p2_pos -= 1560;

					if (place[p2_pos] == 1) {
						p2.top = 626;
						p2.bottom = 637;
						p2_pos += 1560;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}

				else if (p2.top != 626) {
					p2.top += 16;
					p2.bottom += 16;
					p2_pos += 40;

					if (place[p2_pos] == 1) {
						p2.top -= 16;
						p2.bottom -= 16;
						p2_pos -= 40;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}
				turn--;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'j' || wParam == 'J') {
			if (turn == 1) {
				if (p2.left == 3) {
					p2.left = 783;
					p2.right = 798;
					p2_pos += 39;

					if (place[p2_pos] == 1) {
						p2.left == 3;
						p2.right == 18;
						p2_pos -= 39;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}

				else if (p2.left != 3) {
					p2.left -= 20;
					p2.right -= 20;
					p2_pos--;

					if (place[p2_pos] == 1) {
						p2.left += 20;
						p2.right += 20;
						p2_pos++;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}
				turn--;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}

		if (wParam == 'l' || wParam == 'L') {
			if (turn == 1) {
				if (p2.left == 783) {
					p2.left = 3;
					p2.right = 18;
					p2_pos -= 39;

					if (place[p2_pos] == 1) {
						p2.left = 783;
						p2.right = 798;
						p2_pos += 39;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}

				else if (p2.left != 783) {
					p2.left += 20;
					p2.right += 20;
					p2_pos++;

					if (place[p2_pos] == 1) {
						p2.left -= 20;
						p2.right -= 20;
						p2_pos--;
						Beep(560, 300);
						Beep(460, 300);
					}

					else if (place[p2_pos] == 2) {
						if (player2_size == 0) player2_size++;

						else if (player2_size == 1) player2_size--;
					}

					else if (place[p2_pos] == 3) {
						if (player2_shape == 0) player2_shape++;

						else if (player2_shape == 1) player2_shape++;

						else if (player2_shape == 2) player2_shape = 0;
					}
				}
				turn--;

				InvalidateRect(hWnd, NULL, TRUE);
			}

			else Beep(330, 500);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		make_Red = CreateSolidBrush(RGB(255, 0, 0));
		make_Green = CreateSolidBrush(RGB(0, 255, 0));
		make_Blue = CreateSolidBrush(RGB(0, 0, 255));

		for (int i = 0; i < x * y; i++) {
			

			if (i == 7 || i == 541 || i == 185 || i == 374 || i == 1274 || i == 489 ) {
				place[i] = 1;
				oldBrush = SelectObject(hDC, make_Red);
				//빨강, 지나가지 못함
				Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
				SelectObject(hDC, oldBrush);
			}

			else if (i == 43 || i == 126 || i == 398 || i == 784 || i == 1452 || i == 167) {
				place[i] = 2;
				oldBrush = SelectObject(hDC, make_Green);
				//초록, 크기변경
				Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
				SelectObject(hDC, oldBrush);
			}

			else if (i == 4 || i == 98 || i == 654 || i == 1004 || i == 423) {
				place[i] = 3;
				oldBrush = SelectObject(hDC, make_Blue);
				//파랑, 모양 변경
				
				Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
				SelectObject(hDC, oldBrush);
			}

			else if ((1 + i) * 7 % 29 == 0) {	//해당 칸의 색으로 변경
				place[i] = 4;
				if (i >= 0 && i < 500) {
					if (p1_pos == i) {
						p1_R = i * 15;
						p1_G = i * 27;
						p1_B = i * 13;
					}

					if (p2_pos == i) {
						p2_R = i * 15;
						p2_G = i * 27;
						p2_B = i * 13;
					}

					make_rand = CreateSolidBrush(RGB(i * 15, i * 27, i * 13));
					oldBrush = SelectObject(hDC, make_rand);

					Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);

					SelectObject(hDC, oldBrush);
					DeleteObject(make_rand);
				}

				else if (i >= 500 && i < 1100) {
					if (p1_pos == i) {
						p1_R = i * 14;
						p1_G = i * 8;
						p1_B = i * 13;
					}

					if (p2_pos == i) {
						p2_R = i * 14;
						p2_G = i * 8;
						p2_B = i * 13;
					}

					make_rand = CreateSolidBrush(RGB(i * 14, i * 8, i * 34));
					oldBrush = SelectObject(hDC, make_rand);

					Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);

					SelectObject(hDC, oldBrush);
					DeleteObject(make_rand);
				}

				else if (i >= 1100 && i < 1600) {
					if (p1_pos == i) {
						p1_R = i * 47;
						p1_G = i * 12;
						p1_B = i * 9;
					}

					if (p2_pos == i) {
						p2_R = i * 47;
						p2_G = i * 12;
						p2_B = i * 9;
					}

					make_rand = CreateSolidBrush(RGB(i * 47, i * 12, i * 9));
					oldBrush = SelectObject(hDC, make_rand);

					Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);

					SelectObject(hDC, oldBrush);
					DeleteObject(make_rand);
				}
			}

			else Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
		}

		p1_Brush = CreateSolidBrush(RGB(p1_R, p1_G, p1_B));
		p2_Brush = CreateSolidBrush(RGB(p2_R, p2_G, p2_B));
		oldBrush = (HBRUSH)SelectObject(hDC, p1_Brush);

		if (player1_size == 0) {
			if (player1_shape == 0) {
				Rectangle(hDC, p1.left, p1.top, p1.right, p1.bottom);
			}

			else if (player1_shape == 1) {
				Ellipse(hDC, p1.left, p1.top, p1.right, p1.bottom);
			}

			else if (player1_shape == 2) {
				int lastpoint = (p1.left + p1.right) / 2;
				POINT try[3] = { {p1.right,p1.bottom},{p1.left,p1.bottom},{lastpoint,p1.top} };

				Polygon(hDC, try, 3);
			}
		}

		if (player1_size == 1) {
			if (player1_shape == 0) {
				Rectangle(hDC, p1.left + 1, p1.top + 1, p1.right - 2, p1.bottom - 1);
			}

			else if (player1_shape == 1) {
				Ellipse(hDC, p1.left+1, p1.top+1, p1.right-2, p1.bottom-1);
			}

			else if (player1_shape == 2) {
				int lastpoint = (p1.left + p1.right) / 2;
				POINT try[3] = { {p1.right-2,p1.bottom-1},{p1.left+1,p1.bottom-1},{lastpoint,p1.top+1} };

				Polygon(hDC, try, 3);
			}
		}

		SelectObject(hDC, p2_Brush);

		if (player2_size == 0) {
			if (player2_shape == 0) {
				Rectangle(hDC, p2.left, p2.top, p2.right, p2.bottom);
			}

			else if (player2_shape == 1) {
				Ellipse(hDC, p2.left, p2.top, p2.right, p2.bottom);
			}

			else if (player2_shape == 2) {
				int lastpoint = (p2.left + p2.right) / 2;
				POINT try[3] = { {p2.right,p2.bottom},{p2.left,p2.bottom},{lastpoint,p2.top} };

				Polygon(hDC, try, 3);
			}
		}

		if (player2_size == 1) {
			if (player2_shape == 0) {
				Rectangle(hDC, p2.left + 1, p2.top + 1, p2.right - 2, p2.bottom - 1);
			}

			else if (player2_shape == 1) {
				Ellipse(hDC, p2.left + 1, p2.top + 1, p2.right - 2, p2.bottom - 1);
			}

			else if (player2_shape == 2) {
				int lastpoint = (p2.left + p2.right) / 2;
				POINT try[3] = { {p2.right - 2,p2.bottom - 1},{p2.left + 1,p2.bottom - 1},{lastpoint,p2.top + 1} };

				Polygon(hDC, try, 3);
			}
		}

		SelectObject(hDC, oldBrush);


		if (p1_pos == p2_pos) {
			TextOut(hDC, 400, 400, str, lstrlen(str));
		}
		DeleteObject(make_Red);
		DeleteObject(make_Green);
		DeleteObject(make_Blue);
		DeleteObject(p1_B);
		DeleteObject(p2_B);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}