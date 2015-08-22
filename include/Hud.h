#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Grid.h"
#include "Info.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_Text.h"
#include "Tile.h"

class Hud
{
public:
    Hud(RenderWindow *app, Grid &grid, View *view, int screen_width, int screen_height);
    void draw();   
    virtual ~Hud() = default;

private:
    View *m_view1;
    RenderWindow *m_app;
    Event event;
    Grid &m_grid;
    int m_screen_width, m_screen_height;
  

};

