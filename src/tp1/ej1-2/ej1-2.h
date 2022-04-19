#ifndef REDSOCIAL
#define REDSOCIAL

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

struct Actor
{
	Actor(int ID, int inf);

	int id;

	int influencia;

    bool operator==(Actor v) const;
};

class RedSocial
{
public:
	RedSocial(string nombreDelArchivo);

	~RedSocial();

	string nombre() const;

	void cliqueMasInfluyente(vector<Actor>& Q, vector<Actor>& K) const;

	static int influenciaDeGrupo(const vector<Actor>& grupo) ;

	void soloAmigosDeQEnK(vector<Actor>& Q, vector<Actor>& K) const;

	void filtrarPopulares(vector<Actor>& Q, vector<Actor>& K, vector<Actor>& sinPopulares) const;

	bool sonAmigos(Actor v, Actor u) const;

    int solver();

private:
	string _nombreDelArchivo;
	vector<Actor> _actores;
	vector<pair<int, int>> _amistades;
	vector<vector<bool>> _matrizDeAmistades;

};



#endif // !REDSOCIAL
