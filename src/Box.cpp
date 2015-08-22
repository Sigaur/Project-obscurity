#include "..\include\Box.h"

Box::Box() :_contenu(0){}
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
	list[3].setContenu(3);
	list[4].setContenu(4);
	list[5].setContenu(5);
		//etc a completer par la suite

	return list;
}










bool operator==(const Box& left, const Box& right)
{
	return left._contenu == right._contenu;
}

bool operator!=(const Box& left, const Box& right)
{
	return !operator==(left, right);
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


