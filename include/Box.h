#pragma once


#include <iostream>
#include "My_Sprite.h"

#include <stdlib.h>
#include <time.h>



using namespace std;





class Box
{
void afficher();



public:
	Box();
	Box(int Y, int X, int Background, int Object, int Mob, int Light);
	int getX();
	int getY();
	int getBackground();
	int getObject();
	int getMob();
	int getLight();
	void setX(int Y);
	void setY(int X);
	void setBackground(int Background);
	void setObject(int Object);
	void setMob(int Mob);
	void setLight(int Light);
	void reset();
	void setMajoriter(int Y, int X, int Background, int Object, int Mob);
	void setMajoriter(int Y, int X, int Background, int Object, int Mob, int light);

private:
	int m_X;
	int m_Y;
	int m_background;
	int m_object;
	int m_mob;
	int m_light;
};


