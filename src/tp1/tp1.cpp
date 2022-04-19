// tp1.cpp: define el punto de entrada de la aplicación.
//

#include "tp1.h"
#include "ej1/ej1.h"
#include "ej2/ej2.h"
#include "ej3/ej3.h"
#include "ej4/ej4.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

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

		RedSocialEj1 r1(nombre);
		nombreArchivo = r1.nombre();
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
		r1.solverEj1();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
		break;
	}
	case 2:
	{
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    RedSocialEj2 r2(nombre);
		nombreArchivo = r2.nombre();
		r2.solverEj2();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
		break;
	}
	case 3:
	{
		Schedule s(nombre);
		nombreArchivo = s.nombre();
		break;
	}
	case 4:
	{
		ScheduleGol sg(nombre);
		nombreArchivo = sg.nombre();
		break;
	}
	    default: break;
	}

	cout << "Estas trabajando con el ej " << n << endl;

	cout << "Y con el archivo " << nombreArchivo << endl;
	
	return 0;
}




