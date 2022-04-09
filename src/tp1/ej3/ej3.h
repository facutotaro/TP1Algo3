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

    vector<int> reconstruir();

    vector<int> verificador(vector<int>& w);

    vector<vector<int>> solu(vector<int> &w);
private:

    int top_down(int i) const;

    int bottom_up() const;

    string _nombreDelArchivo;

    mutable vector<int> M;

    vector<pair<int, int>> _actividades;

    vector<int> _beneficios;

    int _cantActividades;

    vector<vector<int>> _comienzoAct;

    vector<int> _actDespues;
	
};

#endif // !SCHEDULE