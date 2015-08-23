#pragma once


#include <iostream>
#include "My_Sprite.h"

#include <stdlib.h>
#include <time.h>

#define NBCASE 5
#define NBLIGNE 10

using namespace std;





class Box
{
private:
	int _contenu;//0= vide   1=un obstacle physique  2=personnage
    int _pattern;
	int _light;
    My_Sprite m_sprite;
public:
	/************************            Constructeur Destructeur          *****************************/

    Box();
	Box(int contenu);
	Box(const Box&);
	~Box(){};


	/************************            get set                           *****************************/
	int   getPattern()const;
	void  setPattern(int Pattern);

	int   getContenu()const;
	void  setContenu(int contenu);

	int  getLight()const;
	void  setLight(int light);



	/************************            fonction                          *****************************/
	void afficher();


	/************************            operator                          *****************************/
	Box operator = (const Box& original);




	friend bool operator==(const Box& left, const Box& right);
	friend bool operator!=(const Box& left, const Box& right);



	friend class Level;

};


Box* creationType();


