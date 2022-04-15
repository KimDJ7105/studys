#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 3-1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK Moveset1(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK ShowTail(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK Jump(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK turn(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK left(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK right(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK up(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK down(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK Moveset2(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

typedef struct _tail {
	RECT tail;
	int moveset;
	int way;
	int move_count;
	BOOL show;
	int t_num;
	int t_check;
}tail;

typedef struct _Player {
	RECT player;
	int p_Red;
	int p_Green;
	int p_Blue;
	int x;
	int y;
	int tail_length;
}player;

static player p;
static tail t[20];
int count = 0;
RECT t_c[20];
int num;
int jump_count,turn_c,wall_c,speed_c;
RECT wall[20];

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	static RECT* board;
	static int x,y,part_x,part_y;
	HBRUSH p_brush, t_brush, oldbrush;
	static int T1,check;
	static int mx, my;

	switch (iMessage) {	//이동하는 형태별로 타이머를 만들고 timeproc 에서 조작
	case WM_CREATE:
		p.player.left = 0;
		p.player.top = 0;
		p.player.right = 18;
		p.player.bottom = 18;
		p.p_Red = 255;
		p.p_Green = 255;
		p.p_Blue = 0;
		p.x = 1;
		p.y = 1;
		p.tail_length = 0;
		jump_count = 0;
		turn_c = 0;
		wall_c = 0;
		speed_c = 0;
		T1 = 100;
		x = 40;
		y = 40;
		check = 0;
		board = (RECT*)malloc(x*y*sizeof(RECT));

		for (int i = 0; i < x * y;i++) {
				board[i].left = (720 / x) * part_x;
				board[i].right = board[i].left + (720 / x);
				board[i].top = (720 / y) * part_y;
				board[i].bottom = board[i].top + (720 / y);

				part_x++;

				if (part_x == x) {
					part_x = 0;
					part_y++;
				}
			}

		for (int i = 0; i < 50; i++) {
			t[i].show = FALSE;
		}
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);	
		my = HIWORD(lParam);
		KillTimer(hWnd, 1);

		for (int i = 0; i < count; i++) {
			if (t[i].tail.left < mx && t[i].tail.right > mx && t[i].tail.top < my && t[i].tail.bottom > my) {
				if (t[i].t_check == 1) {
					for (int j = 0; j < count;j++) {
						if (t[j].t_check == 1 && t[j].t_num >= t[i].t_num) {
							t[j].moveset = 1 + rand() % 3;
							t[j].way = 0;
							t[j].t_check = 0;
						}
					}
					p.tail_length = t[i].t_num + 1;
				}
			}
		}

		if (p.player.left < mx && p.player.right > mx && p.player.top < my && p.player.bottom >my) {
			SetTimer(hWnd, 10, T1-50, Moveset2);
			check = 1;
		}

		else {
			check = 2;
			if (p.player.left < mx) {
				SetTimer(hWnd, 6, T1, right);
			}

			else if (p.player.left > mx) {
				SetTimer(hWnd, 7, T1, left);
			}

			if (p.player.top < my) {
				SetTimer(hWnd, 8, T1, down);
			}

			else if (p.player.top > my) {
				SetTimer(hWnd, 9, T1, up);
			}
		}
		break;
	case WM_LBUTTONUP:
		KillTimer(hWnd, 6);
		KillTimer(hWnd, 7);
		KillTimer(hWnd, 8);
		KillTimer(hWnd, 9);
		if (check == 2) {
			SetTimer(hWnd, 1, T1, Moveset1);
		}
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < x * y; i++) {
			if (board[i].left < mx && board[i].right > mx && board[i].top < my && board[i].bottom > my) {
				wall[wall_c] = board[i];
				wall_c++;
			}
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			p.x = 2;
			p.y = 1;
		}

		if (wParam == VK_RIGHT) {
			p.x = 1;
			p.y = 1;
		}	

		if (wParam == VK_UP) {
			p.y = 3;
			p.x = 3;
		}

		if (wParam == VK_DOWN) {
			p.y = 4;
			p.x = 3;
		}
		break;
	case WM_CHAR:
		if (wParam == 's' || wParam == 'S')	 {
			p.player.left += 18;
			p.player.right += 18;
			InvalidateRect(hWnd, NULL, TRUE);

			SetTimer(hWnd, 1, T1, Moveset1);
			SetTimer(hWnd, 2, 500, ShowTail);
		}

		if (wParam == '-') {
			if (T1 < 500) {
				T1 += 50;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, T1, Moveset1);
			}

			else {
				Beep(300, 200);
			}
		}

		if (wParam == '+') {
			if (T1 > 50) {
				T1 -= 50;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, T1, Moveset1);
			}

			else {
				Beep(300, 200);
			}
		}

		if (wParam == 'j' || wParam == 'J') {
			SetTimer(hWnd, 3, T1, Jump);
		}

		if (wParam == 'q' || wParam == 'Q') exit(1);

		if (wParam == 't' || wParam == 'T') {
			KillTimer(hWnd, 1);
			SetTimer(hWnd, 4, T1, turn);
		}

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 41; i++) {
			MoveToEx(hDC, 0, i * 18, NULL);
			LineTo(hDC, 720, i * 18, NULL);
			MoveToEx(hDC, i * 18, 0, NULL);
			LineTo(hDC, i * 18, 720, NULL);
		}

		oldbrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(RGB(0, 0, 0)));

		for (int i = 0; i < wall_c; i++) {
			Rectangle(hDC, wall[i].left, wall[i].top, wall[i].right, wall[i].bottom);
		}
		SelectObject(hDC, oldbrush);

		p_brush = CreateSolidBrush(RGB(p.p_Red, p.p_Green, p.p_Blue));
		oldbrush = (HBRUSH)SelectObject(hDC, p_brush);
		Ellipse(hDC, p.player.left, p.player.top, p.player.right, p.player.bottom);
		SelectObject(hDC, oldbrush);

		t_brush = CreateSolidBrush(RGB(255, 0, 0));
		oldbrush = (HBRUSH)SelectObject(hDC, t_brush);
		for (int i = 0; i <= count; i++) {
			if (t[i].show == TRUE) {
				Ellipse(hDC, t[i].tail.left, t[i].tail.top, t[i].tail.right, t[i].tail.bottom);
			}
		}
		SelectObject(hDC, oldbrush);

		if (jump_count == 2) {
			KillTimer(hWnd, 3);
			jump_count = 0;
		}

		if (turn_c == 3) {
			KillTimer(hWnd, 4);
			turn_c = 0;
			SetTimer(hWnd, 1, T1, Moveset1);
		}

		if (speed_c == 4) {
			KillTimer(hWnd, 10);
			SetTimer(hWnd, 1, T1, Moveset1);
			speed_c = 0;
		}

		DeleteObject(p_brush);
		DeleteObject(t_brush);
		EndPaint(hWnd, &ps);
		break;	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK Moveset1(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {

	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}

	if (p.player.left == 0 && p.player.top == 0) {
		if (p.y == 2) p.y = 1;
	}

	if (p.player.right == 720 && p.player.top == 0) {
		if (p.y == 2) p.y = 1;
	}

	if (p.player.right == 18 && p.player.bottom == 720) {
		if (p.y == 1) p.y = 2;
	}

	if (p.player.right == 720 && p.player.bottom == 720) {
		if (p.y == 1) p.y = 2;
	}

	if (p.player.left == 0 && p.player.top == 0) {
		if (p.x == 3) p.x == 4;
	}

	if (p.player.right == 720 && p.player.top == 0) {
		if (p.x == 3) p.x = 4;
	}

	if (p.player.right == 18 && p.player.bottom == 720) {
		if (p.x == 4) p.x = 3;
	}

	if (p.player.right == 720 && p.player.bottom == 720) {
		if (p.x == 4) p.x = 3;
	}



	if (p.player.left == 0 || p.player.right == 720) {
		if (p.x == 1) p.x = 2;

		else if (p.x == 2) p.x = 1;


		if (p.y == 1) {
			p.player.top += 18;
			p.player.bottom += 18;
		}

		if (p.y == 2) {
			p.player.top -= 18;
			p.player.bottom -= 18;
		}
	}

	if (p.player.top == 0 || p.player.bottom == 720) {
		if (p.y == 3) p.y = 4;

		else if (p.y == 4) p.y = 3;

		if (p.x == 3) {
			p.player.left += 18;
			p.player.right += 18;
		}

		if (p.x == 4) {
			p.player.left -= 18;
			p.player.right -= 18;
		}
	}

	if (p.x == 1) {
		p.player.left += 18;
		p.player.right += 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.left -= 18;
				p.player.right -= 18;
				p.x = 3;
				p.y = 4;
				break;
			}
		}
	}

	else if (p.x == 2) {
		p.player.left -= 18;
		p.player.right -= 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.left += 18;
				p.player.right += 18;
				p.x = 3;
				p.y = 4;
				break;
			}
		}
	}

	if (p.y == 3) {
		p.player.top -= 18;
		p.player.bottom -= 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.top += 18;
				p.player.bottom += 18;
				p.x = 1;
				p.y = 1;
				break;
			}
		}
	}

	else if (p.y == 4) {
		p.player.top += 18;
		p.player.bottom += 18;
		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.top -= 18;
				p.player.bottom -= 18;
				p.x = 1;
				p.y = 1;
				break;
			}
		}
	}

	for (int i = 0; i <= count; i++) {
		if (p.player.left == t[i].tail.left && p.player.top == t[i].tail.top) {
			t[i].t_num = p.tail_length;
			p.tail_length++;
			t[i].t_check = 1;
			t[i].moveset = 4;
			t_c[p.tail_length].left = p.player.left;
			t_c[p.tail_length].right = p.player.right;
			t_c[p.tail_length].top = p.player.top;
			t_c[p.tail_length].bottom = p.player.bottom;
		}
	}

	for (int i = 0; i <= count; i++) {
		if (t[i].moveset >= 4) {
		
			t[i].tail = t_c[num];
			num++;
		}
	}

	num = 0;

	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK Moveset2(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}

	if (p.player.left == 0 && p.player.top == 0) {
		if (p.y == 2) p.y = 1;
	}

	if (p.player.right == 720 && p.player.top == 0) {
		if (p.y == 2) p.y = 1;
	}

	if (p.player.right == 18 && p.player.bottom == 720) {
		if (p.y == 1) p.y = 2;
	}

	if (p.player.right == 720 && p.player.bottom == 720) {
		if (p.y == 1) p.y = 2;
	}

	if (p.player.left == 0 && p.player.top == 0) {
		if (p.x == 3) p.x == 4;
	}

	if (p.player.right == 720 && p.player.top == 0) {
		if (p.x == 3) p.x = 4;
	}

	if (p.player.right == 18 && p.player.bottom == 720) {
		if (p.x == 4) p.x = 3;
	}

	if (p.player.right == 720 && p.player.bottom == 720) {
		if (p.x == 4) p.x = 3;
	}



	if (p.player.left == 0 || p.player.right == 720) {
		if (p.x == 1) p.x = 2;

		else if (p.x == 2) p.x = 1;


		if (p.y == 1) {
			p.player.top += 18;
			p.player.bottom += 18;
		}

		if (p.y == 2) {
			p.player.top -= 18;
			p.player.bottom -= 18;
		}
	}

	if (p.player.top == 0 || p.player.bottom == 720) {
		if (p.y == 3) p.y = 4;

		else if (p.y == 4) p.y = 3;

		if (p.x == 3) {
			p.player.left += 18;
			p.player.right += 18;
		}

		if (p.x == 4) {
			p.player.left -= 18;
			p.player.right -= 18;
		}
	}

	if (p.x == 1) {
		p.player.left += 18;
		p.player.right += 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.left -= 18;
				p.player.right -= 18;
				p.x = 3;
				p.y = 4;
				break;
			}
		}
	}

	else if (p.x == 2) {
		p.player.left -= 18;
		p.player.right -= 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.left += 18;
				p.player.right += 18;
				p.x = 3;
				p.y = 4;
				break;
			}
		}
	}

	if (p.y == 3) {
		p.player.top -= 18;
		p.player.bottom -= 18;

		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.top += 18;
				p.player.bottom += 18;
				p.x = 1;
				p.y = 1;
				break;
			}
		}
	}

	else if (p.y == 4) {
		p.player.top += 18;
		p.player.bottom += 18;
		for (int i = 0; i < wall_c;i++) {
			if (wall[i].left == p.player.left && wall[i].top == p.player.top) {
				p.player.top -= 18;
				p.player.bottom -= 18;
				p.x = 1;
				p.y = 1;
				break;
			}
		}
	}

	for (int i = 0; i <= count; i++) {
		if (p.player.left == t[i].tail.left && p.player.top == t[i].tail.top) {
			t[i].t_num = p.tail_length;
			p.tail_length++;
			t[i].t_check = 1;
			t[i].moveset = 4;
			t_c[p.tail_length].left = p.player.left;
			t_c[p.tail_length].right = p.player.right;
			t_c[p.tail_length].top = p.player.top;
			t_c[p.tail_length].bottom = p.player.bottom;
		}
	}

	for (int i = 0; i <= count; i++) {
		if (t[i].moveset >= 4) {

			t[i].tail = t_c[num];
			num++;
		}
	}

	num = 0;

	speed_c++;

	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK ShowTail(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {

	if (count < 19) {
		t[count].show = TRUE;
		t[count].moveset = 1 + (rand() % 3);
		t[count].way = 0;
		t[count].move_count = 0;

		t[count].tail.left = 18 * (rand() % 40);
		t[count].tail.right = t[count].tail.left + 18;
		t[count].tail.top = 18 * (rand() % 40);
		t[count].tail.bottom = t[count].tail.top + 18;

		count++;
	}

	for (int i = 0; i <= count; i++) {
		if (t[i].moveset == 1) {
			if (t[i].way == 0) {
				if (t[i].tail.right == 720) t[i].way = 1;

				else {
					t[i].tail.left += 18;
					t[i].tail.right += 18;
				}
			}

			else if (t[i].way == 1) {
				if (t[i].tail.left == 0) t[i].way = 0;

				else {
					t[i].tail.left -= 18;
					t[i].tail.right -= 18;
				}
			}

		}

		if (t[i].moveset == 2) {
			if (t[i].way == 0) {
				if (t[i].move_count == 5 || t[i].tail.right == 720) {
					t[i].move_count = 0;
					t[i].way = 1;
				}

				else {
					t[i].tail.left += 18;
					t[i].tail.right += 18;
					t[i].move_count++;
				}
			}

			else if (t[i].way == 1) {
				if (t[i].move_count == 5 || t[i].tail.bottom == 720) {
					t[i].move_count = 0;
					t[i].way = 2;
				}

				else {
					t[i].tail.top += 18;
					t[i].tail.bottom += 18;
					t[i].move_count++;
				}
			}

			else if (t[i].way == 2) {
				if (t[i].move_count == 5 || t[i].tail.left == 0) {
					t[i].move_count = 0;
					t[i].way = 3;
				}

				else {
					t[i].tail.left -= 18;
					t[i].tail.right -= 18;
					t[i].move_count++;
				}
			}

			else if (t[i].way == 3) {
				if (t[i].move_count == 5 || t[i].tail.top == 0) {
					t[i].move_count = 0;
					t[i].way = 0;
				}

				else {
					t[i].tail.top -= 18;
					t[i].tail.bottom -= 18;
					t[i].move_count++;
				}
			}
		}

		if (t[i].moveset == 3) {
			//정지상태
		}

		
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK Jump(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (p.x == 1&&jump_count == 0) {
		p.player.top -= 18;
		p.player.bottom -= 18;
		jump_count++;
	}

	else if (p.x == 1 && jump_count == 1) {
		p.player.top += 18;
		p.player.bottom += 18;
		jump_count++;
	}

	if (p.x == 2 && jump_count == 0) {
		p.player.top -= 18;
		p.player.bottom -= 18;
		jump_count++;
	}

	else if (p.x == 2 && jump_count == 1) {
		p.player.top += 18;
		p.player.bottom += 18;
		jump_count++;
	}

	if (p.x == 3 && jump_count == 0) {
		p.player.left += 18;
		p.player.right += 18;
		jump_count++;
	}

	else if (p.x == 3 && jump_count == 1) {
		p.player.left -= 18;
		p.player.right -= 18;
		jump_count++;
	}

	if (p.x == 4 && jump_count == 0) {
		p.player.left += 18;
		p.player.right += 18;
		jump_count++;
	}

	else if (p.x == 4 && jump_count == 1) {
		p.player.left -= 18;
		p.player.right -= 18;
		jump_count++;
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK turn(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (p.x == 1) {
		if (turn_c == 0) {
			p.player.left += 18;
			p.player.right += 18;
			turn_c++;
		}

		else if (turn_c == 1) {
			p.player.top += 18;
			p.player.bottom += 18;
			turn_c++;
		}

		else if (turn_c == 2) {
			p.player.left -= 18;
			p.player.right -= 18;
			turn_c++;
			p.x = 2;
		}
	}

	else if (p.x == 2) {
		if (turn_c == 0) {
			p.player.left -= 18;
			p.player.right -= 18;
			turn_c++;
		}

		else if (turn_c == 1) {
			p.player.top += 18;
			p.player.bottom += 18;
			turn_c++;
		}

		else if (turn_c == 2) {
			p.player.left += 18;
			p.player.right += 18;
			turn_c++;
			p.x = 1;
		}
	}

	else if(p.y == 3) {
		if (turn_c == 0) {
			p.player.top -= 18;
			p.player.bottom -= 18;
			turn_c++;
		}

		else if (turn_c == 1) {
			p.player.left += 18;
			p.player.right += 18;
			turn_c++;
		}

		else if (turn_c == 2) {
			p.player.top += 18;
			p.player.bottom += 18;
			turn_c++;
			p.y = 4;
		}
	}

	else if (p.y == 4) {
		if (turn_c == 0) {
			p.player.top += 18;
			p.player.bottom += 18;
			turn_c++;
		}

		else if (turn_c == 1) {
			p.player.left += 18;
			p.player.right += 18;
			turn_c++;
		}

		else if (turn_c == 2) {
			p.player.top -= 18;
			p.player.bottom -= 18;
			turn_c++;
			p.y = 3;
		}
	}

	for (int i = 0; i <= count; i++) {
		if (p.player.left == t[i].tail.left && p.player.top == t[i].tail.top) {
			p.tail_length++;
			t[i].moveset = 4;
			t_c[p.tail_length].left = p.player.left;
			t_c[p.tail_length].right = p.player.right;
			t_c[p.tail_length].top = p.player.top;
			t_c[p.tail_length].bottom = p.player.bottom;
		}
	}

	for (int i = 0; i <= count; i++) {
		if (t[i].moveset >= 4) {

			t[i].tail = t_c[num];
			num++;
		}
	}

	num = 0;


	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK left(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}

	p.player.left -= 18;
	p.player.right -= 18;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK right(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}

	p.player.left += 18;
	p.player.right += 18;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK up(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}
	p.player.top -= 18;
	p.player.bottom -= 18;
	InvalidateRect(hWnd, NULL, TRUE);
}

void CALLBACK down(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = p.tail_length - 1; i >= 0; i--) {
		if (i != 0) {
			t_c[i] = t_c[i - 1];
		}

		if (i == 0) {
			t_c[i] = p.player;
		}
	}

	p.player.top += 18;
	p.player.bottom += 18;
	InvalidateRect(hWnd, NULL, TRUE);
}