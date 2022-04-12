// tp1.cpp: define el punto de entrada de la aplicación.
//

#include "tp1.h"
#include "ej1-2/ej1-2.h"
#include "ej3/ej3.h"
#include "ej4/ej4.h"

using namespace std;

int main()
{
	int n = 0;
	do {
		cout << "Ingrese numero de ejercicio: " << endl;
		cin >> n;
	} while (!(n > 0 && n <= 4));

	string nombre = "";
	cout << "Ingrese nombre del archivo: " << endl;
	cin >> nombre;
	string nombreArchivo;

	switch (n)
	{
	case 1:
	{
		RedSocial r1(nombre);
		nombreArchivo = r1.nombre();
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
		cout << "El maximo beneficio es" << s.solver_bu() << endl;
		vector<int> solu = s.reconstruir();
		vector<int> veri = s.verificador(solu);
		vector<vector<int>> sol = s.solu(solu);
		for (int i = 0; i < sol.size(); i++)
		{
			cout << solu[i] << "; ";
			for (int j = 0; j < 4; j++)
			{
				cout << sol[i][j] << "; ";
			}
			cout << endl;
		}
		for (int i = 0; i < solu.size(); i++)
		{
			cout << solu[i] << ", ";
		}
		veri.size() == 0 ? cout << "Esta bien" << endl : cout << "Esta mal" << endl;
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
