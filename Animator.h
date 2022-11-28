// Animator.h

#ifndef _animator_h
#define __animator_h

#include "common.h"
#include <vector>
#include<string>
#include "common.h"
#include "Layer.h"
using namespace std;

class Animator{
	public:

		Animator(int PosX, int PosY);

		vector<vector<string>> video;
		vector<string> currentFrame;

		int videoSize;
		int frameIndex = 0;
		int frameCounter = 0;
		int updateTime = 0.5;
		int accumulatedTime = 0;
		int frameXSize = -1;
		int frameYSize = -1;
		int posX;
		int posY;

		void ReadVideo(string FullPathName);
		void UpdateFrame();
		void LoadFrame();
		//void WriteFrame(Layer &layer);
		
};

#endif
