#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

typedef struct Pos{
	 int x;
	 int y;
}pos;
void gotoxy(int x,int y);
void clrscr(void);
void printxy(int x,int y,char c);
void coverScreen(pos position,int locx,int locy,int sizex,int sizey,char c);

void locate(pos position,int x,int y);
int main(){
	clrscr();
	int zeroAscii = 48;
	char zero=zeroAscii;
	char veryone=zero;
	pos current_pos;
	current_pos.x = 0;
	current_pos.y = 0;
	for(int i=0;i<10;i++){
		veryone = zero+i;
		coverScreen(current_pos,10,10,5,5,veryone);
		sleep(1);
		clrscr();
	}
	printf("\n");
	return 0;
}

void gotoxy(int x,int y){
	 printf("%c[%d;%df",0x1B,y,x);
}

void clrscr(void){
	 system("clear");
}

void printxy(int x,int y,char c){
	 gotoxy(x,y);
	 printf("%c",c);
	 gotoxy(-x,-y);
}

void coverScreen(pos position,int locx,int locy,int sizex,int sizey,char c){
	 locate(position,locx,locy);
	 for(int i=0;i<sizex;i++){
		  for(int j=0;j<sizey;j++){
			   printf("%c",c);
		  }
		  locate(position,locx+1,locy);
	 }
}

void locate(pos position,int x,int y){
	 gotoxy(-position.x,-position.y);
	 position.x = x;
	 position.y = y;
	 gotoxy(x,y);
}
















