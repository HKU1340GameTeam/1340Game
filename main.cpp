// Thu Oct 20 17:20:04 CST 2022
#include<iostream>
#include<string>
#include<cmath>
#include <unistd.h>
//#include <termios.h>
//#include <sys/ioctl.h>
#include "common.h"
#include "Layer.h"
#include "Player.h"
#include "kbhit.h"
#include "Camera.h"
#include "Scene.h"
#include "Conversation.h"
#include "Talk.h"
#include "AboveHeadComment.h"
#include "ConvBox.h"
#include "NPC.h"
using namespace std;

// "kbhit.h" is from stackoverflow written by "orlov_dumitru"

int key_nr;
char Input;
keyboard keyb;

int PlayerXPosition = 5;
int PlayerYPosition = 5;
int main(){

	string state = "Normal";

	//cout << "Enter SceneName: " << endl;
	//cin >> SceneName;

	//system("clear");

	Layer layer;
	Layer layer1;
	Layer layer2;
	Layer layer_fg_color;
	Layer layer1_fg_color;
	Layer layer2_fg_color;
	Layer PhyLayer;

	// initialize camera
	Camera camera = Camera();

	// initialize player
	Player player(0,0,PlayerXPosition,PlayerYPosition,60.0,35.0,30.0,"AboveHeadComment/PlayerComments.txt");

	Scene scene;
	string sceneName = "BirthScene";
	scene.setName(sceneName);
	scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);

	//cout << scene.animList[0].frameYSize << endl;
	//for(int i=0;i<scene.animList[0].frameYSize;i++){
		//cout << scene.animList[0].currentFrameColor[i] << endl;
	//}
	
	//for(int i=0;i<scene.animList[0].videoSize;i++){
		//for(int y=0;y<scene.animList[0].frameYSize;y++){
			 //for(int x=0;x<scene.animList[0].frameXSize;x++){
				//cout << scene.animList[0].videoColor[i][y][x]; 
				////if(videoColor[i][y][x]!=' '){
					////videoColor[i][y][x] = color;
				////}
			//}
			//cout << endl;
		//}
	//}
	//for(int i=0;i<scene.animNum;i++){
		//scene.animList[i].UpdateFrame();
	//}
	//for(int i=0;i<scene.animList[0].frameYSize;i++){
		//cout << scene.animList[0].currentFrameColor[i] << endl;
	//}

	int convIndex = 0;
	ConvBox cb;
	cb.ReadConvBox();
	cb.ReadConvBoxColor();

	Conversation currentConv;
	string currentNPCName;
	int NPCDetectIndex = -2;

	while (state != "Exit") {
		while (state == "Normal") {
			NPCDetectIndex = scene.NPCsDetect(player);
			if (scene.switchScene(player,Input)) {
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
			}
			else if (scene.forceSwitchScene(player)) {
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
			}

			// detect if keyboard is hit
			if(keyb.kbhit()){
				key_nr = keyb.getch();
				Input = key_nr;
				// if 0 is hit, leave the game
				if(Input == '0') {
					state = "Exit";
					break;
				}
				// otherwise, update position of player accordingly, but consider collision by adding physical layer
				else if(NPCDetectIndex!=-1 && Input == 'r'){
					state = "Conv";
					currentConv = scene.NPCList[NPCDetectIndex].conv;
					currentNPCName = scene.NPCList[NPCDetectIndex].name;
					break;
				}
				else{
					player.UpdateFigure();
					player.UpdatePosition(Input, PhyLayer);
				}
			}
			else {
				// p means pass, represnt no input
				Input = 'p';
				player.UpdateFigure();
				player.UpdatePosition(Input, PhyLayer);
			}

			// update layers(1. reseting layers 2. putting object into new position 3. pile up layers)

			scene.resetLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);

			scene.WriteNPCsToLayer(layer1,layer1_fg_color);
			scene.ShowNPCsComment(player,layer1);
			scene.WriteAnimatorsToLayer(layer1,layer1_fg_color);

			layer1.WriteObject(player.figure, player.int_x_pos, player.int_y_pos, 3, 3);
			layer1_fg_color.WriteObject(player.figure_fg_color, player.int_x_pos, player.int_y_pos, 3, 3);
			player.PrintAboveHeadComment(scene.trigger,layer2);

			scene.pileLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);
			camera.EdgeBlockFollowPlayer(layer, layer_fg_color, player);

			gotoxy(1,1);
			camera.colorPrintCam();

			// refresh with refresh rate of 1/deltatime
			usleep(deltaTime);
	
		}

		while (state == "UI") {
			return 0;
		}

		system("clear");
		if(state == "Conv"){
			camera.CenterFollowPlayer(layer,layer_fg_color, player);
		}
		while (state == "Conv") {
			if(keyb.kbhit()){
				key_nr = keyb.getch();
				Input = key_nr;
				// if 0 is hit, leave the game
				if(Input == '0') {
					state = "Exit";
					break;
				}
				// otherwise, update position of player accordingly, but consider collision by adding physical layer
				else{
					convIndex = currentConv.UpdateConv(Input);
					if(convIndex == -1){
						state = "Normal";
						break;
					}
				}
			}
			//camera.CenterFollowPlayer(layer,layer_fg_color, player);
			cb.ResetConvBox();
			cb.WriteNameToBox(currentNPCName);
			cb.WriteConvToBox(currentConv);
			cb.WriteBoxToCam(camera);
			camera.colorPrintCam();
			gotoxy(1,1);
			usleep(deltaTime);
		}
	
	}
	return 0;
}

