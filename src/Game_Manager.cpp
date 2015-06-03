#include "Game_Manager.h"

Game_Manager::Game_Manager(RenderWindow *app_get, View &view1_get, int screen_x_get, int screen_y_get)
: view1(view1_get)
, grid(GRID_WIDTH, GRID_HEIGHT, &view1, app_get)
{
    is_menu_visible = true;
    screen_x = screen_x_get;
    screen_y = screen_y_get;
    x_offset = 0;
    y_offset = 0;
    zoom = 1;
    mouse_wheel_x = 0;
    zoom_rate = 10;
    city_number = 0;
    open_window = true;
    rock = 0;
    wood = 0;
    iron = 0;
    zoom_change = ZOOM_NO_CHANGE;
    selected_citizen = 0;

    iteration = 0;
    app = app_get;
    app->setView(view1);



    window_vec = app->getSize();
    cout<<"x_window"<<window_vec.x<<"y_window "<<window_vec.y<<endl;

    view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(screen_x), static_cast<float>(screen_y)));
    view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));


    Vector2f vecsize;
    vecsize = view1.getSize();
    h = static_cast<int>(vecsize.y);
    w = static_cast<int>(vecsize.x);

    if(is_menu_visible)
    {
        menu1.init(app, & view2);
    }


        windows[0].init(app, "Map", 0.5f, 0.5f, 0, 0, &view2, screen_x, screen_y);
        windows[0].add_glissor(100, 100);
        //windows[0].desactivate();
    for(int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("ressources/font2.ttf");

    }
    selection_sprite.init(app, "ressources/selection.png", &view1);

    create_map(GRID_WIDTH, GRID_HEIGHT);


    m_citizens.push_back(Citizen{grid, app, &view1});
    grid(0, 0).citizen_id = 0;

    building[0].init(app, &view1, 0);

    citizen_action[0].init(app, "Fonder une ville", 0, 0, 0, 0, &view2);
    citizen_action[1].init(app, "Rentrer dans la ville", 0, 0, 0, 0, &view2);
    citizen_action[2].init(app, "Observer la ressource", 0, 0, 0, 0, &view2);
    //now that view1 has been reseted we can load tile files
    grid.loadFiles();
    tile_info.init(app, "lieu vierge", 10, 1);

    interface1.init(app, &view1, w, h);

}

Game_Manager::~Game_Manager()
{
    //dtor
}

void Game_Manager::execute_action(Action action)
{
    switch (action)
    {
    case ACT_GO_UP:
        y_offset -= 50;
        break;
    case ACT_GO_RIGHT:
        x_offset += 50;
        break;
    case ACT_GO_DOWN:
        y_offset += 50;
        break;
    case ACT_GO_LEFT:
        x_offset -= 50;
        break;
    case ACT_ZOOM_IN:
        zoom_change = ZOOM_ADD;
        break;
    case ACT_ZOOM_OUT:
        zoom_change = ZOOM_LESS;
        break;
    case ACT_CLOSE_APP:
        cout << "close app\n";
        app->close();
        break;
    default:
        break;
    }
}

/* x_mouse, y_mouse are in window coordinate (pixels)
   x_cursor, y_cursor are in grid coordinate */
void Game_Manager::handle_mouse_at_window_border(int x_mouse, int y_mouse)
{
    static sf::Clock mouse_move_clock;
    sf::Time mouse_move_time = mouse_move_clock.getElapsedTime();
    if (mouse_move_time.asSeconds() > 0.05) {
        mouse_move_clock.restart();
        Vector2u windowSize = app->getSize();
        const int margin = 10;
        if (x_cursor < -margin || x_cursor > GRID_WIDTH + margin || y_cursor < -margin || y_cursor > GRID_HEIGHT + margin) {
            //we are already too far outside the grid, do nothing
            return;
        }
        if (x_mouse < 5)
        {
            execute_action(ACT_GO_LEFT);
        }
        else if (x_mouse > static_cast<int>(windowSize.x - 5))
        {
            execute_action(ACT_GO_RIGHT);
        }

        if (y_mouse < 5) {
            execute_action(ACT_GO_UP);
        }
        else if (y_mouse > static_cast<int>(windowSize.y - 5))
        {
            execute_action(ACT_GO_DOWN);
        }

    }
}

