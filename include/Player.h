#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>

#include "My_Sprite.h"



enum State
{
	MOVING,
	LIGHT,
	SMASHED,
	DASH,
	VANISH,
    INVINCIBILITY
};

using namespace sf;

using namespace std;

class Player
{
public:
    Player(RenderWindow *app, View *view1);
	float getPosY();
	float getPosX();
    void draw(float y, float x);
    void draw();
	int update(float secTime, int difficulter);
	void moveDown();
	void moveUp();
	void moveRight(float move);
	void moveLeft(float move);
	void setMovable(int set);
	int isMovable();
	int isLight();
	void setLight(int set);
	int getEnergy();
	int getDashCost();
	void dash();
	int getVanishCost();
	void vanish();
	State playerState;
	int isFDReady();
	int isVAReady();
	int isINReady();
	int isEtheral();
	void setEtheral(int set);
	void gainEnergy(int gain);
	void resetPosition();
    void resetplayer();
    void m_FDReduceCost(int value);
    void m_FDReduceCooldown(float value);
    void m_FDIncreaseDistance(int value);
    void m_VAReduceCost(int value);
    void m_VAReduceCooldown(float value);
    void m_VAIncreaseDistance(int value);

private:

    vector<My_Sprite> player_sprite;
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite cooldown_sprite;
    My_Sprite dash_sprite;
    My_Sprite invincibility_sprite;
    My_Sprite vanish_sprite;

    sf::SoundBuffer dash_buffer;
    sf::Sound dash_sound;

	float m_posY;
	float m_posX;
	float m_energy;
	int m_isMovable;
	int m_isLight;
	float m_totalLight;	

	//////////Upgrades/////////////
	///Survival///
	int m_LALvl;
	int m_SRLvl;

	///DASH///
    int m_FDIsUnlocked;
    int m_FDCostLvl;
	float m_FDCoolDownLvl;
	float m_FDDistanceLvl;
	float m_FDCurrentDist;
	float m_FDCurrentCoolDown;
	

	///Vanishing///
	int m_VAIsUnlocked;
	int m_VACostLvl;
	float m_VACoolDownLvl;
	float m_VADistanceLvl;
	float m_VACurrentDist;
	float m_VACurrentCoolDown;


	///Invincibility///
	int m_INIsUnlocked;
	int m_INCostLvl;
	float m_INCoolDownLvl;
	float m_INDistanceLvl;
	float m_INCurrentDist;
	float m_INCurrentCoolDown;


	int m_etheral;
};

