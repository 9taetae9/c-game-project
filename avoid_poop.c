#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include <mmsystem.h>//멀티미디어시스템
#pragma comment(lib, "winmm.lib")//프로그램사용 윈도우미디어프로그램//.wav파일만 재생가능 
// 게임 환경 변수
#define MAX_DDONG       100 // 똥의 최대 개수.

#define LEVEL_COUNT     3   // 레벨마다 늘어날 똥개수
#define LEVEL_SPEED     15  // 레벨마다 빨라질 스피드 (1000 = 1초, 15 = 0.015초)

// 똥 구조체.
int score = 0;
char choose;
struct DDONG
{
	int x, y, wait;
};
// 화면의 특정 위치로 이동해 주는 함수.
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// 키입력 함수
BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

// 게임 함수.
int game(int level)
{
	system("Color F0");
	struct DDONG ddong[MAX_DDONG], user;
	int i, key, check = 1, evade = 0, life = 3;// 피한ㅔ 똥 개수 
	int speed = 75 - level * LEVEL_SPEED;//1: 60, 2: 45, 3:30, 4:15, 5:0 Sleep(speed) 래벨이 증가할수록 대기시간 감소    
	int count = 5 + level * LEVEL_COUNT;
	// 레벨업에 필요한 똥개수
	int levelup = 20 + level * 20;
	// 똥개수 체크. (최대값을 넘지 않도록 조정)
	if (count >= MAX_DDONG) count = MAX_DDONG - 1;
	// 스피드 체크. (최소값이 10 보다 작지 않도록 저정)
	if (speed < 10) speed = 10; //5단계 이후 속도 sleep(10)로 동일하게 지정 
	// 유저 시작 위치(12,19)
	user.x = 12;
	user.y = 19;
	// 똥 초기화.********************************************************
	srand(time(NULL));// 똥떨어지는 위치를 무작위하게 지정 
	for (i = 0; i < count; i++)
	{
		ddong[i].x = rand() % 24 + 1; // 똥 떨어지는 x 좌표(1~24 중 랜덤) 

		ddong[i].y = 3;//똥 시작 높이 

		ddong[i].wait = rand() % 10;//(똥 떨어지는 타이밍 (0~19 중 랜덤) 
	}

	// 게임 루프
	while (check)
	{
		score++;
		// 스피드에 따른 시연 지연.
		Sleep(speed); //()안 단위 1밀리세컨드  
		system("cls"); // 화면 지우기.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
		printf("[똥피하기게임]\tLEVEL %d\n점수 : %d 목숨: %d", level, score, life);
		gotoxy(0, user.y + 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
		printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		if (IsKeyDown(VK_LEFT) && user.x > 1) { user.x--; }
		//if(IsKeyDown(VK_DOWN))//???
		//	user.x--;
		if (IsKeyDown(VK_RIGHT) && user.x <= 23) { user.x++; }
		//if(IsKeyDown(VK_DOWN) && user.x <= 22)///???
		//	user.x++;

// 사람 출력
		gotoxy(user.x, user.y); //(12,19)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf1);
		printf("ㅇ");
		gotoxy(user.x, user.y + 1);
		printf("ㅅ");
		gotoxy(user.x, user.y + 2);
		printf("ㅅ");
		// 똥 움직임 처리
		for (i = 0; i < count; i++)
		{
			if (ddong[i].wait > 0) {
				// 대기시간 동안 아직 똥을 떨어뜨리지 않는다.
				ddong[i].wait--;
			}
			else {
				// 똥을 한칸 아래로 이동한다.

				ddong[i].y++;
				// 똥이 최하단에 도착 했을 때 처리.
				if (ddong[i].y >= 22)//똥 바닥 도착 이후  
				{

					ddong[i].x = rand() % 24 + 1;//1~24
					ddong[i].y = 3;
					evade++;    // 피한 똥개수 카운트
				}
				// 똥 출력
				gotoxy(ddong[i].x, ddong[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfa);
				printf("♬");
				// 충돌 체크
				if (abs(ddong[i].x - user.x) < 2 && ddong[i].y == user.y)
				{
					// 비프음 출력.
					printf("\a");
					life--;
					if (life == 0) {
						check = 0;// 죽으면 check에 0 대입하여 while 루프 탈출
					}

				}
			}
		}
		// 피한 똥개수가 20개면 레벨업.
		if (evade > levelup)
			return 1;
	}
	return 2;
}
// 메인 함수
int main()
{
	system("mode con: cols=26 lines=25");
	int level = 1;
	
	system("Color F0");
	gotoxy(6, 1);
	printf("[똥피하기게임]");
	gotoxy(6, 11);
	printf("1: 게임시작");
	gotoxy(6, 12);
	printf("2:  가이드");
	gotoxy(6, 13);
	printf("3:  끝내기");
	gotoxy(0, 24);
	printf(" ");

	choose = _getch();

	if (choose == '1')
	{
		
		choose == '0';
		while (1)
		{	
			
			system("cls");// clean screen
			system("Color F0");//레벨N 시작 전 배경 색 
			// 레벨 표시.
			gotoxy(6, 1); printf("[똥피하기게임]");
			gotoxy(9, 11); printf("LEVEL %d", level);
			// 시간 지연 (1초 = 1000)
			Sleep(1500);
			
			// 게임 끝
			if (game(level) == 2)
			{
				
				system("cls");
				gotoxy(7, 5);
				system("Color CF");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xCF);
				printf("※게임 오버※\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xCF);
				gotoxy(8, 12);
				printf("레벨 : %d", level);
				gotoxy(8, 13);
				printf("점수 : %d", score);
				score = 0;
				gotoxy(8, 22);
				printf("1: 메인메뉴");
				gotoxy(8, 23);
				printf("2: 끝내기");
				gotoxy(0, 24);
				printf(" ");

				do
				{
					choose = _getch();
					if (choose == '1')
						main();
					if (choose == '2')
						break;
				} while (1);
				break;
			}
			else
				level++;
		}
	}
	else if (choose == '2')
	{
		choose = '0';
		system("cls");
		system("Color 0A");
		gotoxy(6, 1);
		printf("[똥피하기게임]");
		gotoxy(10, 8);
		printf("조작법");
		gotoxy(3, 10);
		printf("이동   : 좌,우 화살표");
		gotoxy(3, 11);
		printf("부스터 : 아래 화살표");
		gotoxy(8, 23);
		printf("1: 돌아가기");
		gotoxy(0, 24);
		printf(" ");

		while (choose != '1')
		{
			choose = _getch();
		}
		main();
	}
	else
		return 0;
}
