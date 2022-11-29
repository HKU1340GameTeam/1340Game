// Conversation.cpp

#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Talk.h"
#include"Conversation.h"
using namespace std;

Conversation::Conversation(){

}

Conversation::Conversation(string FullConversationPath){
	ReadConversation(FullConversationPath);
}

Talk Conversation::ReadTalk(string TalkPathName){
	Talk talk = Talk(TalkPathName);
	return talk;
}

void Conversation::ReadConversation(string FullConversationPath){
	ifstream fin;
	fin.open(FullConversationPath);
	if(fin.fail()){
		cerr << FullConversationPath << " fail to open conversation" << endl;
		exit(1);
	}
	string line;
	while(getline(fin,line)){
		conv.push_back(ReadTalk(line));
	}
	conversationSize = conv.size();
	currentTalk = conv[0];
	currentContent = currentTalk.talkContent[0];
	fin.close();
}

void Conversation::SearchTalk(string TalkName){
	for(int i=0;i<conversationSize;i++){
		//cout << conv[i].talkName << endl;
		if(conv[i].talkName == TalkName){
			currentTalk = conv[i];
			currentContent = currentTalk.currentTalkContent;
			//cout << "currentContent found" << endl; 
			break;
		}
	}
}

// 1 means normal update, 0 means no update, -1 means end talk
int Conversation::UpdateConv(char Input){
	if(currentTalk.category=='l'){
		if(ListenUpdateContent()==1){
			return 1;
		}
		else{
			SearchTalk(currentTalk.nextTalk[0]);
			return 1;
		}
	}
	else if(currentTalk.category=='c'){
		int index = Input - '0';
		index --;
		//cout << "nextTalk index " << index << endl;
		if(index >= currentTalk.choiceSize || index < 0){
			//cout << "choiceSize" << currentTalk.choiceSize << endl;
			return 0;
		}
		else{
			//cout << currentTalk.nextTalk[index] << endl;
			SearchTalk(currentTalk.nextTalk[index]);
			if(currentTalk.category=='e'){
				return -1;
			}
			//cout << currentTalk.currentTalkContent << endl;
			return 1;
		}
	}
	else if(currentTalk.category=='e'){
		return -1;
	}
	else{
		cout << "no such category updating conversation" << endl;
		exit(1);
	}
}

// 1 for successful update, 0 for end of content, -1 for wrong type
int Conversation::ListenUpdateContent(){
	if(currentTalk.category=='l'){
		if(currentTalk.UpdateTalkContent()==0){
			return 0;
		}
		else{
			currentContent = currentTalk.currentTalkContent;
			return 1;
		}
	}
	else{
		return -1;
	}
}

void Conversation::DisplayConv(){
	if(currentTalk.category=='l'){
		cout << currentContent << endl;
	}
	if(currentTalk.category=='c'){
		for(int i=0;i<currentTalk.talkContentSize;i++){
			cout << currentTalk.talkContent[i] << endl;
		}
	}
	if(currentTalk.category=='e'){
		cout << "error displaying end Talk" << endl;
		exit(1);
	}
}

void Conversation::PrintConv(){
	for(int i=0;i<(int)currentTalk.talkContent.size();i++){
		cout << currentTalk.talkContent[i] << endl;
	}
	cout << "nextTalk:" << endl;
	for(int i=0;i<(int)currentTalk.nextTalk.size();i++){
		cout << currentTalk.nextTalk[i] << endl;
	}
}

void Conversation::PrintAllConv(){
	for(int i=0;i<(int)conv.size();i++){
		currentTalk = conv[i];
		PrintConv();
	}
}



