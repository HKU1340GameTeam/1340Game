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
	Player player(0,0,5.0,5.0,60.0,35.0,30.0,"AboveHeadComment/PlayerComments.txt");

	Scene scene;
	string sceneName = "FirstScene";
	scene.setName(sceneName);
	scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);

	int convIndex = 0;
	ConvBox cb;
	cb.ReadConvBox();
	cb.ReadConvBoxColor();

	Conversation currentConv;
	string currentNPCName;
	int NPCDetectIndex = -2;
	// cout << 's' << endl;
	
	//cout << mentor.name << endl;
	//mentor.conv.PrintAllConv();

	//for(int i=0;i<(int)mentor.figure.size();i++){
		//cout << mentor.figure[i] << endl;
	//}
	//for(int i=0;i<(int)mentor.figureColor.size();i++){
		//cout << mentor.figureColor[i] << endl;
	//}
	//cout << mentor.posX << endl;
	//cout << mentor.posY << endl;
	//cout << mentor.leftTriggerRange << endl;
	//cout << mentor.rightTriggerRange << endl;
	//cout << mentor.upTriggerRange << endl;
	//cout << mentor.downTriggerRange << endl;
	//cout << mentor.writeToLayer << endl;

	//cout << mentor.NPCXSize << endl;
	//cout << mentor.NPCYSize << endl;
	
	
	//scene.resetLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);

	//mentor.WriteNPCtoLayer(layer1,layer1_fg_color);

	//scene.pileLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);

	//layer.PrintLayer();


	while (state != "Exit") {
		while (state == "Normal") {
			NPCDetectIndex = scene.NPCsDetect(player);
			if (scene.switchScene(player,Input)) {
				// cout << 'd' << endl;
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

			layer1.WriteObject(player.figure, player.int_x_pos, player.int_y_pos, 3, 3);
			layer1_fg_color.WriteObject(player.figure_fg_color, player.int_x_pos, player.int_y_pos, 3, 3);
			player.PrintAboveHeadComment(scene.trigger,layer2);

			scene.WriteNPCsToLayer(layer1,layer1_fg_color);
			scene.ShowNPCsComment(player,layer1);

			scene.pileLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color);
			camera.EdgeBlockFollowPlayer(layer, layer_fg_color, player);

			gotoxy(1,1);
			camera.colorPrintCam();
			//camera.printCam();
			//cout << scene.trigger[player.int_y_pos][player.int_x_pos] << endl;
			//cout << "Mentor PosX" << mentor.posX << " Mentor PosY" << mentor.posY << endl;
			//cout << "Player pos x" << player.int_x_pos << " Player pos Y" << player.int_y_pos << endl;

			// refresh with refresh rate of 1/deltatime
			usleep(deltaTime);
	
		}

		while (state == "UI") {
			return 0;
		}

		system("clear");
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
			camera.CenterFollowPlayer(layer,layer_fg_color, player);
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

