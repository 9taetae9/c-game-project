#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h> 
//���� ȯ�� ����
#define MAX_DDONG		100 // ���� �ִ� ����

#define LEVEL_COUNT		3 // �������� �þ �� ���� 
#define LEVEL_SPEED		15// �������� ������ ���ǵ� (1000�и������� =1��, 15�и�������=0.015��)
//�� ����ü
int score=0;
char choose;
struct DDONG{
	int x,y, wait;
}; 
//ȭ���� Ư�� ��ġ�� �̵����ִ� �Լ�
void gotoxy(int x, int y){
	COORD Pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
} 
//Ű�Է� �Լ� (????)
BOOL IsKeyDown(int Key){
	return ((GetAsyncKeyState(Key)&0x8000) != 0);//Ű������ Ű�� ���ȴ����� üũ�ϴ� �Լ�
	/*ȣ��� �������� Ű ���¸� �����Ͽ�, �޽��� ť�� ��ġ�� �ʰ�
�ٷ� ������ �� �ֹǷ� Ű �Է��� �ٷ� ó���� �� ���� �ִ�.

GetKeyState() �Լ��� ȣ��� �������� �޽��� ť�� ��ġ��,
�޽��� �߻� ���� ���¸� �����ϰ� �ǹǷ�, Ű���� �޽��� ó�� ��ƾ������ ����ؾ� �Ѵ�.

���Ӱ� ���� Ű �Է¿� �ٷ� ������ �� ��� �ϴ� ���α׷�������
GetAsyncKeyState()�Լ��� ����ϴ� ���� ����.*/

} 
//���� �Լ�
int game(int level){
	system("Color F0");
	struct DDONG ddong[MAX_DDONG], user;
	int i, key, check =1, evade = 0;
	int speed =75-level * LEVEL_SPEED;
	int count = 5 + level * LEVEL_COUNT;// �˰���? 
	//�������� �ʿ��� �˰���
	int levelup=20 + level*20;
	//�˰��� üũ (�ִ밪�� ���� �ʵ��� ����)
	if(count>= MAX_DDONG) count =MAX_DDONG-1;
	//���ǵ� üũ (�ּҰ��� 10 ���� ���� �ʵ��� ����)
	if(speed<10) speed = 10;
	//���� ���� ��ġ
	user.x = 12;
	user.y = 19;
	//���ʱ�ȭ
		for(i=0; i<count; i++){
		srand(time(NULL));
		ddong[i].x = rand() % 24 + 1;// 1~24 ��ȯ 
		ddong[i].y = 3;
		ddong[i].wait = rand() % 20; //0~19 ��ȯ 
	} 
	//���� ����
	while(check){
	score++;
	//���ǵ忡 ���� �ÿ� ����
	sleep(speed);// ?? sleep(x) x�� ���� ��?
	system("cls");// ȭ�� ����� 
	//���� ȯ�� ���	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf0);
	// SetConsoleTextAttribute(GetStdHandle//ǥ���ڵ��� ��ȯ�ϴ� �Լ�(STD_OUTPUT_HANDLE//�̹� #define �� ������ ID),����);
	/* ���� : �Ű����� Ÿ�� WORD 
	typedef unsigned short WORD=> �� �������� �������
	short��=>2byte,16bit 16��Ʈ(0000 0000 1111 1111=0x00FF)�� ���� 8��Ʈ�� �ָ��ؾߵǴµ� 
	16��Ʈ�� �ǵ��� 4��Ʈ�� ������ ����, �׾��� 4���� ��Ʈ�� ������ ������
	�� �� 16������ ������ ���� ���ڷ� ���� ����, 
	*/ 
	printf("[�����ϱ����]\tLEVEL %d\n���� : %d", level,score); 
	gotoxy(0, user.y+3); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
	printf("��������������������������");
	printf("��������������������������");
    // ��� ������ ó��
/*VK�� Virtual Key�� �����̰� //VK_UP (���� ����Ű),VK_LEFT (���� ����Ű),VK_DOWN (�Ʒ��� ����Ű),VK_RIGHT (������ ����Ű)
VK_SPACE (�����̽� ��)*/
	if (IsKeyDown(VK_LEFT)){
		if(user.x > 1){
			user.x--;
			if(IsKeyDown(VK_DOWN))
				user.x--;
		}
	} 
	
	
	
	
	
	
	
	
	
	
	
	
	
	 
} 
