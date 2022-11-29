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

		void ReadConversation(string FullConversationPath);
		Talk ReadTalk(string TalkPathName);
		void SearchTalk(string TalkName);

		// 1 means normal update, 0 means no update, -1 means end talk
		int UpdateConv(char Input);

		void DisplayConv();
		void PrintConv();
		void PrintAllConv();

		int ListenUpdateContent();

};

#endif
