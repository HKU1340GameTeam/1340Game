// NPC.cpp


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
#include "NPC.h"

using namespace std;


NPC::NPC(){

}

NPC::NPC(string NPCPath){
	ReadBasicInfo(NPCPath);
	abc.objectPositionX = posX;
	abc.objectPositionY = posY;
	abc.ReadComments(CommentsPath);
}

void NPC::ShowComment(Player player,Layer &layer){
	if(DetectPlayer(player)){
		abc.objectPositionX = posX;
		abc.objectPositionY = posY;
		abc.PrintComment(layer);
	}
}

void NPC::ReadBasicInfo(string NPCinfoPath){
	ifstream fin;
	fin.open(NPCinfoPath);
	if(fin.fail()){
		cerr << "NPC file cannot be opened" << NPCinfoPath << endl;
		exit(1);
	}
	string line;
	getline(fin,line);
	if(line!="Name:"){
		cerr << "NPC format not correct (Name)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	name = line;

	getline(fin,line);
	if(line!="Conversation Path:"){
		cerr << "NPC format not correct (Conv Path)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	conv.ReadConversation(line);
	
	getline(fin,line);
	if(line!="Figure:"){
		cerr << "NPC format not correct (Figure)" << NPCinfoPath << endl;
		exit(1);
	}
	NPCYSize = 0;
	while(getline(fin,line)){
		if(line!="Figure Color:"){
			if(NPCXSize==-1){
				NPCXSize = line.length();
			}
			else{
				if(NPCXSize!=(int)line.length()){
					cerr << "NPC X Size not consistent (Figure)" << NPCinfoPath << endl;
					exit(1);
				}
			}
			figure.push_back(line);
			NPCYSize ++;
		}
		else{
			break;
		}
	}
	if(line!="Figure Color:"){
		cerr << "NPC format not correct (Figure Color)" << NPCinfoPath << endl;
		exit(1);
	}
	NPCfigureYSize = 0;
	while(getline(fin,line)){
		if(line!="Position X:"){
			if(NPCXSize != (int)line.length()){
				cerr << "NPC X Size not consistent (Color Figure)" << NPCinfoPath << endl;
				exit(1);
			}
			figureColor.push_back(line);
			NPCfigureYSize++;
		}
		else{
			break;
		}
	}
	if(NPCYSize != NPCfigureYSize){
		cerr << "NPC Y Size not consistent (Color Figure)" << NPCinfoPath << endl;
		exit(1);
	}
	if(line!="Position X:"){
		cerr << "NPC format not correct (Position X)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	posX = stoi(line);
	getline(fin,line);
	if(line!="Position Y:"){
		cerr << "NPC format not correct (Position Y)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	posY = stoi(line);


	getline(fin,line);
	if(line!="leftTriggerRange:"){
		cerr << "NPC format not correct (leftTriggerRange)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	leftTriggerRange = stoi(line);

	getline(fin,line);
	if(line!="rightTriggerRange:"){
		cerr << "NPC format not correct (rightTriggerRange)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	rightTriggerRange = stoi(line);

	getline(fin,line);
	if(line!="upTriggerRange:"){
		cerr << "NPC format not correct (upTriggerRange)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	upTriggerRange = stoi(line);

	getline(fin,line);
	if(line!="downTriggerRange:"){
		cerr << "NPC format not correct (downTriggerRange)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	downTriggerRange = stoi(line);

	getline(fin,line);
	if(line!="Write to layer:"){
		cerr << "NPC format not correct (Write to layer)" << NPCinfoPath << endl;
		exit(1);
	}
	getline(fin,line);
	writeToLayer = stoi(line);

	fin.close();
}

bool NPC::DetectPlayer(Player player){
	if(player.int_x_pos < posX+rightTriggerRange && player.int_x_pos > posX-leftTriggerRange && player.int_y_pos < posY+downTriggerRange && player.int_y_pos > posY-upTriggerRange){
		return true;
	}
	else{
		return false;
	}
}

void NPC::WriteNPCtoLayer(Layer &layer, Layer &layerColor){
	layer.WriteObject(figure,posX,posY,NPCXSize,NPCYSize);
	layerColor.WriteObject(figureColor,posX,posY,NPCXSize,NPCYSize);
}

	//void WriteObject(vector<string> pic, int pos_x, int pos_y, int size_x, int size_y);


