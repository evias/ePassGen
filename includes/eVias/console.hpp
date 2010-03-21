#ifndef EVIAS_CORE_CONSOLE_HPP
#define EVIAS_CORE_CONSOLE_HPP

#include <vector>   // vector
#include <map>      // map
#include <string>   // string
#include <iostream> // cout
#include <typeinfo> // typeid
#include <algorithm>// find
#include <iterator> // distance, T::iterator

#include "utils.hpp"

namespace eVias {

	using namespace std; // vector, string

    // easy to read / good looking code :]
    typedef vector<string>      s_vec;
    typedef map<string,string>  s_map;
    typedef map<int,string>     is_map;

	enum consoleCodes {
		RET_SUCCESS			= 0, // ok
		NOTHING_TO_DO 		= 1, // ok
		WRONG_DATA_INPUT 	= 10,// err
        EMPTY_ARG_NAME      = 11,// err
        EMPTY_ARGS_LIST     = 12,// err
        ARG_NAME_INVALID    = 13,// err
        DATA_DISPATCHED     = 20,// err
        DATA_NOT_DISPATCHED = 21,
        ARGS_POS_NOT_SET    = 22
	};

	// @todo: add std::ofstream variable
	// 	@brief: allows logging
	class eViasConsole
	{
		public :
			eViasConsole()
			{
				this->_argsCnt = 0;
				this->_argsVal = NULL;
                this->_dataDispatched = false;
                this->_argsPosSet = false;
				this->_programName = "eVias Console";
				this->_usageMessage = "Not specified";
			};

			eViasConsole(int argc, char** argv)
				: _argsCnt(argc), _argsVal(argv)
			{
                this->_dataDispatched = false;
                this->_argsPosSet = false;
				this->_programName = "eVias Console";
				this->_usageMessage = "Not specified";
			};

			eViasConsole(string project, string usage, int argc, char **argv)
				: _programName(project), _usageMessage(usage),
				  _argsCnt(argc), _argsVal(argv)
			{
                this->_dataDispatched = false;
                this->_argsPosSet = false;
			};

			~eViasConsole()
			{

			};

            // public API
			eViasConsole* const parseAll ();
			eViasConsole* const	dispatchData ();

            eViasConsole* const addAllowedArg(string);      // append singular arg
            eViasConsole* const setAllowedArgs(s_vec);      // set multiple args
            eViasConsole* const addAllowedArgs(s_vec);      // append multiple args

            eViasConsole* const removeAllowedArg(string);   // remove allowed arg
            eViasConsole* const removeAllowedArgs(s_vec);   // remove allowed args

            eViasConsole* const setArgsPositions (is_map);   // specify no-argname rules

            // data getters
            s_vec allowedArgs() {
                return this->_vAllowed;
            };

            s_vec callArgs() {
                return this->_vArgs;
            };

            is_map argsPositions() {
                if (! this->_argsPosSet) {
                    this->_lastReturn = ARGS_POS_NOT_SET;
                    is_map error;
                    error.insert(pair<int, string>(1, "ERROR: arguments positions rules not set"));
                    return error;
                }

                return this->_mPositions;
            };

            s_map readData() {
                if (! this->_dataDispatched) {
                    this->_lastReturn = DATA_NOT_DISPATCHED;
                    s_map error;
                    error.insert(pair<string, string>("ERR", "ERROR: not dispatched or error"));
                    return error;
                }

                s_map::iterator testData = this->_mData.begin();
                if (atoi(((*testData).first).c_str()) == 0) {
                    this->_lastReturn = RET_SUCCESS;
                    // we have arguments name
                    this->_mData.insert(pair<string,string>("ERR", "")); // no error
                    return this->_mData;
                }

                // we need to work with position rules
                if (! this->_argsPosSet) {
                    this->_lastReturn = ARGS_POS_NOT_SET;
                    s_map error;
                    error.insert(pair<string, string>("ERR", "ERROR: args position are not set !"));
                    return error;
                }

                // no arguments name given, fetch with positions
                bool dataFlag = true;
                s_map formattedData;
                is_map::iterator itPos = this->_mPositions.begin();

                if (this->_mPositions.size() != this->_mData.size()) {
                    this->_lastReturn = WRONG_DATA_INPUT;
                    s_map error;
                    error.insert(pair<string, string>("ERR", "ERROR: data and positions do not equal"));
                    return error;
                }

                for (; testData != this->_mData.end() && itPos != this->_mPositions.end();
                       testData++, itPos++)
                {
                    pair<string,string> dataPair((*itPos).second, (*testData).second);
                    formattedData.insert(dataPair);
                }

                this->_lastReturn = RET_SUCCESS;
                return formattedData;
            };

            consoleCodes lastReturn() {
                return this->_lastReturn;
            };

			// @todo: implement in object abstraction layer
			void printMe();

		protected :
			bool _validateInput();
			void _printUsage();

			string 	_programName;

			string  _usageMessage;

		private :
			int 	    _argsCnt;
			char**	    _argsVal;

            bool        _dataDispatched;
            bool        _argsPosSet;

			s_vec       _vArgs;

            is_map      _mPositions;
			s_map	    _mData;
			s_vec       _vAllowed;

			consoleCodes _lastReturn;
	};

};

#endif
