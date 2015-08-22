#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "My_Text.h"
#include "My_Sprite.h"

using namespace sf;


class Menu
{
public:
    Menu(RenderWindow *app, View *view1);
    virtual ~Menu() = default;
    void draw();
    bool is_playing();
    bool is_quitting();
    void update();

private:
    RenderWindow *m_app;
    View *m_view1;
    vector<Button> m_button;
    My_Sprite sprite;
    My_Text text1;
    bool m_playing, m_quit;
};

