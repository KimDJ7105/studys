#include <windows.h>
#include <tchar.h>

//범위를 지정했을 때 범위 내부에 특정 좌표를 잡아서 출력할 수 있을지

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

	PAINTSTRUCT ps;
	HDC hDC;
	RECT rect1;
	RECT rect2;
	RECT rect3;
	RECT rect4;

	TCHAR str1[] = L"ThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRectThisisFirstRect";
	TCHAR str2[] = L"This is Second RectThis is Second Rect";
	TCHAR str3[] = L"This is Third RectThis is Third Rect";
	TCHAR str4[] = L"This is Forth RectThis is Forth Rect";

	switch (iMessage) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		rect1.left = 0;
		rect1.top = 0;
		rect1.right = 400;
		rect1.bottom = 300;

		SetTextColor(hDC, RGB(255, 0, 0));
		SetBkColor(hDC, RGB(0, 0, 200));

		DrawText(hDC, str1, lstrlen(str1), &rect1, DT_WORDBREAK |DT_EDITCONTROL);

		rect2.left = 400;
		rect2.top = 0;
		rect2.right = 800;
		rect2.bottom = 300;
		
		SetTextColor(hDC, RGB(100, 150, 200));
		SetBkColor(hDC, RGB(90, 40, 20));
		DrawText(hDC, str2, 1000, &rect2, DT_WORDBREAK);

		rect3.left = 0;
		rect3.top = 300;
		rect3.right = 400;
		rect3.bottom = 600;

		SetTextColor(hDC, RGB(0, 255, 0));
		SetBkColor(hDC, RGB(10, 100, 130));
		DrawText(hDC, str3, 1000, &rect3, DT_WORDBREAK);

		rect4.left = 400;
		rect4.top = 300;
		rect4.right = 800;
		rect4.bottom = 600;

		SetTextColor(hDC, RGB(130, 180, 60));
		SetBkColor(hDC, RGB(40, 44, 244));
		DrawText(hDC, str4, 1000,&rect4, DT_WORDBREAK );


		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}