#define _CRT_SECURE_NO_WARNINGS  
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"
#include<stdlib.h>
//조원들 헤더↓
#include "BJY.h"
#include "SBG.h"
#include "YYG.h"
#include "SSS.h"
#include "AUT.h"


//함수선언은 125페이지쯤

//출력문은 180페이지쯤 있습니다

//수정 하고프면 맘껏 수정해 주세요



/******************************************************************************
*팀명		:가팀 또는 A팀
프로그램명	:Ai3_GaTeam_lottery
*설명		:로또 번호를 예측하는 프로그램입니다.
*주석작성자	:전규환
*버전		:0.9
*개발팀		:전규환 백지윤 송성수 신봉규 윤영준
*생성일자	:2021-8-23 18:00
*완성일자	:수정내역
*
* WinMain.c	:
		작성자	:	전규환
		기능	:winapi로 만들어진 메인소스입니다.
*				 각 헤더로부터 알고리즘을 받아와
				 화면에 출력하는 소스입니다.

*BJY.h
		작성자	:	백지윤
		기능	:랜덤으로 출력된 번호가 짝수이거나 홀수일때
*				 재생성하는 알고리즘을 가진 코드입니다.
*
*SBG.h
		작성자	:	신봉규
				기능:랜덤으로 출력이 되더라도 연속으로 수가3개
*				 이상일때 재생성을 해주는 알고리즘입니다.
*
*SSS.h
		작성자	:	송성수
		기능	:당첨이력이 낮은 번호의 데이터베이스를 모아
*				 랜덤으로 출력할때 해당 번호를 제외하는 알고
*				 리즘 코드 입니다.
*
*YYG.h
		작성자	:	윤영준
		기능	:출력된 복권번호중에 일의자리의 수 (1~9)가
*				 연속으로 있을시에 해당 번호를 폐기후 다시
*				 출력해주는 알고리즘입니다.
*
* AUTO.h
		:작성자 :https://blog.naver.com/hhhighhh/220742413075
*		:기능	:팀의 복권예제소스의 원본 코드이며 이코드를 수정하여
*				 알고리즘을 제작하였습니다.
*******************************************************************************/


/*******************************************************************************
* 처음으로 만들고 싶어서 급하게 제작한 gui프로그램입니다.
* 안쓰이는 코드,파일,파편화,스파게티등등 ,오류등이 많습니다.
* 팀원들이 각자 원하는 알고리즘을 만들며 여러가지 옵션 출력등을 제작하였는데
* 연결할때 딸랑 값만 가져올수밖에 없는 프로그램밖에 못만들어서 아쉽습니다.*
 *******************************************************************************/





LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Ai3_A팀 복권 프로그램");

//화면 중앙정렬함수
void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT clientRect;
	GetClientRect(window, &clientRect);

	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;

	SetWindowPos(window, NULL,
		screenWidth / 2 - clientWidth / 2,
		screenHeight / 2 - clientHeight / 2,
		clientWidth, clientHeight, 0
	);
}//화면 중앙정렬


