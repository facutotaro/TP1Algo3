#ifndef REDSOCIAL
#define REDSOCIAL

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

	vector<Actor> actores() const;

	vector<pair<int,int>> amistades() const;

	void cliqueMasInfluyente(vector<Actor> Q, vector<Actor> K);

	static int influenciaDeGrupo(const vector<Actor>& grupo) ;

	void soloAmigosDeQEnK(vector<Actor>& Q, vector<Actor>& K) const;

	void agregarCliqueMasGrandeDeKAQ(vector<Actor>& Q, vector<Actor>& K) const;

	vector<Actor> cliqueMasGrande(vector<Actor> grupo) const;

	Actor masPopular(vector<Actor> grupo) const;

	vector<vector<bool>> matrizDeAmistades();

	bool sonAmigos(Actor v, Actor u) const;

    bool estaEnGrupo(int id, const vector<Actor>& grupo) const;

	void solver();

private:
	string _nombreDelArchivo;
	vector<Actor> _actores;
	vector<pair<int, int>> _amistades;
	vector<vector<bool>> _matrizDeAmistades;


};



#endif // !REDSOCIAL
