// Player.cpp

#include "common.h"
#include "Player.h"
#include "Layer.h"
#include "AboveHeadComment.h"
#include <iostream>
#include <cmath>
using namespace std;


Player::Player(float vX,float vY,float posX,float posY,float spX,float spY,float auto_Move_Speed, string FullCommentPath){
	velocity.x=vX;
	velocity.y=vY;
	position.x=posX;
	position.y=posY;
	speed.x=spX;
	speed.y=spY;
	int_x_pos = position.x;
	int_y_pos = position.y;

	autoMoveSpeed = auto_Move_Speed;
	abc = AboveHeadComment(int_x_pos, int_y_pos, FullCommentPath);
}


void Player::toggleHiddenMove(char Input){


	// enable break of automatic movement
	if(hiddenMove == leftMove){
		if(Input == rmove || Input == standMove || Input==rightMove || Input==lmove){
			hiddenMove = emptyMove;
		}
	}

	// enable break of automatic movement
	if(hiddenMove == rightMove){
		if(Input == lmove || Input == standMove || Input==leftMove || Input==rmove){
			hiddenMove = emptyMove;
		}
	}

	// enable jumping while moving horizontally
	if(Input==jump){
		if(prvInput == lmove && prvInput == AutoMoveLabel && justLanded==false){
			hiddenMove = leftMove;
		}
		else if(prvInput == rmove && prvInput == AutoMoveLabel && justLanded==false){
			hiddenMove = rightMove;
		}
	}
}
int Player::InputToVelocity(char Input){

	jumpActivated = false;

	toggleHiddenMove(Input);

	dashIndicator = DashTimeEnd();
	if(dashIndicator != -1){
		if(dashIndicator == 1){
			if(facing == 1){
				velocity.x = dashSpeed;
			}
			else{
				velocity.x = -dashSpeed;
			}
			velocity.y = 0;
			TimeToRereshAutoMove(Input);
			return 2;
		}
		else{
			dashing = false;
		}
	}
	else{
		if(Input == dash && dashNumAvailable > 0){
			dashing = true;
			dashNumAvailable--;
			if(facing == 1){
				velocity.x = dashSpeed;
			}
			else{
				velocity.x = -dashSpeed;
			}
			velocity.y = 0;
			TimeToRereshAutoMove(Input);
			return 2;
		}
	}
	if(Input == jump){
		if(standingOnGround==true){
			velocity.y = -speed.y;
			standingOnGround = false;
			jumpActivated = true;
		}
		else{
			if(jumpAvailable > 0){
				jumpAvailable --;
				velocity.y = -speed.y;
				standingOnGround = false;
				jumpActivated = true;
			}
		}
	}
	else if(Input==leftMove || Input==lmove){
		facing = -1;
		justLanded = false;
		if(prvInput==rightMove || prvInput==leftMove){
			velocity.x = 0;
		}
		else{
			velocity.x = -autoMoveSpeed;
		}
	}
	else if(Input==rightMove || Input==rmove){
		facing = 1;
		justLanded = false;
		if(prvInput==leftMove || prvInput==rightMove){
			velocity.x = 0;
		}
		else{
			velocity.x = autoMoveSpeed;
		}
	}
	else if(Input == standMove){
		justLanded = false;
		velocity.x = 0;
	}
	else if(Input!=rightMove && Input!=leftMove && (prvInput==lmove || prvInput==rmove)){
		velocity.x = 0;
	}

	TimeToRereshAutoMove(Input);

	// calculate hiddenMove (moves horizontally while player is in air)
	if(hiddenMove==leftMove){
		velocity.x = -autoMoveSpeed;
	}
	else if(hiddenMove==rightMove){
		velocity.x = autoMoveSpeed;
	}
	return 1;
	
}

