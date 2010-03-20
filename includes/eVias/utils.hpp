#ifndef EVIAS_CORE_UTILS_HPP
#define EVIAS_CORE_UTILS_HPP

#include <iostream>		// cout
#include <string> 		// string
#include <algorithm> 	// transform
#include <sstream> 		// stringstream
#include <functional>   // ptr_fun, toupper, tolower

#include <cctype>		
#include <ctime>		// time
#include <cstdlib> 		// srand, rand

// @todo define String class
namespace eVias {

	// eViasString errorCodes
	enum errorCodes {
		SUCCESS				= 0,
		ERR_NOT_A_STRING	= 10
	};

	// int to string conversion
	// @todo define in String class
	// @return std::string
	inline std::string intToString(int iIn) 
	{
		std::stringstream ss;

		ss	<< iIn;

		return ss.str();
	}

	// @todo define in String class
	inline std::string strToLower(std::string s)
	{
		std::transform( s.begin(), s.end(), s.begin(), std::ptr_fun(::tolower) );

		return s;
	}

	// @todo define in String class
	inline std::string strToUpper(std::string s)
	{
		std::transform( s.begin(), s.end(), s.begin(), std::ptr_fun(::toupper) );

		return s;
	}

	// Generate and return random password
	// @uses rand() .. srand() must be initialized before
	// @param int length > Password length
	// @return std::string
	inline std::string genPassword(int length)
	{
		std::string password = "";

		int randBoolInt = -1; // 0 or 1
		int secBoolInt  = -1; // 0 or 1
		char randChrInt	= '0'; // between 0 and 9
		char randLChr   = '0'; // between 97 and 122 (lower char)
		char randUChr   = '0'; // between 65 and 90 (upper char)
		char *randPChr 	= new char[2]; // to string conversion

		for (int i = 0; i < length; i++) 
		{
			randBoolInt = rand() % 2; // [0,1]
			secBoolInt  = rand() % 2; // [0,1]
			randChrInt 	= (char) ((rand() % 10) + 48); // [0-9]
			randUChr    = (char) ((rand() % 26) + 65); // [A-Z]
			randLChr 	= (char) ((rand() % 26) + 97); // [a-z]

			if (randBoolInt == 1) {
				if (secBoolInt == 1)
					randPChr[0] = randLChr; // lower case
				else 
					randPChr[0] = randUChr; // upper case
			}
			else {
				randPChr[0] = randChrInt; // digit
			}

			password.append(randPChr);
		}

		// clean memory
		delete randPChr;
		
		return password;
	}
	

};
#endif
