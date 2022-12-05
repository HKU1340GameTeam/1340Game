// ConvBox.h


#ifndef _convbox_h
#define _convbox_h

#include "common.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Layer.h"
#include "Camera.h"
#include "Conversation.h"
using namespace std;

class ConvBox{
	public:

		ConvBox();

		string name;

		string ConvBoxPath = "NPC/ConversationBox.txt";
		string ConvBoxColorPath = "NPC/ConvBoxColor.txt";
		
		vector<string> originalConvBox;
		vector<string> convBox;

		vector<string> originalConvBoxColor;
		vector<string> convBoxColor;

		int initialWritePosX = 63;
		int initialWritePosY = 6;

		int WritePosY = 6;

		int nameWritePosX = 27;
		int nameWritePosY = 2;

		int boxPosX = 1;
		int boxPosY = 28;

		int ConvBoxXSize;
		int ConvBoxYSize;

		// Clear (reset) box to empty
		void ResetConvBox();

		// Read box from .txt file (define shape(filling char) of box)
		void ReadConvBox();
		void ReadConvBoxColor();

		// Conversation character name, content, etc. are all stored in .txt file
		// Write the relevant information onto the box
		void WriteNameToBox(string name);
		void WriteConvToBox(Conversation conv);
		void WriteBoxToCam(Camera &cam);

};
#endif
