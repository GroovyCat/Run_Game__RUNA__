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
#define SIZE 50
#define LEFT 75	 /*키보드 입력 값들(아스키)*/
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

int t, speed = 30;
extern char UserNick[20], password[20]; //로그인에 필요한 변수 2

extern int score, NewScore;				//score 기존값 ,new가 게임 플레이하며 얻어지는 값
extern char Ready[10];					//result변수 초기화 용도
extern int Return_test;

void obj()
{
	//printf("%d", NewScore);
	static int x = 0;
	static int scr = 0;		//요값을 전역변수로 사용하고 싶음
	char ch;
	if (x == 80 && t < 4 )
	{
		while (1) {
			x = 0;
			system("cls");
			gotoxy(35, 11);
			printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			gotoxy(35, 12);
			printf("▤                              ▤");
			gotoxy(35, 13);
			printf("▤  +-----------------------+   ▤");
			gotoxy(35, 14);
			printf("▤  |   최종점수 :    %d점  |    ▤", NewScore);
			gotoxy(35, 15);
			printf("▤  +-----------------------+   ▤");
			gotoxy(35, 16);
			printf("▤         아쉽네요 T_T         ▤");
			gotoxy(35, 17);
			printf("▤                              ▤");
			gotoxy(35, 18);
			printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			gotoxy(30, 21);
			printf(" v : Restart   b : Mainscreen   x : Exit");
			printf("\n\n");
			record_txt();			//결과 기록
			ch = _getch();

			if (ch == 'b') {
				NewScore = 0;
				speed = 30;
				GamePlay(0);	//게임 화면 함수
				break;
			}
			else if (ch == 'v') {
				NewScore = 0;
				speed = 30;
				GamePlay(1);	//게임 플레이
				break;

			}
			else if (ch == 'x')
				exit(-1);
		}
	}
	gotoxy(90 - x, 22);
	printf("□□");
	gotoxy(90 - x, 23);
	printf("□□");
	gotoxy(90 - x, 24);
	printf("□□");                 // 장애물
	x++;
	if (x == 89)                    // 장애물을 넘어올 시 점수 증가 및 속도 증가
	{
		x = 0;
		++NewScore;
		gotoxy(70, 2);
		printf("     ");
		gotoxy(70, 2);
		printf("%d", NewScore);
		if (speed > 10 || NewScore > 5)
			speed -= 5;

	}
}
