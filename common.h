// common.h


#ifndef _common_h
#define _common_h

struct vec{
	float x;
	float y;
};


// the time for refresh(in e-6 seconds)
//const float deltaTime = 50000;
const float deltaTime = 33334;
// used to adjust refresh time
const float refreshOffset = 10000;
// the time in second for refreshing
const float deltaSecond = deltaTime/1000000;
// the thing that's 9.81 in real life
const float g = 90.0;

// died interval time (in seconds)
const float diedWaitTime = 2.5;
const float deathWaitTime = 7.5;


// used to control where cursor goes
void gotoxy(int x,int y);

#endif
