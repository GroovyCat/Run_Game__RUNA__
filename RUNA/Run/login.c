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

typedef struct link {			//연결리스트의 값들 유저닉네임, 비밀번호, 점수 저장 연결리스트
	char UserNick_t[20];
	char password_t[20];
	int score_t;
	struct link *next;

} link;
link *head = NULL;

char UserNick[20], password[20]; //로그인에 필요한 변수 2
int score = 0, NewScore = 1;		//score 기존값 ,new가 게임 플레이하며 얻어지는 값
char Ready[10] = "Ready";		//result변수 초기화 용도
int Return_test;


int loginDesign(void) {

	int x = 10; //타이틀화면이 표시되는 x좌표 
	int y = 5; //타이틀화면이 표시되는 y좌표 
	char Choose;
	
	while (true) {
		 
		system("cls");
		gotoxy(x, y + 0); printf("  ■■■■■■  ■        ■  ■■          ■    ■■■   \n"); Sleep(100);
		gotoxy(x, y + 1); printf("  ■■      ■  ■        ■  ■  ■        ■  ■      ■ \n"); Sleep(100);
		gotoxy(x, y + 2); printf("  ■■    ■■  ■        ■  ■    ■      ■  ■      ■ \n"); Sleep(100);
		gotoxy(x, y + 3); printf("  ■■  ■■    ■        ■  ■      ■    ■  ■■■■■ \n"); Sleep(100);
		gotoxy(x, y + 4); printf("  ■■■        ■        ■  ■        ■  ■  ■      ■ \n"); Sleep(100);
		gotoxy(x, y + 5); printf("  ■■  ■■    ■        ■  ■          ■■  ■      ■ \n"); Sleep(100);
		gotoxy(x, y + 6); printf("  ■■    ■■    ■■■■    ■            ■  ■      ■ \n"); Sleep(100);
		gotoxy(x + 15, y + 10); printf("Connection complete Welcome...");//접속완료 환영합니다.
		gotoxy(x + 15, y + 20); printf("[1]로그인, [2]종료\n\t");
		
		Choose = _getch(); 
		if (Choose == '1') { _getch();  if (login() == 0) { continue; }	return 1; } //로그인 +버퍼(앤터) 비우기
		else if (Choose == '2') { _getch(); exit(-1); }//종료 +버퍼비우기
		else _getch();
		
	}
}

int titleDesign(void) {

	int x = 10; //타이틀화면이 표시되는 x좌표 
	int y = 5; //타이틀화면이 표시되는 y좌표 
	int Choose;//무한루프 탈출 조건문

	while (true)
	{
		system("cls");
		gotoxy(x, y + 0); printf("□■■■■■■□■□□□□■□■■□□□□□■□□■■■□□ \n"); Sleep(100);
		gotoxy(x, y + 1); printf("□■■□□□■□■□□□□■□■□■□□□□■□■□□□■□\n"); Sleep(100);
		gotoxy(x, y + 2); printf("□■■□□■■□■□□□□■□■□□■□□□■□■□□□■□\n"); Sleep(100);
		gotoxy(x, y + 3); printf("□■■□■■□□■□□□□■□■□□□■□□■□■■■■■□ \n"); Sleep(100);
		gotoxy(x, y + 4); printf("□■■■□□□□■□□□□■□■□□□□■□■□■□□□■□ \n"); Sleep(100);
		gotoxy(x, y + 5); printf("□■■□■■□□■□□□□■□■□□□□□■■□■□□□■□ \n"); Sleep(100);
		gotoxy(x, y + 6); printf("□■■□□■■□□■■■■□□■□□□□□□■□■□□□■□ \n"); Sleep(100);
		gotoxy(x + 10, y + 8); printf("Please Enter want Key to Start..");
		gotoxy(x + 20, y + 13); printf("                                                        "); //welcom글씨 지우기위해

		gotoxy(x + 10, y + 10); printf("□1.   Play    □    ");
		gotoxy(x + 10, y + 13); printf("□2. Controls  □    ");
		gotoxy(x + 10, y + 16); printf("□3.  Score    □    ");
		gotoxy(x + 10, y + 19); printf("■4.   EXIT    ■\n\n");
		Sleep(10); // 00.1초 딜레이  
		Choose = _getch();
		if (Choose == '1') { _getch(); return 1; }//키입력이 있으면 무한루프 종료
		else if (Choose == '2') { _getch();  controlsPresent(); } //조작키 함수
		else if (Choose == '3')
		{
			_getch();
			if (head != NULL) print();		//연결리스트 생성 후
			else serch();					//연결리스트 생성 전 ->파일 읽어들여 프린트
		}
		else if (Choose == '4') { exit(-1); }
	}
}

