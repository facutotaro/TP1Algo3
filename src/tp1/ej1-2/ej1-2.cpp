#include "ej1-2.h"

RedSocial::RedSocial(std::string s)
{
	_nombreDelArchivo = std::move(s);

    ifstream my_file;
    my_file.open("../ej1-2/instancias-ej1-2/" + _nombreDelArchivo + ".clq", ios::in);
    if (!my_file) {
    }
    else {
        int N = 0; 
		int M = 0;
		
		my_file >> N; 
		my_file >> M;

        _actores = vector<Actor>(N, Actor(0,0));
        _amistades = vector<pair<int, int>>(M, make_pair(0,0));

        int i = 0;

        while (i < N) {
			Actor actor = Actor(0, 0);
			my_file >> actor.id;
			my_file >> actor.influencia;
			_actores[i] = actor;
            i++;
        }

		while (i < M) {
			my_file >> _amistades[i].first; 
			my_file >> _amistades[i].second;
			i++;
		}

    }
    my_file.close();
}

RedSocial::~RedSocial()
{
	
}

string RedSocial::nombre() const
{
	return _nombreDelArchivo;
}

Actor::Actor(const int ID, const int inf)
{
	id = ID;
	influencia = inf;
}

