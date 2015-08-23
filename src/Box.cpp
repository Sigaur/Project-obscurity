#include "Box.h"

Box::Box(int Y, int X, int Background, int Object, int Mob, int Light)
	: m_Y (Y)
	, m_X (X)
	, m_background(Background)
	, m_object(Object)
	, m_mob(Mob)
	, m_light(Light)
{
	
}


Box::Box()
	: m_Y(0)
	, m_X(0)
	, m_background(0)
	, m_object(1)
	, m_mob(0)
	, m_light(0)
{

}

int Box::getX()
{
	return m_X;
}
int Box::getY()
{
	return m_Y;
}
int Box::getBackground()
{
	return m_background;
}
int Box::getObject()
{
	return m_object;
}
int Box::getMob()
{
	return m_mob;
}
int Box::getLight()
{
	return m_light;
}

void Box::setX(int X)
{
	 m_X=X;
}
void Box::setY(int Y)
{
	 m_Y=Y;
}
void Box::setBackground(int Background)
{
	m_background = Background;
}
void Box::setObject(int Object)
{
	m_object = Object;
}
void Box::setMob(int Mob)
{
	m_mob = Mob;
}
void Box::setLight(int Light)
{
	m_light = Light;
}

void Box::setMajoriter(int Y, int X, int Background, int Object, int Mob)
{
	m_X = X;
	m_Y = Y;
	m_background = Background;
	m_object = Object;
	m_mob = Mob;
}

/************************            Constructeur Destructeur          *****************************/
/*Box::Box() :_contenu(0), _light(0)
{
=======
#include "..\include\Box.h"
>>>>>>> 689a981898c23e3825850ef45feafa94f5e6bf30







/************************            Constructeur Destructeur          *****************************/
/*Box::Box() :_contenu(0), _light(0), _pattern(0){}

Box::Box(int contenu) : _contenu(contenu), _light(0), _pattern(0){}

	



Box::Box(const Box& arg) : _contenu(arg.getContenu()), _light(arg.getLight()), _pattern(arg.getPattern())
{}

<<<<<<< HEAD
/*int		Box::getContenu()const			{ return _contenu; }
void	Box::setContenu(int contenu)	{ _contenu = contenu; }
=======
>>>>>>> 689a981898c23e3825850ef45feafa94f5e6bf30

/************************            get set                           *****************************/
/*
		int		Box::getContenu()const			{ return _contenu; }
		void	Box::setContenu(int contenu)	{ _contenu = contenu; }
>>>>>>> 689a981898c23e3825850ef45feafa94f5e6bf30

		int		Box::getLight()const			{ return _light; }
		void	Box::setLight(int light)		{ _light = light; }

		int		Box::getPattern()const			{ return _pattern; }
		void	Box::setPattern(int Pattern)	{ _pattern = Pattern; }

/************************          fonction                        *****************************/

/*
void Box::afficher()
{	cout <<getContenu();}


/************************            operator                          *****************************/
/*bool operator==(const Box& left, const Box& right)
=======

bool operator==(const Box& left, const Box& right)
>>>>>>> 689a981898c23e3825850ef45feafa94f5e6bf30
{return left._contenu == right._contenu;}

bool operator!=(const Box& left, const Box& right)
{return !operator==(left, right);}


Box Box::operator = (const Box& original)
{
	this->setContenu(original.getContenu());
	this->setLight(original.getLight());
	this->setPattern(original.getPattern());

	return *this;
}
*/




