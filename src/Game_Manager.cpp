#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, View &view2, int screen_x, int screen_y)
	: m_view1(view1)
	, menu1(app, &m_view2)
	, m_grid(GRID_WIDTH, GRID_HEIGHT, &m_view1, app)
	, selection_sprite(app, "resources/selection.png", &m_view1)
	, interface1(app, m_grid, &m_view2, screen_x, screen_y)
	, m_info(app, &view1, 1920, 1080)
	//////////
	, myPlayer()
	, player_sprite(app, "resources/player_moving.png", &m_view1, 248, 5, 1.05f)
	, m_view2(view2)
	, world_sprite(app, "resources/test.png", &m_view1)
{
    is_menu_visible = true;
    is_info = false;
    m_mouse_over_actions = false;
    m_screen_x = screen_x;
    m_screen_y = screen_y;
    x_offset = 0;
    y_offset = 0;

    m_app = app;
    m_app->setView(m_view1);

    window_vec = m_app->getSize();
    cout << "x_window" << window_vec.x << "y_window " << window_vec.y << endl;

    m_view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(m_screen_x), static_cast<float>(m_screen_y)));
    m_view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    Vector2f vecsize = m_view1.getSize();
    m_h = static_cast<int>(vecsize.y);
    m_w = static_cast<int>(vecsize.x);




		Map = generationMap(m_app, &m_view1,1);

		affichage_Level(Map);



	


    for (int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("resources/font2.ttf");
    }

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
			if ((Map->getBoxint(posYpla - 1, posXPla + 1) != 1) && (Map->getBoxint(posYpla - 1, posXPla) != 1))
			{
				myPlayer.moveUp();
			}
			else if ((Map->getBoxint(posYpla - 1, posXPla + 1) != 1) && (hitLimit > 0.75))
			{
				myPlayer.moveUp();
			}
		}
        break;

	case ACT_FRONT_DASH:
		/*
		if ()
		{
			myPlayer.moveRight(0.01);
		}
		break;


		else if ((Map->getBoxint(posYpla - 1, posXPla + 1) != 1) && (hitLimit > 0.80))
			{
				myPlayer.moveUp();
			}
		*/
		break; 

    case ACT_GO_RIGHT:
		if ((myPlayer.getPosX() < 1000) && (Map->getBoxint(posYpla, posXPla + 1) == 0))
		{
			myPlayer.moveRight(0.01);
		}
        break;
    case ACT_GO_DOWN:
		if (myPlayer.getPosY() < 4)
		{
			if ((Map->getBoxint(posYpla + 1, posXPla + 1) != 1) && (Map->getBoxint(posYpla + 1, posXPla) != 1))
			{
				myPlayer.moveDown();
			}
			else if ((Map->getBoxint(posYpla + 1, posXPla + 1) != 1) && (hitLimit > 0.75))
			{
				myPlayer.moveDown();
			}
		}
        break;
    case ACT_GO_LEFT:
		if (myPlayer.getPosX() > 0)
		{
			myPlayer.moveLeft(248.0/50000.0 * 5);//5 = SPEED/////////////////////////////////////
		}
		else
		{
			execute_action(ACT_CLOSE_APP);///////////////////GAME OVER MENU
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
  
    default:
        break;
    }
}

void Game_Manager::handle_mouse_at_window_border(int x_mouse, int y_mouse)
{/*
    static sf::Clock mouse_move_clock;
    sf::Time mouse_move_time = mouse_move_clock.getElapsedTime();
    if (mouse_move_time.asSeconds() > 0.05) {
        mouse_move_clock.restart();
        Vector2u windowSize = m_app->getSize();
        const int margin = 10;
        if (m_x_cursor < -margin || m_x_cursor > GRID_WIDTH + margin || m_y_cursor < -margin || m_y_cursor > GRID_HEIGHT + margin) {
            //we are already too far outside the m_grid, do nothing
            return;
        }
        if (x_mouse < 15)
        {
            execute_action(ACT_GO_LEFT);
        }
        else if (x_mouse > static_cast<int>(windowSize.x - 15))
        {
            execute_action(ACT_GO_RIGHT);
        }

        if (y_mouse < 15) {
            execute_action(ACT_GO_UP);
        }
        else if (y_mouse > static_cast<int>(windowSize.y - 35))
        {
            execute_action(ACT_GO_DOWN);
        }

    }*/
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
	cout << "test1" << endl;
    if (is_menu_visible)
    {
        menu1.update();
        if (menu1.is_playing() == true)
        {
            is_menu_visible = false;
        }
        if (menu1.is_quitting() == true)
        {
            execute_action(ACT_CLOSE_APP);
        }
    }
    else{
		myPlayer.update(secTime);
        /*cout << secTime << "   ";
        cout << myPlayer.getPosY() << endl;*/
        //cout << (m_view2.getCenter().x / 248) - 4 << endl;
        int posXPla = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4;
		cout << endl << posXPla << endl;
        int posYpla = myPlayer.getPosY();

		float hitLimit = (m_view2.getCenter().x + (myPlayer.getPosX() * 248)) / 248 - 4 - posXPla;
		cout << posXPla << "     " << hitLimit << endl;


        /*sf::Vector2i pos((myPlayer.getPosY() * 216), (myPlayer.getPosX() * 248 + 248));
        sf::Vector2i worldPos = m_app->mapPixelToCoords(pos, m_view2);*/
        //sf::Vector2f MousePos = m_app.mapCoordsToPixel((myPlayer.getPosY() * 216), (myPlayer.getPosX() * 248 + 248));


		m_view2.move(5, 0);
		if (!((Map->getBoxint(posYpla, posXPla + 1) != 1) && (Map->getBoxint(posYpla, posXPla) != 1) || (hitLimit > 0.85)))
			{
				execute_action(ACT_GO_LEFT);
			}

		
		if ((Map->getBoxint(posYpla, posXPla + 1) == 2) || (Map->getBoxint(posYpla, posXPla) == 2))
		{


			if ((Map->getBoxint(posYpla, posXPla + 1) == 2) || (hitLimit < 0.85))

			{
				myPlayer.setMovable(0);
				if (myPlayer.isLight() == 0)
				{
					myPlayer.setLight(1);
					//lightTime = lightClock.restart();
				}
			}
			else if (myPlayer.isMovable() == 0)
			{
				myPlayer.setMovable(1);
				if (myPlayer.isLight() == 1)
				{
					myPlayer.setLight(0);
				}
			}
		}
		

		if (myPlayer.isLight())
		{
			//lightTime = lightClock.restart();
			//lightSec = lightTime.asSeconds();
			
			//lightTot += secTime;
			//cout << lightTot << endl;
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

    affichage_Level(Map);

	//m_view2.move(5, 0);
	m_app->setView(m_view1);
	//Changes on the HUD, player
    player_sprite.draw((myPlayer.getPosX() * 248 - 20), (myPlayer.getPosY() * 216));

    }
    m_app->display();
}

void Game_Manager::draw_gui()
{
    m_app->setView(m_view2);
   
    m_app->setView(m_view1);
}

void Game_Manager::create_map(int map_width, int map_height)
{
    //sur 200
   
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
