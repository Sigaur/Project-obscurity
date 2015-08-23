#include "..\include\Level.h"

/************************            Constructeur Destructeur          ************************/
Level::Level(RenderWindow *app, View *view1)
{

    int i = 0;
    m_view1 = view1;
    m_app = app;

	_carte = new Box*[NBLIGNE];
	for ( i = 0; i < NBLIGNE; i++)
		{ _carte[i] = new Box[NBCASE];}


    for (int i = 0; i < 11; i++)
    {
        string path = "resources/obstacle" + std::to_string(i) + ".png";
        m_sprites.push_back(My_Sprite{ m_app, path, m_view1 });
    }
	
	
}

Level::~Level()
{
	int i = 0;
	for ( i = 0; i < NBLIGNE; i++)
		{delete _carte[i];}

	delete _carte;
}

/************************            get set                           *****************************/

void Level::setMap(Box** arg){ _carte = arg; }
Box**  Level::getMap()const{ return _carte; }



void Level::setBox(int y, int x, Box valeur){ _carte[y][x] = valeur; }
Box  Level::getBox(int y, int x)const
{ 	if ((y >= 0 && y < NBLIGNE) && (x >= 0 && x < NBCASE))
		{return _carte[y][x];}	return NULL; 
}



void Level::setBoxInt(int y, int x, int contenu)
{_carte[y][x].setContenu(contenu);}

void Level::setBoxLight(int y, int x, int light)
{	_carte[y][x].setLight(light);}


void Level::setBoxPattern(int y, int x, int Pattern)
{ _carte[y][x].setPattern(Pattern); }


int Level::getBoxint(int y, int x)const
{ if ((y >= 0 && y < NBLIGNE) && (x>=0 && x<NBCASE))
	{return _carte[y][x].getContenu();}
	return 0;
}
int Level::getBoxLight(int y, int x)const
{
	if ((y >= 0 && y < NBLIGNE) && (x >= 0 && x<NBCASE))
	{return _carte[y][x].getLight();}

	return 0;
}

int Level::getBoxPattern(int y, int x)const{
	if ((y >= 0 && y < NBLIGNE) && (x >= 0 && x < NBCASE))
	{return _carte[y][x].getPattern();	}
	return 0;
}

/************************            fonction                          *****************************/


Level * generationMap(RenderWindow *app, View *view1, int difficulter)
{
	Level* Map = new Level(app,view1);

	int mob,caillou,obstacle;
	int *ordre=NULL;

	for (int i = 0; i < NBLIGNE; i++)
	{
		ordre = randomplace();
		obstacle = rand() % (NBCASE - 1);
		caillou = rand() % (obstacle + 1);
		mob = obstacle - caillou;

		for (int j = 0; j < NBCASE; j++)
		{		if (caillou > 0)
					{
						Map->setBoxInt(i, ordre[j], 1);
						caillou--;
					}
				else if (mob > 0)
					{	//on definie un mob de la liste de mob definie
						//Map->setBox(i, ordre[j], Type[1 + random() % (NBTYPE - 2)]);
						Map->setBoxInt(i, ordre[j], 2);//a modif si plusieur type de mob
						mob--;
					}
				else
					{//par defaut on met du vide sinon
						Map->setBoxInt(i, ordre[j], 0);
					}
				//la premiere ligne est vide
				if (i == 0)
					{Map->setBoxInt(i, j, 0);}
			}
	
			delete ordre;
		}

		//verification de securiter
		for (int i = 0; i < NBLIGNE; i++)
		{

			if (Map->getBoxint(i, 0) == 0 && Map->getBoxint(i, 1) == 1 && Map->getBoxint(i + 1, 0) == 1)
			{
				if (rand() % 2 == 0)
				{
					Map->setBoxInt(i, 1, 0);
				}
				else
				{
					Map->setBoxInt(i + 1, 0, 0);
				}
			}

			if (Map->getBoxint(i, 4) == 0 && Map->getBoxint(i, 3) != 0 && Map->getBoxint(i + 1, 4) != 0)
			{
				if (rand() % 2 == 0)
				{
					Map->setBoxInt(i, 3, 0);
				}
				else
				{
					Map->setBoxInt(i + 1, 4, 0);
				}
			}
			
		}
		
//--------------------------------------------------------------------------------------------------
// affichage lumiere

	
		for (int i = 1; i < NBLIGNE; i++)
			{	for (int j = 0; j < NBCASE; j++)
				{
					if (Map->getBoxint(i+1,j)>1)//si il ya un mob = on eclaire
					{
						Map->setBoxLight(i,j,1); 
					}
				else
					{
						Map->setBoxLight(i, j,0);//valeu 2>0 a mettre
					}
				
					if (Map->getBoxint(i, j)==0)//case vide
						{Map->setBoxPattern(i, j,0);}
					else if (Map->getBoxint(i, j) == 1)
						{Map->setBoxPattern(i, j, 1);}
					else
						{Map->setBoxPattern(i, j, 2+rand()%9);}
						

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





void Level::afficher_box(int valeur, int x_get, int y_get)
{
	m_sprites[valeur].draw(x_get * 248, y_get * 216);
	 //  cout << "x_get " << x_get << " y_get" << y_get << " box valeur  " << valeur << endl;
}
		

/************************            operator                          *****************************/




/************************            hors class                          *****************************/

void affichage_Level(Level* leLevel)
{
	//cout << endl;
	int i,j;
	for (i = 0; i<NBLIGNE; i++)
	{
		for (j = 0; j<NBCASE; j++)
		{
			leLevel->afficher_box(leLevel->getBox(i, j).getPattern(), i, j);
			/*
			cout << leLevel->getBox(i, j).getContenu();
			//leLevel->afficher_box(leLevel->getBox(i, j).getPattern(), i, j);
			leLevel->afficher_box(2,i,j);*/
		}

		cout << endl;
	}
	cout << endl;
}

void affichage_Level_light(Level* leLevel)
{
	cout << endl;
	int i, j;
	for (i = 0; i<NBLIGNE; i++)
	{
		for (j = 0; j<NBCASE; j++)
		{
			cout << leLevel->getBox(i, j).getLight();
			//afficher_box(leLevel->getBoxLight(i, j));
			leLevel->afficher_box(1, i, j);
		}
		cout << endl;
	}
	cout << endl;
}
void affichage_Level_patern(Level* leLevel)
{
	cout << endl;
	int i, j;
	for (i = 0; i<NBLIGNE; i++)
	{
		for (j = 0; j<NBCASE; j++)
		{
			cout << leLevel->getBox(i, j).getPattern();
			//afficher_box(leLevel->getBoxPattern(i, j));
			leLevel->afficher_box(1, i, j);
		}
		cout << endl;
	}
	cout << endl;
}



int random()
{return (int)time(0);}