bool Game_Manager::handle_input_events()
{
	Event event;
	bool isEvent = app->pollEvent(event);
	Action action;
	sf::Mouse::Button click = {};
	Vector2i mouse_vec;

	key_event.get_mouse_position(app, mouse_vec);

    //translate to grid coordinates
    selection_vector = app->mapPixelToCoords(mouse_vec, view1);
    x_cursor = static_cast<int>((selection_vector.x / (float)Tile::tile_size.x + selection_vector.y / (float)Tile::tile_size.y - 0.5) * zoom);
    y_cursor = static_cast<int>((selection_vector.y / (float)Tile::tile_size.y - selection_vector.x / (float)Tile::tile_size.x + 0.5) * zoom);
    
    handle_mouse_at_window_border(mouse_vec.x, mouse_vec.y);
        
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

void Game_Manager::update()
{

    bool isEvent = handle_input_events();

    zoom_time = clock_zoom.getElapsedTime();
    if(zoom_time.asSeconds() >  0.05  && zoom_change != ZOOM_NO_CHANGE)
    {
        clock_zoom.restart();
        if(zoom_change == ZOOM_ADD && zoom_rate >= -30)
        {
            zoom = 0.90f;
            zoom_rate --;
        }
        if(zoom_change == ZOOM_LESS  && zoom_rate <= 50)
        {
            zoom = 1.1f;
            zoom_rate ++;
        }
        zoom_change = ZOOM_NO_CHANGE;
    }
    else
    {
        zoom = 1;
    }

    if(is_menu_visible)
    {
        menu1.update();
        if(isEvent == true)
        {
            is_menu_visible = false;
        }
    }

    view1.setCenter(static_cast<float>(x_offset) , static_cast<float>(y_offset));
    view1.zoom(zoom);
    app->setView(view1);

    for(int i = 0; i<6; i++)
    {
        if(windows[i].is_activated())
        {
            windows[i].update();
        }
    }
    citizen_update();
}

void Game_Manager::citizen_update()
{
    m_citizens[0].update();
    if(m_citizens[0].is_selected() )
    {
        citizen_action[0].update(0, h - 50);
    }

    if(citizen_action[0].is_activated() && city_number == 0)
    {
        city[0].init(app, &view1, m_citizens[0].get_x(), m_citizens[0].get_y(), Tile::tile_size.x, Tile::tile_size.y );
        city_number++;
        grid(m_citizens[0].get_x(), m_citizens[0].get_x()).is_city = true;
    }
    if(citizen_action[2].is_activated() )  //l'action sur la ressource
    {
        city[0].init(app, &view1, m_citizens[0].get_x(), m_citizens[0].get_y(), Tile::tile_size.x, Tile::tile_size.y );
        // windows[1].init(app, "Action", 550, 400, w/2, h/2, &view1);

        grid(m_citizens[0].get_x(), m_citizens[0].get_x()).is_city = true;
    }
    if(grid(m_citizens[0].get_x(), m_citizens[0].get_y()).is_city == true)
    {
        m_citizens[0].on_city();
    }
}

void Game_Manager::draw()
{
    app->clear();
    if(! is_menu_visible)
    {
        grid.draw();
        //drwing of the test created sprite
        //sprite_created_1_test.draw();

        for(int i = 0; i < city_number; i++)
        {
            city[i].draw();
        }
        m_citizens[0].draw();

    }
    // Update the window
    draw_gui();
    app->display();
}

void Game_Manager::draw_gui()
{
	highlight_selected_tile();
	app->setView(view2);
    if(is_menu_visible)
    {
        menu1.draw();
    }

    open_window = false;
    if(m_citizens[0].is_selected())
    {
        citizen_action[0].draw();
        if(m_citizens[0].is_on_city())
        {
            citizen_action[1].draw();
        }
        else citizen_action[2].draw();
    }
    for(int i = 0; i<6; i++)
    {

        if(windows[i].is_activated())
        {
            open_window = true;
            windows[i].draw();
        }
    }

    draw_selection();
    interface1.draw();

    app->setView(view1);
}

void Game_Manager::create_map(int map_width, int map_height)
{
    srand(static_cast<unsigned int>(time(0)));

    //sur 200
    water_rate = 55;
    sand_rate = 90;
    deep_sea_rate = 4;
    deep_sea_expansion_rate = 60;
    for (int i = 0; i <map_width; i++)
    {
        for (int j = 0; j< map_height; j++)
        {
            grid(i, j).type = 2;
            grid(i, j).x_pos = i;
            grid(i, j).y_pos = j;
            grid(i, j).height = 1;
            grid(i, j).zone = 1;
            grid(i, j).passing_through = false;
            grid(i, j).is_city = false;
            grid(i, j).ressource_type = RSC_WOOD;
            grid(i, j).owner = PLAYER2;
            grid(i, j).random_pattern = rand() % +5;

        }
    }
    //perlin noise expreimentation
    PerlinNoise perlin4;
    //perlin4.Set(persistence, frequence, amplitude, octave, 20);
    double noise_value = 0;


    for (int i = 0; i < map_width; i++)
    {
        for (int j = 0; j<map_height; j++)
        {
            noise_value = floor(100 * (perlin4.GetHeight(i, j)));
            if (noise_value <= 0 && noise_value > -15)
            {
                grid(i, j).type = 0;

            }
            if (noise_value <= -15 && noise_value > -35)
            {
                grid(i, j).type = 1;

            }
            if (noise_value <= -35 && noise_value > -50)
            {
                grid(i, j).type = 2;

            }
            if (noise_value <= -50 && noise_value > -75)
            {
                grid(i, j).type = 3;

            }
            if (noise_value <= -75 && noise_value > -100)
            {
                grid(i, j).type = 4;

            }
            if (noise_value > 0 && noise_value <= 35)
            {
                grid(i, j).type = 7;

            }
            if (noise_value > 35 && noise_value <= 50)
            {
                grid(i, j).type = 8;

            }

            //   cout<<noise_value<<endl;
        }
    }
}

void Game_Manager::draw_selection()
{

    if(x_cursor >= 0 && x_cursor < GRID_WIDTH && y_cursor >= 0 && y_cursor < GRID_HEIGHT)
    {
        //show height
        stringstream ss;
        ss << grid(x_cursor, y_cursor).height;
        string str = ss.str();
        string path1 = "height " + str;
        selection_text[0].refill(path1);
        selection_text[0].draw(0 , window_vec.y - 550 , 24);

		stringstream ss2;
		ss2 << grid(x_cursor, y_cursor).x_pos;
		str = ss2.str();
		path1 = "x: " + str;
		selection_text[1].refill(path1);
		selection_text[1].draw(0, window_vec.y - 450, 24);


		stringstream ss3;
		ss3 << grid(x_cursor, y_cursor).y_pos;
		str = ss3.str();
		path1 = "y: " + str;
		selection_text[1].refill(path1);
		selection_text[1].draw(0, window_vec.y - 350, 24);

        tile_description(x_cursor, y_cursor);
    }
}

void Game_Manager::tile_description(int tile_x, int tile_y)
{
    if(grid(tile_x, tile_y).ressource_type == RSC_WOOD)
    {
        tile_info.refill("Fr�ne"); 
    }
    else
    {
        tile_info.refill("Lieu vierge");
    }

    tile_info.draw(0 , window_vec.y - 700 , 24);
}

void Game_Manager::highlight_selected_tile()
{
	if (x_cursor >= 0 && x_cursor < GRID_WIDTH && y_cursor >= 0 && y_cursor < GRID_HEIGHT)
	{
		//highlight selected tile
		selection_sprite.draw((x_cursor - y_cursor)* (Tile::tile_size.x / 2), (x_cursor + y_cursor)* (Tile::tile_size.y / 2));
	}
}

void Game_Manager::handle_mouse_click(sf::Mouse::Button click, Vector2i mouse_vec)
{
    if (x_cursor < 0 || x_cursor >= GRID_WIDTH || y_cursor < 0 || y_cursor >= GRID_HEIGHT)
    {
        return;
    }

    //TODO check all units, not only citizen 0
    if(m_citizens[0].get_sprite().getGlobalBounds().contains(selection_vector) && !m_citizens[0].is_selected())
    {
        if (click == sf::Mouse::Button::Left) {
            std::cout << "Unit selected" << std::endl;
            m_citizens[0].select();
            selected_citizen = 0;
        }
        else if (click == sf::Mouse::Button::Right) {
            // ??
        }
    }
    if(m_citizens[0].is_selected() && (x_cursor != m_citizens[0].get_x() || y_cursor != m_citizens[0].get_y()))
    {
        if (click == sf::Mouse::Button::Right) {
            m_citizens[0].set_goal(x_cursor, y_cursor);
        }
        else if (click == sf::Mouse::Button::Left) {
            m_citizens[0].deselect();
        }
    }
}

int Game_Manager::count_neighbours(unsigned int i, unsigned int j , Caracteristic typeorzoneorheight, int value, bool diagonal)
{
    int number = 0;
    if (i == 0 || j == 0 || j + 1 >= GRID_HEIGHT || i + 1 >= GRID_WIDTH) {
        return 0; //TODO handle this correctly
    }

    if(typeorzoneorheight == CRC_TYPE)
    {
        if(grid(i - 1, j).type == value)
            number++;
        if(grid(i, j + 1).type == value)
            number++;
        if(grid(i, j - 1).type == value)
            number++;
        if(grid(i + 1, j).type == value)
            number++;
        if (diagonal)  //diagonal + sides
        {
            if(grid(i - 1, j + 1).type == value)
                number++;
            if(grid(i - 1, j - 1).type == value)
                number++;
            if(grid(i + 1, j + 1).type == value)
                number++;
            if(grid(i + 1, j - 1).type == value)
                number++;
        }
    }
    if(typeorzoneorheight == CRC_ZONE)
    {
        if(grid(i - 1, j).zone == value)
            number++;
        if(grid(i, j + 1).zone == value)
            number++;
        if(grid(i, j - 1).zone == value)
            number++;
        if(grid(i + 1, j).zone == value)
            number++;
        if (diagonal)
        {
            if(grid(i - 1, j + 1).zone == value)
                number++;
            if(grid(i - 1, j - 1).zone == value)
                number++;
            if(grid(i + 1, j + 1).zone == value)
                number++;
            if(grid(i + 1, j - 1).zone == value)
                number++;
        }
    }
    if(typeorzoneorheight == CRC_HEIGTH)
    {
        if(grid(i - 1, j).height == value)
            number++;
        if(grid(i, j + 1).height == value)
            number++;
        if(grid(i, j - 1).height == value)
            number++;
        if(grid(i + 1, j).height == value)
            number++;
        if (diagonal)
        {
            if(grid(i - 1, j + 1).height == value)
                number++;
            if(grid(i - 1, j - 1).height == value)
                number++;
            if(grid(i + 1, j + 1).height == value)
                number++;
            if(grid(i + 1, j - 1).height == value)
                number++;
        }
    }

    return number;
}

