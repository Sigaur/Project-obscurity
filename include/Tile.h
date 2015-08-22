#pragma once

#include <memory>
#include <string>
#include <vector>

#include "My_Sprite.h"


struct Tile_dimension
{
    int m_w;
    int m_h;
};

struct Coordinate
{
    Coordinate(int x = 0, int y = 0)
    {
        m_x = x;
        m_y = y;
    }
    friend bool operator==(const Coordinate& lhs, const Coordinate& rhs){ 
        /* do actual comparison */
        return lhs.m_x == rhs.m_x &&
            lhs.m_y == rhs.m_y;
    }
    friend bool operator!=(const Coordinate& lhs, const Coordinate& rhs){ return !operator==(lhs, rhs); }
    //necessary to use Coordinate as key of an std::map
    friend bool operator< (const Coordinate& lhs, const Coordinate& rhs){
        /* do actual comparison */ 
        if (lhs.m_x < rhs.m_x) {
            return true;
        }
        else if (lhs.m_x == rhs.m_x && lhs.m_y < rhs.m_y) {
            return true;
        }
        else {
            return false;
        }
    }
    friend bool operator>(const Coordinate& lhs, const Coordinate& rhs){ return  operator< (rhs, lhs); }
    friend bool operator<=(const Coordinate& lhs, const Coordinate& rhs){ return !operator> (lhs, rhs); }
    friend bool operator>=(const Coordinate& lhs, const Coordinate& rhs){ return !operator< (lhs, rhs); }

    int m_x;
    int m_y;
};


class Tile
{
public:
    Tile();
    void draw();
	void moveTo(int x, int y);
    void set_building();
    static const int TILE_WIDTH = 128;
    static const int TILE_HEIGHT = 64;
    //used as index of m_tile_sprites
    int m_type;
    int random_pattern;
    int influence_point;
    int m_x_pos;
    int m_y_pos;
    //true if the path of a unit is crossing this tile
    static vector<My_Sprite> m_tile_sprites;
    static const Tile_dimension tile_size;

};
