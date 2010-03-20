#include <iostream>
#include <ctime>
#include <cstdlib>

#include "includes/eVias/utils.hpp"

using namespace eVias;
using namespace std;

int main(int argc, char *argv[])
{
	int maxPass = 100;
	int passLen = 8;

	// argument parsing
	if (argc > 1) {
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

	// generate random seed
	time_t seed;
	time(&seed);
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

    return 0;
}
