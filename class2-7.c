#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming Lab";

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	
	LPPOINT lpPoint;
	PAINTSTRUCT ps;
	HDC hDC;
	static TCHAR str[10][81] = { 0, };
	static TCHAR temp_str[10][81];
	static int count;
	static int line;
	static SIZE size;
	static int y;
	static int n;
	static TCHAR up;
	static int togle;

	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		count = 0;
		line = 0;
		y = 0;
		n = 0;
		togle = 0;
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN) {
			if (line < 9) {
				count = 0;
				line++;

				if (line == 10) line = 0;
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_BACK) {
			if (count > 0) {
				count--;
				str[line][count] = '\0';

			}

			else if (count == 0) {
				line--;
				count = lstrlen(str[line]);
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_ESCAPE) {
			line = 0;
			count = 0;
			
			for (int i = 0; i < 10;i++) {
				str[i][0] = '\0';
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_TAB) {
			str[line][count++] = L' ';
			str[line][count++] = L' ';
			str[line][count++] = L' ';
			str[line][count++] = L' ';
			str[line][count] = '\0';

			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_LEFT) {
			for (int i = 0; i <= count; i++) {
				temp_str[line][i] = str[line][i];
			}

			count--;
			temp_str[line][count] = '\0';

			GetTextExtentPoint32(hDC, temp_str[line], lstrlen(temp_str[line]), &size);
			SetCaretPos(size.cx, y);
		}

		else if (wParam == VK_RIGHT) {
			if (str[line][count] != '\0') {
				
				count++;

				for (int i = 0; i <= count; i++) {
					temp_str[line][i] = str[line][i];
				}

				temp_str[line][count] = '\0';

				GetTextExtentPoint32(hDC, temp_str[line], lstrlen(temp_str[line]), &size);
				SetCaretPos(size.cx, y);
				
			}
		}

		else if (wParam == VK_UP) {
			line--;
			SetCaretPos(size.cx, y-15);
		}

		else if (wParam == VK_DOWN) {
			GetTextExtentPoint32(hDC, temp_str[line], lstrlen(temp_str[line]), &size);
			line++;
			SetCaretPos(size.cx, y + 15);
			str[line][count] = '\0';
		}

		else if (wParam == VK_F1) {
			if (n == 0) n = 1;

			else if (n == 1) n = 0;
		}

		else if(wParam == VK_HOME) {
			count = 0;
			SetCaretPos(0, y);
		}

		else if (wParam == VK_INSERT) {
			if (togle == 0) togle = 1;

			else if (togle == 1) togle = 0;
		}

		else if (wParam == VK_DELETE) {
		int temp_n;
		temp_n = count;
			while (str[line][temp_n] != ' ') {
				temp_n--;
			}

			str[line][++temp_n] = '\0';
			count = temp_n;
			InvalidateRect(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_SPACE) {
			str[line][count++] = L' ';
			str[line][count] = '\0';

			InvalidateRect(hWnd, NULL, TRUE);
        }
	
		else {

			if (n == 0) {
				if (count < 80) {
					str[line][count++] = wParam + 32;
					str[line][count] = '\0';
				}

				else if (count >= 80) {
					count = 0;
					line++;

					if (line == 10) line = 0;
				}
			}

			if (n == 1) {
				if (count < 80) {
					str[line][count++] = wParam;
					str[line][count] = '\0';
				}

				else if (count >= 80) {
					count = 0;
					line++;

					if (line == 10) line = 0;
				}
			}

			if (togle == 0) {
				for (int i = 0; i <= line; i++) {
					TextOut(hDC, 0, i * 15, str[i], lstrlen(str[i]));
					y = i * 15;
				}

				GetTextExtentPoint32(hDC, str[line], lstrlen(str[line]), &size);
				SetCaretPos(size.cx, y);
			}

			if (togle == 1) {
				InvalidateRect(hWnd, NULL, TRUE);
			}

		}

		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		for (int i = 0; i <= line; i++) {
			TextOut(hDC, 0, i * 15, str[i], lstrlen(str[i]));
			y = i * 15;
		}

		GetTextExtentPoint32(hDC, str[line], lstrlen(str[line]), &size);
		SetCaretPos(size.cx, y);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}