//win32 메인함수
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;

	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;


	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_ICON2);//돈모양 아이콘
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MY_MENU);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass,
		lpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int answer = 0;//종료
	OPENFILENAME SFN;
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitmap, OldBitmap;
	CHOOSEFONT		FONT;
	static COLORREF fColor;
	HFONT			hFont, OldFont;
	static LOGFONT	LogFont;


	//도킹용 선언문 놓고 연산하는곳--start
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int AUTO_NUM = 6;

	//BJY-start
	BJY_main();
	int BJY_[6];
	for (int i = 0; i < 6; i++) {
		BJY_[i] = BJYlottonum[i];
	}
	//BJY-endl
	//SBG-start
	SBG_main();
	int SBG_[6];
	for (int i = 0; i < 6; i++) {
		SBG_[i] = SBGlottonum[i];
	}
	//SBG-endl
	//YYG-start
	YYG_main();
	int YYG_[6];
	for (int i = 0; i < 6; i++) {
		YYG_[i] = YYG_lottonum[i];
	}
	//YYG-endl
	//SSS
	SSS_main();
	int SSS_[6];
	for (int i = 0; i < 6; i++) {
		SSS_[i] = YYG_lottonum[i];
	}
	//SSS
	//AUTO

	//AUTTO_main();
	//int AUT_[6];
	//for (int i = 0; i < 6; i++) {
	//	AUT_[i] = AUT_lottonum[i];
	//}

	/*
	for (int i=0; AUT_[i]||SSS_[i]||YYG_[i]||SBG_[i]||BJY_[i];i++)
	{
			BJY_main();
			BJY_[i] = BJYlottonum[i];

			SBG_main();
			SBG_[i] = SBGlottonum[i];

			YYG_main();
			YYG_[i] = YYG_lottonum[i];
			SSS_main();
			SSS_[i] = YYG_lottonum[i];
			AUTTO_main();
			AUT_[i] = AUT_lottonum[i];
			if (i == 4)i = 0;
	}
	*/
	//AUTO


	//도킹용 선언문 놓고 연산하는곳--end
	AddFontResource("NanumGothicLight.ttf");
	LOGFONT logFont;
	static HFONT s_hFont = (HFONT)NULL;
	NONCLIENTMETRICS nonClientMetrics;



	ZeroMemory(&nonClientMetrics, sizeof(NONCLIENTMETRICS));
	switch (iMessage) {
	case WM_CREATE:
		PlaceInCenterOfScreen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);


		break;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 480;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 720;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 480;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 720;
		return FALSE;
	case WM_PAINT:
		ZeroMemory(&logFont, sizeof(LOGFONT));
		hdc = BeginPaint(hWnd, &ps);
		logFont.lfHeight = -MulDiv(20, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_NORMAL;

		MemDC = CreateCompatibleDC(hdc);

		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));

		OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

		BitBlt(hdc, 0, 0, 480, 720, MemDC, 0, 0, SRCCOPY);

		hFont = CreateFontIndirect(&LogFont);
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, fColor);

		//날짜
		LPTSTR TTIME[40];
		wsprintf(TTIME, TEXT("%d / %d "), tm.tm_mon + 1, tm.tm_mday);
		TextOut(hdc, 240, 190, TTIME, lstrlen(TTIME));
		switch (tm.tm_wday) {
		case 0://일
			TextOut(hdc, 290, 240, TEXT("(일)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("6일후 복권추첨이 시작됩니다"), lstrlen(TEXT("6일후 복권추첨이 시작됩니다")));
			break;
		case 1://월
			TextOut(hdc, 290, 240, TEXT("(월)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("5일후 복권추첨이 시작됩니다"), lstrlen(TEXT("6일후 복권추첨이 시작됩니다")));
			break;
		case 2://화
			TextOut(hdc, 290, 240, TEXT("(화)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("4일후 복권추첨이 시작됩니다"), lstrlen(TEXT("6일후 복권추첨이 시작됩니다")));
			break;
		case 3://수
			TextOut(hdc, 290, 240, TEXT("(수)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("3일후 복권추첨이 시작됩니다! "), lstrlen(TEXT("6일후 복권추첨이 시작됩니다!")));
			break;
		case 4://목
			TextOut(hdc, 290, 240, TEXT("(목)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("2일후 복권추첨이 시작됩니다!!"), lstrlen(TEXT("6일후 복권추첨이 시작됩니다!!!")));
			break;
		case 5://금
			TextOut(hdc, 290, 240, TEXT("(금)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("내일 복권추첨이 시작됩니다!!!  얼릉사세요!"), lstrlen(TEXT("1일후 복권추첨이 시작됩니다!!!  얼릉사세요!")));
			break;
		case 6://토
			TextOut(hdc, 290, 240, TEXT("(토)"), lstrlen(TEXT("(일)")));
			TextOut(hdc, 110, 260, TEXT("오늘 복권추첨이 시작합니닭!!!!"), lstrlen(TEXT("오늘 복권추첨이 시작합니다!!!!")));
			break;
		}


		//발행일
		LPTSTR TTTTIME[40];
		wsprintf(TTTTIME, TEXT("발행일: %3d . %3d . %3d   %3d:%3d"), tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
		TextOut(hdc, 110, 240, TTTTIME, lstrlen(TTTTIME));

		TextOut(hdc, 30, 290, TEXT(" - - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -"), 105);
		TextOut(hdc, 30, 310, TEXT("순서/이름                                당첨번호 "), 46);

		//BJY BJY BJY
		TextOut(hdc, 40, 330, TEXT("A"), lstrlen(TEXT("A")));
		TextOut(hdc, 70, 330, TEXT("BJY"), lstrlen(TEXT("BJY")));

		LPTSTR BJY[40];//최대 길이
		wsprintf(BJY, TEXT("%6d  %6d  %6d  %6d  %6d  %6d"), BJY_[0], BJY_[3], BJY_[4], BJY_[1], BJY_[2], BJY_[5]);//프린터함수
		TextOut(hdc, 130, 330, BJY, lstrlen(BJY));


		//YYG YYG YYG
		TextOut(hdc, 40, 360, TEXT("B"), lstrlen(TEXT("A")));
		TextOut(hdc, 70, 360, TEXT("YYG"), lstrlen(TEXT("YYG")));

		LPTSTR YYG[40];//최대 길이
		wsprintf(YYG, TEXT("%6d  %6d  %6d  %6d  %6d  %6d"), YYG_[1], YYG_[2], YYG_[5], YYG_[0], YYG_[3], YYG_[4]);//프린터함수
		TextOut(hdc, 130, 360, YYG, lstrlen(YYG));



		//SBG SBG SBG
		TextOut(hdc, 40, 390, TEXT("C"), lstrlen(TEXT("A")));
		TextOut(hdc, 70, 390, TEXT("SBG"), lstrlen(TEXT("SBG")));

		LPTSTR SBG[40];//최대 길이
		wsprintf(SBG, TEXT("%6d  %6d  %6d  %6d  %6d  %6d"), SBG_[2], SBG_[1], SBG_[0], SBG_[5], SBG_[4], SBG_[3]);//프린터함수
		TextOut(hdc, 130, 390, SBG, lstrlen(SBG));



		//SSS SSS SSS
		TextOut(hdc, 40, 420, TEXT("D"), lstrlen(TEXT("A")));
		TextOut(hdc, 70, 420, TEXT("SSS"), lstrlen(TEXT("SSS")));

		LPTSTR SSS[40];//최대 길이
		wsprintf(SSS, TEXT("%6d  %6d  %6d  %6d  %6d  %6d"), SSS_[3], SSS_[0], SSS_[1], SSS_[4], SSS_[5], SSS_[2]);//프린터함수
		TextOut(hdc, 130, 420, SSS, lstrlen(SSS));


		//AUTO AUTO AUTO
		//TextOut(hdc, 40, 450, TEXT("E"), lstrlen(TEXT("A")));
		//TextOut(hdc, 70, 450, TEXT("AUTO"), lstrlen(TEXT("AUTO")));

		//LPTSTR JGH[30];//최대 길이
		//wsprintf(JGH, TEXT("%6d  %6d  %6d  %6d  %6d  %6d"), AUT_[4], AUT_[5], AUT_[2], AUT_[3], AUT_[0], AUT_[1]);//프린터함수
		//TextOut(hdc, 130, 450, JGH, lstrlen(JGH));


		TextOut(hdc, 30, 480, TEXT(" - - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -- - - - - - -"), 105);
		TextOut(hdc, 140, 510, TEXT("▼쓰인 알고리즘 제목▼"), 12);
		TextOut(hdc, 35, 530, TEXT("A:홀짝  B:일의자리 수 C:연속된 수  D:당첨이력  E:랜덤 "), lstrlen(TEXT("A:홀짝  B:랜덤  C:연속된 수  D:당첨이력  E:일의자리 수")));


		//InvalidateRect(hWnd, NULL, TRUE);//1초마다 화면갱신->버그
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SAVE:
			break;
		case ID_EXIT:
			MessageBox(hWnd,
				TEXT("종료 하시겠습니까?"),
				TEXT("진짜 종료"),
				MB_YESNOCANCEL);
			if (answer == IDYES || answer == IDNO)
				PostQuitMessage(0);
			return 0;
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}