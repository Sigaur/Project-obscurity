#include "Menu.h"

Menu::Menu(RenderWindow *app, View *view1)
    : sprite(app, "resources/menu_background.png", view1)
{
    m_app = app;
    m_view1 = view1;

    text1.init(app, "Dark isn't dull", 24, 0);
    m_button.push_back(Button{ app, "to play", 0, 0, 1920, 1080, m_view1 });
    m_button.push_back(Button{ app, "to quit", 0, 0, 1920, 1080, m_view1 });
    m_playing = false;
    m_quit = false;
}

void Menu::draw()
{
    text1.draw(0, 0, 22);
    sprite.draw(0, 0);
    m_button[0].draw();
    m_button[1].draw();

}

void Menu::update()
{
    m_button[0].update(500, 500);
    if (m_button[0].is_activated())
    {
        m_button[0].desactivate();
        m_playing = true;
    }

    m_button[1].update(600, 600);
    if (m_button[1].is_activated())
    {
        m_button[1].desactivate();
        m_quit = true;
    }

}

bool Menu::is_playing()
{
    return m_playing;
}
bool Menu::is_quitting()
{
    return m_quit;
}