// Color.cpp

#include "Color.h"
#include<iostream>
using namespace std;

void fgColorPrint(char message,char color){
	switch(color){
		case 'a':
			cout << color_def_start;
			cout << black;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'r':
			cout << color_def_start;
			cout << red;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'g':
			cout << color_def_start;
			cout << green;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'y':
			cout << color_def_start;
			cout << yellow;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'b':
			cout << color_def_start;
			cout << blue;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'm':
			cout << color_def_start;
			cout << magenta;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'c':
			cout << color_def_start;
			cout << cyan;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		case 'w':
			cout << color_def_start;
			cout << white;
			cout << color_def_end;
			cout << message;
			cout << reset;
			break;
		default:
			cout << message;
	}

}

void fgColorPrint_plus(char message,char color){
	if(message == ' '){
		cout << ' ';
	}
	else{
		switch(color){
			case 'a':
				cout << color_def_start;
				cout << black;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'r':
				cout << color_def_start;
				cout << red;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'g':
				cout << color_def_start;
				cout << green;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'y':
				cout << color_def_start;
				cout << yellow;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'b':
				cout << color_def_start;
				cout << blue;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'm':
				cout << color_def_start;
				cout << magenta;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'c':
				cout << color_def_start;
				cout << cyan;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			case 'w':
				cout << color_def_start;
				cout << white;
				cout << color_def_end;
				cout << message;
				cout << reset;
				break;
			default:
				cout << message;
		}

	}
}
