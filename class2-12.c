#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 2-12";

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 700, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;

}

int alpatoi(WPARAM wParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	static RECT* rect;
	static RECT Alpa[26], step,End,Box;
	static TCHAR str[50];
	static TCHAR masege[50] = L"You Can Still Save Him!!";
	static int phase,count,life,result,wrong[6],Cc,win,lose;
	static int* correct;
	HBRUSH hbrush, oldbrush;
	HFONT hfont, oldfont;
	HPEN hpen, oldpen;

	switch (iMessage) {
	case WM_CREATE:
		phase = 0;
		count = 0;
		life = 0;
		Cc = 0;
		win = 0;
		lose = 0;

		for (int i = 0; i < 9;i++) {
			Alpa[i].top = 300;
			Alpa[i].bottom = 400;
			Alpa[i].left = 50 + i * 80;
			Alpa[i].right = 130 + i * 80;
		}

		for (int i = 9; i < 18;i++) {
			Alpa[i].top = 400;
			Alpa[i].bottom = 500;
			Alpa[i].left = 50 + (i-9) * 80;
			Alpa[i].right = 130 + (i-9) * 80;
		}

		for (int i = 18; i < 26;i++) {
			Alpa[i].top = 500;
			Alpa[i].bottom = 600;
			Alpa[i].left = 90 + (i-18) * 80;
			Alpa[i].right = 170 + (i-18) * 80;
		}

		for (int i = 0; i < 6;i++) {
			wrong[i] = 30;
		}
		step.left = 500;
		step.right = 750;
		step.top = 220;
		step.bottom = 260;

		End.left = 0;
		End.top = 0;
		End.right = 1000;
		End.bottom = 800;

		Box.left = 620;
		Box.right = 700;
		Box.top = 185;
		Box.bottom = 220;
		break;
	case WM_KEYDOWN:
		break;
	case WM_CHAR:
		if (phase == 0) {
			if (wParam == VK_RETURN) {
				rect = (RECT*)malloc(sizeof(RECT) *lstrlen(str));
				correct = (int*)malloc(sizeof(int) * lstrlen(str));
				for (int i = 0; i < count; i++) {
					rect[i].left = 50 + i * 60;
					rect[i].right = 110 + i * 60;
					rect[i].top = 180;
					rect[i].bottom = 260;
				}

				phase = 1;
				InvalidateRect(hWnd, NULL, TRUE);
			}

			str[count++] = wParam;
			str[count] = '\0';
		}

		else if (phase == 1) {
			result = 0;
			for (int i = 0; i < count; i++) {
				if (str[i] == wParam) {
					int seek = 0;

					for (int j = 0; j < Cc;j++) {
						if (i == correct[j]) seek = 1;
					}

					if (seek != 1) {
						correct[Cc] = i;
						result = 1;
						Cc++;
						break;
					}
				}
			}

			if (result != 1) {
				wrong[life] = alpatoi(wParam) - 1;
				life++;
			}

			if (Cc == count-1) {
				win = 1;
			}

			if (life == 6) {
				lose = 1;
			}

			InvalidateRect(hWnd, NULL, TRUE);

			if (wParam == VK_BACK) {
				phase = 0;
				count = 0;
				life = 0;
				Cc = 0;
				win = 0;
				lose = 0;

				for (int i = 0; i < 6;i++) {
					wrong[i] = 30;
				}

				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 26; i++) {
			Rectangle(hDC, Alpa[i].left, Alpa[i].top, Alpa[i].right, Alpa[i].bottom);

			TCHAR alpha[2];
			alpha[0] = i + 65;
			alpha[1] = '\0';

			hfont = CreateFont(65, 35, 0, 0, 300, 0, 0, 0, NULL, 0, 0, 0, 0, NULL);
			oldfont = (HFONT)SelectObject(hDC, hfont);

			DrawText(hDC, alpha, lstrlen(alpha), &Alpa[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			SelectObject(hDC, oldfont);
			DeleteObject(hfont);
		}

		if (phase == 1) {
			Rectangle(hDC, step.left, step.top, step.right, step.bottom);
			MoveToEx(hDC, 600, 220, NULL);
			LineTo(hDC,600 ,15 );
			MoveToEx(hDC, 600, 15, NULL);
			LineTo(hDC, 720, 15);

			if (life >= 1) {	//ÁÙ
				MoveToEx(hDC, 660, 15, NULL);
				LineTo(hDC, 660, 35);
			}

			if (life >= 2) {	//¸Ó¸®
				Ellipse(hDC, 645, 35, 675, 65);
			}

			if (life >= 3) {	//¸ö
				MoveToEx(hDC, 660, 65, NULL);
				LineTo(hDC, 660, 115);
			}

			if (life >= 4) {	//¾çÆÈ
				MoveToEx(hDC, 660, 85, NULL);
				LineTo(hDC, 640, 135);
				MoveToEx(hDC, 660, 85, NULL);
				LineTo(hDC, 680, 135);
			}

			if (life >= 5) {	//¾ç ´Ù¸®
				MoveToEx(hDC, 660, 115, NULL);
				LineTo(hDC, 640, 185);
				MoveToEx(hDC, 660, 115, NULL);
				LineTo(hDC, 680, 185);

				TextOut(hDC, 0, 0, masege, lstrlen(masege));
			}

			for (int i = 0; i < count; i++) {
				Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
			}

			for (int i = 0; i < 26;i++) {
				for (int j = 0; j < 6; j++) {
					if (wrong[j] == i) {
						hbrush = CreateSolidBrush(RGB(150, 150, 150));
						oldbrush = (HBRUSH)SelectObject(hDC, hbrush);
						Rectangle(hDC, Alpa[i].left, Alpa[i].top, Alpa[i].right, Alpa[i].bottom);
						
						TCHAR alpha[2];
						alpha[0] = i + 65;
						alpha[1] = '\0';

						hfont = CreateFont(65, 35, 0, 0, 300, 0, 0, 0, NULL, 0, 0, 0, 0, NULL);
						oldfont = (HFONT)SelectObject(hDC, hfont);

						SetBkColor(hDC, RGB(150, 150, 150));

						DrawText(hDC, alpha, lstrlen(alpha), &Alpa[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						SetBkColor(hDC, RGB(250, 250, 250));
						SelectObject(hDC, oldfont);
						SelectObject(hDC, oldbrush);
						DeleteObject(hfont);
						DeleteObject(hbrush);
					}

				}
			}
		}

		for (int i = 0; i < Cc; i++) {
			TCHAR alpha[2];
			alpha[0] = str[correct[i]];
			alpha[1] = '\0';

			hfont = CreateFont(65, 35, 0, 0, 300, 0, 0, 0, NULL, 0, 0, 0, 0, NULL);
			oldfont = (HFONT)SelectObject(hDC, hfont);

			DrawText(hDC,alpha , lstrlen(alpha),&rect[correct[i]], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			SelectObject(hDC, oldfont);
			DeleteObject(hfont);
		}

		if (win == 1) {
			if (life >= 5) {
				Rectangle(hDC, Box.left, Box.top, Box.right, Box.bottom);
				hpen = CreatePen(PS_SOLID, 1,RGB(255, 255, 255));
				oldpen = (HPEN)SelectObject(hDC, hpen);
				MoveToEx(hDC, 660, 15, NULL);
				LineTo(hDC, 660, 35);
				SelectObject(hDC, oldpen);
				DeleteObject(hpen);
			}
			Beep(330, 200);
			Beep(440, 200);
			Beep(554, 200);
			Beep(659, 200);
			Beep(880, 300);

			Rectangle(hDC, End.left, End.top, End.right, End.bottom);

			TCHAR Endment[10] = L"You win!";

			TCHAR Endment2[15] = L"You did It!";

			if (life >= 5) {
				DrawText(hDC, Endment2, lstrlen(Endment2), &End, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			else DrawText(hDC, Endment, lstrlen(Endment), &End, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		if (lose == 1) {
			Beep(1000, 500);
			
			Rectangle(hDC, End.left, End.top, End.right, End.bottom);

			TCHAR Endment[11] = L"Game Over!";

			DrawText(hDC, Endment, lstrlen(Endment), &End, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int alpatoi(WPARAM wParam) {
	if (wParam == 'a' || wParam == 'A') return 1;
	if (wParam == 'b' || wParam == 'B') return 2;
	if (wParam == 'c' || wParam == 'C') return 3;
	if (wParam == 'd' || wParam == 'D') return 4;
	if (wParam == 'e' || wParam == 'E') return 5;
	if (wParam == 'f' || wParam == 'F') return 6;
	if (wParam == 'g' || wParam == 'G') return 7;
	if (wParam == 'h' || wParam == 'H') return 8;
	if (wParam == 'i' || wParam == 'I') return 9;
	if (wParam == 'j' || wParam == 'J') return 10;
	if (wParam == 'k' || wParam == 'K') return 11;
	if (wParam == 'l' || wParam == 'L') return 12;
	if (wParam == 'm' || wParam == 'M') return 13;
	if (wParam == 'n' || wParam == 'N') return 14;
	if (wParam == 'o' || wParam == 'O') return 15;
	if (wParam == 'p' || wParam == 'P') return 16;
	if (wParam == 'q' || wParam == 'Q') return 17;
	if (wParam == 'r' || wParam == 'R') return 18;
	if (wParam == 's' || wParam == 'S') return 19;
	if (wParam == 't' || wParam == 'T') return 20;
	if (wParam == 'u' || wParam == 'U') return 21;
	if (wParam == 'v' || wParam == 'V') return 22;
	if (wParam == 'w' || wParam == 'W') return 23;
	if (wParam == 'x' || wParam == 'X') return 24;
	if (wParam == 'y' || wParam == 'Y') return 25;
	if (wParam == 'z' || wParam == 'Z') return 26;
}