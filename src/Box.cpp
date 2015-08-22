#include "..\include\Box.h"

Box::Box() :_contenu(0)
{
  
}
Box::Box(int contenu) : _contenu(contenu){}
Box::Box(const Box& arg) : _contenu(arg.getContenu()){}


int   Box::getContenu()const{ return _contenu; }
void  Box::setContenu(int contenu){ _contenu = contenu; }





Box* creationType()
{
	Box* list = new Box[NBTYPE];

	list[0].setContenu(0);//vide
	list[1].setContenu(1);//mob
	list[2].setContenu(2);//obstacle

		//etc a completer par la suite

	return list;
}

















Box Box::operator = (const Box& original)
{

	this->setContenu(original.getContenu());

	return *this;
}

void afficher_box(Box box)
{
	cout << box.getContenu();
}


