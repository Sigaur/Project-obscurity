#include "..\include\Level.h"

/************************            Constructeur Destructeur          ************************/
Level::Level(RenderWindow *app, View *view1)
{
    int i = 0;
    m_view1 = view1;
    m_app = app;

	_carte = new Box*[NBLIGNE];
	for ( i = 0; i < NBLIGNE; i++)
	{
        _carte[i] = new Box[NBCASE];
	}
    m_sprites.push_back(m_app, "resources/desk", m_view1, 3);
    m_sprites.push_back(m_app, "resources/desk", m_view1, 3);
    m_sprites.push_back(m_app, "resources/desk", m_view1, 3);

}

Level::~Level()
{
	int i = 0;
	for ( i = 0; i < NBLIGNE; i++)
		{
			delete _carte[i];
		}

	delete _carte;

}

/************************            get set                           *****************************/

void Level::setMap(Box** arg){ _carte = arg; }
Box**  Level::getMap(){ return _carte; }



void Level::setBox(int y, int x, Box valeur){ _carte[y][x] = valeur; }
Box  Level::getBox(int y, int x){ return _carte[y][x]; }

/************************            fonction                          *****************************/

void Level::afficher_box(int valeur)
{
    m_sprites[valeur].draw_tile(500, 500, 1);
}


/************************            operator                          *****************************/




/************************            hors class                          *****************************/

void affichage_Level(Level* leLevel)
{
	cout << endl;
	int i,j;
	for (i = 0; i<NBLIGNE; i++)
	{
		for (j = 0; j<NBCASE; j++)
		{
			afficher_box(leLevel->getBox(i, j));



		}

		cout << endl;

	}
	cout << endl;
}





