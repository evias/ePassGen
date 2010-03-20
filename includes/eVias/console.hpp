#ifndef EVIAS_CORE_CONSOLE_HPP
#define EVIAS_CORE_CONSOLE_HPP

#include <vector> // std::vector
#include <string> // std::string
#include <iostream> // std::cout
#include <typeinfo> // std::typeid

namespace eVias {

	using namespace std; // vector, string

	enum consoleCodes {
		RET_SUCCESS			= 0, // ok
		NOTHING_TO_DO 		= 1, // ok
		WRONG_DATA_INPUT 	= 10 // err
	};

	// @todo: implement parseAll method
	//	@brief: fill up _vArgs before validate
	// @todo: add std::ofstream variable
	// 	@brief: allows logging
	class eViasConsole
	{
		public :
			eViasConsole()
			{ 
				this->_argsCnt = 0;
				this->_argsVal = NULL;
				this->_programName = "eVias Console";
				this->_usageMessage = "Not specified";
			};

			eViasConsole(int argc, char** argv)
				: _argsCnt(argc), _argsVal(argv) 
			{ 
				this->_programName = "eVias Console";
				this->_usageMessage = "Not specified";
			};

			eViasConsole(string project, string usage, int argc, char **argv)
				: _programName(project), _usageMessage(usage), 
				  _argsCnt(argc), _argsVal(argv)
			{

			};	

			~eViasConsole() 
			{

			};

			consoleCodes parseAll();

			// @todo: implement in object abstraction layer
			void printMe();

		protected :
			bool _validateInput();
			void _printUsage();

			string 	_programName;

			string  _usageMessage;

		private :
			int 	_argsCnt;
			char**	_argsVal;

			vector<string> _vArgs;

			consoleCodes _lastReturn;
	};

};

#endif
