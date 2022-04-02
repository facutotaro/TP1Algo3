#ifndef REDSOCIAL
#define REDSOCIAL

#include "string"

using namespace std;

class RedSocial
{
public:

	RedSocial(string nombreDelArchivo);

	~RedSocial();

	string nombre() const;

private:
	string _nombreDelArchivo;
};

#endif // !REDSOCIAL




