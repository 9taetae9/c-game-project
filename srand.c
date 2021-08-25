#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h> 
int main(){
	int i;
	
	srand((unsigned)time(NULL));
	for(i=0; i<5; i++){
		printf("%d \n",rand()/1000);
	}
	char nYN='y';
	nYN=toupper(nYN);
	printf("%c", nYN);
	return 0;
}
