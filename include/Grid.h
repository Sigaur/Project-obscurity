#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

#include "My_Sprite.h"
#include "Tile.h"




class Grid
{
public:
    Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app);
    virtual ~Grid() = default;
    void loadFiles();
    //get tile at position
    Tile &operator()(size_t x, size_t y);
    Tile &operator()(Coordinate coord);
    /* Check if coordinate is valid within this grid. */
    bool is_valid(Coordinate coord);
    void draw();
private:
    std::vector<std::vector<Tile> > m_grid;
    sf::View *m_view1;
    sf::RenderWindow *m_app;
    Clock clock1;
    Time time1;
};

