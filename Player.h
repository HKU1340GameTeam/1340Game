// player.h

#ifndef _player_h
#define _player_h

#include "common.h"
#include <vector>
#include "Layer.h"
using namespace std;

class Player{
	public:
		// the velocity is speed plus direction of the movement
		vec velocity;
		// position is the left top corner's position of the figure
		vec position;
		// speed is how fast the player moves
		vec speed;

		// horizontal speed of the player after jump
		float autoMoveSpeed;

		// int_?_pos is the integer position of the player
		int int_x_pos;
		int int_y_pos;

		// Jump control
		bool standingOnGround = false;
		bool jumpActivated = false;
		bool justLanded = false;

		// figure is the player's appearance
		vector<vector<char>> figure={{' ','O',' '},
						             {'/','|','\\'},
						             {'/',' ','\\'}};
		// figure foreground color
		vector<vector<char>> figure_fg_color={{' ','y',' '},
											  {'y','y','y'},
											  {'y',' ','y'}};
		// figure background color (which is not implemented yet)
		//vector<vector<char>> figure_bg_color={{' ','n',' '},
									 //{'n','n','n'},
									 //{'n',' ','n'}};
		// how close the position is to the margins of the body of the player
		const int ceilMarginOffset=0;
		const int floorMarginOffset=2;
		const int leftMarginOffset=0;
		const int rightMarginOffset=2;

		// Move Control
		char leftMove = 'q'; // constant left move
		char rightMove = 'e'; // constant right move
		char lmove='a'; // left move
		char rmove='d'; // right move
		char standMove = 'w'; // let the player stop
		char jump = ' '; // space for jump
		char emptyMove = 'p'; // move that means nothing

		// Raycast Related
		char raycast_x_ignore = 'p';// p for platform

		// Since only one input can be read at a time, it is impossible to enable features like, going forward while
		// jumping, so a compensation is made below, by recording previous inputs and activating hidden move when you
		// type lmove/rmove and immediately press jump, that will enable a moving jump
		// Previous Input
		char prvInput='p';
		char hiddenMove='p';
		// p represents 'nothing'
		

		// Time counter(used for calculating time to refresh hidden move)
		float TimeToRefreshAutoMoveInSecond_Time_Counter = 0.0;
		const float TimeToRefreshAutoMoveInSecond = 0.25;
		char AutoMoveLabel;


		// Constructor
        Player(float vX,float vY,float posX,float posY,float spX,float spY, float auto_Move_Speed);

		// Position Control
		int UpdatePosition(char Input,Layer PhyLayer);
		void CorrectPosition(int new_x_pos,int new_y_pos,Layer PhyLayer);
		void StandingOnGround(Layer PhyLayer);
		bool PlayerOutOfLayer(int x_pos,int y_pos,Layer Layer);

		// Input Control
		void toggleHiddenMove(char Input);
		void InputToVelocity(char Input);
		bool TimeToRereshAutoMove(char Input);

		// Raycast
		int Raycast(char direction,Layer PhyLayer);
		int raycast(int x,int y,char direction,Layer PhyLayer);


};

#endif
