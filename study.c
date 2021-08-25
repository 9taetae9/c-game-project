#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h> 
//게임 환경 변수
#define MAX_DDONG		100 // 똥의 최대 개수

#define LEVEL_COUNT		3 // 레벨마다 늘어날 똥 개수 
#define LEVEL_SPEED		15// 레벨마다 빨라질 스피드 (1000밀리세컨드 =1초, 15밀리세컨드=0.015초)
//똥 구조체
int score=0;
char choose;
struct DDONG{
	int x,y, wait;
}; 
//화면의 특정 위치로 이동해주는 함수
void gotoxy(int x, int y){
	COORD Pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
} 
//키입력 함수 (????)
BOOL IsKeyDown(int Key){
	return ((GetAsyncKeyState(Key)&0x8000) != 0);//키보드의 키가 눌렸는지를 체크하는 함수
	/*호출된 시점에서 키 상태를 조사하여, 메시지 큐를 거치지 않고
바로 리턴을 해 주므로 키 입력을 바로 처리해 줄 수가 있다.

GetKeyState() 함수는 호출된 시점에서 메시지 큐를 거치며,
메시지 발생 후의 상태를 리턴하게 되므로, 키보드 메시지 처리 루틴내에서 사용해야 한다.

게임과 같이 키 입력에 바로 반응을 해 줘야 하는 프로그램에서는
GetAsyncKeyState()함수를 사용하는 편이 좋다.*/

} 
//게임 함수
int game(int level){
	system("Color F0");
	struct DDONG ddong[MAX_DDONG], user;
	int i, key, check =1, evade = 0;
	int speed =75-level * LEVEL_SPEED;
	int count = 5 + level * LEVEL_COUNT;// 똥개수? 
	//레벨업에 필요한 똥개수
	int levelup=20 + level*20;
	//똥개수 체크 (최대값을 넘지 않도록 조정)
	if(count>= MAX_DDONG) count =MAX_DDONG-1;
	//스피드 체크 (최소값이 10 보다 작지 않도록 조정)
	if(speed<10) speed = 10;
	//유저 시작 위치
	user.x = 12;
	user.y = 19;
	//똥초기화
		for(i=0; i<count; i++){
		srand(time(NULL));
		ddong[i].x = rand() % 24 + 1;// 1~24 반환 
		ddong[i].y = 3;
		ddong[i].wait = rand() % 20; //0~19 반환 
	} 
	//게임 루프
	while(check){
	score++;
	//스피드에 따른 시연 지연
	sleep(speed);// ?? sleep(x) x에 들어가는 것?
	system("cls");// 화면 지우기 
	//게임 환경 출력	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf0);
	// SetConsoleTextAttribute(GetStdHandle//표준핸들을 반환하는 함수(STD_OUTPUT_HANDLE//이미 #define 된 일종의 ID),색상);
	/* 색상 : 매개변수 타입 WORD 
	typedef unsigned short WORD=> 즉 정수값을 넣으면됨
	short형=>2byte,16bit 16비트(0000 0000 1111 1111=0x00FF)중 뒤의 8비트에 주목해야되는데 
	16비트중 맨뒤의 4비트는 글자의 색상, 그앞의 4개의 비트는 배경색을 지정함
	즉 총 16가지의 색상의 배경과 글자로 지정 가능, 
	*/ 
	printf("[똥피하기게임]\tLEVEL %d\n점수 : %d", level,score); 
	gotoxy(0, user.y+3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");
    // 사람 움직임 처리
/*VK는 Virtual Key의 약자이고 //VK_UP (위쪽 방향키),VK_LEFT (왼쪽 방향키),VK_DOWN (아래쪽 방향키),VK_RIGHT (오른쪽 방향키)
VK_SPACE (스페이스 바)*/
	if (IsKeyDown(VK_LEFT)){
		if(user.x > 1){
			user.x--;
			if(IsKeyDown(VK_DOWN))
				user.x--;
		}
	} 
	
	
	
	
	
	
	
	
	
	
	
	
	
	 
} 
