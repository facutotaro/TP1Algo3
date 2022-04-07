#ifndef REDSOCIAL
#define REDSOCIAL

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Actor
{
	Actor(const int ID, const int inf);

	int id;

	int influencia;
};

class RedSocial
{
public:
	RedSocial(string nombreDelArchivo);

	~RedSocial();

	string nombre() const;

	vector<Actor> actores();

	vector<pair<int,int>> amistades();

	void cliqueMasInfluyente(vector<Actor> Q, vector<Actor> K);

	int influenciaDeGrupo(vector<Actor> grupo);

	void soloAmigosDeQEnK(vector<Actor> Q, vector<Actor> K);

	void agregarCliqueMasGrandeDeKAQ(vector<Actor> Q, vector<Actor> K);

private:
	string _nombreDelArchivo;
	vector<Actor> _actores;
	vector<pair<int, int>> _amistades;

};



#endif // !REDSOCIAL
