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

		// facing 1 for right, -1 for left
		int facing = 0;

		// Jump control
		bool standingOnGround = false;
		bool jumpActivated = false;
		bool justLanded = false;
		int extraJump = 1;
		int jumpAvailable = extraJump;

		// dash control
		bool dashing = false;
		float dashLastTime = 0.25;
		float dashingTime = 0.0;
		float dashSpeed = 100.0;
		int dashIndicator;// 1 for dashing, 0 for end of dash, -1 for not dashing

		// figure is the player's appearance
		vector<string> figure={{" 0 "},
						       {"/|\\"},
						       {"/ \\"}};
		// figure foreground color
		vector<string> figure_fg_color={{" y "},
										{"yyy"},
										{"y y"}};
		// Normal Figure
		vector<string> normalFigure={{" 0 "},
						       {"/|\\"},
						       {"/ \\"}};
		// Normal Figure foreground color
		vector<string> normalFigure_fg_color={{" y "},
										{"yyy"},
										{"y y"}};
		// right dash figure
		vector<string> rightDashFigure={{"--0"},
										{"-/ "},
										{"-/>"}};
		// right dash figure color
		vector<string> rightDashFigure_fg_color={{"yyy"},
												 {"yy "},
												 {"yyy"}};
		// left dash figure
		vector<string> leftDashFigure={{"0--"},
									   {" \\-"},
									   {"<\\-"}};
		// left dash figure color
		vector<string> leftDashFigure_fg_color={{"yyy"},
												{" yy"},
												{"yyy"}};
		// jump figure
		vector<string> jumpFigure={{"\\0/"},
								   {" | "},
								   {"/ \\"}};
		// jump figure color
		vector<string> jumpFigure_fg_color={{"yyy"},
											{" y "},
											{"y y"}};
		// right jump figure
		vector<string> rightJumpFigure={{" 0/"},
										{"/| "},
										{"/ >"}};
		// right jump figure color
		vector<string> rightJumpFigure_fg_color={{" yy"},
											{"yy "},
											{"y y"}};
		// left jump figure
		vector<string> leftJumpFigure={{"\\0 "},
										{" |\\"},
										{"< \\"}};
		// left jump figure color
		vector<string> leftJumpFigure_fg_color={{"yy "},
												{" yy"},
												{"y y"}};

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
		char leftMove = 'o'; // constant left move
		char rightMove = '['; // constant right move
		char lmove='l'; // left move
		char rmove='\''; // right move
		char standMove = ';'; // let the player stop
		char jump = '3'; // space for jump
		char emptyMove = 'p'; // move that means nothing
		char dash = ' ';

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
		const float TimeToRefreshAutoMoveInSecond = 0.3;
		char AutoMoveLabel;

		// DashControl
		int DashTimeEnd();

		// Constructor
        Player(float vX,float vY,float posX,float posY,float spX,float spY, float auto_Move_Speed);

		// Position Control
		int UpdatePosition(char Input,Layer PhyLayer);
		void CorrectPosition(int new_x_pos,int new_y_pos,Layer PhyLayer);
		void StandingOnGround(Layer PhyLayer);
		bool PlayerOutOfLayer(int x_pos,int y_pos,Layer Layer);

		// Input Control
		void toggleHiddenMove(char Input);
		int InputToVelocity(char Input);
		bool TimeToRereshAutoMove(char Input);

		// Raycast
		int Raycast(char direction,Layer PhyLayer);
		int raycast(int x,int y,char direction,Layer PhyLayer);

		// Figure Update
		void UpdateFigure();

};

#endif
