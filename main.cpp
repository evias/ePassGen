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
	string usageMsg("./bin/ePassGen [-l <passSize> -n <passCount>]");
    string args[] = {
        "-n", "-l"
    };
    vector<string> argsName;
    map<string,string> callArgs;
    map<int,string> argsPos;

    argsName.assign(args, args + 2);
    argsPos.insert(pair<int,string>(1,"-n"));
    argsPos.insert(pair<int,string>(2,"-l"));

    // use of custom argument parsing, allows me
    // to deal with and without arguments name.
    eViasConsole *app = new eViasConsole("ePassGen", usageMsg, argc, argv);

    // allowed args are the strings allowed as -"something" keys
    // args position is used if no "-l" or "-n" is specified
    // means a specified order needs to be read
    // parseAll is the magic
    app ->setAllowedArgs(argsName)
        ->setArgsPositions(argsPos)
	    ->parseAll();

    // set data if arguments were parsed successfully
    if (app->lastReturn() == RET_SUCCESS) {
        callArgs = app->readData();
        if (callArgs["ERR"].empty()) {
            maxPass = atoi(callArgs["-n"].c_str());
            passLen = atoi(callArgs["-l"].c_str());
        }
        else {
            cout    << callArgs["ERR"]  << endl;
            return app->lastReturn();
        }
    }

    // only needed for argument parsing
	delete app;

	// generate execution time related seed
	// will differ every SECOND
	time  (&seed);
	srand ((unsigned long) seed);

    int i = 0;
	// generate maxPass passwords
	for (i = 1; i <= maxPass; i++) {
		// generate password of length passLen
		cout << genPassword(passLen);

		if (i % 5 == 0)
			cout << endl;
		else
			cout << " ";
	}

	if ((i-1) < 5 || (i-1) % 5 != 0)
		cout << endl;

    return 0;
}
