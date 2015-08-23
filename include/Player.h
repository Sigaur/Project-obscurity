#include <SFML/Graphics.hpp>
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
	VANISH
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
    int update(float secTime);
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
	State playerState;

private:

    vector<My_Sprite> player_sprite;
    View *m_view1;
    RenderWindow *m_app;

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
};