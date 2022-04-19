#ifndef SCHEDULEG
#define SCHEDULEG

#include "string"
#include <vector>
#include <iostream>

using namespace std;

class ScheduleGol
{
public:

	ScheduleGol(string &s);

	~ScheduleGol();

    int solver()const;

    void imprimir()const;

private:
    int _cantActividades;

    vector<pair<int, int>> _actividades;

    mutable vector<int> _sched;

    mutable vector<int> _solu;
    
    string _nombreDelArchivo;
};

#endif // !SCHEDULEG