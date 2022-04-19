#ifndef SCHEDULEG
#define SCHEDULEG

#include "string"
#include <vector>

using namespace std;

class ScheduleGol
{
public:

	ScheduleGol();

	~ScheduleGol();

    int solver();

    void imprimir();

private:
    int _cantActividades;

    vector<pair<int, int>> _actividades;

    vector<int> _sched;

    vector<int> _solu;
};

#endif // !SCHEDULEG