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