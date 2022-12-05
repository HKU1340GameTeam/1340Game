// AboveHeadComment.cpp
#include "common.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Layer.h"
#include "AboveHeadComment.h"
using namespace std;

// Please refers to AboveHeadComment.h for documentation

AboveHeadComment::AboveHeadComment(){
}
AboveHeadComment::AboveHeadComment(int PosX, int PosY, string FullPath){
	objectPositionX = PosX;
	objectPositionY = PosY;
	ReadComments(FullPath);
}

void AboveHeadComment::ReadComments(string FullPath){
	ifstream fin;
	fin.open(FullPath);
	if (fin.fail()) {
		cerr << "Cannot Open AboveHeadComment file<" << FullPath << ">; Reason: failed opening file.";
		exit(1);
	}

	string ln;
	while (getline(fin, ln)) {
		comments.push_back(ln);
		if(getline(fin,ln)){
			istringstream iss(ln);
			int x, y;
			iss >> x >> y;
			leftOffsets.push_back(x);
			upOffsets.push_back(y);
		}
		else{
			cerr << "Above Head Comment File Format Not Correct" << FullPath << endl;
			exit(1);
		}
	}
	fin.close();

}

void AboveHeadComment::PrintComment(Layer &layer){
	for(int chrIdx = 0;chrIdx<(int)comments[currentCommentIndex].length();chrIdx++){
		//cout << objectPositionX << endl;
		//cout << objectPositionY << endl;
		//cout << leftOffsets[currentCommentIndex] << endl;
		//cout << upOffsets[currentCommentIndex] << endl;
		//cout << chrIdx << endl;
		if(!layer.OutOfLayer(objectPositionX-leftOffsets[currentCommentIndex]+chrIdx,objectPositionY-upOffsets[currentCommentIndex])){
			layer.layer[objectPositionY-upOffsets[currentCommentIndex]][objectPositionX-leftOffsets[currentCommentIndex]+chrIdx] = comments[currentCommentIndex][chrIdx];
			//cout << comments[currentCommentIndex][chrIdx] << endl;
		}
	}
}
