#ifndef EVIAS_CORE_UTILS_HPP
#define EVIAS_CORE_UTILS_HPP

#include <iostream>		// cout
#include <string> 		// string
#include <algorithm> 	// transform
#include <sstream> 		// stringstream
#include <functional>   // ptr_fun, toupper, tolower
#include <map>          // map
#include <vector>       // vector

#include <cctype>
#include <ctime>		// time
#include <cstdlib> 		// srand, rand

// @todo define String class
namespace eVias {

    using namespace std;

	// eViasString errorCodes
	enum errorCodes {
		SUCCESS				= 0,
		ERR_NOT_A_STRING	= 10
	};

    void s_mapDump(map<string,string>);
    void s_vecDump(vector<string>);

	// int to string conversion
	// @todo define in String class
	// @return std::string
	std::string intToString(int iIn);

	// @todo define in String class
	std::string strToLower(std::string s);

	// @todo define in String class
	std::string strToUpper(std::string s);

	// Generate and return random password
	// @uses rand() .. srand() must be initialized before
	// @param int length > Password length
	// @return std::string
	std::string genPassword(int length);

};
#endif
