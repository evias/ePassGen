#include <iostream> // cout, endl
#include <ctime>    // time, time_t
#include <cstdlib>  // srand, rand

#include "includes/eVias/utils.hpp" // genPassword
#include "includes/eVias/console.hpp" // eViasConsole

using namespace eVias; // eViasConsole, genPassword
using namespace std; // cout, endl

int main(int argc, char *argv[])
{
	int maxPass = 100;
	int passLen = 8;
	time_t seed;

	string usageMsg("./bin/ePassGen [-ln] [passCount] [passSize]");

	eViasConsole *app = new eViasConsole("ePassGen", usageMsg, argc, argv);

	app->printMe();

	delete app;
/*
	// argument parsing
	if (argc > 1) {
		// @todo:
		// - argument with - (eViasConsole)

		// has args for load
		if (argc == 2) {
			// only passwords count
			maxPass = atoi(argv[1]);
		}
		else {
			// both count and length
			maxPass = atoi(argv[1]);
			passLen = atoi(argv[2]);
		}
	}

	// generate execution time related seed
	// will differ every SECOND
	time  (&seed);
	srand ((unsigned long) seed);

	// generate maxPass passwords
	for (int i = 1; i <= maxPass; i++) {
		// generate password of length passLen
		cout << genPassword(passLen);

		if (i % 5 == 0)
			cout << endl;
		else
			cout << " ";
	}

	if (maxPass < 5) 
		cout << endl;
*/
    return 0;
}
