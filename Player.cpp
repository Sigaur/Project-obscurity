#include "Player.h"

Player::Player()
	: m_posY(3)
	, m_posX(0.1)
	, m_energy(100)
{

}

void Player::draw(float y, float x)
{
	
}

float Player::getPosY()
{
	return m_posY;
}

float Player::getPosX()
{
	return m_posX;
}