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
	void update(float secTime);
	void moveDown();
	void moveUp();
	void setMovable(int set);
	int isMovable();
	int isLight();
	void setLight(int set);

private:
	float m_posY;
	float m_posX;
	float m_energy;
	int m_isMovable;
	int m_isLight;
	float m_totalLight;
	float m_immunityTime;
};