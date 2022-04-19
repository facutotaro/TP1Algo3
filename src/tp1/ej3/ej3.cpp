#include "ej3.h"
#include <fstream>
#include <utility>
#include <iostream>

Schedule::Schedule(string &s)
{
    _nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open(_nombreDelArchivo, ios::in);
    if (!my_file) {
    }
    else {
        my_file >> _cantActividades;

        _actividades = vector<pair<int, int>>(_cantActividades, make_pair(0, 0));
        _beneficios = vector<int>(_cantActividades, 0);
        _comienzoAct = vector<vector<int>>(2 * _cantActividades+2, vector<int>());
        _actDespues = vector<int>(_cantActividades, 0);
        M = vector<int>(_cantActividades + 1, 0);

        int i = 0;

        while (!my_file.eof()&&i<_cantActividades) {

            my_file >> _actividades[i].first;
            my_file >> _actividades[i].second;
            my_file >> _beneficios[i];

            i++;
        }

    }
    my_file.close();
    //Creamos un vector de vectores con la hora a la que comienza una actividad
    for (int i = 0; i < _cantActividades; i++)
    {
        _comienzoAct[_actividades[i].first].push_back(i);
    }
    int j = _comienzoAct.size()-1;
    //Recorremos las este vector y a las que no tienen hora, le agregamos el numero de la siguiente actividad que comienza
    while (j >= 0 && _comienzoAct[j].empty())
    {
        _comienzoAct[j].push_back(_cantActividades);
        j--;
    }
    for (int i = j; i >= 0; i--)
    {
        if (_comienzoAct[i].empty())
        {
            _comienzoAct[i].push_back(_comienzoAct[i+1][0]);
        }
    }
    //Ahora, queremos tener cual es la inmediata actividad que arranca despues. Entonces, relleamos con el primer elemento de los vectores del vector de vectores
    //anterior, que, por como lo construimos, tiene la proxima actividad que empieza despues de cada hora
    for (int i = 0; i < _actDespues.size(); i++)
    {
        _actDespues[i] = _comienzoAct[_actividades[i].second + 1][0];
    }

    vector<int> _solu;
}

Schedule::~Schedule()
{

}

int Schedule::solver_td() const {
    return top_down(0);
}

int Schedule::solver_bu() const {
    return bottom_up();
}

int Schedule::top_down(int i) const {
    if (i == _cantActividades) return 0;
    else
    {
        if (M[i] == 0)
        {
            //Si no se calcul� el beneficio hasta la siguiente actividad lo calculo, y sin� lo uso. Y lo compara con el beneficio de la
            //actividad actual con el llamado recursivo del conjunto de actividades que arrancan despues de que esta termina
            M[i] = max(M[i+1] == 0 ? top_down(i+1) : M[i+1], _beneficios[i] + top_down(_actDespues[i]));
        }
    }
    return M[i];
}

int Schedule::bottom_up() const {
    M[_cantActividades] = 0;
    for (int i = _cantActividades-1; i >=1; i--)
    {   
        //M[i] almacena el beneficio maximo entre la actividad i y la n-1
        //Luego, para completarlo, tomamos el maximo entre no meter a la actividad (M[i+1]) o meterla y sumar el 
        //maximo del conjunto de actividades que arrancan despues de ella
        M[i] = max(M[_actDespues[i]] + _beneficios[i], M[i + 1]);
    }
    M[0] = max(M[_actDespues[0]] + _beneficios[0], M[0 + 1]);
    return M[0];
}

void Schedule::reconstruir()const
{
    int i = 0;
    //La idea es la siguiente. 
    //Como para M[i] vamos acumulando el beneficio m�ximo entre las actividades i y n-1
    //y todas las actividades tienen beneficio mayor a 0, entonces si M[i] es mayor que M[i+1] significa que insertamos a la actividad i
    //Luego, saltamos a la casilla de la primera actividad que se puede realizar despues de que termine la actividad i y seguimos la misma l�gica
    //Tanto en td como bu vamos a llenar todas las casiillas porque en cada actividad llamamos a la siguiente
    while(i < _cantActividades)
    {
        while (i < _cantActividades && M[i] == M[i + 1])
        {
            i++;
        }
        _solu.push_back(i);
        i = _actDespues[i];
    }
}


//Verifica si el fin de una actividad es antes del comienzo de otra
vector<int> Schedule::verificador(vector<int> &w)const
{
    vector<int> v;
    for (int i = 0; i < w.size(); i++)
    {
        for (int j = i+1; j < w.size(); j++)
        {
            if (_actividades[w[i]].second >= _actividades[w[j]].first)
            {
                v.push_back(w[i]);
                break;
            }
        }
    }
    return v;
}


//Reconstruye una matriz con el comienzo, fin y beneficio, y el acumulado de los beneficios de un vector con el indice de las actividades
vector<vector<int>> Schedule::solu(vector<int> &w)const
{
    vector<vector<int>> v;
    vector<int> k;
    k.push_back(_actividades[w[0]].first);
    k.push_back(_actividades[w[0]].second);
    k.push_back(_beneficios[w[0]]);
    k.push_back(_beneficios[w[0]]);
    v.push_back(k);
    for (int i = 1; i < w.size(); i++)
    {
        vector<int> k;
        k.push_back(_actividades[w[i]].first);
        k.push_back(_actividades[w[i]].second);
        k.push_back(_beneficios[w[i]]);
        k.push_back(v[i - 1][3] + _beneficios[w[i]]);
        v.push_back(k);
    }
    return v;
}

void Schedule::imprimir()const
{
    for (int i = 0; i < _solu.size(); i++)
    {
        cout << _solu[i] << " ";
    }
}