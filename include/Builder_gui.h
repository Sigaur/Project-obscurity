#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Building.h"
#include "Button.h"
#include "Grid.h"
#include "My_Sprite.h"
#include "My_Text.h"

class Builder_gui
{
public:
    Builder_gui(Grid &grid, RenderWindow *app, View *view, View *view2);
    ~Builder_gui();
    void draw();
    bool is_activated();
    void update();

private : 
    Grid &m_grid;
    View *m_view1, *m_view2;
    RenderWindow *m_app;
    Event event;
    My_Sprite gui_sprite;
    std::vector <Button> m_building_button;
    Button m_cross;
    Building m_building;
    My_Text buildings_name;


};

