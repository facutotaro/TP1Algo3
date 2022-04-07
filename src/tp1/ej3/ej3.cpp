#include "ej3.h"
#include <fstream>
#include <utility>
#include <iostream>

Schedule::Schedule(std::string s)
{
    _nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open("../ej3/instancias-3/instancias/" + _nombreDelArchivo + ".txt", ios::in);
    if (!my_file) {
    }
    else {
        my_file >> _cantActividades;

        _actividades = vector<pair<int, int>>(_cantActividades, make_pair(0, 0));
        _beneficios = vector<int>(_cantActividades, 0);
        _memo = vector<int>(2*_cantActividades, 0);

        /*_noColisiones_td = vector<int>(_cantActividades, 0);
        _noColisiones_bu = vector<int>(_cantActividades, _cantActividades);
        */

        int i = 0;

        while (!my_file.eof()) {

            my_file >> _actividades[i].first;
            my_file >> _actividades[i].second;
            my_file >> _beneficios[i];

            i++;
        }

    }
    my_file.close();

    /*for(int i = 0; i < _cantActividades; i++) {
        int prox_sin_col = i + 1;
        while (prox_sin_col != _cantActividades) {
            if (_actividades[i].second < _actividades[prox_sin_col].first) {
                break;
            }
            prox_sin_col++;
        }
        _noColisiones_td[i] = prox_sin_col;
    }

    for(int j = _cantActividades - 1; j >= 0; j--) {
        int ant_sin_col = j - 1;
        while (ant_sin_col != -1) {
            if (_actividades[j].first > _actividades[ant_sin_col].second) {
                break;
            }
            ant_sin_col--;
        }
        _noColisiones_bu[j] = ant_sin_col;
    }
    */
}

Schedule::~Schedule()
{

}

string Schedule::nombre() const
{
return _nombreDelArchivo;
}

int Schedule::solver_td() const {
return top_down(0);
}

int Schedule::solver_bu() const {
return bottom_up();
}

int Schedule::top_down(int i) const {
    if(i == _cantActividades) {
        _memo[_actividades[i - 1].second] = 0;
        return _memo[_actividades[i - 1].second];
    }
    if(_memo[_actividades[i].first] == 0){
            int t_i = _actividades[i].second + 1;
            int j = i + 1;
            while(j < _cantActividades && t_i > _actividades[j].first){
                j++;
            }
            int maximo = 0;
            for(int k = j; k < _cantActividades; k++){
                maximo = max(maximo, top_down(k));
            }
            _memo[_actividades[i].first] = max(_beneficios[i] + maximo, top_down(i + 1));
        /*int prox_sin_col = _noColisiones_td[i];
        while(prox_sin_col != _cantActividades){
            if(_actividades[i].second <= _actividades[prox_sin_col].first){
                break;
            }
            prox_sin_col++;
        }
        _memo[i] = max(_beneficios[i] + top_down(prox_sin_col), top_down(i + 1));*/
        }
    return _memo[_actividades[i].first];
}

int Schedule::bottom_up() const {
    vector<int> M(2*_cantActividades+1, 0);
    /*vector<int> M(_cantActividades, 0);
    M[0] = _beneficios[0];
    for(int j = 1; j < _cantActividades; j++){
        if(_actividades[j].first > _actividades[j-1].second){
            M[j] = M[j-1] + _beneficios[j];
        } else{
            int idx = _noColisiones_bu[j];
            int ant_sin_col;
            if(idx != -1){
                ant_sin_col = M[idx];
            } else{
                ant_sin_col = 0;
            }
            M[j] = _beneficios[j] + ant_sin_col;
        }
    }
    return M[_cantActividades - 1];*/
    int idx = _cantActividades;
    for (int i = M.size()-2; i >=0 ; i--;)
    {
        if (idx >= 0)
        {
            if (i > _actividades[idx].first)
            {
                M[i] = M[i + 1];
            }
            else
            {
                M[i] = max(_beneficios[idx] + M[_actividades[idx].second + 1], M[i], M[i+1]);
                idx--;
            }
        }
        else
        {
            M[i] = M[i + 1];
        }
    }
    return M[0];
}

vector<pair<int, int>> Schedule::reconstruir() const {
}