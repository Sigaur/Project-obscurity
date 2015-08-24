#include "Game_Manager.h"





Game_Manager::Game_Manager(RenderWindow *app, View &view1, View &view2, int screen_x, int screen_y)
	: m_view1(view1)
	, menu1(app, &m_view2)
	, m_grid(GRID_WIDTH, GRID_HEIGHT, &m_view1, app)
	, selection_sprite(app, "resources/selection.png", &m_view1)
	, light_bar(app, "resources/light_bar.png", &m_view1)
	, light_bar_background(app, "resources/light_bar_background.png", &m_view1)
    , light_bar_grad(app, "resources/light_bar_grad.png", &m_view1)
    , empty(app, "resources/empty.png", &m_view1)
    , bone(app, "resources/bone.png", &m_view1)
    , interface1(app, m_grid, &m_view2, screen_x, screen_y)
	, m_info(app, &view1, 1920, 1080)
	//////////
	, myPlayer(app, &m_view1)
	, m_view2(view2)
    , world_sprite(app, "resources/test.png", &m_view1)
    , tree_background(app, "resources/skill_tree.png", &m_view1)
    , _difficulter(0)
{
    is_menu_visible = true;
    is_info = false;
    is_tree = false;
    m_mouse_over_actions = false;
    m_screen_x = screen_x;
    m_screen_y = screen_y;
    x_offset = 0;
    y_offset = 0;
    skill_level = 0;
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

	
	for (int i = 0; i < 12; i++)
    {
        string path = "resources/obstacle" + std::to_string(i) + ".png";
        m_box_sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
    }
  
      for (int i = 0; i < 1; i++)
      {
          string path = "resources/background" + std::to_string(i) + ".png";
          m_box_background.push_back(My_Sprite{ m_app, path, &m_view1 });
      }
      
          for (int i = 0; i < 3; i++)
          {
              string path = "resources/light" + std::to_string(i) + ".png";
              m_light_sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
          }

          for (int i = 0; i < 5; i++)
          {
              string path = "resources/opponent" + std::to_string(i) + ".png";
              mob_sprite.push_back(My_Sprite{ m_app, path, &m_view1 });
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


    death_buffer.loadFromFile("resources/death.ogg");

    death_sound.setBuffer(death_buffer);

    skill_button.push_back(Button{ app, "resume" , 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "light resistance", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "sharp reflex", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "D cost", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "D cooldown", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "D distance", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "V cost", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "V Cooldown", 0, 0, 1920, 1080, &m_view1 });
    skill_button.push_back(Button{ app, "V distance", 0, 0, 1920, 1080, &m_view1 });
}

void Game_Manager::execute_action(Action action)
{
	
	int posXPla =(int) ((m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4);
	
	int posYpla = (int) myPlayer.getPosY();
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
			myPlayer.moveRight((float)0.1);
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
			myPlayer.moveLeft((float)  (248.0/3000.0));//5 = SPEED/////////////////////////////////////
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

	Manger((int)myPlayer.getPosY(), (int)((m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4));
	actualisationNiveau((int) ((m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4));
    if (myPlayer.getEnergy() <= 0)
    {
        execute_action(ACT_RESTART_APP);
    }

    if (is_tree)
    {
        int cost = 20;
        skill_button[0].update(100, 100);
        if (skill_button[0].is_activated())
        {
            skill_button[0].desactivate();
            is_tree = false;
        }
        skill_button[3].update(670, 290);

        if (skill_button[3].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[3].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_FDReduceCost(-10);
            skill_level++;

        }
        skill_button[4].update(870, 290);

        if (skill_button[4].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[4].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_FDReduceCooldown(-1.0f);
            skill_level++;

        }
        skill_button[5].update(1070, 290);

        if (skill_button[5].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[5].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_FDIncreaseDistance(1);
            skill_level++;

        }

        skill_button[6].update(1310, 290);

        if (skill_button[6].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[6].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_VAReduceCost(-10);
            skill_level++;

        }
        skill_button[7].update(1450, 290);

        if (skill_button[7].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[7].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_VAReduceCooldown(-1.0f);
            skill_level++;

        }
        skill_button[8].update(1650, 290);

        if (skill_button[8].is_activated() && myPlayer.getEnergy() > cost)
        {
            skill_button[8].desactivate();
            myPlayer.gainEnergy(-cost);
            myPlayer.m_VAIncreaseDistance(1);
            skill_level++;

        }
    }
	else if (is_menu_visible)
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
		int retour = myPlayer.update(secTime, _difficulter);
	
		if (retour == 1)
		{
			execute_action(ACT_GO_RIGHT);
		}

		int posXPla =(int) ((m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4);
		
		int posYpla =(int) myPlayer.getPosY();

		float hitLimit = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4 - posXPla;
	
		if (((hitLimit > 0.75)) && (Map[posYpla][posXPla + 1].getObject() == 0) && (myPlayer.isEtheral()) && (myPlayer.playerState != VANISH))
		{
			
			myPlayer.setEtheral(0);
		}
		if (myPlayer.isEtheral())
		{
			retour = 2;
		}
	
		m_view2.move(500 * secTime, 0);
		
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
			{
			if ((!((Map[posYpla][posXPla].getLight() != 0) && (hitLimit > 0.75))) && (Map[posYpla][posXPla + 1].getLight() == 0))
				{
				myPlayer.setMovable(0);
				if (myPlayer.isLight() == 0)
				{
					myPlayer.setLight(1);
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

    if (is_tree)
    {
        tree_background.draw(0, 0);
        skill_button[0].draw();
        skill_button[3].draw();
        skill_button[4].draw();
        skill_button[5].draw();
        skill_button[6].draw();
        skill_button[7].draw();
        skill_button[8].draw();

        energy_text.refill(to_string(myPlayer.getEnergy()));
        energy_text.draw(0, 0, 55);
        if (skill_level < 3)
        {
            empty.draw(0, 500);
        }
        else if (skill_level >= 3)
        {
            empty.draw(0, 700);
        }
    }
    else if (is_menu_visible)
    {
        menu1.draw();
    }
    else
    {
	m_app->setView(m_view2);
	//Changes on the world
	world_sprite.draw(0, 0);
    afficherMapobjet();
   
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
	int  light;

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
{//damier

	resetMap();

	int choix;

	
	for (int x = 5; x < MAXX; x++)
	{
		choix = (rand() % 4) * 2;
		for (int y = 0; y < MAXY; y++)
		{
			if (x%2==0 &&y%2==1)//regle a
				{
					
					Map[y][x].setObject(1 + rand() % 9);
				}
			else if (y % 2==0 && x%2==0 &&  y == choix)
			{
				Map[y][x].setType(1 + rand() % 9, 1 + rand() % 8, 2);
			}
			else if (y % 2 == 0 && x % 2 == 0 && y != choix)
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

			}//regle d
			else
			{

			}
		}
	}




	Lumiere();
}

void Game_Manager::CreationMonde7(int difficulter)
{

	resetMap();

	int nbrlight = 0;
	int *ordre = NULL;
	int currentLight = 0, rndY = 0;


	for (int x = 5; x < MAXX; x++)
	{
		//pose des light
		currentLight = 0, rndY = 0;

		nbrlight =2+ rand() % difficulter;
		if (nbrlight > 5)
			{ nbrlight =4;}

		if (nbrlight != 0)
		{
			while (currentLight < nbrlight)
			{
				rndY = rand() % MAXY;
				if (Map[rndY][x].getMob() == 0)
				{
					Map[rndY][x].setLight(2);
					currentLight++;
				}
			}
		}

	}

	
	

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
	case 7:CreationMonde7(_difficulter);//full light///				=easy
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
	//     6		   8
	//     2 		   4
	// 5 1 O 3 7     51026
	//	   4		   x
	//     8		   x


		for (int x = 0; x < MAXX ; x++)
		{
		//lumiere gauche  37
			if ( x - 1> 0 && ( Map[y][x-1].getMob() == 3 || Map[y][x-1].getMob() == 7) )
				{
					Map[y][x].setLight(2);
				}
			else if (x - 2 > 0  && Map[y][x-2].getMob() == 7)
				{
					Map[y][x].setLight(2);
				}
		//lumiere droite  15=BON
			else if (x + 1 < MAXX && (Map[y][x + 1].getMob() == 1 || Map[y][x + 1].getMob() == 5))
			{
				Map[y][x].setLight(2);
			}
			else if (x + 2 < MAXX  && Map[y][x + 2].getMob() == 5)
			{
				Map[y][x].setLight(2);
			}


			//lumiere bas 4 8 
			else if (y - 1> 0 && (Map[y-1][x].getMob() == 4 || Map[y-1][x].getMob() == 8))
				{
					Map[y][x].setLight(2);
				}
			else if (y - 2 > 0 && Map[y-2][x].getMob() == 8)
				{
					Map[y][x].setLight(2);
				}
			//lumiere haut 2 6 
			else if (y+1 < MAXY && (Map[y+1][x].getMob() == 2 || Map[y+1][x].getMob() == 6))
				{
					Map[y][x].setLight(2);
				}
			else if (y+2 < MAXY  && Map[y+2][x].getMob() ==6)
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

				//     6		   8
				//     2 		   4
				// 5 1 O 3 7     51026
				//	   4		   x
				//     8		   x



                if ((Map[i][j].getMob() == 1 || Map[i][j].getMob() == 5))
                {
                    mob_sprite[0].draw(j * 248, i * 216);
                }
                if ((Map[i][j].getMob() == 4 || Map[i][j].getMob() == 8))
                {
                    mob_sprite[1].draw(j * 248, i * 216);
                }
                if ((Map[i][j].getMob() == 2|| Map[i][j].getMob() == 6))
                {
                    mob_sprite[2].draw(j * 248, i * 216);
                }
                if ((Map[i][j].getMob() == 3 || Map[i][j].getMob() == 7))
                {
                    mob_sprite[3].draw(j * 248, i * 216);
                }

                if (Map[i][j].getMob() == 55)
                {
                   bone.draw(j * 248, i * 216);
                }
			}
			
		}
		
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

void Game_Manager::Manger(int y,int x)
{

	if (Map[y][x].getMob() != 0)
	{
        death_sound.play();
		myPlayer.gainEnergy(_difficulter* _difficulter);
		Map[y][x].setMob(55);
	}
}

void Game_Manager::activate_skill_tree()
{
    is_tree = true;
}

void Game_Manager::actualisationNiveau(int x)
{
	int energy = myPlayer.getEnergy();
	if (x > MAXX )
	{

		activate_skill_tree();
		ChoixDifficulter(_difficulter++);
		ChoixMonde(menu1.getWorld());
		myPlayer.resetPosition();
		m_view2.setCenter(Vector2f(960, 540));

		myPlayer.gainEnergy(energy + 20 * _difficulter);
	
		draw();

	}



}