int login() {		//로그인 함수
	   //기존유저 기존=score점수 신규=1 중복=0 중복일경우 반복
	gotoxy(12, 25);
	printf("닉네임과 비밀번호를 입력하세요. [특수문자 = X 공백 = X]");
	drawSquare(30, 18, 51, 20);
	gotoxy(31, 19);
	scanf("%s", UserNick);
	drawSquare(30, 21, 51, 23);
	gotoxy(31, 22);
	scanf("%s", password);
	Return_test = login_Success();

	return Return_test;
}
int login_Success()		//로그인 [기존유저] ,[신규유저], [중복닉네임] 확인함수 
{
	char *result = Ready;				//record 텍스트를 분리한 값을 저장
	char line[SIZE]="reset";
	FILE *fp = NULL;

	if ((fp = fopen("record.txt", "r+")) == NULL)
	{
		printf("파일오픈오류\n");
		exit(1);
	}

	while (!feof(fp))
	{
		fgets(line, SIZE, fp);				//한줄씩 읽어드림
		//텍스트에 아무것도 없을 상태 [신규일 경우 if문]
		if (strcmp(line, "reset") == 0) { fprintf(fp, "NickName: %s\t PW: %s\t SCORE: %d", UserNick, password, 0); break; }
		result = strtok(line, ": \t");		//텍스트를 분리하는데 이용하는 함수
		while (result != NULL) {			//텍스트를 일정 기준마다 분리하여 원하는값 을 얻는 반복문

			if (strcmp(result, "NickName") == 0) {			//한 줄 읽어들여 중복 검사 if문
				result = strtok(NULL, ": \t");

				if (strcmp(result, UserNick) == 0) {	//닉네임 중복의 확인	
					result = strtok(NULL, ": \t");
				}

				else break; 		//중복 아닐경우 빠져나옴 다음 줄 읽어드리기 위해



				if (strcmp(result, "PW") == 0) {		//닉네임 중복일 경우 확인후 pw:를 기준으로 텍스트 나누기
					result = strtok(NULL, ": \t");

					if (strcmp(result, password) == 0) {	//PW중복확인 => 기존유저 조건
						result = strtok(NULL, ": \t");

						if (strcmp(result, "SCORE") == 0) {
							result = strtok(NULL, ": \t");
							fclose(fp);								//파일 닫기
							return atoi(result);					//기존유저의 점수를 반환
						}
					}

					else {
						gotoxy(12, 25);  
						printf("                **  중복된 닉네임 입니다.  **                                     \n");
						Sleep(2000);
						return 0;
					}
				}
			}
		}
	}

	fclose(fp);	//파일 닫기
	return 1;   //신규유저 중복 없음
}

void serch()		//텍스트 파일내  [전체 Rank score or 자신의 Rank score]
{	//닉네임을 통한 결과값 검색 
	FILE *fp = NULL;
	char line[SIZE] = "a";
	char *result = Ready;				//record1 텍스트를 분리한 값을 저장
	int Rank = 0;				//rank변수
	char i[10];

	if ((fp = fopen("record.txt", "r")) == NULL)
	{
		printf("파일오픈오류\n");
		exit(1);
	}

	while (1)
	{
		system("cls");		//포함 고민
		printf("[1. 전체 Rank 출력] [2. 자신의 Rank만 출력] : ");
		scanf("%s", i);							//요 부분을 getchar함수로??

		if (strcmp(i, "1")==0)
		{
			while (!feof(fp))
			{
				fgets(line, SIZE, fp);				//한줄씩 읽어드림
				Rank++;								//순위를 위해 만든 변수 한줄 넘어갈때마다 1+

				result = strtok(line, ": \t");		//텍스트를 분리하는데 이용하는 함수
				while (result != NULL) {			//텍스트를 일정 기준마다 분리하여 원하는값 을 얻는 반복문

					if (strcmp(result, "NickName") == 0)
					{			//한 줄 읽어들여 중복 검사 if문
						result = strtok(NULL, ": \t");
						printf("Rank: %d,\t NickName: %s,\t ", Rank, result);

						while (strcmp(result, "SCORE") != 0) result = strtok(NULL, ": \t");//SCORE찾을때 까지 텍스트 분리
						result = strtok(NULL, ": \t");
						printf("Score: %s \n", result);		//Score값 출력
						result = strtok(NULL, ": \t");
					}
				}
			}
			Sleep(2000);
			fclose(fp);
			
			return GamePlay(0);		//게임 화면 함수

		}


		else if (strcmp(i, "2")==0)
		{
			while (!feof(fp))
			{
				fgets(line, SIZE, fp);				//한줄씩 읽어드림
				Rank++;								//순위를 위해 만든 변수 한줄 넘어갈때마다 1+

				result = strtok(line, ": \t");		//텍스트를 분리하는데 이용하는 함수
				while (result != NULL) {			//텍스트를 일정 기준마다 분리하여 원하는값 을 얻는 반복문

					if (strcmp(result, "NickName") == 0)	//한 줄 읽어들여 중복 검사 if문
					{
						result = strtok(NULL, ": \t");
						if (strcmp(result, UserNick) == 0) {	//닉네임 확인
							printf("Rank: %d,\t NickName: %s,\t ", Rank, result);
							result = strtok(NULL, ": \t");
						}

						else break; 		//중복 아닐경우 빠져나옴 다음 줄 읽어드리기 위해

						while (strcmp(result, "SCORE") != 0) result = strtok(NULL, ": \t");//SCORE찾을때 까지 텍스트 분리
						result = strtok(NULL, ": \t");
						printf("Score: %s \n", result);		//Score값 출력

						Sleep(2000);
						fclose(fp);
						return GamePlay(0);		//게임 화면 함수
					}
				}
			}

			printf("기록이 없습니다. 게임을 플레이하셔야 기록됩니다....\n");
			printf("게임을 플레이 해주세요~..");
			Sleep(2000);
			fclose(fp);
			return GamePlay(0);		//게임 화면 함수
		}
		else printf("잘못입력하였습니다. 다시 입력해주세요: "); Sleep(1000);
	}

}

