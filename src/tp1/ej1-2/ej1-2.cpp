#include "ej1-2.h"

RedSocial::RedSocial(std::string s)
{
	_nombreDelArchivo = s;
}

RedSocial::~RedSocial()
{
}

string RedSocial::nombre() const
{
	return _nombreDelArchivo;
}

Actor::Actor(const int ID, const int inf)
{
	id = ID;
	influencia = inf;
}