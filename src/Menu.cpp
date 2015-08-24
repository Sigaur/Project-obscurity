#include "Menu.h"

Menu::Menu(RenderWindow *app, View *view1)
    : sprite(app, "resources/menu_background.png", view1)
{
    m_app = app;
    m_view1 = view1;

    text1.init(app, "Dark isn't dull", 24, 1);
    m_button.push_back(Button{ app, "to play", 0, 0, 1920, 1080, m_view1 });
    m_button.push_back(Button{ app, "to quit", 0, 0, 1920, 1080, m_view1 });

	m_button.push_back(Button{ app, "how play", 0, 0, 1920, 1080, m_view1 });

	text2.init(app, "Change world", 24, 1);
	m_button.push_back(Button{ app, "world ", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "world Classic", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "time to eat", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "peacefull", 0, 0, 1920, 1080, m_view1 });
	m_button.push_back(Button{ app, "easy", 0, 0, 1920, 1080, m_view1 });


    m_playing = false;
    m_quit = false;
	monde = 1;
	difficulte = 1;
}


	

void Menu::draw()
{
    sprite.draw(0, 0);
    m_button[0].draw();
    m_button[1].draw();
	m_button[2].draw();
	m_button[3].draw();
	m_button[4].draw();
	m_button[5].draw();
	m_button[6].draw();


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

	m_button[2].update(550, 550);
	if (m_button[2].is_activated())
	{
		m_button[2].desactivate();
		m_playing = true;
	}

	m_button[3].update(1400, 800);
	if (m_button[3].is_activated())
	{
		monde = 1;
		(4);
		m_button[3].desactivate();
		m_playing = true;
	}

	m_button[4].update(1400, 700);
	if (m_button[4].is_activated())
	{
		monde = 2;
		m_button[4].desactivate();
		m_playing = true;
	}

	m_button[5].update(1400, 600);
	if (m_button[5].is_activated())
	{
		monde = 3;
		m_button[5].desactivate();
		m_playing = true;
	}

	m_button[6].update(1400, 500);
	if (m_button[6].is_activated())
	{
		monde = 4;
		m_button[6].desactivate();
		m_playing = true;
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