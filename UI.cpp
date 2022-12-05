#include <iostream>
#include <string>
#include "UI.h"
#include <fstream>
#include <vector>
#include "Player.h"
using namespace std;

UI::UI(){
}

void UI::ResetUI(){
	for (int i=0; i<(int)ui.size(); i++){
		ui[i] = original_UI[i];
	}
}

void UI::ReadCursorFigure(){
	ifstream fin;
	fin.open(cursorPath);
	if (fin.fail()){
		cout << "Fail to open file" << endl;
		exit(1);
	}
	string line;
	while(getline(fin, line)){
		CursorFigure.push_back(line);
	}
	fin.close();
}

void UI::ReadUI(){
	ifstream fin;
	fin.open(UIPath);
	if (fin.fail()){
		cout << "Fail to open file" << endl;
		exit(1);
	}
	string line;
	while (getline(fin, line)){
		ui.push_back(line);
		original_UI.push_back(line);
	}
	fin.close();
}
void UI::UpdateCursorPosition(char Input){
	if (Input == down && button != 3){
		button += 1;
	}
	if (Input == up && button != 0){
		button -= 1;
	
	}                                                                                
}

void UI::WriteCursor(){
	ResetUI();
	int y= 0;
	int x = 0;
	for (int j=CursorYposition[button]; j<CursorYposition[button]+4; j++){
        for (int k=CursorXposition[button]; k<CursorXposition[button]+9; k++){
            ui[j][k] = CursorFigure[y][x];  
            x++;
        }
        y++;
        x = 0;
    }
}
void UI::PrintUI(){
	for (int i=0; i<(int)ui.size(); i++){
		cout << ui[i] << endl;
	}
}

//void UI::PrintColor(){
	//for(int i=0;i<CamYSize;i++){
		//for(int j=0;j<CamXSize;j++){
			//fgColorPrint_plus(cam[i][j],fgColorCam[i][j]);
		//}
		//cout << endl;
	//}
//}

void UI::SavedFile(string RebirthScene, int rebirthPosX, int rebirthPosY, int HP){
	string file;
	string game = "Game/";
	char i;
	bool success = false;
	ofstream fout;
	while(!success){
		cout << "Please enter file name: ";
		cin >> file;
		cout << endl;
		file += ".txt";
		cout << "Are you sure you want to save as: " << file << "? (y/n):";
		cin >> i;
		if(i=='y'){
			success = true;
		}
		fout.open(game+file);
		if (fout.fail()){
			cout << "Fail to open file" << endl;
			success = false;
		}
		if(success == false){
			cout << "Please input again" << endl;
		}

	}
	fout << RebirthScene << " " << rebirthPosX << " " << rebirthPosY << " " << HP;
	fout.close();
}

void UI::LoadFile(Player &player){
	string file;
	char q;
	string game = "Game/";
	//cout << "Please enter file name: ";
	//cin >> file;
	//file += ".txt";
	int c = 0;
	ifstream fin;
	while (c == 0){
		cout << "\n";
		cout << "Please enter file name: ";
		cin >> file;
		file += ".txt";
		fin.open(game+file);
		cout << "\n";
		if(fin.fail()){
			cout << "You entered: " << file << ", the file doesn't exist"<< endl; 
			//cout << "Please enter again: " ;
			//cin >+ file;
			//file += ".txt";
		}
		else{
			cout << "Are you sure you want to load: " << file << "? (y/n)";
			cin >> q;
			if (q == 'y'){	
				c = 1;
			}
			else{
				fin.close();
			}
		}	
	}
	
	string line;
	getline(fin,line);
	string name;
	int x;
	int y;
	int MaxHP;
	istringstream iss(line);

	iss >> name >> x >> y >> MaxHP;
	player.rebirthPosX = x;
	player.rebirthPosY = y;
	player.RebirthScene = name;
	player.maxHP = MaxHP;
	player.HP = MaxHP;

	player.position.x = player.rebirthPosX;
	player.int_x_pos = player.rebirthPosX;
	player.position.y = player.rebirthPosY;
	player.int_y_pos = player.rebirthPosY;

	fin.close();

}

