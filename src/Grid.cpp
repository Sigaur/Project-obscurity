#include "Grid.h"


Grid::Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app)
    : m_grid(width, std::vector<Tile>(heigth))
    , m_view1(view1)
    , m_app(app)

{
    clock1.restart();
}

void Grid::loadFiles()
{

    
   
}

Tile &Grid::operator()(size_t x, size_t y)
{
    return m_grid.at(x).at(y);
}

Tile &Grid::operator()(Coordinate coord)
{
    return m_grid.at(coord.m_x).at(coord.m_y);
}

bool Grid::is_valid(Coordinate coord)
{
    return coord.m_x >= 0 && coord.m_x < m_grid.size() && coord.m_y >= 0 && coord.m_y < m_grid.size();
}

void Grid::draw()
{
    for (size_t i = 0; i < m_grid.size(); i++)
    {
        for (size_t j = 0; j < m_grid[0].size(); j++)
        {
            (*this)(i, j).draw();
           
		}
	}
    

}
