#include <windows.h>//������ �� ������ �Լ����� ���� (COORD, SetConsoleCursorPosition(), GetStdHandle())
#include <stdio.h>//ǥ������� ���̺귯�� 
#include <conio.h>/* �ܼ� ����� �Լ��� �����ϴ� ��� ����
getch()�Լ�  */ 
 
// ���� ȯ�� ����
#define MAX_DDONG       100 // ���� �ִ� ����.

#define LEVEL_COUNT     3   // �������� �þ �˰���
#define LEVEL_SPEED     15  // �������� ������ ���ǵ� (1000 = 1��, 15 = 0.015��)
// �� ����ü.
int score = 0;
char choose;
struct DDONG{
    int x, y, wait;
};
// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
void gotoxy(int x, int y){
    COORD Pos = {x, y};//X,Y ��ǥ�� ȭ�� ���� ���� ���� ���� ��.  
    /*COORD coord;
    coord.X=x;
    coord.Y=y;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
	*/
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)/*�ܼ� ȭ�� ���ۿ� ���� �ڵ� */, Pos/*�� Ŀ�� ��ġ��\
	�����ϴ� COORD ����ü*/);//������ �ܼ� ȭ�� ���ۿ��� Ŀ�� ��ġ�� �����ϴ� �Լ� 
}
// Ű�Է� �Լ�
BOOL IsKeyDown(int Key){
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

// ���� �Լ�.
int game(int level){
	system("Color F0");
    struct DDONG ddong[MAX_DDONG], user;
    int i, key, check = 1, evade = 0;
    int speed = 75 - level * LEVEL_SPEED;
    int count = 5 + level * LEVEL_COUNT;
    // �������� �ʿ��� �˰���
    int levelup = 20 + level * 20;
    // �˰��� üũ. (�ִ밪�� ���� �ʵ��� ����)
    if( count >= MAX_DDONG ) count = MAX_DDONG - 1;
    // ���ǵ� üũ. (�ּҰ��� 10 ���� ���� �ʵ��� ����)
    if( speed < 10 ) speed = 10;
    // ���� ���� ��ġ.
    user.x = 12;
    user.y = 19;
    // �� �ʱ�ȭ.
    for(i=0; i<count; i++)
    {
        ddong[i].x = rand() % 24 + 1;
        ddong[i].y = 3;
        ddong[i].wait = rand() % 20;
    }
    // ���� ����
    while(check)
    {
		score ++;
        // ���ǵ忡 ���� �ÿ� ����.
        Sleep(speed);
        // ȭ�� �����.
        system("cls");
        // ���� ȯ�� ���.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf0);
        printf("[�����ϱ����]\tLEVEL %d\n���� : %d", level,score);
		gotoxy(0,user.y+3);	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
		printf("��������������������������");
		printf("��������������������������");
        // ��� ������ ó��
		if (IsKeyDown(VK_LEFT))
		{
			if(user.x > 1)
			{
				user.x--;
				if(IsKeyDown(VK_DOWN))
					user.x--;
			}
		}
		if (IsKeyDown(VK_RIGHT))
		{
			if(user.x <= 23)
			{
				user.x++;
				if(IsKeyDown(VK_DOWN) && user.x <= 22)
					user.x++;
			}
		}
        // ��� ���
        gotoxy(user.x, user.y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf0);
        printf("��");
		gotoxy(user.x, user.y+1);
		printf("��");
		gotoxy(user.x, user.y+2);
		printf("��");
        // �� ������ ó��
        for(i=0; i<count; i++)
        {
            if( ddong[i].wait > 0 )
            {
                // ���ð� ���� ���� ���� ����߸��� �ʴ´�.
                ddong[i].wait--;
            }
            else
            {
                // ���� ��ĭ �Ʒ��� �̵��Ѵ�.
                ddong[i].y++;
                // ���� ���ϴܿ� ���� ���� �� ó��.
                if( ddong[i].y >= 22 )
                {
                    ddong[i].x = rand() % 24 + 1;
                    ddong[i].y = 3;
                    evade++;    // ���� �˰��� ī��Ʈ
                }
                // �� ���
                gotoxy(ddong[i].x, ddong[i].y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xf5);
                printf("��");
                // �浹 üũ
                if( abs(ddong[i].x - user.x) < 2 && ddong[i].y == user.y )
                {
                    // ������ ���.
                    printf("\a");
                    check = 0;
                }
            }
        }
        // ���� �˰����� 20���� ������.
        if(evade > levelup)
			return 1;
    }
    return 2;
}
// ���� �Լ�
int main()
{
	system("mode con: cols=26 lines=25"); 
    int level = 1;

	system("Color 0A");
	gotoxy(6,1);
	printf("[�����ϱ����]");
	gotoxy(6,11);
	printf("1: ���ӽ���");
	gotoxy(6,12);
	printf("2:  ���̵�");
	gotoxy(6,13);
	printf("3:  ������");
	gotoxy(0,24);
	printf(" ");

	choose = _getch();

	if (choose == '1')
	{
		choose == '0';
		while(1)
		{
			// ȭ�� �����.
			system("cls");
			system("Color 0A");
			// ���� ǥ��.
			gotoxy(6,1); printf("[�����ϱ����]");
			gotoxy(9,11); printf("LEVEL %d", level); 
			// �ð� ���� (1�� = 1000)
			Sleep(1500);
			// ���� ����.
			if( game(level) == 2 )
			{
				system("cls");
				gotoxy(8, 5);
				system("Color 0F");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0D);
				printf("���� ����\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
				gotoxy(8, 12);
				printf("���� : %d", level);
				gotoxy(8, 13);
				printf("���� : %d", score);
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
				} while(1);
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
		gotoxy(6,1);
		printf("[�����ϱ����]");
		gotoxy(10,8);
		printf("���۹�");
		gotoxy(3,10);
		printf("�̵�   : ��,�� ȭ��ǥ");
		gotoxy(3,11);
		printf("�ν��� : �Ʒ� ȭ��ǥ");
		gotoxy(8,23);
		printf("1: ���ư���");
		gotoxy(0,24);
		printf(" ");

		while(choose != '1')
		{
			choose = _getch();
		}
		main();
	}
	else
		return 0;
}
