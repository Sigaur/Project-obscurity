#include "Game_Manager.h"





Game_Manager::Game_Manager(RenderWindow *app, View &view1, View &view2, int screen_x, int screen_y)
	: m_view1(view1)
	, menu1(app, &m_view2)
	, m_grid(GRID_WIDTH, GRID_HEIGHT, &m_view1, app)
	, selection_sprite(app, "resources/selection.png", &m_view1)
	, light_bar(app, "resources/light_bar.png", &m_view1)
	, light_bar_background(app, "resources/light_bar_background.png", &m_view1)
	, light_bar_grad(app, "resources/light_bar_grad.png", &m_view1)
	, mob_sprite(app, "resources/opponent0.png", &m_view1)
	, interface1(app, m_grid, &m_view2, screen_x, screen_y)
	, m_info(app, &view1, 1920, 1080)
	//////////
	, myPlayer(app, &m_view1)
	, m_view2(view2)
	, world_sprite(app, "resources/test.png", &m_view1)
	, _difficulter(0)
{
    is_menu_visible = true;
    is_info = false;
    m_mouse_over_actions = false;
    m_screen_x = screen_x;
    m_screen_y = screen_y;
    x_offset = 0;
    y_offset = 0;

    energy_text.init(app, "100", 50, 1);
	difficulter_text.init(app, "1", 50, 1);

    m_app = app;
    m_app->setView(m_view1);

    window_vec = m_app->getSize();
    cout << "x_window" << window_vec.x << "y_window " << window_vec.y << endl;

    m_view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(m_screen_x), static_cast<float>(m_screen_y)));
    m_view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    Vector2f vecsize = m_view1.getSize();
    m_h = static_cast<int>(vecsize.y);
    m_w = static_cast<int>(vecsize.x);

	
	for (int i = 0; i < 14; i++)
    {
        string path = "resources/obstacle" + std::to_string(i) + ".png";
        m_box_sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
    }
  
      for (int i = 0; i < 3; i++)
      {
          string path = "resources/background" + std::to_string(i) + ".png";
          m_box_background.push_back(My_Sprite{ m_app, path, &m_view1 });
      }
      
          for (int i = 0; i < 3; i++)
          {
              string path = "resources/light" + std::to_string(i) + ".png";
              m_light_sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
          }



    for (int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("resources/font2.ttf");
    }


    if (!music.openFromFile("resources/music.ogg"))
    {
        cout << "music init failed" << endl;
    }
    music.setLoop(true);

    music.play();

}

void Game_Manager::execute_action(Action action)
{
	
	int posXPla = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4;
	
	int posYpla = myPlayer.getPosY();
	float hitLimit = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4 - posXPla;
	
	

    switch (action)
	{
    case ACT_GO_UP:
		if (myPlayer.getPosY() > 0)
		{
			if (((Map[posYpla - 1][posXPla + 1].getObject() == 0) && (Map[posYpla - 1][posXPla].getObject() == 0))
				|| ((Map[posYpla - 1][posXPla + 1].getObject() == 0) && (hitLimit > 0.75))
				|| (myPlayer.playerState == VANISH))
			{
				myPlayer.moveUp();
			}
		}
        break;
	case ACT_FRONT_DASH:		
		if ((myPlayer.getEnergy() - myPlayer.getDashCost() >= 0) && (myPlayer.isFDReady()))
		{
			myPlayer.dash();
		}
		break;
	case ACT_VANISH:
		if ((myPlayer.getEnergy() - myPlayer.getVanishCost() >= 0) && (myPlayer.isVAReady()))
		{
			myPlayer.vanish();
		}
		break;
    case ACT_GO_RIGHT:
		if (((myPlayer.getPosX() < 1000) && (Map[posYpla][posXPla + 1].getObject() == 0)) || (myPlayer.playerState == VANISH))
		{
			myPlayer.moveRight(0.1);
		}
        break;
    case ACT_GO_DOWN:
		if (myPlayer.getPosY() < 4)
		{
			if (((Map[posYpla + 1][posXPla + 1].getObject() == 0) && (Map[posYpla + 1][posXPla].getObject() == 0))
				|| ((Map[posYpla + 1][posXPla + 1].getObject() == 0) && ((hitLimit > 0.75) /*|| (hitLimit < 0.05)*/))
				||  (myPlayer.playerState == VANISH))
			{
				myPlayer.moveDown();
			}
		}
        break;
    case ACT_GO_LEFT:
		myPlayer.playerState = SMASHED;
		if (myPlayer.getPosX() > 0)
		{
			myPlayer.moveLeft(248.0/3000.0);//5 = SPEED/////////////////////////////////////
		}
		else
		{
			cout << endl << " Game over" << endl;
			execute_action(ACT_RESTART_APP);///////////////////GAME OVER MENU

		}
        break;
    case ACT_ZOOM_IN:
        break;
    case ACT_ZOOM_OUT:
        break;
    case ACT_CLOSE_APP:
        cout << "close app\n";
        m_app->close();

        break;
	case ACT_RESTART_APP:

		cout << "restart app remettre view1 et reset\n";
		//temporaire
		ChoixDifficulter(_difficulter-2);
		myPlayer.resetplayer();
		actualisationNiveau(MAXX + 1);

		//Pause();


		//m_app->close();

		break;
    default:
        break;
    }
}


