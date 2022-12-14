#include "common.h"
#include "Camera.h"
#include "Layer.h"
#include "Player.h"
#include "Color.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
using namespace std;

//Camera::Camera(){
	//ifstream fin;
	//fin.open("Camera/camera.txt");
	//if(fin.fail()){
		//perror("fail to open file");
		//throw "fail to open file";
	//}
	//string line;
	//while(getline(fin,line)){
		//if(CamXSize != 0){
			//if(int(line.size()) != CamXSize){
				//perror("Cam X direction size not consistent");
				//throw "Cam X direction size not consistent";
			//}
		//}
		//cam.push_back(line);
		//fgColorCam.push_back(line);
	//}
	//if(int(cam.size()) != CamYSize){
		//perror("Cam Y direction size not consistent");
		//throw "Cam Y direction size not consistent";
	//}
	//fin.close();
//}

Camera::Camera(){
	string Ceil = "**";
	string Middle = "*";
	for(int i=2;i<CamXSize;i++){
		Ceil+="*";
		Middle+=" ";
	}
	Middle+="*";
	cam.push_back(Ceil);
	fgColorCam.push_back(Ceil);
	for(int i=2;i<CamYSize;i++){
		cam.push_back(Middle);
		fgColorCam.push_back(Middle);
	}
	cam.push_back(Ceil);
	fgColorCam.push_back(Ceil);
}

void Camera::printCam(){
	for(int i=0;i<CamYSize;i++){
		cout << cam[i] << endl;
	}
}

void Camera::colorPrintCam(){
	for(int i=0;i<CamYSize;i++){
		for(int j=0;j<CamXSize;j++){
			fgColorPrint_plus(cam[i][j],fgColorCam[i][j]);
		}
		cout << endl;
	}
}


void Camera::FollowPlayer(Layer layer,Player player){
	int pixel_x_pos;
	int pixel_y_pos;
	y_pos = player.int_y_pos - center_y_offset;
	x_pos = player.int_x_pos - center_x_offset;
	for(int i=1;i<CamYSize-1;i++){
		for(int j=1;j<CamXSize-1;j++){
			pixel_x_pos = x_pos + j;
			pixel_y_pos = y_pos + i;
			if(!layer.OutOfLayer(pixel_x_pos,pixel_y_pos)){
				try{
					cam[i][j] = layer.layer[pixel_y_pos][pixel_x_pos];
				}
				catch(int num){
					cout << pixel_y_pos << ' ' << pixel_x_pos << endl;
					perror("im confused");
				}
			}
			else{
				cam[i][j] = '*';
			}
		}
	}

}

void Camera::EdgeBlockFollowPlayer(Layer layer, Layer fgColorLayer, Player player){
	int pixel_x_pos;
	int pixel_y_pos;
	y_pos = player.int_y_pos - center_y_offset;
	x_pos = player.int_x_pos - center_x_offset;
	if(x_pos<0){
		x_pos = 0;
	}
	else if(x_pos>layer.LayerXSize-CamXSize){
		x_pos = layer.LayerXSize - CamXSize;
	}
	if(y_pos<0){
		y_pos = 0;
	}
	else if(y_pos>layer.LayerYSize-CamYSize){
		y_pos = layer.LayerYSize - CamYSize;
	}
	for(int i=1;i<CamYSize-1;i++){
		for(int j=1;j<CamXSize-1;j++){
			pixel_x_pos = x_pos + j;
			pixel_y_pos = y_pos + i;
			if(!layer.OutOfLayer(pixel_x_pos,pixel_y_pos)){
				try{
					cam[i][j] = layer.layer[pixel_y_pos][pixel_x_pos];
					fgColorCam[i][j] = fgColorLayer.layer[pixel_y_pos][pixel_x_pos];
				}
				catch(int num){
					cout << pixel_y_pos << ' ' << pixel_x_pos << endl;
					perror("im confused");
				}
			}
			else{
				cam[i][j] = '*';
			}
		}
	}

}

void Camera::CenterFollowPlayer(Layer layer, Layer fgColorLayer, Player player){
	int pixel_x_pos;
	int pixel_y_pos;
	y_pos = player.int_y_pos - centerPlayerYOffset;
	x_pos = player.int_x_pos - centerPlayerXOffset;
	for(int i=1;i<CamYSize-1;i++){
		for(int j=1;j<CamXSize-1;j++){
			pixel_x_pos = x_pos + j;
			pixel_y_pos = y_pos + i;
			if(!layer.OutOfLayer(pixel_x_pos,pixel_y_pos)){
				try{
					cam[i][j] = layer.layer[pixel_y_pos][pixel_x_pos];
					fgColorCam[i][j] = fgColorLayer.layer[pixel_y_pos][pixel_x_pos];
				}
				catch(int num){
					cout << pixel_y_pos << ' ' << pixel_x_pos << endl;
					perror("im confused");
				}
			}
			else{
				cam[i][j] = ' ';
				fgColorCam[i][j] = ' ';
			}
		}
	}
}

