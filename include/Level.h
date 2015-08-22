#pragma once
#include "Box.h"




class Level
{
private:
	Box ** _carte;

public:

	/************************            Constructeur Destructeur          *****************************/
	Level();
	Level(const Level&);
	~Level();


	/************************            get set                           *****************************/
	void setBox(int y, int x, Box valeur);
	Box getBox(int y, int x);

	void setMap(Box**);
	Box**  getMap();


	/************************            fonction                          *****************************/


	friend Level * generationMap(int difficulter);


	/************************            operator                          *****************************/



	friend class Box;



};





void affichage_Level(Level* leniveau);