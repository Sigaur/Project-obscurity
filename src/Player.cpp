#include "Player.h"

Player::Player(RenderWindow *app, View *view1)
	: m_posY(3)
	, m_posX(1)
	, m_energy(100)
	, m_isMovable(1)
	, m_isLight(0)
	, m_LALvl(0.1)
	, m_SRLvl(0)

	, m_FDIsUnlocked(1)
	, m_FDCostLvl(20)
	, m_FDCoolDownLvl(10)
	, m_FDDistanceLvl(1)
	, m_FDCurrentDist(1)
	, m_FDCurrentCoolDown(10)

	, m_VAIsUnlocked(1)
	, m_VACostLvl(20)
	, m_VACoolDownLvl(10)
	, m_VADistanceLvl(10)
	, m_VACurrentDist(1)
	, m_VACurrentCoolDown(10)

	, m_INIsUnlocked(0)
	, m_INCostLvl(0)
	, m_INCoolDownLvl(30)
	, m_INDistanceLvl(0)
	, m_INCurrentDist(0)
	, m_INCurrentCoolDown(30)

	, playerState(MOVING)
	, m_etheral(0)
    , cooldown_sprite(app, "resources/cooldown.png", view1)
    , dash_sprite(app, "resources/dash.png", view1)
    , vanish_sprite(app, "resources/vanish.png", view1)
    , invincibility_sprite(app, "resources/invincibility.png", view1)
{
    m_view1 = view1;
    m_app = app;
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_moving.png", m_view1,  248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_light.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_smashed.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_dash.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_vanish.png", m_view1, 248, 5, 1.0f });
    player_sprite.push_back(My_Sprite{ m_app, "resources/player_invincibility.png", m_view1, 248, 5, 1.0f });

    dash_buffer.loadFromFile("resources/dash.ogg");

    dash_sound.setBuffer(dash_buffer);
}


void Player::resetplayer(){
	m_posY = 3;
	m_posX = 1;
	m_energy = 100;
	m_isMovable = 1;
	m_isLight = 0;
	m_LALvl = 0.1;
	m_SRLvl = 0;

	m_FDIsUnlocked = 1;
	m_FDCostLvl = 10;
	m_FDCoolDownLvl = 10;
	m_FDDistanceLvl = 1;
	m_FDCurrentDist = 1;
	m_FDCurrentCoolDown = 10;

	m_VAIsUnlocked = 1;
	m_VACostLvl = 10;
	m_VACoolDownLvl = 10;
	m_VADistanceLvl = 10;
	m_VACurrentDist = 1;
	m_VACurrentCoolDown = 10;

	m_INIsUnlocked = 0;
	m_INCostLvl = 0;
	m_INCoolDownLvl = 30;
	m_INDistanceLvl = 0;
	m_INCurrentDist = 0;
	m_INCurrentCoolDown = 30;

	playerState = MOVING;
	m_etheral = 0;

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
    else  if (playerState == VANISH)
    {
        player_sprite[4].draw((m_posX * 248 - 20), m_posY * 216);
    }
    else  if (playerState == INVINCIBILITY)
    {
        player_sprite[5].draw((m_posX * 248 - 20), m_posY * 216);
    }

    //

    dash_sprite.draw(500, 0);
    if (!isFDReady() ) 
    {
        cooldown_sprite.draw(500, 0);

    }


    vanish_sprite.draw(500 + invincibility_sprite.get_w(), 0);
    if (!isVAReady())
    {
        cooldown_sprite.draw(500 + invincibility_sprite.get_w(), 0);
    }

    invincibility_sprite.draw(500 + invincibility_sprite.get_w() * 2, 0);
    if (!isINReady())
    {
        cooldown_sprite.draw(500 + invincibility_sprite.get_w() * 2, 0);
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
			m_energy-=2;
		}
	}
	else
	{
		if (playerState == LIGHT)
		{
			playerState = MOVING;
		}
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

	if (m_FDCurrentCoolDown < m_FDCoolDownLvl)
	{
		m_FDCurrentCoolDown += secTime;
	}
	if (m_VACurrentCoolDown < m_VACoolDownLvl)
	{
		m_VACurrentCoolDown += secTime;
	}
	if (m_INCurrentCoolDown < m_INCoolDownLvl)
	{
		m_INCurrentCoolDown += secTime;
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
	m_FDCurrentCoolDown = 0.0;
	playerState = DASH;
    dash_sound.play();
}

int Player::getVanishCost()
{
	return m_VACostLvl;
}

void Player::vanish()
{
	m_energy -= m_VACostLvl;
	m_VACurrentDist = 0.0;
	m_VACurrentCoolDown = 0.0;
	playerState = VANISH;
	m_etheral = 1;
}

int Player::isFDReady()
{
	if (m_FDCurrentCoolDown >= m_FDCoolDownLvl)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Player::isVAReady()
{
	if (m_VACurrentCoolDown >= m_VACoolDownLvl)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Player::isINReady()
{
	if (m_INCurrentCoolDown >= m_INCoolDownLvl)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Player::isEtheral()
{
	return m_etheral;
}

void Player::setEtheral(int set)
{
	m_etheral = set;
}

void Player::gainEnergy(int gain)
{
	m_energy += gain;
}

void Player::resetPosition()
{

	m_posY = 3;
	m_posX=1;
	m_energy = 100;
	m_isMovable = 1;
	m_isLight = 0;
	m_LALvl = 0.1;
	m_SRLvl = 0;

}