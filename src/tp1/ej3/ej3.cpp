#include "ej3.h"

Schedule::Schedule(std::string s)
{
	_nombreDelArchivo = s;
    _actividades = vector<pair<int, int>>(5, make_pair(0, 0));
    _cantActividades = _actividades.size();
    _beneficios = vector<int>(_cantActividades, 0);
    _memo = vector<int>(_cantActividades + 1, -1);

    _noColisiones_td = vector<int>(_cantActividades, 0);
    _noColisiones_bu = vector<int>(_cantActividades, 0);
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
    if(_memo[i] == -1){
        if(i == _cantActividades){
            _memo[i] = 0;
        } else {
            int prox_sin_col = _noColisiones_td[i];
            /*while(prox_sin_col != _cantActividades){
                if(_actividades[i].second <= _actividades[prox_sin_col].first){
                    break;
                }
                prox_sin_col++;
            }
            */
            _memo[i] = max(_beneficios[i] + top_down(prox_sin_col), top_down(i + 1));
        }
    }
    return _memo[i];
}

int Schedule::bottom_up() const {
    vector<int> M(_cantActividades, 0);
    M[0] = _beneficios[0];
    for(int j = 1; j < _cantActividades; j++){
        if(_actividades[j].first >= _actividades[j-1].second){
            M[j] = M[j-1] + _beneficios[j];
        } else{
            M[j] = max(_beneficios[j] + M[_noColisiones_bu[j]], M[j - 1]);
        }
    }
    return M[_cantActividades - 1];
}
