#define _CRT_NONSTDC_NO_WARNINGS//��ǥ�� �Լ��� ������� �� ���� ����
#define _CRT_SECURE_NO_WARNINGS//scanf ���� ���� ���� ������ ���� ���� 
#include <stdio.h>
#include <conio.h>

int main(){
	int num1, num2; // �Է� ���۸� ������� ����, ȭ�鿡 Ű�� �Է��� �������� ���� 
	//Ű�� ������ ���� ���ڰ� c1�� ����ǰ� printf���� ���
	//�ݸ� getchar�Լ��� �Է� ����(�Է��� ���ڰ� ȭ�鿡 ����)�� ����ϴµ�\
	 �Է� ���ۿ� ���� ����Ű�� ������ ������ ���� �ȴ�. 
	printf("���� �� ���� �Է��ϼ���: ");
	scanf("%d %d", &num1,&num2);
	printf("�ΰ� ������ ���� %d �Դϴ�.\n", num1 + num2); 
	printf("�ƹ� Ű�� �Է��ϸ� �ܼ� â�� �ݽ��ϴ�.\n");
	int c1=getche();// Ű�� �Է��� ������ �ܼ� â�� ��� ���� �ֵ��� ����. 
	printf("%c",c1);
	return 0; 
} 
