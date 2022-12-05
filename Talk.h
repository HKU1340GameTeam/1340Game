// Talk.h

#ifndef _talk_h
#define _talk_h

#include <iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class Talk{
	public:
		Talk();
		Talk(string FullPathName);
		// c for choice, l for listen, or e for end
		char category;
		string talkName;

		// Vector that store all talk content
		vector<string> talkContent;
		// One string from talkContent
		string currentTalkContent;
		int talkContentSize;
		int currentContentIndex=0;

		vector<string> nextTalk;
		int choiceSize;

		// Read talk content from file
		void ReadTalk(string FullPathName);
		int UpdateTalkContent();

};

#endif
