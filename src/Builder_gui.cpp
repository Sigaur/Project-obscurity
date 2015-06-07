#include "Builder_gui.h"


Builder_gui::Builder_gui(Grid &grid, RenderWindow *app, View *view, View *view2)
    : m_grid(grid)
    ,gui_sprite(app, "ressources/builder_gui.png", view2)
{
    m_view1 = view;
    m_app = app;
}


Builder_gui::~Builder_gui()
{
}

void Builder_gui::draw()
{
    Vector2u windowSize = m_app->getSize();
    gui_sprite.draw(windowSize.x - gui_sprite.get_w(), 0);
}