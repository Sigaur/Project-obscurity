#include "Building.h"

Building::Building(RenderWindow *app, View *view, int type)
: m_sprite(m_app, "ressources/empty.png", m_view1) 
{
    m_app = app;
    m_view1 = view;

    m_x = 0;
    m_y = 0;
    m_type = type;
}

void Building::draw(int x_get, int y_get)
{
    m_sprite.draw(x_get, y_get);
}
