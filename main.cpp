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
using namespace std;

// "kbhit.h" is from stackoverflow written by "orlov_dumitru"

int key_nr;
char Input;
keyboard keyb;
int main(){

	string SceneName;

	cout << "Enter SceneName: " << endl;
	cin >> SceneName;

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

	cout << "successful" << endl;

	while(1){
		// detect if keyboard is hit
		if(keyb.kbhit()){
			key_nr = keyb.getch();
			Input = key_nr;
			// if 0 is hit, leave the game
			if(Input == '0'){
				break;
			}
			// otherwise, update position of player accordingly, but consider collision by adding physical layer
			else{
				player.UpdatePosition(Input,PhyLayer);
			}
		}
		else{
			// p means pass, represnt no input
			Input = 'p';
			player.UpdatePosition(Input,PhyLayer);
		}

		// update layers(1. reseting layers 2. putting object into new position 3. pile up layers)
		layer.ResetLayer();
		layer1.ResetLayer();
		layer2.ResetLayer();
		cout << "successful" << endl;
		layer_fg_color.ResetLayer();
		layer1_fg_color.ResetLayer();
		layer2_fg_color.ResetLayer();

		layer1.WriteObject(player.figure,player.int_x_pos,player.int_y_pos,3,3);
		layer1_fg_color.WriteObject(player.figure_fg_color,player.int_x_pos,player.int_y_pos,3,3);

		layer.AddLayerOnTop(layer1);
		layer.AddLayerOnTop(layer2);

		layer_fg_color.AddLayerOnTop(layer1_fg_color);
		layer_fg_color.AddLayerOnTop(layer2_fg_color);
		camera.EdgeBlockFollowPlayer(layer,layer_fg_color,player);

		gotoxy(1,1);
		camera.colorPrintCam();
		//camera.printCam();

		// refresh with refresh rate of 1/deltatime
		usleep(deltaTime);

	}

	return 0;
}

