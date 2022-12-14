// NPC.h


#ifndef _npc_h
#define _npc_h

#include "common.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Layer.h"
#include "Conversation.h"
#include "Player.h"
#include "AboveHeadComment.h"
using namespace std;

class NPC{
	public:

		NPC();
		NPC(string NPCPath);

		// name of the npc
		string name;

		// conversation of the npc
		Conversation conv;

		// Above head comment
		string CommentsPath; 
		AboveHeadComment abc = AboveHeadComment();

		// figure of the npc
		vector<string> figure;
		vector<string> figureColor;

		// position of the NPC
		int posX;
		int posY;
		
		// how far from NPC's position can player be detected
		int leftTriggerRange;
		int rightTriggerRange;
		int upTriggerRange;
		int downTriggerRange;

		// 1 for layer 1, 2 for layer 2
		int writeToLayer;

		int NPCXSize=-1;
		int NPCYSize=-1;
		int NPCfigureYSize=-1;

		// Read information of NPC
		// including Shape & Color of figure, position, region could be detacted
		void ReadBasicInfo(string NPCinfoPath);

		// Check if player is in range of detection
		// display above head comment if yes
		bool DetectPlayer(Player player);
		void ShowComment(Player player,Layer &layer);

		// Display NPC figure to screen
		void WriteNPCtoLayer(Layer &layer, Layer &layerColor);

};




#endif
