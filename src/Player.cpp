#include "Player.h"

Player::Player()
	: m_posY(3)
	, m_posX(0)
	, m_energy(100)
	, m_isMovable(1)
	, m_isLight(0)
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

void Player::moveUp()
{
	if ((m_posY > 0) && (m_isMovable))
	{
		//if position est libre......
		{
			m_posY--;
		}
	}
}

void Player::moveDown()
{
	if ((m_posY < 4) && (m_isMovable))
	{
		//if position est libre......
		{
			m_posY++;
		}
	}
}

void Player::setMovable(int set)
{
	m_isMovable = set;
}

int Player::isMovable()
{
	return m_isMovable;
}

int Player::isLight()
{
	return m_isLight;
}

void Player::setLight(int set)
{
	m_isLight = set;
}