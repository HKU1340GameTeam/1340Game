// Conversation.h

#ifndef _conversation_h
#define _conversation_h

#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Talk.h"
using namespace std;

class Conversation{
	public:
		Conversation();
		Conversation(string FullConversationPath);

		vector<Talk> conv;

		Talk currentTalk;
		string currentContent;
		int conversationSize;

		// Read conversation from text file
		// All related conversation will be read
		void ReadConversation(string FullConversationPath);
		Talk ReadTalk(string TalkPathName);
		// Search for the next talk when this talk end
		// next talk's information are stored after the talk content
		void SearchTalk(string TalkName);

		// 1 means normal update, 0 means no update, -1 means end talk
		int UpdateConv(char Input);

		// Output conversation to scree
		void DisplayConv();
		void PrintConv();
		void PrintAllConv();

		// check for the next talk (see if end or switch to next talk);
		int ListenUpdateContent();

};

#endif
