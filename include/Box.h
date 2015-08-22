#pragma once


#include <iostream>
#include "My_Sprite.h"

#include <stdlib.h>
#include <time.h>

#define NBCASE 5
#define NBLIGNE 10
#define NBTYPE 5
using namespace std;





class Box
{
private:
	int _contenu;//0= vide   1=un obstacle physique  2=personnage
	bool light;

    My_Sprite m_sprite;
public:
	/************************            Constructeur Destructeur          *****************************/

    Box();
	Box(int contenu);
	Box(const Box&);
	~Box(){};


	/************************            get set                           *****************************/

	int   getContenu()const;
	void  setContenu(int contenu);





	/************************            fonction                          *****************************/
	


	/************************            operator                          *****************************/
	Box operator = (const Box& original);




	friend bool operator==(const Box& left, const Box& right);
	friend bool operator!=(const Box& left, const Box& right);



	friend class Level;

};

void afficher_box(Box Box);
Box* creationType();


