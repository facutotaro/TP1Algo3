#ifndef REDSOCIAL2
#define REDSOCIAL2

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class RedSocialEj2
{
public:
    RedSocialEj2(string nombreDelArchivo);

    ~RedSocialEj2();

    string nombre() const;

    void solverEj2();

private:
    struct Actor2
    {
        Actor2(int ID, int inf);

        int id;

        int influencia;

        bool operator==(Actor2 v) const;
    };

    void cliqueMasInfluyente(vector<Actor2>& Q, vector<Actor2>& K) const;

    static int influenciaDeGrupo(const vector<Actor2>& grupo) ;

    int influenciaGruposIndependientes(vector<vector<Actor2>>& I, vector<Actor2>& K) const;

    void soloAmigosDeQEnK(vector<Actor2>& Q, vector<Actor2>& K) const;

    void filtrarPopulares(vector<Actor2>& Q, vector<Actor2>& K, vector<Actor2>& sinPopulares) const;

    bool sonAmigos(Actor2 v, Actor2 u) const;

    bool noTieneAmigos(const vector<Actor2>& grupo, Actor2 a) const;

    string _nombreDelArchivo;
    vector<Actor2> _actores;
    vector<pair<int, int>> _amistades;
    vector<vector<bool>> _matrizDeAmistades;
    mutable int influenciaMaximaVista2;
    mutable vector<Actor2> _res;


};

#endif // !REDSOCIAL2
