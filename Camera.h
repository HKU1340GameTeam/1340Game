// Camera.h

#ifndef _camera_h
#define _camera_h

#include "common.h"
#include "Layer.h"
#include "Player.h"
#include "Color.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
class Camera{
	public:
		Camera();
		// x,y are the top-left corner's position of the camera
		int x_pos;
		int y_pos;

		// offset to the center
		int center_x_offset = 86;
		int center_y_offset = 28;

		// MaxXLength is the horizontal Length of the Camera, ..Y.. is the vertical one
		int CamXSize = 178;
		int CamYSize = 43;

		// Offset putting the player to center
		int centerPlayerXOffset = 86;
		int centerPlayerYOffset = 20;
		
		// Cam that records figure
		vector<string> cam;
		// Cam that records foreground color
		vector<string> fgColorCam;


		string deadCamListName = "Camera/deadCamList.txt";
		// died cam appearence list
		vector<string> deadCamList;

		// died cam
		vector<string> deadCam;

		// died cams
		vector<vector<string>> deadCams;

		// display cam without color
		void printCam();
		// display cam with color
		void colorPrintCam();
		// move to follow the exact position of player
		void FollowPlayer(Layer layer,Player player);
		// move to follow the exact position of player
		void CenterFollowPlayer(Layer layer, Layer fgColorLayer, Player player);
		// move to follow player but will not be out of edge
		void EdgeBlockFollowPlayer(Layer layer, Layer fgColorLayer, Player player);
		// move to follow player but will not be out of edge
		void EdgeBlockFollowDeathPlayer(Layer layer, Layer fgColorLayer, Player player);
		// Check if the point is out of camera
		bool OutOfCamera(int x,int y);
		// Read Died Cam Info
		void ReadDeadCamList();
		// Read Died Cam
		void ReadDeadCam(string Path);
		void ReadDeadCams();

		// Write Death Cam
		void WriteDeadCam(int i);
		void WriteOneRandomDeadCam();
		// Write Objects
		void WriteObject(vector<string> pic, int pos_x, int pos_y, int size_x, int size_y);
		void WriteObject(string message, int pos_x, int pos_y);

		// LKH
		// move to follow player placed at center but will not be out of edge except if player's near ground
		void EdgeCenterFollowPlayer(Layer layer, Layer fgColorLayer, Player player);

		// move to center
		int target = 20;
		float accDeviation = 0.0, mvSpd = 0.0, maxDeviation = 0.0;
		bool toCenter = true;
		void moveToCenter(bool cen, float Spd, int target);
};

#endif
