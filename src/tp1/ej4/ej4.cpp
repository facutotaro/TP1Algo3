#include "ej4.h"

ScheduleGol::ScheduleGol(std::string s)
{
	_nombreDelArchivo = s;
}

ScheduleGol::~ScheduleGol()
{

}

string ScheduleGol::nombre() const
{
	return _nombreDelArchivo;
}