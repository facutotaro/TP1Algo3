#include "ej4.h"
#include <fstream>
#include <utility>
#include <iostream>

ScheduleGol::ScheduleGol(string &s)
{
    _nombreDelArchivo = s;

    ifstream my_file;
    my_file.open(_nombreDelArchivo, ios::in);
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

int ScheduleGol::solver()const{
    for(int i = 0; i < _cantActividades; i++){
        if(_sched[_actividades[i].second] == -1){
            _sched[_actividades[i].second] = i;
        } else{
            if(_actividades[_sched[_actividades[i].second]].first < _actividades[i].first){
                _sched[_actividades[i].second] = i;
            }
        }
    }

    /* Ponemos en nuestro vector _sched (de 2n + 1 posiciones) las actividades según su tiempo de
     * finalización. Si tenemos dos actividades que terminan a la misma hora, priorizamos las más cortas.
     */

    vector<int> ordenFin;
    for(int & i : _sched){
        if(i != -1){
            ordenFin.push_back(i);
        }
    }

    /* Ahora a medida que van apareciendo actividades en el vector _sched, es decir recorriendo de
     * izquierda a derecha y salteandonos las posiciones de _sched que tienen -1, agregamos las
     * actividades en orden de tiempo de finalización en un vector ordenFin.
     */

    int res = 1;
    _solu.push_back(ordenFin[0]);
    for(int i = 1; i < ordenFin.size(); i++){
        if(_actividades[ordenFin[i]].first > _actividades[_solu[_solu.size() - 1]].second){
            _solu.push_back(ordenFin[i]);
            res++;
        }
    }

    /* La variable res representa la solución del problema, que es cuántas actividades voy a poder
     * hacer teniendo en cuenta que el beneficio de cada actividad es 1. Por otro lado, yo sé que
     * siempre voy a querer agarrarme la actividad que más temprano termine e inductivamente (luego
     * se usa este dato en la demostración) el caso base se da con el conjunto de actividades
     * seleccionadas vacío, por lo que siguiendo la estrategia agregaríamos la actividad que más
     * temprano finaliza (linea 67, coincide con la primera de ordenFin). Luego recorremos todo
     * ordenFin y si encontramos una actividad que no solape horarios con la última actividad agregada
     * incrementamos la solución y agregamos la actividad al vector solución.
     */

    return res;
}

void ScheduleGol::imprimir()const
{
    for (int i = 0; i < _solu.size(); i++)
    {
        cout << _solu[i] << " ";
    }
}