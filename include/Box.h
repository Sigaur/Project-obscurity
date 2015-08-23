#pragma once


#include <iostream>
#include "My_Sprite.h"

#include <stdlib.h>
#include <time.h>



using namespace std;





class Box
{
/*private:
	int _contenu;//0= vide   1=un obstacle physique  2=personnage
    int _pattern;
	int _light;
    My_Sprite m_sprite;
public:
	/************************            Constructeur Destructeur          *****************************/
	/*
    Box();
	Box(int contenu);
	Box(const Box&);
	~Box(){};


	/************************            get set                           *****************************/
	/*int   getPattern()const;
	void  setPattern(int Pattern);

	int   getContenu()const;
	void  setContenu(int contenu);

	int  getLight()const;
	void  setLight(int light);



	/************************            fonction                          *****************************/
	void afficher();


	/************************            operator                          *****************************/
	/*Box operator = (const Box& original);




	friend bool operator==(const Box& left, const Box& right);
	friend bool operator!=(const Box& left, const Box& right);



	friend class Level;*/

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

private:
	int m_X;
	int m_Y;
	int m_background;
	int m_object;
	int m_mob;
	int m_light;
};
/*
void afficher_box(Box Box);
Box* creationType();*/


