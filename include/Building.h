#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Glissor.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "Sprite_Creator.h"



class Building
{
public:
    Building(RenderWindow *app_get, View *view_get, int type_get);
    virtual ~Building() = default;
    void draw(int x_get, int y_get);
    void draw();
    string get_file();
    int get_x();
    int get_y();
    void selected();

private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite m_sprite;
    int m_x, m_y, m_type;

    Sprite_Creator m_sprite_creator;
};


