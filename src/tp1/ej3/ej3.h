#ifndef SCHEDULE
#define SCHEDULE

#include "string"
#include <vector>
#include <iostream>

using namespace std;

class Schedule
{
public:

	Schedule(string& s);

	~Schedule();

    int solver_td() const;

    int solver_bu() const;

    void reconstruir() const;

    vector<int> verificador(vector<int>& w) const;

    vector<vector<int>> solu(vector<int> &w)const;

    void imprimir()const;
private:

    int top_down(int i) const;

    int bottom_up() const;

    mutable vector<int> M;

    vector<pair<int, int>> _actividades;

    vector<int> _beneficios;

    int _cantActividades;

    vector<vector<int>> _comienzoAct;

    vector<int> _actDespues;

    mutable vector<int> _solu;
	
    string _nombreDelArchivo;
};

#endif // !SCHEDULE