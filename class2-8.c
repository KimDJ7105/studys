#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Progaramming 2-8";

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
	POINT Trypot[3] = {{400,400},{325,550},{475,550}};	//»ï°¢Çü
	POINT Penta[5] = { {650,200},{580,275},{610,375},{690,375},{720,275} };	//¿À°¢Çü
	POINT MV_Penta[5] = { {400,220},{340,280},{370,365},{430,365},{460,280} };	//Áß¾Ó ¿À°¢Çü
	POINT HourGlass_one[3] = { {325,70},{475,70},{400,130} };	//¸ð·¡½Ã°è part 1
	POINT HourGlass_two[3] = { {400,130},{325,190},{475,190} };	//¸ð·¡½Ã°è part 2
	POINT MV_HG_one[3] = { {340,250}, {460,250}, {400,300} };	//Áß¾Ó ¸ð·¡½Ã°è 1
	POINT MV_HG_two[3] = { {400,300},{340,350},{460,350} };	//Áß¾Ó ¸ð·¡½Ã°è 2
	POINT MV_try[3] = { {400,265},{345,375},{455,375} };	//Áß¾Ó »ï°¢Çü
	static int toggle = 0;

	HPEN hpen, oldpen;
	HBRUSH for_try, for_penta, for_hourG, for_pie, oldBrush;

	static int Red = 0, Green= 0 , Blue = 0;

	switch (iMessage) {
	case WM_CREATE:
		
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (toggle == 0) toggle = 1;

		else if (toggle == 1) toggle = 2;
		

		Rectangle(hDC, 300, 200, 500, 400);

			if (wParam == 'Q') {
				exit(1);
			}

			if (wParam == 'W') {
				srand(time(NULL));

				if (toggle == 1) {
					Red = rand() % 256;
					Green = rand() % 256;
					Blue = rand() % 256;
				}

				for_hourG = CreateSolidBrush(RGB(Red, Green, Blue));
				oldBrush =(HBRUSH)SelectObject(hDC, for_hourG);

				Polygon(hDC, HourGlass_one, 3);
				Polygon(hDC, HourGlass_two, 3);

				Polygon(hDC, MV_HG_one, 3);
				Polygon(hDC, MV_HG_two, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_hourG);
			}

			if (wParam == 'A') {
				srand(time(NULL));

				if (toggle == 1) {
					Red = rand() % 256;
					Green = rand() % 256;
					Blue = rand() % 256;
				}

				for_pie = CreateSolidBrush(RGB(Red, Green, Blue));
				hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

				oldBrush = (HBRUSH)SelectObject(hDC, for_pie);	//¿øÀ» »öÀ¸·Î Ã¤¿ò
				Ellipse(hDC, 100, 205, 290, 395);
				(HBRUSH)SelectObject(hDC, oldBrush);	//ÆÄÀÌ·Î Èò»öÀ» µ¡Ä¥
				Pie(hDC, 100, 205, 290, 395, 195, 205, 100, 300);
				oldpen = (HPEN)SelectObject(hDC, hpen);
				Arc(hDC, 100, 205, 290, 395, 195, 205, 100, 300);

				SelectObject(hDC, oldpen);

				oldBrush = (HBRUSH)SelectObject(hDC, for_pie);	//¿øÀ» »öÀ¸·Î Ã¤¿ò
				Ellipse(hDC, 325, 225, 475, 375);
				(HBRUSH)SelectObject(hDC, oldBrush);	//ÆÄÀÌ·Î Èò»öÀ» µ¡Ä¥
				Pie(hDC, 325, 225, 475, 375, 400, 225, 325, 300);
				oldpen = (HPEN)SelectObject(hDC, hpen);
				Arc(hDC, 325, 225, 475, 375, 400, 225, 325, 300);

				SelectObject(hDC, oldpen);

				DeleteObject(for_pie);
				DeleteObject(hpen);
			}

			if (wParam == 'S') {
				srand(time(NULL));
				if (toggle == 1) {
					Red = rand() % 256;
					Green = rand() % 256;
					Blue = rand() % 256;
				}

				for_try = CreateSolidBrush(RGB(Red, Green, Blue));
				oldBrush = (HBRUSH)SelectObject(hDC, for_try);

				Polygon(hDC, Trypot, 3);
				Polygon(hDC, MV_try, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_try);
			}

			if (wParam == 'D') {
				srand(time(NULL));
				if (toggle == 1) {
					Red = rand() % 256;
					Green = rand() % 256;
					Blue = rand() % 256;
				}

				for_penta = CreateSolidBrush(RGB(Red, Green, Blue));
				oldBrush = (HBRUSH)SelectObject(hDC, for_penta);

				Polygon(hDC, Penta, 5);
				Polygon(hDC, MV_Penta, 5);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_penta);
			}

			if (wParam == VK_LEFT) {
				for_pie = CreateSolidBrush(RGB(180, 0, 180));
				hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

				//ÆÄÀÌ ±×¸®±â
				oldBrush = (HBRUSH)SelectObject(hDC, for_pie);	//¿øÀ» »öÀ¸·Î Ã¤¿ò
				Ellipse(hDC, 325, 225, 475, 375);
				(HBRUSH)SelectObject(hDC, oldBrush);	//ÆÄÀÌ·Î Èò»öÀ» µ¡Ä¥
				Pie(hDC, 325, 225, 475, 375, 400, 225, 325, 300);
				oldpen = (HPEN)SelectObject(hDC, hpen);
				Arc(hDC, 325, 225, 475, 375, 400, 225, 325, 300);	//Èò»öÀ¸·Î È£¸¦ µ¡Ä¥

				SelectObject(hDC, oldBrush);
				SelectObject(hDC, oldpen);

				DeleteObject(for_pie);
				DeleteObject(hpen);

			}

			else if (wParam == VK_RIGHT) {
				for_penta = CreateSolidBrush(RGB(0, 60, 255));
				oldBrush = (HBRUSH)SelectObject(hDC, for_penta);

				Polygon(hDC, MV_Penta, 5);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_penta);
			}

			else if (wParam == VK_UP) {
				for_hourG = CreateSolidBrush(RGB(100, 255, 20));
				oldBrush = (HBRUSH)SelectObject(hDC, for_hourG);

				Polygon(hDC, MV_HG_one, 3);
				Polygon(hDC, MV_HG_two, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_hourG);
			}

			else if (wParam == VK_DOWN) {
				for_try = CreateSolidBrush(RGB(255, 50, 0));
				oldBrush = (HBRUSH)SelectObject(hDC, for_try);

				Polygon(hDC, MV_try, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(for_try);
			}

		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYUP:
		toggle = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		for_try = CreateSolidBrush(RGB(255, 50, 0));
		for_penta = CreateSolidBrush(RGB(0, 60, 255));
		for_hourG = CreateSolidBrush(RGB(100, 255, 20));
		for_pie = CreateSolidBrush(RGB(180, 0, 180));

		//»ç°¢Çü ±×¸®±â
		Rectangle(hDC, 300, 200, 500, 400);
		//»ï°¢Çü ±×¸®±â
		oldBrush = (HBRUSH)SelectObject(hDC, for_try);
		Polygon(hDC, Trypot, 3);
		//¿À°¢Çü ±×¸®±â
		(HBRUSH)SelectObject(hDC, for_penta);
		Polygon(hDC, Penta, 5);
		//¸ð·¡½Ã°è ±×¸®±â
		(HBRUSH)SelectObject(hDC, for_hourG);
		Polygon(hDC, HourGlass_one, 3);
		Polygon(hDC, HourGlass_two, 3);
		//ÆÄÀÌ ±×¸®±â
		(HBRUSH)SelectObject(hDC, for_pie);	//¿øÀ» »öÀ¸·Î Ã¤¿ò
		Ellipse(hDC, 100, 205, 290, 395);
		(HBRUSH)SelectObject(hDC, oldBrush);	//ÆÄÀÌ·Î Èò»öÀ» µ¡Ä¥
		Pie(hDC, 100, 205, 290, 395, 195, 205, 100, 300);
		oldpen = (HPEN)SelectObject(hDC, hpen);
		Arc(hDC, 100, 205, 290, 395, 195, 205, 100, 300);	//Èò»öÀ¸·Î È£¸¦ µ¡Ä¥

		SelectObject(hDC, oldpen);
		DeleteObject(hpen);
		DeleteObject(for_try);
		DeleteObject(for_penta);
		DeleteObject(for_hourG);
		DeleteObject(for_pie);


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}