bool Camera::OutOfCamera(int x,int y){
	if(x >= CamXSize-1 || x <= 0){
		return true;
	}
	if(y >= CamYSize-1 || y <= 0){
		return true;
	}
	return false;
}



void Camera::ReadDeadCamList(){
	ifstream fin;
	fin.open(deadCamListName);
	if(fin.fail()){
		cerr << "cannot open " << deadCamListName << endl;
		exit(1);
	}
	string line;
	while(getline(fin,line)){
		deadCamList.push_back(line);
	}
	fin.close();
}

void Camera::ReadDeadCam(string Path){
	ifstream fin;
	fin.open(Path);
	if(fin.fail()){
		cerr << "cannot open " << Path << endl;
		exit(1);
	}
	string line;
	while(getline(fin,line)){
		if((int)line.length()!=CamXSize){
			cerr << Path << " not consistent with cam X size" << endl;
			exit(1);
		}
		deadCam.push_back(line);
	}
	if((int)deadCam.size()!=CamYSize){
		cerr << Path << " not consistent with cam Y size" << endl;
		exit(1);
	}
	fin.close();
}

void Camera::ReadDeadCams(){
	ReadDeadCamList();
	for(int i=0;i<(int)deadCamList.size();i++){
		ReadDeadCam(deadCamList[i]);
		deadCams.push_back(deadCam);
		deadCam.clear();
	}
}

void Camera::WriteDeadCam(int i){
	deadCam = deadCams[i];
	for(int i=0;i<CamYSize;i++){
		for(int j=0;j<CamXSize;j++){
			if(!OutOfCamera(j,i)){
				if(deadCam[i][j]!=' '){
					cam[i][j] = deadCam[i][j];
				}
			}
		}
	}
	for(int i=0;i<CamYSize;i++){
		for(int j=0;j<CamXSize;j++){
			if(!OutOfCamera(j,i)){
				if(deadCam[i][j]!=' '){
					fgColorCam[i][j] = 'm';
				}
			}
		}
	}
}

void Camera::WriteOneRandomDeadCam(){
	srand(time(NULL));
	int numOfDeadCam = deadCams.size();
	int randNum = rand();
	randNum = randNum % numOfDeadCam;
	WriteDeadCam(randNum);
}


void Camera::WriteObject(vector<string> pic, int pos_x, int pos_y, int size_x, int size_y){
	for(int i=0;i<size_y;i++){
		for(int j=0;j<size_x;j++){
			if(!OutOfCamera(pos_x+j,pos_y+i)){
				if(pic[i][j]!=' '){
					cam[pos_y+i][pos_x+j] = pic[i][j];
				}
			}
		}
	}
}

void Camera::WriteObject(string message, int pos_x, int pos_y){
	for(int i=0;i<(int)message.length();i++){
		if(!OutOfCamera(pos_x+i,pos_y)){
			cam[pos_y][pos_x+i] = message[i];
		}
	}

}

void Camera::WriteColor(string message, int pos_x, int pos_y, char color){
	for(int i=0;i<(int)message.length();i++){
		if(!OutOfCamera(pos_x+i,pos_y)){
			fgColorCam[pos_y][pos_x+i] = color;
		}
	}
}



void Camera::EdgeBlockFollowDeathPlayer(Layer layer, Layer fgColorLayer, Player player){
	int pixel_x_pos;
	int pixel_y_pos;
	y_pos = player.deathXPos - center_y_offset;
	x_pos = player.deathYPos - center_x_offset;
	if(x_pos<0){
		x_pos = 0;
	}
	else if(x_pos>layer.LayerXSize-CamXSize){
		x_pos = layer.LayerXSize - CamXSize;
	}
	if(y_pos<0){
		y_pos = 0;
	}
	else if(y_pos>layer.LayerYSize-CamYSize){
		y_pos = layer.LayerYSize - CamYSize;
	}
	for(int i=1;i<CamYSize-1;i++){
		for(int j=1;j<CamXSize-1;j++){
			pixel_x_pos = x_pos + j;
			pixel_y_pos = y_pos + i;
			if(!layer.OutOfLayer(pixel_x_pos,pixel_y_pos)){
				try{
					cam[i][j] = layer.layer[pixel_y_pos][pixel_x_pos];
					fgColorCam[i][j] = fgColorLayer.layer[pixel_y_pos][pixel_x_pos];
				}
				catch(int num){
					cout << pixel_y_pos << ' ' << pixel_x_pos << endl;
					perror("im confused");
				}
			}
			else{
				cam[i][j] = '*';
			}
		}
	}

}


