// Animator.h

#ifndef _animator_h
#define __animator_h

#include "common.h"
#include <vector>
#include "Layer.h"
using namespace std;

class Animator{
	public:
		vector<vector<string>> video;
		vector<string> currentFrame;

		int frameCounter = 0;
		int updateTime = 0.5;
		

		void ReadVideo();
		void UpdateFrame();
		void WriteFrame(Layer layer);

		
};

#endif
