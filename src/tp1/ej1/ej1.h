#ifndef REDSOCIAL1
#define REDSOCIAL1

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


class RedSocialEj1
{
public:
    RedSocialEj1(string nombreDelArchivo);

	~RedSocialEj1();

	string nombre() const;

    void solverEj1();

private:
    struct Actor1
    {
        Actor1(int ID, int inf);

        int id;

        int influencia;

        bool operator==(Actor1 v) const;
    };
    void cliqueMasInfluyente(vector<Actor1>& Q, vector<Actor1>& K) const;

    static int influenciaDeGrupo(const vector<Actor1>& grupo) ;

    void soloAmigosDeQEnK(vector<Actor1>& Q, vector<Actor1>& K) const;

    void filtrarPopulares(vector<Actor1>& Q, vector<Actor1>& K, vector<Actor1>& sinPopulares) const;

    bool sonAmigos(Actor1 v, Actor1 u) const;

	string _nombreDelArchivo;
	vector<Actor1> _actores;
	vector<pair<int, int>> _amistades;
	vector<vector<bool>> _matrizDeAmistades;
    mutable int influenciaMaximaVista1 = -1;
    mutable vector<Actor1> _res;
};



#endif // !REDSOCIAL1
