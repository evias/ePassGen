#include "../../includes/eVias/utils.hpp"

namespace eVias
{
    // debug method for map<string,string>
    // @todo implement in debug namespace
    void s_mapDump(map<string,string> mMap) {
        map<string,string>::iterator it = mMap.begin();

        cout << "----Map Dump" << endl;
        for( ; it != mMap.end(); it++) {
            cout << (*it).first   << " - " << (*it).second << endl;
        }
        cout << "----End Dump" << endl;
    }

    // debug method for vector<string>
    // @todo implement in debug namespace
    void s_vecDump(vector<string> vVec) {
        vector<string>::iterator it = vVec.begin();

        cout << "----Vector Dump" << endl;
        for( ; it != vVec.end(); it++) {
            cout << (*it) << endl;
        }
        cout << "----End Dump" << endl;
    }

	// int to string conversion
	// @todo define in String class
	// @return std::string
	std::string intToString(int iIn)
	{
		std::stringstream ss;

		ss	<< iIn;

		return ss.str();
	}

	// @todo define in String class
	std::string strToLower(std::string s)
	{
		std::transform( s.begin(), s.end(), s.begin(), std::ptr_fun(::tolower) );

		return s;
	}

	// @todo define in String class
	std::string strToUpper(std::string s)
	{
		std::transform( s.begin(), s.end(), s.begin(), std::ptr_fun(::toupper) );

		return s;
	}

	// Generate and return random password
	// @uses rand() .. srand() must be initialized before
	// @param int length > Password length
	// @return std::string
	std::string genPassword(int length)
	{
		std::string password = "";
		int randBoolInt = -1; // 0 or 1
		int secBoolInt  = -1; // 0 or 1
		char *randPChr 	= new char[2]; // to string conversion

		for (int i = 0; i < length; i++)
		{
			randBoolInt = rand() % 2; // [0,1]
			secBoolInt  = rand() % 2; // [0,1]

			if (randBoolInt == 1) {
				if (secBoolInt == 1)
					randPChr[0] = (char) ((rand() % 26) + 97); // [a-z]
				else
					randPChr[0] = (char) ((rand() % 26) + 65); // [A-Z]
			}
			else {
				randPChr[0] = (char) ((rand() % 10) + 48); // [0-9]
			}

            randPChr[1] = '\0';

			password.append(randPChr);
		}
		delete randPChr;

		return password;
	}

};
