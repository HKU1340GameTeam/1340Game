// Camera.h

#ifndef _camera_h
#define _camera_h

#include "common.h"
#include "Layer.h"
#include "Player.h"
#include "Color.h"
#include <vector>
#include <string>
class Camera{
	public:
		Camera();
		// x,y are the top-left corner's position of the camera
		int x_pos;
		int y_pos;

		// offset to the center
		int center_x_offset = 73;
		int center_y_offset = 25;

		// MaxXLength is the horizontal Length of the Camera, ..Y.. is the vertical one
		int CamXSize = 150;
		int CamYSize = 40;
		
		// Cam that records figure
		vector<string> cam;
		// Cam that records foreground color
		vector<string> fgColorCam;

		// display cam without color
		void printCam();
		// display cam with color
		void colorPrintCam();
		// move to follow the exact position of player
		void FollowPlayer(Layer layer,Player player);
		// move to follow player but will not be out of edge
		void EdgeBlockFollowPlayer(Layer layer, Layer fgColorLayer, Player player);

};

#endif
