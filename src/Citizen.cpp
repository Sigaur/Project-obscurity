#include "Citizen.h"

Citizen::Citizen(Grid &grid, RenderWindow *app, View *view, View *view2, Game_Manager &game_manager)
    : m_grid(grid)
    , m_sprite_creator1(app, m_view1)
    , m_goal_sprite(app, "ressources/goal.png", m_view1)
    , m_sprite(app, m_sprite_creator1.create_character(5, GDR_WOMAN), m_view1)
    , m_game_manager(game_manager)
{
    over_city = false;
    m_has_goal = false;
    m_move_clock.restart();
    m_view1 = view;
    m_app = app;

    static int i = 0; //TODO in reality two units should never be on the same tile
    m_x = i++;
    m_y = i++;
    path_place = 0;
    path_number = 0;
    m_is_selected = false;

    m_name.init(app, m_sprite_creator1.create_character_name(GDR_WOMAN), 25,  1);

    m_citizen_actions.push_back(Button{ app, "Fonder une ville", 0, 0, 0, 0, view2 });
    m_citizen_actions.push_back(Button{ app, "Rentrer dans la ville", 0, 0, 0, 0, view2 });
    m_citizen_actions.push_back(Button{ app, "Observer la ressource", 0, 0, 0, 0, view2 });
}

int Citizen::get_x()
{
    return m_x;
}

int Citizen::get_y()
{
    return m_y;
}

bool Citizen::get_goal()
{
    return m_has_goal;
}

void Citizen::draw()
{
    m_sprite.draw( ( m_x - m_y) * 64 + 50, (m_y +m_x) * 32 );
    m_name.draw(( m_x - m_y)  * 64, ( m_x + m_y - 1)  * 32 - 10, 10);

    if(m_has_goal)
    {
        m_goal_sprite.draw( ( m_goal_x - m_goal_y) * 64, (m_goal_x +m_goal_y) * 32);
    }

    if (is_selected())
    {
        m_citizen_actions[0].draw();
        if (is_on_city())
        {
            m_citizen_actions[1].draw();
        }
        else
        {
            m_citizen_actions[2].draw();
        }
    }
}

void Citizen::set_goal(int goal_x , int goal_y)
{
    if (m_has_goal) {
        // to reset pass_through tiles
        reset_goal();
    }

    path_place = 0;
    m_goal_x = goal_x;
    m_goal_y = goal_y;
    m_has_goal = true;
    find_path_to_goal();
}

void Citizen::reset_goal()
{
    for(Coordinate coord : m_move_path)
    {
        m_grid(coord.m_x, coord.m_y).passing_through = false;
    }
    m_move_path.clear();
}

/* This does not avoid obstacles. */
void Citizen::find_path_basic()
{
    m_move_path.push_back(Coordinate{ get_x(), get_y() });
    while (1)
    {
        int next_x;
        if (m_move_path.back().m_x < m_goal_x)
        {
            next_x = m_move_path.back().m_x + 1;
        }
        else if (m_move_path.back().m_x > m_goal_x)
        {
            next_x = m_move_path.back().m_x - 1;
        }
        else next_x = m_move_path.back().m_x;

        int next_y;
        if (m_move_path.back().m_y < m_goal_y)
        {
            next_y = m_move_path.back().m_y + 1;
        }
        else if (m_move_path.back().m_y > m_goal_y)
        {
            next_y = m_move_path.back().m_y - 1;
        }
        else next_y = m_move_path.back().m_y;
        
        m_move_path.push_back(Coordinate{ next_x, next_y });

        m_grid(next_x, next_y).passing_through = true;

        if (next_x == m_goal_x && next_y == m_goal_y)
        {
            break;
        }
    }
}

/* This avoids obstacles (water, mountain, etc.) . */
void Citizen::find_path_advanced()
{
    //a* homemade :)

}

void Citizen::find_path_to_goal()
{
    find_path_basic();
    //find_path_advanced();
}

void Citizen::select()
{
    m_is_selected = true;
    m_sprite.add_color(90, 120, 40, 255);
}

void Citizen::deselect()
{
    m_is_selected = false;
    m_sprite.add_color(255, 255, 255, 255);

}

void Citizen::on_city()
{
    over_city  = true;
}

bool Citizen::is_on_city()
{
    return over_city;
}

Sprite Citizen::get_sprite()
{
    return m_sprite.get_sprite();
}

bool Citizen::is_selected()
{
    return m_is_selected;
}

void Citizen::update()
{
    Time elapsed_move = m_move_clock.getElapsedTime();
    if(m_has_goal && m_x == m_goal_x && m_y == m_goal_y)
    {
        path_place = 0;
        m_has_goal = false;
        over_city = false;
    }

    if(elapsed_move.asSeconds() >  0.5 && m_has_goal && !m_move_path.empty())
    {
        m_move_clock.restart();
        m_x = m_move_path[0].m_x;
        m_y = m_move_path[0].m_y;
        m_grid(m_x, m_y).passing_through = false;
        m_move_path.pop_front();
        //cout << "move to (" << x << ", " << y << ")\n";
    }


    //0->fonder une ville
    //1->rentrer dans la ville
    //2->observer la ressource
    if (is_selected())
    {
        m_game_manager.show_action_button(m_citizen_actions[0]);
    }

    if (m_citizen_actions[0].is_activated())
    {
        m_game_manager.create_city(get_x(), get_y());

    }
    if (m_citizen_actions[2].is_activated())  //l'action sur la ressource
    {
        //TODO
        //m_cities.push_back(City{ m_app, &m_view1, m_units[0]->get_x(), m_units[0]->get_y(), Tile::tile_size.x, Tile::tile_size.y });
        // windows[1].init(app, "Action", 550, 400, w/2, h/2, &view1);

        //m_grid(get_x(), get_x()).is_city = true;
    }
    if (m_grid(get_x(), get_y()).is_city == true)
    {
        on_city();
    }
}

void Citizen::handle_mouse_click(Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor)
{
    if (get_sprite().getGlobalBounds().contains(selection_vector) && !is_selected())
    {
        if (click == sf::Mouse::Button::Left) {
            std::cout << "Unit selected" << std::endl;
            select();
        }
        else if (click == sf::Mouse::Button::Right) {
            // ??
        }
    }
    if (is_selected() && (x_cursor != get_x() || y_cursor != get_y()))
    {
        if (click == sf::Mouse::Button::Right) {
            set_goal(x_cursor, y_cursor);
        }
        else if (click == sf::Mouse::Button::Left) {
            deselect();
        }
    }
}
