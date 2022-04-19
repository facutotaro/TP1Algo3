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

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);
    cin.tie(0);
	int n = stoi(argv[1]);

	switch (n)
	{
	case 1:
	{
		RedSocialEj1 r1;
        r1.solverEj1();
		cout << endl;
		break;
	}
	case 2:
	{

	    RedSocialEj2 r2;
		r2.solverEj2();
		cout << endl;
		break;
	}
	case 3:
	{
		Schedule s;
		cout << s.solver_bu() << endl;
		//s.td() si se quiere la resolucion top down
		s.imprimir();
		cout << endl;
	}
	case 4:
	{	

		ScheduleGol sg;
		cout << sg.solver() << endl;
		sg.imprimir();
		cout << endl;
		break;
	}
	    default: break;
	}

	return 0;
}




