#ifndef SCHEDULEG
#define SCHEDULEG

#include "string"
#include <vector>

using namespace std;

class ScheduleGol
{
public:

	ScheduleGol(string nombreDelArchivo);

	~ScheduleGol();

    int solver();

	string nombre() const; 

private:
	string _nombreDelArchivo;

    int _cantActividades;

    vector<pair<int, int>> _actividades;

    vector<int> _sched;

    vector<int> _solu;
};

#endif // !SCHEDULEG