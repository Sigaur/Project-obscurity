#include "..\include\Level.h"

/************************            Constructeur Destructeur          ************************/
Level::Level()
{
	int i = 0;

	_carte = new Box*[NBLIGNE];
	for ( i = 0; i < NBLIGNE; i++)
	{
		_carte[i] = new Box[NBCASE];
	}


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
Level * generationMap(int difficulter)
{
	srand(time(0));

	Box* Type = creationType();
	Level* Map = new Level;


	
	int tampon=0;

	for (int i = 0; i < NBLIGNE; i++)
	{
		for (int j = 0; j < NBCASE; j++)
		{
			if (i == 0)
					{ tampon = 0; }//premiere colonne tous est vide

			
			//else if (Map[i - 1][j] != Type[0])			{ tampon = 0; }
			else if (i % 3  == 0){ tampon = 0; }
			else if (i % 7  == 0 && difficulter<4){ tampon = 0; }
			else if (i % 11 == 0 && difficulter<3){tampon = 0; }
			else if (i % 13 == 0 && difficulter<2){ tampon = 0; }
			else if (i % 14 == 0 && difficulter<1){ tampon = 0; }
			
			else
			{
				if (rand() % 2 == 0)
					{
						tampon = rand() % (NBTYPE + 1);
					}
				else
					{
						tampon = rand() % 2;
					}

			}

		
			cout << tampon;


			Map->setBox(i, j, Type[tampon].getContenu());

		}
		cout << endl;
	}




	return Map;
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




