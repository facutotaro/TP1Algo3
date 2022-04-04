#ifndef SCHEDULE
#define SCHEDULE

#include "string"
#include <vector>

using namespace std;

class Schedule
{
public:

	Schedule(string nombreDelArchivo);

	~Schedule();

    int solver_td() const;

    int solver_bu() const;

	string nombre() const;

private:
	string _nombreDelArchivo;

    vector<pair<int, int>> _actividades;

    vector<int> _beneficios;

    size_t _cantActividades;

    vector<int> _noColisiones_td;

    vector<int> _noColisiones_bu;

    mutable vector<int> _memo;

    int top_down(int i) const;

    int bottom_up() const;
};

#endif // !SCHEDULE