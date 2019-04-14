#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>	//키보드 입력 함수 사용을 위해
#include "run_function.h"
#pragma warning (disable:4996) //오류 제거용


#define true 1	//참 거짓 값 매크로
#define FALSE 0

void getup()    // 게임 플레이 화면에 점수 표시 및 space 버튼 클릭 설명, 맵 바닥 고정 블록 생성
{
	system("cls");
	gotoxy(10, 2);
	printf("   Press Space to Jump   ");
	gotoxy(62, 2);
	printf("SCORE : ");
	gotoxy(1, 25);
	for (int x = 0; x < 49; x++)
		printf("■");
}

void controlsPresent(void) {  // 게임 조작키 설명
	system("cls");
	int x = 25, y = 9;
	char ch;

	drawSquare(x - 1, y - 1, x + 30, y + 7);
	gotoxy(x + 10, y - 1);
	printf("%c", 22);
	gotoxy(x + 10, y + 7);
	printf("%c", 21);

	gotoxy(x, y);
	printf(" Space    %c Jump           ", 5);
	gotoxy(x, y + 1);
	printf(" ESC      %c Pause          ", 5);
	gotoxy(x, y + 2);
	printf(" x        %c GameExit       ", 5);
	gotoxy(x, y + 3);
	printf(" b        %c MainScreen     ", 5);
	gotoxy(x, y + 4);
	printf(" v        %c Restart        ", 5);
	gotoxy(x, y + 5);
	printf(" s        %c bgm Toggle     ", 5);
	gotoxy(x, y + 6);
	printf("          %c            \n\n", 5);

	Sleep(5000);		//5초 대기
	ch = getch();		//키입력시 함수빠져나감
	_getch();			//버퍼 비우기
	return;

}

void drawSquare(int left, int top, int right, int bottom) {	//4각형 그려주는 함수(좌 상 우 하)
	int i, j;
	for (i = 0; i <= bottom - top; i++) {
		if (i == 0) {
			gotoxy(left, top + i);
			printf("%c", 1);
			for (j = 0; j <= right - left - 2; j++)
				printf("%c", 6);
			printf("%c", 2);
		}
		else if (i == bottom - top) {
			gotoxy(left, top + i);
			printf("%c", 3);
			for (j = 0; j <= right - left - 2; j++)
				printf("%c", 6);
			printf("%c", 4);
		}
		else {
			gotoxy(left, top + i);
			printf("%c", 5);
			gotoxy(right, top + i);
			printf("%c", 5);
		}
	}
	return;
}