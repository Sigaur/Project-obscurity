#include "Player.h"

Player::Player()
	: m_posY(3)
	, m_posX(1)
	, m_energy(100)
	, m_isMovable(1)
	, m_isLight(0)
	, m_LALvl(1.0)
	, m_SRLvl(0)
	
	, m_FDIsUnlocked(1)
	, m_FDCostLvl(20)
	, m_FDCoolDownLvl(5)
	, m_FDDistanceLvl(0)
	, m_FDCurrentDist(0)
	, m_FDCurrentCoolDown(0)

	, m_VAIsUnlocked(0)
	, m_VACostLvl(0)
	, m_VACoolDownLvl(0)
	, m_VADistanceLvl(0)
	, m_VACurrentDist(0)
	, m_VACurrentCoolDown(0)
	
	, m_INIsUnlocked(0)
	, m_INCostLvl(0)
	, m_INCoolDownLvl(0)
	, m_INDistanceLvl(0)
	, m_INCurrentDist(0)
	, m_INCurrentCoolDown(0)
	
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

void Player::update(float secTime)
{	
	//cout << m_energy << "    " << m_totalLight<< endl;
	if (m_isLight)
	{
		m_totalLight += secTime;
		while (m_totalLight > m_LALvl + 0.1)
		{
			m_totalLight -= 0.1;
			m_energy--;
		}
	}
	else if (m_totalLight != 0.0)
	{
		if (m_totalLight > 0.0)
		{
			m_totalLight -= secTime;
		}
		if (m_totalLight < 0.0)
		{
			m_totalLight = 0.0;
		}
	}
}

void Player::moveRight(float move)
{
	m_posX += move;
}

void Player::moveLeft(float move)
{
	m_posX -= move;
}