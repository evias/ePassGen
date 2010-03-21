#include "../../includes/eVias/console.hpp"

namespace eVias {

	 eViasConsole* const eViasConsole::parseAll() {
		if (! (this->_argsCnt > 1)) {
            this->_lastReturn = NOTHING_TO_DO;
			return this;
		}

		for (int i = 0; i < this->_argsCnt; i++) {
			this->_vArgs.push_back(this->_argsVal[i]);
		}

		bool validData = this->_validateInput();

		if (! validData) {
			this->_printUsage();
		}

        this->dispatchData();

		return this;
	}

	bool eViasConsole::_validateInput() {
		if (this->_argsCnt != this->_vArgs.size()) {
			this->_lastReturn = WRONG_DATA_INPUT;
			return false;
		}

		this->_lastReturn = RET_SUCCESS;
		return true;
	}

	eViasConsole* const eViasConsole::dispatchData() {
		s_vec::iterator   itMixed;      // go through available args
        s_vec::iterator   itBefore;     // be able to work with arg-1
        s_vec::iterator   itFoundArg;   // use for finding current arg in allowed args
        size_t            stIndexFound;  // find current arg

        if (! (this->_vArgs.size() > 1)) {
            // only got executable name
            this->_lastReturn = NOTHING_TO_DO;
            return this;
        }

        // initialize
        itMixed = this->_vArgs.begin();
        itBefore= this->_vArgs.begin();
        for (int i = 0; itMixed != this->_vArgs.end(); itMixed++, i++) {
            if (i == 0) {
                // first argument is program name
                continue;
            }

            if (i > 1) {
                itBefore++; // only increment the second time.. makes current_arg-1
            }

            if ((*itMixed)[0] == '-') {
                // - beginning arg name

                // verify argument is allowed
                itFoundArg = find(this->_vAllowed.begin(), this->_vAllowed.end(), (*itMixed));

                // get distance between beginning and iterator position
                stIndexFound = distance(this->_vArgs.begin(), itFoundArg);

                if (stIndexFound != this->_vArgs.size()) {
                    // valid argument, will be added next turn
                    continue;
                }
                else {
                    // not a valid argument
                    this->_lastReturn = WRONG_DATA_INPUT;
                    return this;
                }
            }
            else {
                // arg value
                if ((*itBefore)[0] == '-') {
                    // fetched valid - beginning argument .. now fetch its value
                    this->_mData.insert(pair<string, string>((*itBefore), (*itMixed)));
                    continue;
                }

                if (itBefore == this->_vArgs.begin()) {
                    // first loop, value without arg-name
                    this->_mData.insert(pair<string,string>("1", (*itMixed)));
                    continue;
                }

                // coming here means no arg-name for current argument value
                this->_mData.insert(pair<string,string>((intToString(i+1)), (*itMixed)));
            }
        }

        this->_dataDispatched = true;

        this->_lastReturn = RET_SUCCESS;
        return this;
	}

    eViasConsole* const eViasConsole::addAllowedArg(string argName) {
        if (argName.empty()) {
            this->_lastReturn = EMPTY_ARG_NAME;
            return this;
        }

        this->_vAllowed.push_back (argName);

        this->_lastReturn = RET_SUCCESS;
        return this;
    }

    eViasConsole* const eViasConsole::addAllowedArgs(s_vec argList) {
        if (argList.empty()) {
            this->_lastReturn = EMPTY_ARGS_LIST;
            return this;
        }

        // insert at the end
        s_vec::iterator itEnd = this->_vAllowed.begin() + (this->_vAllowed.size()-1);

        // insert all elements
        this->_vAllowed.insert(itEnd, argList.begin(), argList.end());

        this->_lastReturn = RET_SUCCESS;
        return this;
    }

    eViasConsole* const eViasConsole::setAllowedArgs(s_vec argList) {
        if (argList.empty()) {
            this->_lastReturn = EMPTY_ARGS_LIST;
            return this;
        }

        this->_vAllowed.clear();

        // insert all elements
        this->_vAllowed.assign(argList.begin(), argList.end());

        this->_lastReturn = RET_SUCCESS;
        return this;
    }

    eViasConsole* const eViasConsole::removeAllowedArg(string argName) {
        if (this->_dataDispatched) {
            // cannot remove after dispatch
            this->_lastReturn = DATA_DISPATCHED;
            return this;
        }

        if (argName.empty()) {
            this->_lastReturn = EMPTY_ARG_NAME;
            return this;
        }

        // look for argument existance
        s_vec::iterator itFound   = find(this->_vAllowed.begin(), this->_vAllowed.end(), argName);
        size_t indexAt = distance(this->_vAllowed.begin(), itFound);

        if (indexAt == this->_vAllowed.size()) {
            this->_lastReturn = ARG_NAME_INVALID;
            return this;
        }

        // remove argument
        this->_vAllowed.erase(itFound);

        this->_lastReturn = RET_SUCCESS;
        return this;
    }

    eViasConsole* const eViasConsole::removeAllowedArgs(s_vec argList) {
        if (this->_dataDispatched) {
            this->_lastReturn = DATA_DISPATCHED;
            return this;
        }

        if (argList.empty()) {
            this->_lastReturn = EMPTY_ARGS_LIST;
            return this;
        }

        bool            allValid = true;            // data validation
        s_vec::iterator itArgs   = argList.begin(); // args to remove
        s_vec::iterator itFound;                    // validation
        vector<s_vec::iterator> findingsList;       // positions in _vAllowed
        vector<s_vec::iterator>::iterator itFindings;// positions iteration for erase
        size_t          foundAt;                    // validation

        for( ; itArgs != argList.end(); itArgs++) {
            // look for argument existance
            itFound = find(this->_vAllowed.begin(), this->_vAllowed.end(), (*itArgs));
            foundAt = distance(this->_vAllowed.begin(), itFound);

            if (foundAt == this->_vAllowed.size()) {
                allValid = false;
                break;
            }

            // add position in _vAllowed
            findingsList.push_back(itFound);
        }

        if (! allValid) {
            this->_lastReturn = ARG_NAME_INVALID;
            return this;
        }

        itFindings = findingsList.begin();

        for ( ; itFindings != findingsList.end(); itFindings++) {
            // remove position in _vAllowed
            this->_vAllowed.erase((*itFindings));
        }

        this->_lastReturn = RET_SUCCESS;
        return this;
    }

    eViasConsole* const eViasConsole::setArgsPositions(is_map mMap) {
        is_map::iterator itArgs = mMap.begin();
        s_vec::iterator  argValid;
        size_t           argIndex;

        for( ; itArgs != mMap.end(); itArgs++) {
            // validate argument name
            argValid = find(this->_vAllowed.begin(), this->_vAllowed.end(), (*itArgs).second);
            argIndex = distance(this->_vAllowed.begin(), argValid);

            if (argIndex == this->_vAllowed.size()) {
                this->_lastReturn = ARG_NAME_INVALID;
                return this;
            }

            // insert into gateway
            this->_mPositions.insert(pair<int,string>((*itArgs).first, (*itArgs).second));
        }

        this->_argsPosSet = true;

        this->_lastReturn = RET_SUCCESS;
        return this;
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
