#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>

using namespace sf;

using namespace std;

class Player
{
public:
	Player();
	float getPosY();
	float getPosX();
	void draw(float y, float x);

private:
	float m_posY;
	float m_posX;
	float m_energy;
};