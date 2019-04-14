#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>	//키보드 입력 함수 사용을 위해
#include <MMSystem.h>
#include "run_function.h"
#pragma comment(lib,"Winmm.lib")
#pragma warning (disable:4996) //오류 제거용

int main()
{
	system("mode con: lines=29 cols=100");
	cursor(0);		//커서 숨기기 함수
	loginDesign();	//로그인 화면
	GamePlay(0);	//게임 시작 화면

}