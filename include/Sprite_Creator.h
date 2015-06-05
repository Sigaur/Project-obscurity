#pragma once

#include "My_Sprite.h"
#include "My_window.h"
#include <string>
#include <SFML/Graphics.hpp>

class Sprite_Creator
{
public:
    Sprite_Creator(RenderWindow *app, View *view);
    /*void draw();*/
    string create_character(int sunlight_get, bool woman);
    string create_resources( int resources_id);
    string get_file();
    string get_character_name();
    string get_resource_name();
    float get_solidity();
    float get_flexibility();
    Color color_maker(int red_get, int green_get, int blue_get, bool large_randomness, bool dark);
    virtual ~Sprite_Creator() = default;

private:
    View *m_view1;
    RenderWindow *m_app;

    std::vector<My_Sprite> resources_sprites;
    int sunlight;
    float solidity, flexibility;
    string resource_name;
    string character_name;

};


