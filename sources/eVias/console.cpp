#include "../../includes/eVias/console.hpp"

namespace eVias {

	consoleCodes eViasConsole::parseAll() {
		if (! (this->_argsCnt > 1)) {
			return NOTHING_TO_DO; 
		}

		bool validData = this->_validateInput();

		if (! validData) {
			this->_printUsage();
		}

		return this->_lastReturn;
	}

	bool eViasConsole::_validateInput() {
		if (this->_argsCnt != this->_vArgs.size()) {
			this->_lastReturn = WRONG_DATA_INPUT;
			return false;
		}	

		this->_lastReturn = RET_SUCCESS;
		return true;
	}

	void eViasConsole::_printUsage() {
		cout	<< "--------------------------------------"	<< endl
				<< " Usage of " << this->_programName 		<< endl
				<< this->_usageMessage						<< endl
				<< "--------------------------------------" << endl;
	}

	void eViasConsole::printMe()
	{
		cout	<< "------ eVias printMe ------"	<< endl
				<< this->_programName << " running"	<< endl
				<< "---------------------------"	<< endl;
	}	
};
