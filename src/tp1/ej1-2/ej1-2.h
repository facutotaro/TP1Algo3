#ifndef REDSOCIAL
#define REDSOCIAL

#include "string"
#include <vector>

using namespace std;

class RedSocial
{
public:
	RedSocial(string nombreDelArchivo);

	~RedSocial();

	string nombre() const;

	vector<Actor> actores;

	//vector <Actor> amigos_de(int id); Funcion Auxiliar maybe?

	vector<pair<Actor, Actor>> amistades;

private:
	string _nombreDelArchivo;
};

struct Actor
{
	Actor(const int ID, const int inf);

	int id;

	int influencia;
};

#endif // !REDSOCIAL
