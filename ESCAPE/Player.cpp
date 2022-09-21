#include "Player.h"
#include "Utils.h"

void Player::Init()
{
	this->_pos_x = 0;
	this->_pos_y = 0;
	this->_goal_x = 0;
	this->_goal_y = 0;
	this->_direction = UP;
	this->_eyeSight = 3;

	return;
}