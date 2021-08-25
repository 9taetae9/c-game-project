#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
BOOL IsKeyDown(int Key){ 
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
	}
int main(){
getch(); 
if (IsKeyDown(VK_LEFT)){
	printf("You *just* pressed left key !"); 
	}
	return 0;
}
