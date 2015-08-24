#include "Menu.h"

Menu::Menu(RenderWindow *app, View *view1)
: help(app, "resources/help.png", view1)

    , sprite(app, "resources/menu_background.png", view1)
{
    m_app = app;
    m_view1 = view1;

    text1.init(app, "Dark isn't dull", 24, 1);
    m_button.push_back(Button{ app, "to play", 0, 0, 1920, 1080, m_view1 });
    m_button.push_back(Button{ app, "to quit", 0, 0, 1920, 1080, m_view1 });

	m_button.push_back(Button{ app, "how play", 0, 0, 1920, 1080, m_view1 });

	text2.init(app, "Change world", 24, 1);
	m_button.push_back(Button{ app, "World ", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "World Classic", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "Time to eat", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "Peacefull", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "Easy", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "Checkerboard (HARD)", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "Light burnt", 0, 0, 1920, 1080, m_view1 });

    m_playing = false;
    m_quit = false;
	monde = 1;
	difficulte = 1;
}


	

void Menu::draw()
{
    sprite.draw(0, 0);

    m_button[2].update(550, 550);
    if (m_button[2].is_activated())
    {
        help.draw(0, 0);
    }
	for (int i = 0; i < 10; i++)
	{
		m_button[i].draw();
	}

    text1.draw(200, 300, 80);
	text2.draw(1400, 900, 50);
}

void Menu::update()
{

	
    m_button[0].update(500, 500);
    if (m_button[0].is_activated())
    {
		monde = 1;
        m_button[0].desactivate();
        m_playing = true;
    }

    m_button[1].update(600, 600);
    if (m_button[1].is_activated())
    {
        m_button[1].desactivate();
        m_quit = true;
    }



	for (int i = 0; i < 7; i++)
	{
		m_button[3+i].update(1400, 800-i*100);
		if (m_button[3+i].is_activated())
		{
			monde = 1+i;
			m_button[3+i].desactivate();
			m_playing = true;
		}
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

int Menu::getWorld()
{ 
	return monde; 
}

int Menu::getDifficulte()
{
	return difficulte;
}