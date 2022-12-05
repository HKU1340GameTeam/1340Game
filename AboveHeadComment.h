// AboveHeadComment.h


#ifndef _aboveheadcomment_h
#define  _aboveheadcomment_h

#include "common.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Layer.h"
using namespace std;

class AboveHeadComment{
	public:

		AboveHeadComment();
		// Read comment and initialize member variable
		AboveHeadComment(int PosX, int PosY, string FullPath);

		vector<string> comments;
		vector<int> leftOffsets;
		vector<int> upOffsets;
		int currentCommentIndex = 0;
		int objectPositionX;
		int objectPositionY;

		// Put comment above NPC head
		void PrintComment(Layer &layer);
		// Read comment from txt file
		void ReadComments(string FullPath);

};




#endif
