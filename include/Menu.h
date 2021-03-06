#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "My_Text.h"
#include "My_Sprite.h"
#include "utilitaire.h"

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
	int getWorld();
	int getDifficulte();

private:
    RenderWindow *m_app;
    My_Sprite help;

    View *m_view1;
    vector<Button> m_button;
    My_Sprite sprite;
    My_Text text1;
	My_Text text2;
    bool m_playing, m_quit;
	int monde;
	int difficulte;

};

