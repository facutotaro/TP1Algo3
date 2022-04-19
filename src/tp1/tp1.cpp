// tp1.cpp: define el punto de entrada de la aplicación.
//

#include "tp1.h"
#include "ej1-2/ej1-2.h"
#include "ej3/ej3.h"
#include "ej4/ej4.h"

using namespace std;

int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);
    cin.tie(0);
	int n = stoi(argv[1]);

	string nombre = argv[2];
	string nombreArchivo;

	switch (n)
	{
	case 1:
	{
		RedSocial r1(nombre);
		nombreArchivo = r1.nombre();
		cout << nombreArchivo << endl;
		break;
	}
	case 2:
	{
		RedSocial r2(nombre);
		nombreArchivo = r2.nombre();
		break;
	}
	case 3:
	{
		Schedule s(nombre);
		nombreArchivo = s.nombre();
		cout << "El maximo beneficio es " << s.solver_bu() << endl;
		break;
	}
	case 4:
	{
		ScheduleGol sg(nombre);
		nombreArchivo = sg.nombre();
		break;
	}
	}

	cout << "Estas trabajando con el ej " << n << endl;

	cout << "Y con el archivo " << nombreArchivo << endl;
	
	return 0;
}
