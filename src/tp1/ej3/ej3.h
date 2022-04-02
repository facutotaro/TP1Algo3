#ifndef SCHEDULE
#define SCHEDULE

#include "string"

using namespace std;

class Schedule
{
public:

	Schedule(string nombreDelArchivo);

	~Schedule();

	string nombre() const;

private:
	string _nombreDelArchivo;
};

#endif // !SCHEDULE