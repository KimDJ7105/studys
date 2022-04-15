#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 2-11";

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

void utoi(TCHAR str[30], int order[6]);

typedef struct _figure {
	RECT point;
	int fig_type;
	int Red;
	int Green;
	int Blue;
}figure;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC;
	static RECT* rect;
	static int x, y, part_x, part_y,fig_num,sel,pick,eq_color;
	static figure f[10],highlight;
	HBRUSH hbrush, oldbrush;
	static TCHAR str[15] = L"Selected :";


	switch (iMessage) {
	case WM_CREATE:
		part_x = 0;
		part_y = 0;
		fig_num = 0;
		pick = 15;
		eq_color = 0;
		srand(time(NULL));
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			if (pick < 15) {
				if (f[pick].point.left != 0) {
					f[pick].point.left -= 800 / x;
					f[pick].point.right -= 800 / x;
				}
			}
		}

		if (wParam == VK_RIGHT) {
			if (pick < 15) {
				if (f[pick].point.right != 800) {
					f[pick].point.left += 800 / x;
					f[pick].point.right += 800 / x;
				}
			}
		}

		if (wParam == VK_UP) {
			if (pick < 15) {
				if (f[pick].point.top != 0) {
					f[pick].point.top -= 640 / y;
					f[pick].point.bottom -= 640 / y;
				}
			}
		}

		if (wParam == VK_DOWN) {
			if (pick < 15) {
				if (f[pick].point.bottom != 640) {
					f[pick].point.top += 640 / y;
					f[pick].point.bottom += 640 / y;
				}
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == 's') {
			x = 30;
			y = 30;

			rect = (RECT*)malloc(x * y * sizeof(RECT));

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
			
		}

		else if (wParam == 'm') {
			x = 40;
			y = 40;

			rect = (RECT*)malloc(x * y * sizeof(RECT));

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
			
		}

		else if (wParam == 'l') {
			x = 50;
			y = 50;

			rect = (RECT*)malloc(x * y * sizeof(RECT));

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
			
		}

		if (wParam == 'e') {
			if (fig_num <= 9) {
				sel = rand() % (x * y);
				f[fig_num].Red = rand() % 256;
				f[fig_num].Green = rand() % 256;
				f[fig_num].Blue = rand() % 256;
				f[fig_num].point.left = rect[sel].left;
				f[fig_num].point.top = rect[sel].top;
				f[fig_num].point.right = rect[sel].right;
				f[fig_num].point.bottom = rect[sel].bottom;

				f[fig_num].fig_type = 3;

				fig_num++;
			}

			else if (fig_num > 9) {

				for (int i = 0; i < 9; i++) {
					f[i] = f[i + 1];
				}

				sel = rand() % (x * y);
				f[9].Red = rand() % 256;
				f[9].Green = rand() % 256;
				f[9].Blue = rand() % 256;
				f[9].point.left = rect[sel].left;
				f[9].point.top = rect[sel].top;
				f[9].point.right = rect[sel].right;
				f[9].point.bottom = rect[sel].bottom;

				f[9].fig_type = 3;
			}

			//Ellipse(hDC, f[fig_num].point.left, f[fig_num].point.top, f[fig_num].point.right, f[fig_num].point.bottom);
		}

		else if (wParam == 't') {
			if (fig_num <= 9) {
				sel = rand() % (x * y);
				f[fig_num].Red = rand() % 256;
				f[fig_num].Green = rand() % 256;
				f[fig_num].Blue = rand() % 256;
				f[fig_num].point.left = rect[sel].left;
				f[fig_num].point.top = rect[sel].top;
				f[fig_num].point.right = rect[sel].right;
				f[fig_num].point.bottom = rect[sel].bottom;

				f[fig_num].fig_type = 1;

				fig_num++;
			}

			else if (fig_num > 9) {

				for (int i = 0; i < 9; i++) {
					f[i] = f[i + 1];
				}

				sel = rand() % (x * y);
				f[9].Red = rand() % 256;
				f[9].Green = rand() % 256;
				f[9].Blue = rand() % 256;
				f[9].point.left = rect[sel].left;
				f[9].point.top = rect[sel].top;
				f[9].point.right = rect[sel].right;
				f[9].point.bottom = rect[sel].bottom;

				f[9].fig_type = 1;
			}

			/*int lastpoint = (f[fig_num].point.left + f[fig_num].point.right) / 2;
			POINT try[3] = { {f[fig_num].point.right,f[fig_num].point.bottom},{f[fig_num].point.left,f[fig_num].point.bottom},{lastpoint,f[fig_num].point.top} };

			Polygon(hDC, try, 3);*/
		}

		else if (wParam == 'r') {
			if (fig_num <= 9) {
				sel = rand() % (x * y);
				f[fig_num].Red = rand() % 256;
				f[fig_num].Green = rand() % 256;
				f[fig_num].Blue = rand() % 256;
				f[fig_num].point.left = rect[sel].left;
				f[fig_num].point.top = rect[sel].top;
				f[fig_num].point.right = rect[sel].right;
				f[fig_num].point.bottom = rect[sel].bottom;

				f[fig_num].fig_type = 2;

				fig_num++;
			}

			else if (fig_num > 9) {

				for (int i = 0; i < 9; i++) {
					f[i] = f[i + 1];
				}

				sel = rand() % (x * y);
				f[9].Red = rand() % 256;
				f[9].Green = rand() % 256;
				f[9].Blue = rand() % 256;
				f[9].point.left = rect[sel].left;
				f[9].point.top = rect[sel].top;
				f[9].point.right = rect[sel].right;
				f[9].point.bottom = rect[sel].bottom;

				f[9].fig_type = 2;
			}

			//Rectangle(hDC, f[fig_num].point.left, f[fig_num].point.top, f[fig_num].point.right, f[fig_num].point.bottom);
		}

		if (wParam == VK_NUMPAD1 || wParam == '1') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[0].fig_type;
			highlight.Red = f[0].Red;
			highlight.Green = f[0].Green;
			highlight.Blue = f[0].Blue;
			pick = 0;
		}

		else if (wParam == VK_NUMPAD2 || wParam == '2') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[1].fig_type;
			highlight.Red = f[1].Red;
			highlight.Green = f[1].Green;
			highlight.Blue = f[1].Blue;
			pick = 1;
		}

		else if (wParam == VK_NUMPAD3 || wParam == '3') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[2].fig_type;
			highlight.Red = f[2].Red;
			highlight.Green = f[2].Green;
			highlight.Blue = f[2].Blue;
			pick = 2;
		}

		else if (wParam == VK_NUMPAD4 || wParam == '4') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[3].fig_type;
			highlight.Red = f[3].Red;
			highlight.Green = f[3].Green;
			highlight.Blue = f[3].Blue;
			pick = 3;
		}

		else if (wParam == VK_NUMPAD5 || wParam == '5') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[4].fig_type;
			highlight.Red = f[4].Red;
			highlight.Green = f[4].Green;
			highlight.Blue = f[4].Blue;
			pick = 4;
		}

		else if (wParam == VK_NUMPAD6 || wParam == '6') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[5].fig_type;
			highlight.Red = f[5].Red;
			highlight.Green = f[5].Green;
			highlight.Blue = f[5].Blue;
			pick = 5;
		}

		else if (wParam == VK_NUMPAD7 || wParam == '7') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[6].fig_type;
			highlight.Red = f[6].Red;
			highlight.Green = f[6].Green;
			highlight.Blue = f[6].Blue;
			pick = 6;
		}

		else if (wParam == VK_NUMPAD8 || wParam == '8') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[7].fig_type;
			highlight.Red = f[7].Red;
			highlight.Green = f[7].Green;
			highlight.Blue = f[7].Blue;
			pick = 7;
		}

		else if (wParam == VK_NUMPAD9 || wParam == '9') {
			highlight.point.left = 880;
			highlight.point.top = 30;
			highlight.point.right = 880 + (800 / x);
			highlight.point.bottom = 30 + (640 / y);
			highlight.fig_type = f[8].fig_type;
			highlight.Red = f[8].Red;
			highlight.Green = f[8].Green;
			highlight.Blue = f[8].Blue;
			pick = 8;
		}

		else if (wParam == VK_NUMPAD0 || wParam == '0') {
		highlight.point.left = 880;
		highlight.point.top = 30;
		highlight.point.right = 880 + (800 / x);
		highlight.point.bottom = 30 + (640 / y);
		highlight.fig_type = f[9].fig_type;
		highlight.Red = f[9].Red;
		highlight.Green = f[9].Green;
		highlight.Blue = f[9].Blue;
		pick = 9;
		}

		if (wParam == '-') {
			if ((f[pick].point.right - f[pick].point.left) > 800/x) {
				f[pick].point.right -= 800/x;
				f[pick].point.bottom -= 640/y;
			}
		}

		else if (wParam == '+') {
			if (f[pick].point.right < 800 && f[pick].point.bottom < 640) {
				f[pick].point.right += 800/x;
				f[pick].point.bottom += 640/y;
			}
		}

		if (wParam == 'c') {
			if (eq_color == 0) eq_color = 1;

			else if (eq_color == 1) eq_color = 0;
		}

		if (wParam == 'd') {
			for (int i =  pick; i < 9; i++) {
				f[i] = f[i + 1];
			}
			fig_num--;
		}

		if (wParam == 'p') {
			part_x = 0;
			part_y = 0;
			fig_num = 0;
			pick = 15;
			eq_color = 0;

			for (int i = 0; i < 10;i++) {
				f[i].fig_type = 0;
			}
			
			x = 0;
			y = 0;
			rect = NULL;
		}

		if (wParam == 'q') {
			exit(1);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i < x * y;i++) {
			Rectangle(hDC, rect[i].left, rect[i].top, rect[i].right, rect[i].bottom);
		}
		

		for (int i = 0; i < fig_num + 1;i++) {
			if (f[i].fig_type == 1) {
				hbrush = CreateSolidBrush(RGB(f[i].Red, f[i].Green, f[i].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				int lastpoint = (f[i].point.left + f[i].point.right) / 2;
				POINT try[3] = { {f[i].point.right,f[i].point.bottom},{f[i].point.left,f[i].point.bottom},{lastpoint,f[i].point.top} };

				Polygon(hDC, try, 3);

				SelectObject(hDC,oldbrush);
				DeleteObject(hbrush);
			}

			else if (f[i].fig_type == 2) {
				hbrush = CreateSolidBrush(RGB(f[i].Red, f[i].Green, f[i].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Rectangle(hDC, f[i].point.left, f[i].point.top, f[i].point.right, f[i].point.bottom);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}

			else if (f[i].fig_type == 3) {
				hbrush = CreateSolidBrush(RGB(f[i].Red, f[i].Green, f[i].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Ellipse(hDC, f[i].point.left, f[i].point.top, f[i].point.right, f[i].point.bottom);
				
				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}
		}

		if (pick < 15) {
			TextOut(hDC, 880, 15, str, lstrlen(str));
			if (highlight.fig_type == 1) {
				hbrush = CreateSolidBrush(RGB(highlight.Red, highlight.Green, highlight.Blue));
				oldbrush = SelectObject(hDC, hbrush);

				int lastpoint = (highlight.point.left + highlight.point.right) / 2;
				POINT try[3] = { {highlight.point.right,highlight.point.bottom},{highlight.point.left,highlight.point.bottom},{lastpoint,highlight.point.top} };

				Polygon(hDC, try, 3);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}

			else if (highlight.fig_type == 2) {
				hbrush = CreateSolidBrush(RGB(highlight.Red, highlight.Green, highlight.Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Rectangle(hDC, highlight.point.left, highlight.point.top, highlight.point.right, highlight.point.bottom);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}
			else if (highlight.fig_type == 3) {
				hbrush = CreateSolidBrush(RGB(highlight.Red, highlight.Green, highlight.Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Ellipse(hDC, highlight.point.left, highlight.point.top, highlight.point.right, highlight.point.bottom);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}

			if (f[pick].fig_type == 1) {
				hbrush = CreateSolidBrush(RGB(f[pick].Red, f[pick].Green, f[pick].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				int lastpoint = (f[pick].point.left + f[pick].point.right) / 2;
				POINT try[3] = { {f[pick].point.right,f[pick].point.bottom},{f[pick].point.left,f[pick].point.bottom},{lastpoint,f[pick].point.top} };

				Polygon(hDC, try, 3);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}

			else if (f[pick].fig_type == 2) {
				hbrush = CreateSolidBrush(RGB(f[pick].Red, f[pick].Green, f[pick].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Rectangle(hDC, f[pick].point.left, f[pick].point.top, f[pick].point.right, f[pick].point.bottom);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}

			else if (f[pick].fig_type == 3) {
				hbrush = CreateSolidBrush(RGB(f[pick].Red, f[pick].Green, f[pick].Blue));
				oldbrush = SelectObject(hDC, hbrush);

				Ellipse(hDC, f[pick].point.left, f[pick].point.top, f[pick].point.right, f[pick].point.bottom);

				SelectObject(hDC, oldbrush);
				DeleteObject(hbrush);
			}
		}

		if (eq_color == 1) {
			for (int i = 0; i < fig_num + 1;i++) {
				if (f[i].fig_type == 1) {
					hbrush = CreateSolidBrush(RGB(255,0,0));
					oldbrush = SelectObject(hDC, hbrush);

					int lastpoint = (f[i].point.left + f[i].point.right) / 2;
					POINT try[3] = { {f[i].point.right,f[i].point.bottom},{f[i].point.left,f[i].point.bottom},{lastpoint,f[i].point.top} };

					Polygon(hDC, try, 3);

					SelectObject(hDC, oldbrush);
					DeleteObject(hbrush);
				}

				else if (f[i].fig_type == 2) {
					hbrush = CreateSolidBrush(RGB(0, 255, 0));
					oldbrush = SelectObject(hDC, hbrush);

					Rectangle(hDC, f[i].point.left, f[i].point.top, f[i].point.right, f[i].point.bottom);

					SelectObject(hDC, oldbrush);
					DeleteObject(hbrush);
				}

				else if (f[i].fig_type == 3) {
					hbrush = CreateSolidBrush(RGB(0, 0, 255));
					oldbrush = SelectObject(hDC, hbrush);

					Ellipse(hDC, f[i].point.left, f[i].point.top, f[i].point.right, f[i].point.bottom);

					SelectObject(hDC, oldbrush);
					DeleteObject(hbrush);
				}
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