void record_txt() {	//결과 연결리스트를 통해

	PlaySound(NULL, NULL, NULL);	//음악 종료

	if (NewScore > score) {	//기록 함수 실행 조건 [기존기록 새로 갱신]
		score = NewScore;	//신규기록을 기존 점수변수에 저장

		if (head == NULL) Create_link_list(); //연결리스트 생성이 안돼 있었을 경우 [생성-> 정렬]

		else link_Sort(UserNick, password, score);	//연결리스트 이미 생성되어있을 경우 [정렬]
	
		link_txt();
	}
	
}


void Create_link_list() {		//연결리스트에 값을 생성하기위해 구조화하는 함수

	int count = 0;				//원하는 택스트값을 다읽어왔는지 확인하기 위한 변수 + 몇번읽어들였는지 확인하는 변수
	char *result = Ready;				//record.txt를 읽기위한 변수

	char *NickName = 0, *PW = 0;			//텍스트 값을 저장한 변수 + link_start를 매개변수에 사용
	int old_score;					//텍스트 값을 저장한 변수 + link_start를 매개변수에 사용

	char line[SIZE]="reset";			//텍스트를 한줄씩 읽어드릴때 사용하는 배열

	FILE *rid = fopen("record.txt", "r");

	if ((rid = fopen("record.txt", "r")) == NULL)
	{
		printf("파일오픈오류\n");
		exit(1);
	}
	while (!feof(rid))			//record.txt 읽어드리며 분리 하는 반복문
	{
		fgets(line, SIZE, rid);		//텍스트를 한줄씩 읽어들여 임시로 배열에 저장
		result = strtok(line, ": \t");		//텍스트를 분리하는데 이용하는 함수
		while (result != NULL) {			//텍스트를 일정 기준마다 분리하여 원하는값 을 얻는 반복문


			if (strcmp(result, "NickName") == 0)
			{
				result = strtok(NULL, ": \t");

			/*	//텍스트 내에 값과 현제 로그인중인 값 중복확인후 [연결리스트 생성 제외 시키기 위한 if문]
				if (strcmp(result, UserNick) == 0)
				{
					while (strcmp(result, "SCORE") != 0) result = strtok(NULL, ": \t");		//score전까지 
					for (int i = 0; i < 2; i++)	result = strtok(NULL, ": \t");				//텍스트 나누기 2회= 한줄 다 읽기
					continue; //다음줄 실행하기 위해 -> 반복문 시작위치로
				}
			*/
				NickName = result;
				count++;
			}

			if (strcmp(result, "PW") == 0)
			{
				PW = strtok(NULL, ": \t");
				count++;
			}

			if (strcmp(result, "SCORE") == 0)
			{
				result = strtok(NULL, ": \t");
				old_score = atoi(result);
				count++;
			}

			if (count == 3) {	//NickName, PW, SCORE값 받았을 경우
				//텍스트 [ALL 데이터] -> 연결리스트 생성
				link_start(NickName, PW, old_score);
				count = 0;
			}
			result = strtok(NULL, ": \t");
		}
	}

	link_Sort(UserNick, password, score);	//연결리스트 삽입->정렬

}




