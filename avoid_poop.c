#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h> 
#include <mmsystem.h>//��Ƽ�̵��ý���
#pragma comment(lib, "winmm.lib")//���α׷���� ������̵�����α׷�//.wav���ϸ� ������� 
// ���� ȯ�� ����
#define MAX_DDONG       100 // ���� �ִ� ����.

#define LEVEL_COUNT     3   // �������� �þ �˰���
#define LEVEL_SPEED     15  // �������� ������ ���ǵ� (1000 = 1��, 15 = 0.015��)

// �� ����ü.
int score = 0;
char choose;
struct DDONG
{
	int x, y, wait;
};
// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// Ű�Է� �Լ�
BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

// ���� �Լ�.
int game(int level)
{
	system("Color F0");
	struct DDONG ddong[MAX_DDONG], user;
	int i, key, check = 1, evade = 0, life = 3;// ���Ѥ� �� ���� 
	int speed = 75 - level * LEVEL_SPEED;//1: 60, 2: 45, 3:30, 4:15, 5:0 Sleep(speed) ������ �����Ҽ��� ���ð� ����    
	int count = 5 + level * LEVEL_COUNT;
	// �������� �ʿ��� �˰���
	int levelup = 20 + level * 20;
	// �˰��� üũ. (�ִ밪�� ���� �ʵ��� ����)
	if (count >= MAX_DDONG) count = MAX_DDONG - 1;
	// ���ǵ� üũ. (�ּҰ��� 10 ���� ���� �ʵ��� ����)
	if (speed < 10) speed = 10; //5�ܰ� ���� �ӵ� sleep(10)�� �����ϰ� ���� 
	// ���� ���� ��ġ(12,19)
	user.x = 12;
	user.y = 19;
	// �� �ʱ�ȭ.********************************************************
	srand(time(NULL));// �˶������� ��ġ�� �������ϰ� ���� 
	for (i = 0; i < count; i++)
	{
		ddong[i].x = rand() % 24 + 1; // �� �������� x ��ǥ(1~24 �� ����) 

		ddong[i].y = 3;//�� ���� ���� 

		ddong[i].wait = rand() % 10;//(�� �������� Ÿ�̹� (0~19 �� ����) 
	}

	// ���� ����
	while (check)
	{
		score++;
		// ���ǵ忡 ���� �ÿ� ����.
		Sleep(speed); //()�� ���� 1�и�������  
		system("cls"); // ȭ�� �����.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf0);
		printf("[�����ϱ����]\tLEVEL %d\n���� : %d ���: %d", level, score, life);
		gotoxy(0, user.y + 3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0e);
		printf("�ѤѤѤѤѤѤѤѤѤѤѤѤ�");
		printf("�ѤѤѤѤѤѤѤѤѤѤѤѤ�");
		if (IsKeyDown(VK_LEFT) && user.x > 1) { user.x--; }
		//if(IsKeyDown(VK_DOWN))//???
		//	user.x--;
		if (IsKeyDown(VK_RIGHT) && user.x <= 23) { user.x++; }
		//if(IsKeyDown(VK_DOWN) && user.x <= 22)///???
		//	user.x++;

// ��� ���
		gotoxy(user.x, user.y); //(12,19)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xf1);
		printf("��");
		gotoxy(user.x, user.y + 1);
		printf("��");
		gotoxy(user.x, user.y + 2);
		printf("��");
		// �� ������ ó��
		for (i = 0; i < count; i++)
		{
			if (ddong[i].wait > 0) {
				// ���ð� ���� ���� ���� ����߸��� �ʴ´�.
				ddong[i].wait--;
			}
			else {
				// ���� ��ĭ �Ʒ��� �̵��Ѵ�.

				ddong[i].y++;
				// ���� ���ϴܿ� ���� ���� �� ó��.
				if (ddong[i].y >= 22)//�� �ٴ� ���� ����  
				{

					ddong[i].x = rand() % 24 + 1;//1~24
					ddong[i].y = 3;
					evade++;    // ���� �˰��� ī��Ʈ
				}
				// �� ���
				gotoxy(ddong[i].x, ddong[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xfa);
				printf("��");
				// �浹 üũ
				if (abs(ddong[i].x - user.x) < 2 && ddong[i].y == user.y)
				{
					// ������ ���.
					printf("\a");
					life--;
					if (life == 0) {
						check = 0;// ������ check�� 0 �����Ͽ� while ���� Ż��
					}

				}
			}
		}
		// ���� �˰����� 20���� ������.
		if (evade > levelup)
			return 1;
	}
	return 2;
}
// ���� �Լ�
int main()
{
	system("mode con: cols=26 lines=25");
	int level = 1;
	
	system("Color F0");
	gotoxy(6, 1);
	printf("[�����ϱ����]");
	gotoxy(6, 11);
	printf("1: ���ӽ���");
	gotoxy(6, 12);
	printf("2:  ���̵�");
	gotoxy(6, 13);
	printf("3:  ������");
	gotoxy(0, 24);
	printf(" ");

	choose = _getch();

	if (choose == '1')
	{
		
		choose == '0';
		while (1)
		{	
			
			system("cls");// clean screen
			system("Color F0");//����N ���� �� ��� �� 
			// ���� ǥ��.
			gotoxy(6, 1); printf("[�����ϱ����]");
			gotoxy(9, 11); printf("LEVEL %d", level);
			// �ð� ���� (1�� = 1000)
			Sleep(1500);
			
			// ���� ��
			if (game(level) == 2)
			{
				
				system("cls");
				gotoxy(7, 5);
				system("Color CF");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xCF);
				printf("�ذ��� ������\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xCF);
				gotoxy(8, 12);
				printf("���� : %d", level);
				gotoxy(8, 13);
				printf("���� : %d", score);
				score = 0;
				gotoxy(8, 22);
				printf("1: ���θ޴�");
				gotoxy(8, 23);
				printf("2: ������");
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
		printf("[�����ϱ����]");
		gotoxy(10, 8);
		printf("���۹�");
		gotoxy(3, 10);
		printf("�̵�   : ��,�� ȭ��ǥ");
		gotoxy(3, 11);
		printf("�ν��� : �Ʒ� ȭ��ǥ");
		gotoxy(8, 23);
		printf("1: ���ư���");
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
