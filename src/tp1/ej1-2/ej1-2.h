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

	void cliqueMasInfluyente(vector<Actor> Q, vector<Actor> K) const;

	static int influenciaDeGrupo(const vector<Actor>& grupo) ;

	void soloAmigosDeQEnK(const vector<Actor>& Q, vector<Actor> K) const;

	void agregarCliqueMasGrandeDeKAQ(vector<Actor> Q, const vector<Actor>& K) const;

	vector<Actor> cliqueMasGrande(const vector<Actor>& grupo) const;

	bool sonAmigos(Actor v, Actor u) const;

	vector<Actor> solver() const;

private:
	string _nombreDelArchivo;
	vector<Actor> _actores;
	vector<pair<int, int>> _amistades;


};



#endif // !REDSOCIAL