void Camera::EdgeCenterFollowPlayer(Layer layer, Layer fgColorLayer, Player player){
	int pixelX;
	int pixelY;

	// x_pos = player.int_x_pos - center_x_offset;
	// y_pos = player.int_y_pos - center_y_offset;

	// move
	if (toCenter && center_y_offset > target) {
		int thisDeviation = round(accDeviation+mvSpd) - round(accDeviation);
		accDeviation += mvSpd;
		// center_y_offset += (center_y_offset+thisDeviation >= target)? thisDeviation: target-center_y_offset;
		if (center_y_offset+thisDeviation >= target) {
			center_y_offset += thisDeviation;
		}
		else {
			center_y_offset = target;
		}
	}
	else if (!toCenter && center_y_offset < target) {
		int thisDeviation = round(accDeviation+mvSpd) - round(accDeviation);
		accDeviation += mvSpd;
		// center_y_offset += (center_y_offset+thisDeviation <= target)? thisDeviation: target-center_y_offset;
		if (center_y_offset+thisDeviation <= target) {
			center_y_offset += thisDeviation;
		}
		else {
			center_y_offset = target;
		}
	}

	if (center_y_offset == target) {
		if (maxDeviation < 0 && accDeviation < maxDeviation) {
			accDeviation = maxDeviation;
		}
		else if (maxDeviation > 0 && accDeviation > maxDeviation) {
			accDeviation = maxDeviation;
		}
		else if (maxDeviation == 0) {
			accDeviation = 0;
		}
	}

	x_pos = player.int_x_pos - center_x_offset;
	y_pos = player.int_y_pos - center_y_offset;

	if (x_pos < 0) {
		x_pos = 0;
	}
	else if (x_pos > layer.LayerXSize-CamXSize) {
		x_pos = layer.LayerXSize-CamXSize;
	}

	if (y_pos < 0) {
		y_pos = 0;
	}
	else if (y_pos > layer.LayerYSize-CamYSize) {
		y_pos = layer.LayerYSize-CamYSize-round(accDeviation);
	}
	// else if (y_pos > layer.LayerYSize+abs(maxDeviation)-CamYSize) { y_pos = layer.LayerYSize+abs(maxDeviation)-CamYSize; }
	// else if (y_pos > layer.LayerYSize-CamYSize+(28-target) ) { y_pos = layer.LayerYSize-CamYSize + round(accDeviation); }

	for (int i = 1; i < CamYSize-1; i++) {
		for (int j = 1; j < CamXSize-1; j++) {
			pixelX = x_pos + j;
			pixelY = y_pos + i;

			if (!layer.OutOfLayer(pixelX, pixelY)) {
				try {
					cam[i][j] = layer.layer[pixelY][pixelX];
					fgColorCam[i][j] = fgColorLayer.layer[pixelY][pixelX];
				}
				catch (int num) {
					cout << '(' << pixelY << ", " << pixelX << ')' << endl;
					perror("im confused");
				}
			}

			else {
				cam[i][j] = '%';
				fgColorCam[i][j] = 'w';
			}
		}
	}
}


void Camera::moveToCenter(bool cen, float spd, int tgt) {
	toCenter = cen;
	int trt = tgt;

	if (trt >= 40 || trt <= 3) {
		// trt = (cen)? 20: 28;
		if (cen) {
			trt = 20;
		}
		else {
			trt = 28;
		}
	}

	if (spd == 0) {
		spd = 1.0;
	}

	if (target != trt) {
		target = trt;
		maxDeviation = target - center_y_offset + accDeviation; // int? !!! //accDeviation;
	}

	if (center_y_offset > target) {
		// mvSpd = (spd<0)? spd: -spd;
		if (spd < 0) {
			mvSpd = spd;
		}
		else {
			mvSpd = -spd;
		}
	}
	else if (center_y_offset < target) {
		// mvSpd = (spd>0)? spd: -spd;
		if (spd > 0) {
			mvSpd = spd;
		}
		else {
			mvSpd = -spd;
		}
	}
}

