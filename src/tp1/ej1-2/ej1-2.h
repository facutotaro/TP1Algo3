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

	//vector <Actor> amigos_de(int id); Funcion Auxiliar maybe?

private:
	string _nombreDelArchivo;
	vector<Actor> _actores;
	vector<pair<int, int>> _amistades;

};



#endif // !REDSOCIAL
