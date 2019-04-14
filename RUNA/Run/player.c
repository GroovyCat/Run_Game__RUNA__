#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>	
#include "run_function.h"
#pragma warning (disable:4996) //오류 제거용


#define true 1	//참 거짓 값 매크로
#define FALSE 0
#define SIZE 50
#define LEFT 75	 //키보드 입력 값들(아스키)
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
int t, speed1 = 30;
void player(int jump)  //캐릭터 생성 및 점프 구현
{
	static int a = 1;

	if (jump == 0)
		t = 0;
	else if (jump == 2)
		t--;
	else t++;
	gotoxy(2, 15 - t);
	printf("                 ");
	gotoxy(2, 16 - t);
	printf("                 ");
	gotoxy(2, 17 - t);
	printf("                 ");
	gotoxy(2, 18 - t);
	printf("                 ");
	gotoxy(2, 19 - t);
	printf("                 ");
	gotoxy(2, 20 - t);
	printf("                 ");
	gotoxy(2, 21 - t);
	printf("      @          ");
	gotoxy(2, 22 - t);
	printf("     @@@         ");
	gotoxy(2, 23 - t);
	if (jump == 1 || jump == 2) {
		printf("    @    @");
		gotoxy(2, 24 - t);
		printf("     @    @");
	}
	else if (a == 1)
	{
		printf("   @    @");
		gotoxy(2, 24 - t);
		printf("               ");
		a = 2;
	}
	else if (a == 2)
	{
		printf("              ");
		gotoxy(2, 24 - t);
		printf("              ");
		a = 1;
	}
	gotoxy(2, 24 - t);
	if (jump != 0) {
		printf("            ");
	}
	else
	{

		//printf("          ");
	}
	delay(speed1);
}
void delay(unsigned int mseconds)   // 시간
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

int GamePlay(int Title_or_Game) {

	char ch;
	int i;
	int Mod = 0;
	int CountSound = 0;
	if (Title_or_Game == 0) Mod = titleDesign();	//매개변수 스타트 지점 title	

	if (Title_or_Game > Mod) Mod = Title_or_Game;	//매개변수 스타트 지점 GamePlay

	switch (Mod)
	{
	case 1:
		getup();
		sndPlaySoundA("A.wav", SND_ASYNC | SND_LOOP); //음악 재생
		while (1)
		{
			while (!_kbhit())
			{
				player(0);
				obj();
			}
			ch = _getch();
			if (ch == ' ')
			{
				Beep(300.8128, 40); //점프 음
				for (i = 0; i < 10; i++)
				{
					player(1);
					obj();
				}
				for (i = 0; i < 10; i++)
				{
					player(2);
					obj();
				}
			}
			if (ch == 's' || ch == 'S') {	//사운드 토글 if문
				CountSound++;
				if (CountSound % 2 == 1)PlaySound(NULL, NULL, NULL);
				else sndPlaySoundA("A.wav", SND_ASYNC | SND_LOOP);
			}
			else if (ch == 27)
				while (1) {
					gotoxy(30, 10);
					printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
					gotoxy(30, 11);
					printf("▤                              ▤");
					gotoxy(30, 12);
					printf("▤  +-----------------------+   ▤");
					gotoxy(30, 13);
					printf("▤  |      일 시 정 지      |   ▤");
					gotoxy(30, 14);
					printf("▤  +-----------------------+   ▤");
					gotoxy(30, 15);
					printf("▤  Press any key to resume..   ▤");
					gotoxy(30, 16);
					printf("▤                              ▤");
					gotoxy(30, 17);
					printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
					cursor(0);
					system("pause>null");
					if (_kbhit()) // 다시 한번 누르면 게임 진행
					{
						system("cls");
						getup();
						break;
					}
				}
			else // 원하지 않는 키 입력 되면 패스
			{
				continue;
			}
			while (_kbhit()) _getch(); //버퍼제거
		}
	default:
		printf("\n\t 잘못입력하였습니다 다시 입력해주세요 : "); Sleep(1400);
	}
}
