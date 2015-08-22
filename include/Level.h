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
<<<<<<< HEAD
	void setBox		(int y, int x, Box valeur);
	void setBoxInt	(int y, int x, int contenu);
	void setBoxLight(int y, int x, int light);

	Box getBox		(int y, int x);
	int getBoxint	(int y, int x);
	int getBoxLight	(int y, int x);

    
=======
	void setBox(int y, int x, Box valeur);
	Box getBox(int y, int x);
	int getBoxint(int y, int x);
    void afficher_box(int valeur, int x_get, int y_get);
>>>>>>> 3d038c233d792f1d9d4cc7dc3db6a5cea85b62f5
    void setMap(Box**);
	Box**  getMap();


	/************************            fonction                          *****************************/
		void afficher_box(int valeur);

	friend Level * generationMap(RenderWindow *app, View *view1, int difficulter);


	/************************            operator                          *****************************/



	friend class Box;



};


int* randomplace();
int random();

void affichage_Level(Level* leniveau);
void affichage_Level_light(Level* leLevel);