bool Game_Manager::handle_input_events()
{
    Event event;
    bool isEvent = m_app->pollEvent(event);
    Action action;
    sf::Mouse::Button click = {};
    Vector2i mouse_vec;

    key_event.get_mouse_position(m_app, mouse_vec);


bool ret = false;
if (isEvent)
{
    if (key_event.manage_key_event(event, action))
    {
        execute_action(action);
        ret = true;
    }
    if (key_event.manage_mouse_click(event, click)) {
        if (!open_window) {
            handle_mouse_click(click, mouse_vec);
        }
        ret = true;
    }
}
return ret;
}

void Game_Manager::update(float secTime)
{

	Manger(myPlayer.getPosY(), (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4);
	actualisationNiveau((m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4);

	
	if (is_menu_visible)
	{
		
		menu1.update();
		if (menu1.is_playing() == true)
		{
			ChoixDifficulter(menu1.getDifficulte());
			ChoixMonde(menu1.getWorld());
			is_menu_visible = false;
		}
		if (menu1.is_quitting() == true)
		{
			execute_action(ACT_CLOSE_APP);
		}
	}
	else
	{
		int retour = myPlayer.update(secTime);
	
		if (retour == 1)
		{
			execute_action(ACT_GO_RIGHT);
		}

		/*cout << secTime << "   ";
		cout << myPlayer.getPosY() << endl;*/
		//cout << (m_view2.getCenter().x / 248) - 4 << endl;
		int posXPla = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4;
		//cout << endl << posXPla << endl;
		int posYpla = myPlayer.getPosY();

		float hitLimit = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4 - posXPla;
		//cout << posXPla << "     " << hitLimit << endl;

		if (((hitLimit > 0.75)) && (Map[posYpla][posXPla + 1].getObject() == 0) && (myPlayer.isEtheral()) && (myPlayer.playerState != VANISH))
		{
			//system("PAUSE");
			myPlayer.setEtheral(0);
		}
		if (myPlayer.isEtheral())
		{
			retour = 2;
		}
		/*sf::Vector2i pos((myPlayer.getPosY() * 216), (myPlayer.getPosX() * 248 + 248));
		sf::Vector2i worldPos = m_app->mapPixelToCoords(pos, m_view2);*/
		//sf::Vector2f MousePos = m_app.mapCoordsToPixel((myPlayer.getPosY() * 216), (myPlayer.getPosX() * 248 + 248));


		m_view2.move(500 * secTime, 0);
		//((Map[posYpla][posXPla + 1].getObject == 0) && (Map[posYpla][posXPla].getObject == 0) || (hitLimit > 0.85)))
		if ((((Map[posYpla][posXPla + 1].getObject() != 0) || (Map[posYpla][posXPla].getObject() != 0))
			&& (!(((hitLimit > 0.75)) && (Map[posYpla][posXPla + 1].getObject() == 0)))
			&& (retour != 2)))
		{
			execute_action(ACT_GO_LEFT);
		}
		else 
		{
			if ((myPlayer.playerState == SMASHED) && (Map[posYpla][posXPla + 2].getObject() == 0))
			{
				myPlayer.playerState = MOVING;
			}
			
		}

		if ((Map[posYpla][posXPla + 1].getLight() != 0) || (Map[posYpla][posXPla].getLight() != 0))
			//if ((Map->getBoxint(posYpla, posXPla + 1) == 2) || (Map->getBoxint(posYpla, posXPla) == 2))
		{
			if ((!((Map[posYpla][posXPla].getLight() != 0) && (hitLimit > 0.75))) && (Map[posYpla][posXPla + 1].getLight() == 0))
				//if ((Map->getBoxint(posYpla, posXPla + 1) == 2) || (hitLimit < 0.85))
			{
				myPlayer.setMovable(0);
				if (myPlayer.isLight() == 0)
				{
					myPlayer.setLight(1);
					//lightTime = lightClock.restart();
				}
			}
			else
			{
				if (myPlayer.isMovable() == 0)
				{
					myPlayer.setMovable(1);
				}
				if (myPlayer.isLight() == 1)
				{
					cout << "UNLIGHT" << endl;
					//system("PAUSE");
					myPlayer.setLight(0);
				}
			}
		}
	}
	bool isEvent = handle_input_events();


}

void Game_Manager::draw()
{
    static sf::Clock render_clock;
    if (render_clock.getElapsedTime().asMilliseconds() < 2) {
        return;
    }
    render_clock.restart();
    m_app->clear();

    if (is_menu_visible)
    {
        menu1.draw();
    }
    else
    {
	m_app->setView(m_view2);
	//Changes on the world
	world_sprite.draw(0, 0);
    afficherMapobjet();
    //affichage_Level(Map);//pour afficher la map en valeu numerique
	
	//m_view2.move(5, 0);
	m_app->setView(m_view1);
	//Changes on the HUD, player
    myPlayer.draw();
    light_bar_background.draw(m_screen_x - light_bar_background.get_w(), 0);
    light_bar.draw(m_screen_x + 28 - light_bar_background.get_w(), 40);
    light_bar_grad.draw(m_screen_x - light_bar_background.get_w(), 0);
    energy_text.refill(to_string(myPlayer.getEnergy() ) );
    energy_text.draw(0, 0, 55);
	difficulter_text.refill(to_string(_difficulter-1));
	difficulter_text.draw(0, 100, 55);
    }
    m_app->display();
}

void Game_Manager::draw_gui()
{
    m_app->setView(m_view2);
   
    m_app->setView(m_view1);
}

void Game_Manager::highlight_selected_tile()
{
    if (m_x_cursor >= 0 && m_x_cursor < GRID_WIDTH && m_y_cursor >= 0 && m_y_cursor < GRID_HEIGHT)
    {
        //highlight selected tile
        selection_sprite.draw((m_x_cursor - m_y_cursor)* (Tile::tile_size.m_w / 2), (m_x_cursor + m_y_cursor)* (Tile::tile_size.m_h / 2));
    }
}

void Game_Manager::handle_mouse_click(sf::Mouse::Button click, Vector2i mouse_vec)
{
    if (m_x_cursor < 0 || m_x_cursor >= GRID_WIDTH || m_y_cursor < 0 || m_y_cursor >= GRID_HEIGHT)
    {
        return;
    }

   
}

int Game_Manager::count_neighbours(unsigned int i, unsigned int j, Caracteristic typeorzoneorheight, int value, bool diagonal)
{
    int number = 0;
    if (i == 0 || j == 0 || j + 1 >= GRID_HEIGHT || i + 1 >= GRID_WIDTH) {
        return 0; //TODO handle this correctly
    }

    if (typeorzoneorheight == CRC_TYPE)
    {
        if (m_grid(i - 1, j).m_type == value)
            number++;
        if (m_grid(i, j + 1).m_type == value)
            number++;
        if (m_grid(i, j - 1).m_type == value)
            number++;
        if (m_grid(i + 1, j).m_type == value)
            number++;
        if (diagonal)  //diagonal + sides
        {
            if (m_grid(i - 1, j + 1).m_type == value)
                number++;
            if (m_grid(i - 1, j - 1).m_type == value)
                number++;
            if (m_grid(i + 1, j + 1).m_type == value)
                number++;
            if (m_grid(i + 1, j - 1).m_type == value)
                number++;
        }
    }

    return number;
}

void Game_Manager::show_action_button(Button &button)
{
    button.update(0, m_h - 50);
}

void Game_Manager::set_info()
{
    is_info = true;
    m_info.activate();
}



void Game_Manager::passagesecuriserMonde1(int difficulter)
{

	int repere[MAXY][2];
	int videD = 0, videG = 0, choix;
	int choixG, choixD;
	int cmp1, cmp2;
	int mob, light;

	for (int x = 4; x < MAXX; x++)
	{	
	//-------------------------------------------------------------------------------------------------	
		for (int y = 0; y < MAXY; y++)
		{ //trouver case vide gauche
			if (Map[y][x].getObject() == 0)
			{
				repere[y][0] = 0;
				videD++;
			}
			else
			{
				repere[y][0] = 1;
			}
			//trouver case vide droite
			if (Map[y][x].getObject() == 0)
			{
				repere[y][1] = 0;
				videG++;
			}
			else
			{
				repere[y][1] = 1;
			}
		}
//-------------------------------------------------------------------------------------------------	

		//selection des cases de passage Gauche
		if (videG == 0)
		{
			cout << endl << "WARNING passagebloquer" << endl;
		}
		else
		{
			choix = rand() % videG;

			cmp1 = 0, cmp2 = 0;
			while (cmp2 < choix)
			{
				while (repere[cmp1][0] != 0) { cmp1++; }//on parcour les cases et ont sarrete au vide
				cmp2++; cmp1++;
			}
			choixG = cmp1;
		}
		//selection des cases de passage Droite
		if (videD == 0){ cout << endl << "WARNING passagebloquer" << endl; }
		else
		{
			choix = rand() % videD;

			cmp1 = 0, cmp2 = 0;
			while (cmp2 < choix)
			{
				while (repere[cmp1][1] != 0)
				{
					cmp1++;
				}//on parcour les cases et ont sarrete au vide
				cmp2++; cmp1++;
			}
			choixD = cmp1;
		}
		//-------------------------------------------------------------------------------------------------	

		for (int y = 0; y < MAXY; y++)
		{
			//if (Map[y][colonne].getLight() == 0 && rand() % difficulter == 0)
			if (Map[y][x].getLight() == 0 && rand() % difficulter == 0)
			{
				if ((choixD == choixG) && !(choixD == y))
				{
					light = (rand() % 2)*(3);
					Map[y][x].setLight(light);
				}
				else if ((choixD < choixG) && !(y >= choixD && y <= choixG))
				{
					light = (rand() % 2)*(3);
					Map[y][x].setLight(light);
				}
				else if ((choixD > choixG) && !(y <= choixD && y >= choixG))
				{
					light = (rand() % 2)*(3);
					Map[y][x].setLight(light);
				}
			}
		}
		//-------------------------------------------------------------------------------------------------	
	}

}
void Game_Manager::passagesecuriserMonde3(int difficulter)
{//les cases securiser qui ne font pas partie du chemin sont des lampes


	int repere[MAXY][2];
	int videD = 0, videG = 0, choix;
	int choixG, choixD;
	int cmp1, cmp2;
	int mob, light;

	for (int x = 4; x < MAXX; x++)
	{
		//-------------------------------------------------------------------------------------------------	
		for (int y = 0; y < MAXY; y++)
		{ //trouver case vide gauche
			if (Map[y][x].getObject() == 0)
			{
				repere[y][0] = 0;
				videD++;
			}
			else
			{
				repere[y][0] = 1;
			}
			//trouver case vide droite
			if (Map[y][x].getObject() == 0)
			{
				repere[y][1] = 0;
				videG++;
			}
			else
			{
				repere[y][1] = 1;
			}
		}
		//-------------------------------------------------------------------------------------------------	

		//selection des cases de passage Gauche
		if (videG == 0)
		{
			cout << endl << "WARNING passagebloquer" << endl;
		}
		else
		{
			choix = rand() % videG;

			cmp1 = 0, cmp2 = 0;
			while (cmp2 < choix)
			{
				while (repere[cmp1][0] != 0) { cmp1++; }//on parcour les cases et ont sarrete au vide
				cmp2++; cmp1++;
			}
			choixG = cmp1;
		}
		//selection des cases de passage Droite
		if (videD == 0){ cout << endl << "WARNING passagebloquer" << endl; }
		else
		{
			choix = rand() % videD;

			cmp1 = 0, cmp2 = 0;
			while (cmp2 < choix)
			{
				while (repere[cmp1][1] != 0)
				{
					cmp1++;
				}//on parcour les cases et ont sarrete au vide
				cmp2++; cmp1++;
			}
			choixD = cmp1;
		}
		//-------------------------------------------------------------------------------------------------	

		for (int y = 0; y < MAXY; y++)
		{
			
			if (Map[y][x].getLight() == 0 )
			{
				if ((choixD == choixG) && !(choixD == y))
				{
					
					Map[y][x].setLight(3);
				}
				else if ((choixD < choixG) && !(y >= choixD && y <= choixG))
				{
				
					Map[y][x].setLight(3);
				}
				else if ((choixD > choixG) && !(y <= choixD && y >= choixG))
				{
				
					Map[y][x].setLight(3);
				}
			}
		}
		//-------------------------------------------------------------------------------------------------	
	}

}
void Game_Manager::CreationMonde1(int difficulter)
{
	resetMap();

	int nbrmob = 0, obstacle = 0, nbrLight = 0;
	int *ordre = NULL;
	int currentLight = 0, currentObst = 0;
	int rndY = 0;

	for (int x = 5; x < MAXX; x++)
	{
		if (x % 2 != 0)
		{
			currentObst = NULL;
			currentLight = NULL;

			obstacle = rand() % difficulter;
			nbrLight = rand() % difficulter;


			//pose des obstacles
			if (obstacle != 0)
			{
				while (currentObst < obstacle)
				{
					rndY = rand() % MAXY;
					if (Map[rndY][x].getObject() == 0)
					{
						Map[rndY][x].setObject(1+rand() % 9);////////////Differents sprites
						currentObst++;
					}
				}
			}

			//pose des lumiere natuel
			if (nbrLight != 0)
			{
				while (currentLight < nbrLight)
				{
					rndY = rand() % MAXY;
					if (Map[rndY][x].getObject() == 0)
					{
						Map[rndY][x].setLight(3);////////////Differents sprites
						currentLight++;
					}
				}
			}
		}
		else
		{ //pose des mobs
			int currentMob = 0, rndY = 0;
			int nbrmob = rand() % difficulter;
			if (nbrmob != 0)
			{
				while (currentMob < nbrmob)
				{
					rndY = rand() % MAXY;
					//if (Map[rndY][x].getObject() == 0 && Map[rndY][x].getMob()==0)
					if (Map[rndY][x].getMob() == 0)
					{
						Map[rndY][x].setMob(1 + rand() % 8);////////////Differents sprites
						currentMob++;
					}
				}
			}

		}

	}

	Lumiere();
	passagesecuriserMonde1(difficulter);


}
void Game_Manager::CreationMonde2(int difficulter)
{

	resetMap();


	int nbrmob = 0;
	int *ordre = NULL;
	int currentMob = 0, rndY = 0;


	for (int x = 5; x < MAXX; x++)
	{
		 //pose des mobs
			 currentMob = 0, rndY = 0;
			 nbrmob = rand() % difficulter;
			if (nbrmob != 0)
			{
				while (currentMob < nbrmob)
				{
					rndY = rand() % MAXY;
					if (Map[rndY][x].getMob() == 0)
					{
						Map[rndY][x].setMob(1 + rand() % 8);////////////Differents sprites
				
						currentMob++;
					}
				}
			}

	}

	Lumiere();
	passagesecuriserMonde1(difficulter);

}
void Game_Manager::CreationMonde3(int difficulter)
{

	resetMap();

	int  obstacle = 0, nbrLight = 0;
	int *ordre = NULL;
	int currentLight = 0, currentObst = 0;
	int rndY = 0;

	for (int x = 5; x < MAXX; x++)
	{
		if (x % 2 == 0)
		{
			currentObst = NULL;
			currentLight = NULL;


			obstacle = 1 + rand() % (difficulter - 1);
			nbrLight = 1 + rand() % (difficulter - 1);


			//pose des obstacles
			if (obstacle != 0)
			{
				while (currentObst < obstacle)
				{
					rndY = rand() % MAXY;
					if (Map[rndY][x].getObject() == 0)
					{
						Map[rndY][x].setObject(rand() % 10);////////////Differents sprites
						currentObst++;
					}
				}
			}

			//pose des lumiere natuel
			if (nbrLight != 0)
			{
				while (currentLight < nbrLight)
				{
					rndY = rand() % MAXY;
					if (Map[rndY][x].getObject() == 0)
					{
						Map[rndY][x].setLight(3);////////////Differents sprites
						currentLight++;
					}
				}
			}
		}
		else
		{
			passagesecuriserMonde3(difficulter);
		}


	}




}
void Game_Manager::CreationMonde4(int difficulter)
{//parfois chemin totalment bloquer

	resetMap();

	int current = 3,precedent;

	for (int x = 5; x < MAXX; x++)
	{
		precedent = current;
		current = modifcourant(current); 

		for (int y = 0; y < MAXY; y++)
		{
			
			if (y == current)
				{ }
			else if ( y != precedent)
			{	
				if (rand() % (difficulter+1)!=0)
				{
					if (rand() % 2) 
					{
						Map[y][x].setObject(2 + rand() % 8);
					}
					else
					{
						Map[y][x].setLight(3);
					}
					
				}
				else
				{
					//vide
				}

			}
			else
			{
				if (rand() % 2 == 0)
				{
					Map[y][x].setMob(1 + rand() % 8);
				}
				else
				{
					//vide
				}
			}

		}
	}

		Lumiere();
}
void Game_Manager::CreationMonde5(int difficulter)
{//un chemin de lumiere le reste du vide

	resetMap();



	int current = 3, precedent;

	for (int x = 5; x < MAXX; x++)
	{
		precedent = current;
		current = modifcourant(current);




		for (int y = 0; y < MAXY; y++)
		{
			if (y == current)
			{
				if (y % 3 != 0)
				{
					Map[y][x].setLight(3);
					
				}
				
			}
			else if (y != precedent)
			{
				if (rand() % 3 != 0)
				{
					
				}
				else
				{
					//vide
				}

			}
			else
			{
				if (rand() % 2 == 0)
				{
					Map[y][x].setMob(1 + rand() % 8);
				}
				else
				{
					//vide
				}
			}

		}
	}

	Lumiere();
}

void Game_Manager::CreationMonde6()
{
	resetMap();

	int test,choix;

	ChoixDifficulter(1); cout << "blockage de la difficulter a 1" << endl;



	for (int x = 5; x < MAXX; x++)
	{
		choix = (rand() % 4) * 2;
		for (int y = 0; y < MAXY; y++)
		{
			if (x%2==0 &&y%2==1)
				{
					
					Map[y][x].setObject(1 + rand() % 9);
				}
			else if (y % 2 == 0 && y == choix)
			{
				Map[y][x].setType(1 + rand() % 9, 1 + rand() % 8, 0);
			}
			else if (y % 2 == 0 && y != choix)
			{ 
			//vide
			}
			else if (x % 2 == 1 && y % 2 == 1)
			{ 
				if (rand()%2==0)
				{
					Map[y][x].setMob(1 + rand() % 8);
				}
				else
				{
					Map[y][x].setLight(2);
				}

			}
			else
			{

			}
		}
	}




	Lumiere();
}



void Game_Manager::ChoixMonde(int choix)
{
	switch (choix)
	{
	case 1:CreationMonde4(_difficulter);//classic			=Normal	
		break;
	case 2:CreationMonde1(_difficulter);//simple				=Classic
		break;
	case 3:CreationMonde2(_difficulter);//monde que de mob	=time to eat
		break;
	case 4:CreationMonde3(_difficulter);//monde sans mob		=peacefull
		break;
	case 5:CreationMonde5(_difficulter);//simple				=easy
		break;
	case 6:CreationMonde6();//damier///				=easy
		break;
	default:CreationMonde4(_difficulter);
		break;
	}

}
void Game_Manager::ChoixDifficulter(int difficulter)
{
	switch (difficulter)
	{
	case 1:_difficulter = 2;
		break;
	case 2:_difficulter = 3;
		break;
	case 3:_difficulter = 4;
		break;
	case 4:_difficulter = 5;
		break;
	case 5:_difficulter = 5;
		break;

	default:_difficulter = 2;
		break;
	}
}







int Game_Manager::modifcourant(int actuel)
{
	int test = rand() % 7;

	if (actuel == 0)
		{if (test < 4)
			{ return 0; }return 1; 
		}
	else if (actuel == 5)
		{
			if (test < 4)
			{
				return 5;
			}return 4;
		}
	else
	{
		if (test == 4){ return actuel; }
		else if (test < 4){ return actuel-1; }
		else	{ return actuel+1; }
	}

}

void Game_Manager::resetMap()
{

for (size_t x = 0; x < MAXX; x++)
{
	for (size_t y = 0; y < MAXY; y++)
	{
		Map[y][x].reset();
	}
}

}

void Game_Manager::Lumiere()
{

	//-------------------------------------------------------------------------------
	//---------------  Mise de la lumiere du au mob  --------------------------------
	//-------------------------------------------------------------------------------


	for (int y = 0; y < MAXY; y++)
	{
	//     6
	//     2 
	// 5 1 O 3 7
	//	   4 
	//     8


		for (int x = 0; x < MAXX ; x++)
		{
		//lumiere gauche 1 5 37
			if ( x - 1> 0 && ( Map[y][x-1].getMob() == 3 || Map[y][x-1].getMob() == 7) )
				{
					Map[y][x].setLight(2);
				}
			else if (x - 2 > 0  && Map[y][x-2].getMob() == 7)
				{
					Map[y][x].setLight(2);
				}
			//lumiere bas 4 8 26
			else if (y - 1> 0 && (Map[y-1][x].getMob() == 4 || Map[y-1][x].getMob() == 8))
				{
					Map[y][x].setLight(2);
				}
			else if (y - 2 > 0 && Map[y-2][x].getMob() == 8)
				{
					Map[y][x].setLight(2);
				}
			//lumiere haut 2 6 48
			else if (y+1 < MAXY && (Map[y+1][x].getMob() == 2 || Map[y+1][x].getMob() == 6))
				{
					Map[y][x].setLight(2);
				}
			else if (y+2 < MAXY  && Map[y+2][x].getMob() == 6)
				{
					Map[y][x].setLight(2);
				}
			//lumiere droite 3 7 15
			else if (x+1 < MAXX && (Map[y][x+1].getMob() == 1 || Map[y][x+1].getMob() == 5))
				{
					Map[y][x].setLight(2);
				}
			else if (x+2 < MAXX  && Map[y][x+2].getMob() == 5)
				{
					Map[y][x].setLight(2);
				}
			
			else
				{ }
			


		}
	}
	

}

void Game_Manager::afficherMapobjet()
{

	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)

		{
			m_box_background[0].draw(j * 248, i * 216);
			if (Map[i][j].getObject() != 0)
			{
				m_box_sprites[Map[i][j].getObject() - 1].draw(j * 248, i * 216);
			}
			if (Map[i][j].getLight() < 3)
			{
				m_light_sprites[Map[i][j].getLight()].draw(j * 248, i * 216);
			}
			if (Map[i][j].getMob() != 0)
			{
				mob_sprite.draw(j * 248, i * 216);
			}
			//cout << Map[i][j].getObject()<<" ";
		}
		//cout << endl;
	}
}

