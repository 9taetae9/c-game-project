#define _CRT_NONSTDC_NO_WARNINGS//비표준 함수를 사용했을 때 에러 방지
#define _CRT_SECURE_NO_WARNINGS//scanf 보안 경고로 인한 컴파일 에러 방지 
#include <stdio.h>
#include <conio.h>

int main(){
	int num1, num2; // 입력 버퍼를 사용하지 않음, 화면에 키의 입력을 보여주지 않음 
	//키를 누르는 순간 문자가 c1에 저장되고 printf에서 출력
	//반면 getchar함수는 입력 버퍼(입력한 문자가 화면에 보임)를 사용하는데\
	 입력 버퍼에 들어간뒤 엔터키를 누르면 변수에 저장 된다. 
	printf("숫자 두 개를 입력하세요: ");
	scanf("%d %d", &num1,&num2);
	printf("두개 숫자의 합은 %d 입니다.\n", num1 + num2); 
	printf("아무 키나 입력하면 콘솔 창을 닫습니다.\n");
	int c1=getche();// 키를 입력할 때까지 콘솔 창이 계속 켜져 있도록 만듦. 
	printf("%c",c1);
	return 0; 
} 
