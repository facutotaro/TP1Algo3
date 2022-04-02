#ifndef SCHEDULEG
#define SCHEDULEG

#include "string"

using namespace std;

class ScheduleGol
{
public:

	ScheduleGol(string nombreDelArchivo);

	~ScheduleGol();

	string nombre() const; 

private:
	string _nombreDelArchivo;
};

#endif // !SCHEDULEG