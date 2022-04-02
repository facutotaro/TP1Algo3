#include "ej3.h"

Schedule::Schedule(std::string s)
{
	_nombreDelArchivo = s;
}

Schedule::~Schedule()
{

}

string Schedule::nombre() const
{
	return _nombreDelArchivo;
}