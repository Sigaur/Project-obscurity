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
	, m_object(0)
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
int Box::setX(int X)
{
	return m_X;
}
int Box::setY(int Y)
{
	return m_Y;
}
int Box::setBackground(int Background)
{
	return m_background;
}
int Box::setObject(int Object)
{
	return m_object;
}
int Box::setMob(int Mob)
{
	return m_mob;
}
int Box::setLight(int Light)
{
	return m_light;
}


/************************            Constructeur Destructeur          *****************************/
/*Box::Box() :_contenu(0), _light(0)
{

	srand(time(0));
	//_pattern = rand() % 10;
	_pattern = _contenu ;

}

Box::Box(int contenu) : _contenu(contenu), _light(0){
    srand(time(0));
	//_pattern = rand() % 10;

	_pattern = _contenu ;

	
}

Box::Box(const Box& arg) : _contenu(arg.getContenu()), _light(arg.getLight()), _pattern(arg.getPattern())
{
	
	//cout << endl << "Box =" << _contenu  << _light << _pattern <<endl;

}


/************************            get set                           *****************************/

/*int		Box::getContenu()const			{ return _contenu; }
void	Box::setContenu(int contenu)	{ _contenu = contenu; }

int		Box::getLight()const			{ return _light; }
void	Box::setLight(int light)		{ _light = light; }

int		Box::getPattern()const			{ return _pattern; }
void	Box::setPattern(int Pattern)	{ _pattern = Pattern; }
/************************          fonction                        *****************************/
/*Box* creationType()//obsolete
{
	Box* list = new Box[NBTYPE];

	list[0].setContenu(0);//vide
	list[1].setContenu(1);//obstacle
	list[2].setContenu(2);//mob
	/*
	list[3].setContenu(3);
	list[4].setContenu(4);
	list[5].setContenu(5);
	*/
		//etc a completer par la suite

/*	return list;
}




void afficher_box(Box box)
{
	//cout << box.getContenu();
}


/************************            operator                          *****************************/
/*bool operator==(const Box& left, const Box& right)
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




