// Scene.h

#ifndef _scene_h
#define _scene_h

#include "Layer.h"
#include "Player.h"
#include "Animator.h"
#include "NPC.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Scene{
public:
	int sizeX = 0, sizeY = 0;
	string sceneName = "";
	vector<string> trigger; // ~Layer
	// set tp as vector of vector of string
	// inner vector: char, sceneName, pos
	// vector<vector<string>> tp;
	map<char, string> tp;
	map<char, int> tpX;
	map<char, int> tpY;

	vector<Animator> animList;
	int animNum;
	vector<NPC> NPCList;
	int NPCNum;

	string SceneFolderName = "GameScenes";

	void ReadNPCs(string NPCPath);
	void ReadAnimators(string AnimPath);

	int NPCsDetect(Player player);
	void WriteNPCsToLayer(Layer &layer,Layer &layerColor);
	void ShowNPCsComment(Player player, Layer &layer);

	void WriteAnimatorsToLayer(Layer &layer,Layer &layerColor);

	void setName(string sn);
	// map that contains char indicating which to trigger
	void readTrigger(); // fn = filename
	// function that set up layer and player position
	// read information from a <sceneName>.txt file
	// sample format of file
	// ln1 Scene Name
	// ln2-7 filename -> layer
	// after: pair of <char, scene to trigger (num to return)>
	void loadNewScene(Layer &l0, Layer &l1, Layer &l2, Layer &fgc, Layer &l1c, Layer &l2c, Layer &Phy);
	// return 0 if keep playing scene
	// teleport player away when player choosed to 
	bool switchScene(Player &p, char Input); //keeping playing
	// return 0 if keep playing scene
	// forces player to be teleported away
	bool forceSwitchScene(Player &p);
	// reset layers
	void resetLayer(Layer &l0, Layer &l1, Layer &l2, Layer &fgc, Layer &l1c, Layer &l2c);
	// pile up layer
	void pileLayer(Layer &l0, Layer &l1, Layer &l2, Layer &fgc, Layer &l1c, Layer &l2c);

};



#endif