void link_start(char *New_NickName, char *pw, int New_score)		//매개 값을 연결리스트에 저장
{
	link *tmp;
	link *temp;
	tmp = (link*)malloc(sizeof(link));

	if (head == NULL) {	//생성이 하나도 안되었을경우
		strcpy(tmp->UserNick_t, New_NickName);
		strcpy(tmp->password_t, pw);
		tmp->score_t = New_score;
		tmp->next = head;
		head = tmp;
		return 1;
	}

	else {	//연결리스트 마지막에 삽입
		temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = tmp;
		strcpy(tmp->UserNick_t, New_NickName);
		strcpy(tmp->password_t, pw);
		tmp->score_t = New_score;
		tmp->next = NULL;
		return 1;
	}

}

void link_Sort(char *Ne_NickName, char *pw, int New_score) {	//현제 닉네임 Score -> 연결리스트에 삽입(정렬 상태)
	link *tmp;
	link *current = 0;
	link *follow = 0;


	DeleteDuplicates(UserNick);	//중복 삭제 함수

	current = follow = head;
	//새로운 노드 생성
	if ((tmp = (link*)malloc(sizeof(link))) == 0) {
		printf("no memory allocated...\n");
		return 0;
	}
	strcpy(tmp->UserNick_t, Ne_NickName);
	strcpy(tmp->password_t, pw);
	tmp->score_t = New_score;

	//삽입 위치로 이동
	while ((current != NULL) && current->score_t > New_score)
	{		
		follow = current;
		current = current->next;	//다음 노드로 이동
	}

	//삽입
	tmp->next = current;
	if (current == head) head = tmp;	//처음

	else follow->next = tmp;			//중간or끝

	return;
}

int DeleteDuplicates(char *Nick)					//중복 삭제 함수
{
	link *delt = head;
	link *temp;
	int i = 1;

	if (strcmp(delt->UserNick_t, Nick)==0) {
		head = delt->next;
		return;
	}
	while (delt->next != NULL) {
		i++;
		temp = delt;
		delt = delt->next;
		if (strcmp(delt->UserNick_t, Nick) == 0)
		{
			temp->next = delt->next;
			system("pause");
			return;
		}
	}
}

int print() {	//연결리스트 잘 생성됬는지 확인 함수.
	link *print;
	print = head;
	int Rank = 0;

	system("cls");

	if (print == NULL) {
		printf("리스트값이 없습니다.");
		return;
	}
	Rank++;
	while (print->next != NULL) {
		printf("Rank: %d,\t	NickName: %s, \t ", Rank, print->UserNick_t);
		//printf("%s ", print->password_t);
		printf("Score: %d \n", print->score_t);
		print = print->next;
		Rank++;
	}

	printf("Rank: %d,\t	NickName: %s, \t ", Rank, print->UserNick_t);
	//printf("%s ", print->password_t);
	printf("Score: %d \n", print->score_t);
	Sleep(3000);

	return GamePlay(0);		//게임 화면 함수

}


int link_txt(void) {	//정렬된 연결리스트를 파일에 출력하는 함수.

	FILE *rd = fopen("record.txt", "wt");
	char UserNick_tt[20];	//텍스트에 파일에 출력하기 위한 임시 배열
	char password_tt[20];	//텍스트에 파일에 출력하기 위한 임시 배열

	int Tscore;				//점수(score) 변수

	link *rp;
	rp = head;

	if (rp == NULL) {		//연결리스트가 없을 때 
		printf("리스트값이 없습니다.");
		return;
	}

	while (rp->next != NULL) {		//처음 부터 연결리스트 마지막 전까지 반복
		strcpy(UserNick_tt, rp->UserNick_t);
		fprintf(rd, "NickName: %s\t ", UserNick_tt);
		strcpy(password_tt, rp->password_t);
		fprintf(rd, "PW: %s\t ", password_tt);
		Tscore = rp->score_t;
		fprintf(rd, "SCORE: %d\n", Tscore);
		rp = rp->next;
	}

	//마지막 연결리스트 파일 입출력
	strcpy(UserNick_tt, rp->UserNick_t);
	fprintf(rd, "NickName: %s\t ", UserNick_tt);
	strcpy(password_tt, rp->password_t);
	fprintf(rd, "PW: %s\t ", password_tt);
	Tscore = rp->score_t;
	fprintf(rd, "SCORE: %d", Tscore);
	rp->next=NULL;
	fclose(rd);	//파일입출력 닫기
	
}