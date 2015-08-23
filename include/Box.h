#pragma once


#include <iostream>
#include "My_Sprite.h"

#include <stdlib.h>
#include <time.h>

#define NBCASE 5
#define NBLIGNE 10
#define NBTYPE 3
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
	int setX(int Y);
	int setY(int X);
	int setBackground(int Background);
	int setObject(int Object);
	int setMob(int Mob);
	int setLight(int Light);

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


