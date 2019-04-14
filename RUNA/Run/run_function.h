#pragma once
//xyCursor.c
void cursor(int n);                                         // 커서 지우기
void gotoxy(int x, int y);                                  // x좌표, y좌표 지정 및 계산

//title.c
void getup();                                               //화면 왼쪽 상단, 화면 점수 표시, 게임 맵 고정바닥 블록 생성 
void controlsPresent(void);                                 //컨트롤조작키 설명
void drawSquare(int left, int top, int right, int bottom);  //사각형그리기 좌/상/우/하

//object.c
void obj();                                                 //장애물

//player.c
void player(int jump);                                      //캐릭터
void delay(unsigned int mseconds);                          //시간
int GamePlay(int Title_or_Game);		                    //게임 플레이 OR 게임 시작화면				

//login.c
int loginDesign();                                          //로그인 화면 디자인
int titleDesign();					                        //게임시작화면 디자인
int login();	                                            //로그인 동작
int login_Success();                                        //로그인 성공 유무 확인
void serch();	                                            //기록을 검사  1.전체 2.유저 닉네임
void record_txt();											//결과 값을 텍스트에 기록[밑의 함수 3가지 사용]
void Create_link_list();									//txt파일읽어서 연결리스트에 값 넣기
void link_start(char *NickName, char *pw, int score);		//텍스트 읽어들여 연결리스트에 저장
void link_Sort(char *Ne_NickName, char *pw, int New_score);	//연결리스트 정렬
int DeleteDuplicates(char *Nick);										//연결리스트 닉네임 중복삭제
int print();												//연결리스트 정렬 확인 
int link_txt(void);											//정렬된 연결리스트 값을 txt에 삽입