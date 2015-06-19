#include "Info.h"


Info::Info(RenderWindow *app, View *view, int screen_width, int screen_height)
    : m_window(app, "Info", 0.5f, 0.5f, 0, 0, view, screen_width, screen_height)
{
    m_view1 = view;
    m_screen_x = screen_width;
    m_screen_y = screen_height;
    m_app = app;
}


Info::~Info()
{
}

void Info::draw()
{
    m_window.draw();
}


void Info::fill(String name)
{
    m_name = name;
    m_window.set_name(name);
}


void Info::update()
{
    m_window.update();
}