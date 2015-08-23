#include "..\include\Box.h"



/************************            Constructeur Destructeur          *****************************/
Box::Box() :_contenu(0), _light(0), _pattern(0){}

Box::Box(int contenu) : _contenu(contenu), _light(0), _pattern(0){}

Box::Box(const Box& arg) : _contenu(arg.getContenu()), _light(arg.getLight()), _pattern(arg.getPattern())
{}


/************************            get set                           *****************************/

		int		Box::getContenu()const			{ return _contenu; }
		void	Box::setContenu(int contenu)	{ _contenu = contenu; }

		int		Box::getLight()const			{ return _light; }
		void	Box::setLight(int light)		{ _light = light; }

		int		Box::getPattern()const			{ return _pattern; }
		void	Box::setPattern(int Pattern)	{ _pattern = Pattern; }

/************************          fonction                        *****************************/


void Box::afficher()
{	cout <<getContenu();}


/************************            operator                          *****************************/

bool operator==(const Box& left, const Box& right)
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





