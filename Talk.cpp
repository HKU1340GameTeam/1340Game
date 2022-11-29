// Talk.cpp

#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Talk.h"
using namespace std;

Talk::Talk(string FullPathName){
	ReadTalk(FullPathName);
}

Talk::Talk(){

}


// First line is talk name
// Second line is 
void Talk::ReadTalk(string FullPathName){
	ifstream fin;
	fin.open(FullPathName);
	if(fin.fail()){
		cerr << FullPathName << "fail to open file" << endl;
		exit(1);
	}
	string line;
	getline(fin,line);
	talkName = line;
	getline(fin,line);
	if(line=="listen"){
		category='l';
	}
	else if(line=="choice"){
		category='c';
	}
	else if(line=="end"){
		category='e';
	}
	else{
		cerr << FullPathName << "Talk category doesn't exist" << endl;
		exit(1);
	}
	getline(fin,line);
	if(line != "TalkStarts"){
		cerr << FullPathName << "Talk file format error" << endl;
		exit(1);
	}
	while(getline(fin,line)){
		if(line=="TalkEnds"){
			break;
		}
		talkContent.push_back(line);
	}
	talkContentSize = talkContent.size();
	if(line!="TalkEnds"){
		cerr << FullPathName << "Talk file format error" << endl;
		exit(1);
	}
	getline(fin,line);
	if(line!="NextTalk"){
		cerr << FullPathName << "Talk file format error" << endl;
		exit(1);
	}
	while(getline(fin,line)){
		if(line=="NextTalkEnds"){
			break;
		}
		nextTalk.push_back(line);

	}
	choiceSize = nextTalk.size();
	if(line!="NextTalkEnds"){
		cerr << FullPathName << "Talk file format error" << endl;
		exit(1);
	}
	if(category=='c'){
		if(choiceSize!=(talkContentSize-1)){
			cerr << FullPathName << "talkContentSize need to be one less than choiceSize" << endl;
			exit(1);
		}
	}
	else if(category=='l'){
		if(choiceSize!=1){
			cerr << FullPathName << "choiceSize need to be 1 for listen" << endl;
			exit(1);
		}
	}
	else if(category=='e'){
	}
	else{
		cerr << FullPathName << "Talk read program error" << endl;
		exit(1);
	}
	currentTalkContent = talkContent[0];

	fin.close();

}


// 1 for successful update, 0 for end of talk content, -1 for choice or end
int Talk::UpdateTalkContent(){
	if(category=='l'){
		if(talkContentSize-1<=currentContentIndex){
			return 0;
		}
		else{
			currentContentIndex ++;
			currentTalkContent = talkContent[currentContentIndex];
			return 1;
		}
	}
	else{
		return -1;
	}

}








