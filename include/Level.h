#pragma once
#include "Box.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>



class Level
{
private:
    Box ** _carte;
    View *m_view1;
    RenderWindow *m_app;
    vector <My_Sprite> m_sprites;

public:

	/************************            Constructeur Destructeur          *****************************/
    Level(RenderWindow *app, View *view1);
	Level(const Level&);
	~Level();


	/************************            get set                           *****************************/
	void setBox(int y, int x, Box valeur);
	Box getBox(int y, int x);
	int getBoxint(int y, int x);
    void afficher_box(int valeur);
    void setMap(Box**);
	Box**  getMap();


	/************************            fonction                          *****************************/


	friend Level * generationMap(RenderWindow *app, View *view1, int difficulter);


	/************************            operator                          *****************************/



	friend class Box;



};


int* randomplace();
int random();

void affichage_Level(Level* leniveau);