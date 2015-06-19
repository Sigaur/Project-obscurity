#pragma once

#include <vector>
#include "My_Sprite.h"
#include "My_Window.h"
#include "My_Text.h"

class Info
{
public:
    Info(RenderWindow *app, View *view, int screen_width, int screen_height);
    void draw();
    void update();
    void fill(String name);
    virtual ~Info();
private:
    View *m_view1;
    RenderWindow *m_app;
    My_window m_window;

    String m_name;
    My_Text m_name_text;
    int m_screen_y, m_screen_x;
    enum Type
    {
        CITIZEN,
        TILE,
        BUILDING
    };
    Type m_type;

};

