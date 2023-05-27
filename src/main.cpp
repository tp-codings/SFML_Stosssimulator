#include "Engine.h"
#include "EnginePi.h"
#include <time.h>


int main()
{
	srand(static_cast<unsigned>(time(0)));

	//Engine Engine;
	EnginePi pi;

	//Engine.run();
	pi.run();

	return 0;
}