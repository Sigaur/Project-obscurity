#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "Box.h"
#include "Button.h"
#include "Key_event.h"
#include "Grid.h"
#include "Hud.h"
#include "Info.h"
#include "Level.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "Player.h"

#include "Random.h"
/*#define NBCASE 5
#define NBLIGNE 20
#define NBCAILLOU 2
#define NBMOB 2*/
#define MAXY 5
#define MAXX 200
using namespace sf;

enum Caracteristic {
    CRC_TYPE,
    CRC_ZONE,
    CRC_HEIGTH
};

enum Zoom_change { ZOOM_NO_CHANGE, ZOOM_ADD, ZOOM_LESS };

class Game_Manager
{
public:
	Game_Manager(RenderWindow *app, View &view1, View &view2, int screen_x, int screen_y);
    void draw();
    void quit();
	void update(float secTime);
    void show_action_button(Button &button);
    void set_info();
    void set_building_menu();
    void create_city(int x, int y);


    void afficherMapobjet(Box Map[MAXY][MAXX]);
    void afficherMapLight(Box Map[MAXY][MAXX]);

	void CreationMonde1obsolete1(int difficulter);
	void CreationMonde1obsolete2(int difficulter);
	void CreationMonde1(int difficulter);
	void CreationMonde2(int difficulter);//monde que de mob
	void CreationMonde3(int difficulter);//monde sans mob
	void CreationMonde4(int difficulter);

	void passagesecuriser(int colonne, int difficulter);
	void passagesecuriserMonde1(int difficulter);
	void passagesecuriserMonde3(int difficulter);
	int  modifcourant(int actuel);

	void resetMap();
	void Lumiere(int portee);

    virtual ~Game_Manager() = default;
    Hud interface1;

private:
    void create_map(int map_width, int map_height);
    void draw_tile(int type, int, int);
    void draw_gui();
    int count_neighbours(unsigned int i, unsigned int j , Caracteristic typeorzoneorheight, int value, bool diagonal);
    void draw_selection();
	void handle_mouse_click(sf::Mouse::Button click, Vector2i mouse_vec);
    bool handle_input_events();
    void update_units();
	void highlight_selected_tile();
    void execute_action(Action action);
    void handle_mouse_at_window_border(int x_mouse, int y_mouse);

    Key_event_handler key_event;
    RenderWindow *m_app;
    View m_view1;
    View m_view2;
    Vector2u window_vec;
    //mouse related stuff:
    Vector2f m_selection_vector;
    int m_x_cursor, m_y_cursor;

    Texture tile_texture[10];
    bool is_menu_visible, is_building_menu;
    bool is_building_selected;
    bool m_mouse_over_actions;

    Menu menu1;
    bool open_window, is_info;
    int x_offset;
    int y_offset;


    static const int GRID_WIDTH = 40;
    static const int GRID_HEIGHT = 40;
    Grid m_grid;

    Info m_info;

    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels

    My_Sprite selection_sprite;
    vector<My_Sprite> m_box_sprites;
    vector<My_Sprite> m_box_background;
    vector<My_Sprite> m_light_sprites;
    My_Sprite action_sprite;
    My_Sprite light_bar;
    My_Sprite light_bar_background;
    My_Sprite light_bar_grad;
    My_Sprite mob_sprite;
    My_Text selection_text[5], tile_info;
    My_Text energy_text;
	/////////////////NEW
	Player myPlayer;
	My_Sprite world_sprite;
	Box Map[MAXY][MAXX];//[5][20]
	
}; 




#endif // GAME_MANAGER_H