void Game_Manager::afficherMapMob()
{

	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)

		{

			cout << Map[i][j].getMob() << " ";
		}
		cout << endl;
	}
}
void Game_Manager::afficherMapLight()
{
	cout << endl;
	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)
		{

			cout << Map[i][j].getLight() << " ";

		}
		cout << endl;
	}
	cout << endl;
}

void Game_Manager::Manger()
{//fonction jamais utiliser
	
	if (Map[(int)myPlayer.getPosY()][(int)myPlayer.getPosX()].getMob() != 0)
	{
	
		myPlayer.gainEnergy( _difficulter);
		Map[(int)myPlayer.getPosY()][(int)myPlayer.getPosX()].setMob(0);
	}

}

void Game_Manager::Manger(int y,int x)
{

	//cout << endl << " Position =" << y << " " << m_view2.getCenter().x << " " << myPlayer.getPosX() << " "<<x << endl;




	if (Map[y][x].getMob() != 0)
	{
		myPlayer.gainEnergy( _difficulter);
		Map[y][x].setMob(0);
	}



}

void Game_Manager::actualisationNiveau(int x)
{
	int energy = myPlayer.getEnergy();
	if (x+5 > MAXX )
	{
		cout << "on change le niveau" << endl;
		cout << "inserer ici le menu de competence" << endl;
		

		ChoixDifficulter(_difficulter++);
		ChoixMonde(menu1.getWorld());
		myPlayer.resetPosition();

		cout << m_view2.getCenter().x << "  " << m_view2.getCenter().y<< endl;

		m_view2.setCenter(Vector2f(960, 540));

		myPlayer.gainEnergy(energy);
	
		draw();

	}



}


