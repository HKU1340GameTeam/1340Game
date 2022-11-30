// ConvBox.cpp

#include "common.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Layer.h"
#include "Camera.h"
#include "ConvBox.h"
#include "Conversation.h"
using namespace std;

ConvBox::ConvBox(){
}

void ConvBox::ResetConvBox(){
	convBox = originalConvBox;
}

void ConvBox::ReadConvBox(){
	ifstream fin;
	fin.open(ConvBoxPath);
	if(fin.fail()){
		cerr << "ConvBox fail to open file" << ConvBoxPath << endl;
		exit(1);
	}

	string line;
	ConvBoxYSize = 1;
	getline(fin,line);
	originalConvBox.push_back(line);
	convBox.push_back(line);
	ConvBoxXSize = line.size();
	while(getline(fin,line)){
		if((int)line.length()!=ConvBoxXSize){
			cerr << "ConvBox X direction size not consistent" << endl;
			exit(1);
		}
		originalConvBox.push_back(line);
		convBox.push_back(line);
		ConvBoxYSize ++;
	}
	fin.close();
}
void ConvBox::ReadConvBoxColor(){
	ifstream fin;
	fin.open(ConvBoxColorPath);
	if(fin.fail()){
		cerr << "ConvBox fail to open file" << ConvBoxPath << endl;
		exit(1);
	}

	string line;
	ConvBoxYSize = 1;
	getline(fin,line);
	originalConvBoxColor.push_back(line);
	convBoxColor.push_back(line);
	ConvBoxXSize = line.size();
	while(getline(fin,line)){
		if((int)line.length()!=ConvBoxXSize){
			cerr << "ConvBox X direction size not consistent" << endl;
			exit(1);
		}
		originalConvBoxColor.push_back(line);
		convBoxColor.push_back(line);
		ConvBoxYSize ++;
	}
	fin.close();
}

void ConvBox::WriteConvToBox(Conversation conv){
	if(conv.currentTalk.category=='l'){
		for(int i=0;i<(int)conv.currentContent.length();i++){
			if(i+initialWritePosX < ConvBoxXSize){
				convBox[initialWritePosY][i+initialWritePosX] = conv.currentContent[i];
			}
		}
	}
	else if(conv.currentTalk.category=='c'){
		WritePosY = initialWritePosY - ((int)conv.currentTalk.talkContent.size()/2);
		if(WritePosY < 1){
			cerr << "In ConvBox, since choice to many, out of ConvBox. Above" << endl;
			exit(1);
		}
		for(int j = 0;j<(int)conv.currentTalk.talkContent.size();j++){
			WritePosY++;
			if(WritePosY > ConvBoxYSize){
				cerr << "In ConvBox, since choice to many, out of ConvBox. Below" << endl;
				exit(1);
			}
			for(int i=0;i<(int)conv.currentTalk.talkContent[j].length();i++){
				convBox[WritePosY][i+initialWritePosX] = conv.currentTalk.talkContent[j][i];
			}
		}
		WritePosY = initialWritePosY;
	}
	else{
		for(int i=0;i<(int)conv.currentContent.length();i++){
			if(i+initialWritePosX < ConvBoxXSize){
				convBox[initialWritePosY][i+initialWritePosX] = conv.currentContent[i];
			}
		}
	}

}

void ConvBox::WriteBoxToCam(Camera &cam){
	for(int i=0;i<ConvBoxYSize;i++){
		for(int j=0;j<ConvBoxXSize;j++){
			//if(!cam.OutOfCamera(boxPosX+j,boxPosY+i)){
			cam.cam[boxPosY+i][boxPosX+j] = convBox[i][j];
			cam.fgColorCam[boxPosY+i][boxPosX+j] = convBoxColor[i][j];
			//}
		}
	}
}

void ConvBox::WriteNameToBox(string name){
	for(int i=0;i<(int)name.length();i++){
		if(i+nameWritePosX < ConvBoxXSize){
			convBox[nameWritePosY][i+nameWritePosX] = name[i];
		}
	}
}








