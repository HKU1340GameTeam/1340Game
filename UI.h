// UI.h

#ifndef _UI_h
#define _UI_h

#include <vector>
#include <string>
#include "Player.h"
#include "Color.h"
using namespace std;
class UI
{
	public:
		UI();

		int CursorXposition[4] = {58, 64, 62, 62};
		int CursorYposition[4] = {19, 25, 31, 37};
		char down = 'j';
		char up = 'k';
		string save = "Player/SavedFile.txt";
		string cursorPath = "UI/cursor.txt";
		string UIPath = "UI/UI.txt";

		vector<string> ui;
		vector<string> original_UI;
		vector<string> CursorFigure;
		int button = 0;
		vector<int> ButtonXpostion;
		vector<int> ButtonYpostion;
		void ReadUI();
		void ReadCursorFigure();
		void ReadButton();
		void UpdateCursorPosition(char Input);
		void WriteCursor();
		void ResetUI();
		void PrintUI();
		void SavedFile(string RebirthScene, int rebirthPosX, int rebirthPosY, int HP);	
		void LoadFile(Player &player);
		void PrintColor();
};
#endif
