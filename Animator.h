// Animator.h

#ifndef _animator_h
#define _animator_h

#include "common.h"
#include <vector>
#include<string>
#include "common.h"
#include "Layer.h"
using namespace std;

class Animator{
	public:

		// Initialize animator
		Animator(int PosX, int PosY, float updateInterval, char Color);
		Animator();

		string AnimatorInfoFile = "Player/Animator.txt";
		float AnimatorSpeedUp;
		vector<vector<string>> video;
		vector<vector<string>> videoColor;
		vector<string> currentFrame;
		vector<string> currentFrameColor;

		int videoSize;
		int frameIndex = 0;
		int frameCounter = 0;

		float updateTime = 0.5;
		float accumulatedTime = 0;

		int frameXSize = -1;
		int frameYSize = -1;
		int posX;
		int posY;

		char color;

		// Read video from .txt file;
		// Frames are sparated by line of *s;
		void ReadVideo(string FullPathName);

		// Add color (if provided) to pixel of each frame;
		void ConvertColor();

		// Update frame index  to point to the next frame;
		void UpdateFrame();

		// Load the current frame; (clear the last fram, load the new one)
		void LoadFrame();

		//void WriteFrame(Layer &layer);
		
};

#endif
