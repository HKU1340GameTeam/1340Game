// animator.cpp

#include "Animator.h"
#include<vector>
#include<string>
#include "Layer.h"
#include "common.h"
#include<iostream>
using namespace std;


Animator::Animator(int PosX, int PosY, float updateInterval){
	posX = PosX;
	posY = PosY;
	updateTime = updateInterval;
}

Animator::Animator(){
}

void Animator::ReadVideo(string FullPathName){
	ifstream fin;
	fin.open(FullPathName);
	if(frameXSize != -1){
		cerr << FullPathName << " already read a file" << endl;
		exit(1);
	}
	if(fin.fail()){
		cerr << FullPathName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	string separation;
	getline(fin,line);
	separation = line;
	frameXSize = line.size();
	int YsizeCount = 0;
	while(getline(fin,line)){
		if((int)line.size() != frameXSize){
			cerr << FullPathName << "frame X size not consistent" << endl;
			exit(1);
		}
		if(line != separation){
			currentFrame.push_back(line);
			YsizeCount++;
		}
		else{
			video.push_back(currentFrame);
			currentFrame.clear();
			if(frameYSize != -1){
				if(frameYSize != YsizeCount){
					cerr << FullPathName << "frame Y size not consistent" << endl;
					exit(1);
				}
			}
			else{
				frameYSize = YsizeCount;
			}
			YsizeCount = 0;
		}
	}
	videoSize = video.size();
	frameXSize-=1;
	currentFrame.clear();
	LoadFrame();
	fin.close();
}

void Animator::LoadFrame(){
	currentFrame.clear();
	for(int i=0;i<frameYSize;i++){
		currentFrame.push_back(video[frameIndex][i]);
	}
}
void Animator::UpdateFrame(){
	accumulatedTime += deltaSecond;
	if(accumulatedTime >= updateTime){
		accumulatedTime = 0;
		currentFrame.clear();
		frameIndex ++;
		if(frameIndex >= (videoSize)){
			frameIndex = 0;
		}
		LoadFrame();
	}
	
}
//void Animator::WriteFrame(Layer &layer){
	//layer.WriteObject(currentFrame,posX,posY,frameXSize,frameYSize);
//}

//void Layer::WriteObject(vector<vector<char>> pic, int pos_x, int pos_y, int size_x, int size_y){
	//for(int i=0;i<size_y;i++){
		//for(int j=0;j<size_x;j++){
			//if(!OutOfLayer(pos_x+j,pos_y+i)){
				//if(pic[i][j]!=' '){
					//layer[pos_y+i][pos_x+j] = pic[i][j];
				//}
			//}
		//}
	//}

//}



