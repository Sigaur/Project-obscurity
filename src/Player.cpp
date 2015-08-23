#include "Player.h"

Player::Player(RenderWindow *app, View *view1)
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
	, m_FDDistanceLvl(1)
	, m_FDCurrentDist(1)
	, m_FDCurrentCoolDown(0)

	, m_VAIsUnlocked(1)
	, m_VACostLvl(20)
	, m_VACoolDownLvl(5)
	, m_VADistanceLvl(10)
	, m_VACurrentDist(1)
	, m_VACurrentCoolDown(0)

	, m_INIsUnlocked(0)
	, m_INCostLvl(0)
	, m_INCoolDownLvl(0)
	, m_INDistanceLvl(0)
	, m_INCurrentDist(0)
	, m_INCurrentCoolDown(0)

	, playerState(MOVING)
	, m_etheral(0)

{
    m_view1 = view1;
    m_app = app;
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_moving.png", m_view1,  248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_light.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_smashed.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_dash.png", m_view1, 248, 5, 1.0f });

}

void Player::draw(float y, float x)
{
}


void Player::draw()
{
    if (playerState == MOVING)
    {
        player_sprite[0].draw((m_posX * 248 - 20), m_posY * 216);
    }
    else  if (playerState == LIGHT)
    {
        player_sprite[1].draw((m_posX * 248 - 20), m_posY * 216);
    }
    else  if (playerState == SMASHED)
    {
        player_sprite[2].draw((m_posX * 248 - 20), m_posY * 216);
    }
    else  if (playerState == DASH)
    {
        player_sprite[3].draw((m_posX * 248 - 20), m_posY * 216);
    }
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
	cout << "Light ->" << set << endl;
	m_isLight = set;
}

int Player::update(float secTime)
{	
	int retour = 0;
	//cout << m_energy << "    " << m_totalLight<< endl;
	if (m_isLight)
	{
		cout << "LUMIERE!!!!" << endl;
		playerState = LIGHT;
		m_totalLight += secTime;
		while (m_totalLight > m_LALvl + 0.1)
		{
			m_totalLight -= 0.1;
			m_energy--;
		}
	}
	else
	{
		playerState = MOVING;
		if (m_totalLight != 0.0)
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
	
	if (m_FDCurrentDist < m_FDDistanceLvl)
	{
		m_FDCurrentDist += 0.1;
		//moveRight(0.1);
		retour = 1;
	}
	else if (playerState == DASH)
	{
		playerState = MOVING;
	}

	if (m_VACurrentDist < m_VADistanceLvl)
	{
		m_VACurrentDist += 0.1;
		retour = 2;
	}
	else if (playerState == VANISH)
	{
		playerState = MOVING;
	}

	return retour;
}

void Player::moveRight(float move)
{
	m_posX += move;
}

void Player::moveLeft(float move)
{
	m_posX -= move;
}

int Player::getEnergy()
{
	return m_energy;
}

int Player::getDashCost()
{
	return m_FDCostLvl;
}

void Player::dash()
{
	m_energy -= m_FDCostLvl;
	m_FDCurrentDist = 0.0;
	playerState = DASH;
}

int Player::getVanishCost()
{
	return m_VACostLvl;
}

void Player::vanish()
{
	m_energy -= m_VACostLvl;
	m_VACurrentDist = 0.0;
	playerState = VANISH;
	m_etheral = 1;
}