void Player::CorrectPosition(int new_x_pos,int new_y_pos,Layer PhyLayer){
	int distanceToGround=Raycast('j',PhyLayer)-1;
	int distanceToCeil=Raycast('k',PhyLayer)-1;
	int distanceToLeft=Raycast('h',PhyLayer)-1;
	int distanceToRight=Raycast('l',PhyLayer)-1;
	int delta_y = new_y_pos - int_y_pos;
	int delta_x = new_x_pos - int_x_pos;

	//if(PlayerOutOfLayer(new_x_pos,new_y_pos,PhyLayer)){
		//new_x_pos = int_x_pos;
		//position.x = int_x_pos;
	//}
	//int_x_pos += delta_x;
	
	// X direction raycast
	if(delta_x < 0 && -delta_x >= distanceToLeft){
		delta_x = -distanceToLeft;
		velocity.x = 0;
		int_x_pos += delta_x;
		position.x = int_x_pos;
	}
	else if(delta_x > 0 && delta_x >= distanceToRight){
		delta_x = distanceToRight;
		velocity.x = 0;
		int_x_pos += delta_x;
		position.x = int_x_pos;

	}
	else{
		int_x_pos += delta_x;
	}
	// Y direction raycast
	if(delta_y >= distanceToGround && velocity.y >= 0){

		if(velocity.y != 0){
			justLanded = true;
		}
		delta_y = distanceToGround;
		velocity.y = 0;
		standingOnGround=true;

		int_y_pos += delta_y;

		position.y = int_y_pos;

		hiddenMove = emptyMove;

		jumpAvailable = extraJump;

		dashNumAvailable = dashNum;
	}
	else if(-delta_y >= distanceToCeil && velocity.y <= 0){

		delta_y = -distanceToCeil;

		velocity.y = 0;

		int_y_pos += delta_y;

		position.y = int_y_pos;
	}
	else{
		int_y_pos += delta_y;
	}
}


int Player::UpdatePosition(char Input,Layer PhyLayer){
	StandingOnGround(PhyLayer);

	InputToVelocity(Input);

	// update velocity Y
	if(standingOnGround==false && jumpActivated==false && dashing == false){
		velocity.y += g * deltaSecond;
	}

	position.x+=velocity.x * deltaSecond;
	position.y+=velocity.y * deltaSecond;

	int new_y_pos = round(position.y);
	int new_x_pos = round(position.x);

	CorrectPosition(new_x_pos,new_y_pos,PhyLayer);



	if(prvInput==rightMove && Input==rightMove){
		prvInput=standMove;
	}
	else if(prvInput==leftMove && Input==leftMove){
		prvInput=standMove;
	}
	//else if(Input==' ' && prvInput==leftMove){
		//prvInput=lmove;
	//}
	//else if(Input==' ' && prvInput==rightMove){
		//prvInput=rmove;
	//}
	else if(Input == leftMove || Input == rightMove || Input == standMove || Input == lmove || Input == rmove){
		prvInput=Input;
		AutoMoveLabel=Input;
	}


	return 0;
}


bool Player::TimeToRereshAutoMove(char Input){
	if(Input==AutoMoveLabel || Input==emptyMove){
		TimeToRefreshAutoMoveInSecond_Time_Counter+=deltaSecond;
		if(TimeToRefreshAutoMoveInSecond_Time_Counter >= TimeToRefreshAutoMoveInSecond){
			TimeToRefreshAutoMoveInSecond_Time_Counter = 0.0;
			AutoMoveLabel = emptyMove;
			return true;
		}
		else{
			return false;
		}
	}
	else{
		TimeToRefreshAutoMoveInSecond_Time_Counter = 0.0;
		AutoMoveLabel=emptyMove;
		return false;
	}
}

