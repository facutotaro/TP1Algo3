// tp1.cpp: define el punto de entrada de la aplicación.
//

#include "tp1.h"
#include "ej1-2/ej1-2.h"
#include "ej3/ej3.h"
#include "ej4/ej4.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


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
<<<<<<< HEAD
		auto t1 = high_resolution_clock::now();
		RedSocial r1(nombre);
		nombreArchivo = r1.nombre();
		cout << "El maximo beneficio es " << r1.solver() << endl;
		//r1.solver();
		auto t2 = high_resolution_clock::now();
		auto tiempo = duration_cast<milliseconds>(t2 - t1);
		duration<double, std::milli> tiempo_d = t2 - t1;
		cout << "Tarda " << tiempo_d.count()/1000 << " segundos" << endl;
=======

		RedSocial r1(nombre);
		nombreArchivo = r1.nombre();
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
		r1.solverEj1();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
>>>>>>> FedeJuli
		break;
	}
	case 2:
	{
<<<<<<< HEAD
		auto t1 = high_resolution_clock::now();
		RedSocial r2(nombre);
		nombreArchivo = r2.nombre();
		r2.solver();
		auto t2 = high_resolution_clock::now();
		auto tiempo = duration_cast<milliseconds>(t2 - t1);
		duration<double, std::milli> tiempo_d = t2 - t1;
		cout << "Tarda " << tiempo_d.count()/1000 << " segundos" << endl;
=======
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	    RedSocial r2(nombre);
		nombreArchivo = r2.nombre();
		r2.solverEj2();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
>>>>>>> FedeJuli
		break;
	}
	case 3:
	{
		auto t1 = high_resolution_clock::now();
		Schedule s(nombre);
		nombreArchivo = s.nombre();
		cout << "El maximo beneficio es " << s.solver_bu() << endl;
		auto t2 = high_resolution_clock::now();
		auto tiempo = duration_cast<milliseconds>(t2 - t1);
		duration<double, std::milli> tiempo_d = t2 - t1;
		cout << "Tarda " << tiempo_d.count()/1000 << " segundos" << endl;
		break;
	}
	case 4:
	{	
		auto t1 = high_resolution_clock::now();
		ScheduleGol sg(nombre);
		nombreArchivo = sg.nombre();
		cout << "El maximo beneficio es " << sg.solver() << endl;
		auto t2 = high_resolution_clock::now();
		auto tiempo = duration_cast<milliseconds>(t2 - t1);
		duration<double, std::milli> tiempo_d = t2 - t1;
		cout << "Tarda " << tiempo_d.count()/1000 << " segundos" << endl;
		break;
	}
	    default: break;
	}

	cout << "Estas trabajando con el ej " << n << endl;

	cout << "Y con el archivo " << nombreArchivo << endl;
	
	return 0;
}




