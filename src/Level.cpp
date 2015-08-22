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



	m_sprites.push_back(My_Sprite{ m_app, "resources/desk", m_view1, });
	m_sprites.push_back(My_Sprite{ m_app, "resources/desk", m_view1, });
	m_sprites.push_back(My_Sprite{ m_app, "resources/desk", m_view1, });
	
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


int Level::getBoxint(int y, int x){ return _carte[y][x].getContenu(); }

/************************            fonction                          *****************************/


Level * generationMap(RenderWindow *app, View *view1, int difficulter)
{
	srand((int)time(NULL));

	Box* Type = creationType();


	Level* Map = new Level(app,view1);


	
	int mob,caillou,obstacle;
	int *ordre=NULL;
	int tampon;
	

	for (int i = 0; i < NBLIGNE; i++)
	{


		ordre = randomplace();
		obstacle = rand() % (NBCASE - 1);
		caillou = rand() % (obstacle + 1);
		mob = obstacle - caillou;


		for (int j = 0; j < NBCASE; j++)

		{
			if (i == 0)
			{
				tampon = 0;
			}//premiere colonne tous est vide
			if (i % (difficulter + 4) == 0)
			{
				tampon = 0;
			}//premiere colonne tous est vide
			//else if (Map->getBox(i-1,j)!= Type[0])	{ tampon = 0; }




			else
			{
				if (caillou > 0)
				{
					Map->setBox(i, ordre[j], Type[1].getContenu());
					caillou--;
				}
				else if (mob > 0)
				{
					//on definie un mob de la liste de mob definie
					Map->setBox(i, ordre[j], Type[2 + random() % (NBTYPE - 2)].getContenu());
					mob--;
				}
				else
				{//par defaut on met du vide sinon
					Map->setBox(i, ordre[j], Type[0].getContenu());
				}
				//la premiere ligne est vide
				if (i == 0)
					Map->setBox(i, j, Type[0].getContenu());

			}


			//delete ordre;
		}

		//verification de securiter
		for (int i = 0; i < NBLIGNE; i++)
		{





			if (Map->getBoxint(i, 0) == 0 && Map->getBoxint(i, 1) == 1 && Map->getBoxint(i + 1, 0) == 1)
			{
				if (rand() % 2 == 0)
				{
					Map->setBox(i, 1, Type[0].getContenu());
				}
				else
				{
					Map->setBox(i + 1, 0, Type[0].getContenu());
				}
			}

			if (Map->getBoxint(i, 4) == 0 && Map->getBoxint(i, 3) != 0 && Map->getBoxint(i + 1, 4) != 0)
			{
				if (rand() % 2 == 0)
				{
					Map->setBox(i, 3, Type[0].getContenu());
				}
				else
				{
					Map->setBox(i + 1, 4, Type[0].getContenu());
				}
			}



		}

	}



	return Map;
}

int* randomplace()
{

	int max = 4, min = 0;
	
	//genere aleatoirement la suite de 0 a 4
	int j = 4;
	int tampon;
	int *lign=new int[NBCASE];
	
	for (int i = 0; i < NBCASE; i++)
		{
			lign[i] = 0;
		}


	do{
	
		tampon =rand() % (NBCASE + 1 );
	

		if (lign[tampon] == 0)
			{
				lign[tampon] = j; j--;

				if (tampon >= max){ max = tampon - 1; }
				if (tampon <= min){ min = tampon + 1; }

			}
	

	
		} while (j > 0);

	return lign;
}





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
			afficher_box(leLevel->getBox(i, j).getContenu() );


		}

		cout << endl;

	}
	cout << endl;
}

int random()
{
	return (int)time(0);
}



