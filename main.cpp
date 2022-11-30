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
using namespace std;

// "kbhit.h" is from stackoverflow written by "orlov_dumitru"

int key_nr;
char Input;
keyboard keyb;
int main(){

	string state = "Normal";

	//cout << "Enter SceneName: " << endl;
	//cin >> SceneName;

	system("clear");

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
	Player player(0,0,5.0,5.0,60.0,35.0,30.0);

	/*
	// read the shape of scene
	layer.ReadLayerFromFile("Scenes/"+SceneName+"/emptyScene.txt");
	layer1.ReadLayerFromFile("Scenes/"+SceneName+"/scene1.txt");
	layer2.ReadLayerFromFile("Scenes/"+SceneName+"/scene2.txt");

	// read the color of scene
	layer_fg_color.ReadLayerFromFile("Scenes/"+SceneName+"/emptyScene.txt");
	layer1_fg_color.ReadLayerFromFile("Scenes/"+SceneName+"/fgColor_scene1.txt");
	layer2_fg_color.ReadLayerFromFile("Scenes/"+SceneName+"/fgColor_scene2.txt");

	// read the layer for controling collision
	PhyLayer.ReadLayerFromFile("Scenes/"+SceneName+"/phyScene.txt");
	*/

	Scene scene;
	string sceneName = "FirstScene";
	scene.setName(sceneName);
	scene.loadNewScene(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, PhyLayer);
	// cout << 's' << endl;

	while (state != "Exit") {
		while (state == "Normal") {

			if (scene.switchScene(player)) {
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

			scene.resetLayer(layer, layer1, layer2, layer_fg_color, layer1_fg_color, layer2_fg_color, player);
			camera.EdgeBlockFollowPlayer(layer, layer_fg_color, player);

			gotoxy(1,1);
			camera.colorPrintCam();
			//camera.printCam();

			// refresh with refresh rate of 1/deltatime
			usleep(deltaTime);
	
		}

		while (state == "UI") {
			return 0;
		}

		while (state == "Conv") {
			return 0;
		}
	
	}
	return 0;
}

