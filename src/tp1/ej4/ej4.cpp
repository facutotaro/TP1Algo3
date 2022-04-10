#include "ej4.h"
#include <fstream>
#include <utility>
#include <iostream>

ScheduleGol::ScheduleGol(std::string s)
{
	_nombreDelArchivo = s;

    ifstream my_file;
    my_file.open("../ej4/instancias-4/instancias/interval_instance_" + _nombreDelArchivo, ios::in);
    if (!my_file) {
    }
    else {
        my_file >> _cantActividades;

        _actividades = vector<pair<int, int>>(_cantActividades, make_pair(0, 0));
        _sched = vector<int>(2*_cantActividades + 1, -1);

        int i = 0;
        while(!my_file.eof()){
            my_file >> _actividades[i].first;
            my_file >> _actividades[i].second;
            i++;
        }
    }
}

ScheduleGol::~ScheduleGol()
{

}

string ScheduleGol::nombre() const
{
	return _nombreDelArchivo;
}

int ScheduleGol::solver() {
    for(int i = 0; i < _cantActividades; i++){
        if(_sched[_actividades[i].second] == -1){
            _sched[_actividades[i].second] = i;
        } else{
            if(_actividades[_sched[_actividades[i].second]].first < _actividades[i].first){
                _sched[_actividades[i].second] = i;
            }
        }
    }
    vector<int> ordenFin;
    for(int & i : _sched){
        if(i != -1){
            ordenFin.push_back(i);
        }
    }

    int res = 1;
    _solu.push_back(ordenFin[0]);
    for(int i = 1; i < ordenFin.size(); i++){
        if(_actividades[ordenFin[i]].first > _actividades[_solu[_solu.size() - 1]].second){
            _solu.push_back(ordenFin[i]);
            res++;
        }
    }
    return res;
}