// 1 for dashing, 0 for dash time end, -1 for not dashing
int Player::DashTimeEnd(){
	if(dashing == true){
		dashingTime += deltaSecond;
		if(dashingTime >= dashLastTime){
			dashingTime = 0;
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		return -1;
	}
}


int Player::Raycast(char direction,Layer PhyLayer){
	int minimum = 1000;
	int x_pos=int_x_pos;
	int y_pos=int_y_pos;
	int reflection;
	if(direction == 'j'){
		y_pos+=floorMarginOffset;
		for(int i=x_pos+leftMarginOffset;i<x_pos+rightMarginOffset+1;i++){
			reflection = raycast(i,y_pos,direction,PhyLayer);
			if(reflection<minimum){
				minimum = reflection;
			}
		}
		
	}
	else if(direction == 'k'){
		y_pos+=ceilMarginOffset;
		for(int i=x_pos+leftMarginOffset;i<x_pos+rightMarginOffset+1;i++){
			reflection = raycast(i,y_pos,direction,PhyLayer);
			if(reflection<minimum){
				minimum = reflection;
			}
		}
		
	}
	else if(direction == 'l'){
		x_pos+=rightMarginOffset;
		for(int i=y_pos+ceilMarginOffset;i<y_pos+floorMarginOffset+1;i++){
			reflection = raycast(x_pos,i,direction,PhyLayer);
			if(reflection<minimum){
				minimum = reflection;
			}
		}
	}
	else if(direction == 'h'){
		x_pos+=leftMarginOffset;
		for(int i=y_pos+ceilMarginOffset;i<y_pos+floorMarginOffset+1;i++){
			reflection = raycast(x_pos,i,direction,PhyLayer);
			if(reflection<minimum){
				minimum = reflection;
			}
		}
	}
	return minimum;
}

int Player::raycast(int x,int y,char direction,Layer PhyLayer){
	int counter = 0;
	bool found = false;
	if(direction=='j'){
		while(!found){
			y+=1;
			if(PhyLayer.layer[y][x]!=' ' || PhyLayer.OutOfLayer(x,y)){
				found=true;
			}
			counter+=1;
		}
	}
	else if(direction=='k'){
		while(!found){
			y-=1;
			if((PhyLayer.layer[y][x]!=' ' && PhyLayer.layer[y][x]!=raycast_x_ignore) || PhyLayer.OutOfLayer(x,y)){
				found=true;
			}
			counter+=1;
		}
	}
	else if(direction=='h'){
		while(!found){
			x-=1;
			if(PhyLayer.OutOfLayer(x,y)){
				found=true;
			}
			else if(PhyLayer.layer[y][x]!=' ' && PhyLayer.layer[y][x]!=raycast_x_ignore){
				found=true;
			}
			counter+=1;
		}
	}
	else if(direction=='l'){
		while(!found){
			x+=1;
			if(PhyLayer.OutOfLayer(x,y)){
				found=true;
			}
			else if(PhyLayer.layer[y][x]!=' ' && PhyLayer.layer[y][x]!=raycast_x_ignore){
				found=true;
			}
			counter+=1;
		}
	}
	return counter;
}

void Player::StandingOnGround(Layer PhyLayer){
	if(Raycast('j',PhyLayer)==1){
		standingOnGround=true;
	}
	else{
		standingOnGround=false;
	}
}

		const int ceilMarginOffset=0;
		const int floorMarginOffset=2;
		const int leftMarginOffset=0;
		const int rightMarginOffset=2;

bool Player::PlayerOutOfLayer(int x_pos,int y_pos,Layer PhyLayer){
	if(PhyLayer.OutOfLayer(x_pos+ceilMarginOffset,y_pos) ||
	   PhyLayer.OutOfLayer(x_pos+floorMarginOffset,y_pos) ||
	   PhyLayer.OutOfLayer(x_pos,y_pos+leftMarginOffset) ||
	   PhyLayer.OutOfLayer(x_pos,y_pos+rightMarginOffset)){
		return true;
	}
	else{
		return false;
	}

}


void Player::UpdateFigure(){
	if(dashing == true){
		if(facing == 1){
			figure = rightDashFigure;
			figure_fg_color = rightDashFigure_fg_color;
		}
		else{
			figure = leftDashFigure;
			figure_fg_color = leftDashFigure_fg_color;
		}
	}
	else if(velocity.y < 0){
		if(velocity.x == 0){
			figure = jumpFigure;
			figure_fg_color = jumpFigure_fg_color;
		}
		else if(facing == 1){
			figure = rightJumpFigure;
			figure_fg_color = rightJumpFigure_fg_color;
		}
		else if(facing == -1){
			figure = leftJumpFigure;
			figure_fg_color = leftJumpFigure_fg_color;
		}
	}
	else{
		figure = normalFigure;
		figure_fg_color = normalFigure_fg_color;
	}
}


void Player::PrintAboveHeadComment(vector<string> trigger, Layer &scene2Layer){
	if(trigger[int_y_pos][int_x_pos]!=' ' && trigger[int_y_pos][int_x_pos]!='*'){
		abc.currentCommentIndex = 0;
		abc.objectPositionX = int_x_pos;
		abc.objectPositionY = int_y_pos;
		abc.PrintComment(scene2Layer);
	}
}




