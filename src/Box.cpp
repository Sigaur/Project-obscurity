#include "..\include\Box.h"

Box::Box() :_contenu(0)
{
  
}
Box::Box(int contenu) : _contenu(contenu){
    srand(time(0));
   m_pattern = rand()% 10;
}

Box::Box(const Box& arg) : _contenu(arg.getContenu()){
    srand(time(0));
    m_pattern = rand() % 10;   
    //cout << "random" << m_pattern << endl;

}


int		Box::getContenu()const			{ return _contenu; }
void	Box::setContenu(int contenu)	{ _contenu = contenu; }

int		Box::getLight()const			{ return _light; }
void	Box::setLight(int light)		{ _light = light; }



Box* creationType()
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

int Box::get_pattern()
{
    return m_pattern;
}


void afficher_box(Box box)
{
	//cout << box.getContenu();
}


