#ifndef SCHEDULE
#define SCHEDULE

#include "string"
#include <vector>

using namespace std;

class Schedule
{
public:

	Schedule();

	~Schedule();

    int solver_td() const;

    int solver_bu() const;

    void reconstruir();

    vector<int> verificador(vector<int>& w);

    vector<vector<int>> solu(vector<int> &w);

    void imprimir();
private:

    int top_down(int i) const;

    int bottom_up() const;

    mutable vector<int> M;

    vector<pair<int, int>> _actividades;

    vector<int> _beneficios;

    int _cantActividades;

    vector<vector<int>> _comienzoAct;

    vector<int> _actDespues;

    vector<int> _solu;
	
};

#endif // !SCHEDULE