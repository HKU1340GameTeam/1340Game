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

int PlayerXPosition = 130;
int PlayerYPosition = 15;

int playerStatus = -1;
int main(){

	string state = "Normal";

	Layer layer;
	Layer layer1;
	Layer layer2;
	Layer layer_fg_color;
	Layer layer1_fg_color;
	Layer layer2_fg_color;
	Layer PhyLayer;

	// initialize camera
	Camera camera = Camera();
	camera.ReadDeadCams();

	// initialize player
	//Player player(0,0,PlayerXPosition,PlayerYPosition,60.0,35.0,30.0,"AboveHeadComment/PlayerComments.txt");
	Player player(0,0,PlayerXPosition,PlayerYPosition,60.0,35.0,30.0,"AboveHeadComment/PlayerComments.txt");
	player.Load();

	Scene scene;
	string sceneName = player.RebirthScene;
	scene.setName(sceneName);
	scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);

	int convIndex = 0;
	ConvBox cb;
	cb.ReadConvBox();
	cb.ReadConvBoxColor();

	Conversation currentConv;
	string currentNPCName;
	int NPCDetectIndex = -2;

	while (state != "Exit") {
		while (state == "Normal") {
			layer1_fg_color.WriteObject(player.deathFigure_fg_color, player.int_x_pos, player.int_y_pos, 3, 3);
			layer1.WriteObject(player.deathFigure, player.int_x_pos, player.int_y_pos, 3, 3);
			scene.pileLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);
			camera.EdgeBlockFollowPlayer(layer, layer_fg_color, player);

			NPCDetectIndex = scene.NPCsDetect(player);
			if (scene.teleportSwitchScene(player,Input)) {
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
				for(int i=0;i<50;i++){
					if(keyb.kbhit()){
						key_nr = keyb.getch();
					}
				}
			}
			else if (scene.forceSwitchScene(player)) {
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
			}
			else if (scene.diedSwitchScene(player)) {
				player.HP --;
				gotoxy(1,1);
				player.ResetPlayer();
				camera.WriteObject(player.GetHealthMessage(),player.HPXPos,player.HPYPos);
				camera.colorPrintCam();
				for(int i=0;i<50;i++){
					if(keyb.kbhit()){
						key_nr = keyb.getch();
					}
				}
				sleep(diedWaitTime);
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
				for(int i=0;i<50;i++){
					if(keyb.kbhit()){
						key_nr = keyb.getch();
					}
				}
				Input = 'p';
			}
			if(player.HP <= 0){
				scene.setName(player.RebirthScene);
				player.position.x = player.rebirthPosX;
				player.position.y = player.rebirthPosY;
				player.int_x_pos = player.rebirthPosX;
				player.int_y_pos = player.rebirthPosY;
				player.HP = player.maxHP;
				gotoxy(1,1);
				player.ResetPlayer();
				camera.WriteOneRandomDeadCam();
				camera.colorPrintCam();
				for(int i=0;i<50;i++){
					if(keyb.kbhit()){
						key_nr = keyb.getch();
					}
				}
				sleep(deathWaitTime);
				scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
				for(int i=0;i<50;i++){
					if(keyb.kbhit()){
						key_nr = keyb.getch();
					}
				}
				Input = 'p';
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
			playerStatus = player.PrintAboveHeadComment(scene.trigger,layer2, -1);
			if(playerStatus == 1 && Input == 'r'){
				playerStatus = player.PrintAboveHeadComment(scene.trigger,layer2, 2);
				player.SetRebirth(scene.sceneName);
			}
			scene.pileLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);
			camera.EdgeBlockFollowPlayer(layer, layer_fg_color, player);
			camera.WriteObject(player.GetHealthMessage(),player.HPXPos,player.HPYPos);



			gotoxy(1,1);
			camera.colorPrintCam();

			cout << "X: " << player.int_x_pos << " Y: " << player.int_y_pos << endl;

			// refresh with refresh rate of 1/deltatime
			if(playerStatus == 2){
				sleep(2);
			}
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

