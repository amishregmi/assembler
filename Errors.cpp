#include "Errors.h"
#include "stdafx.h"

vector<string> Errors::m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting()
NAME
	Errors::InitErrorReporting()
SYNOPSIS
	Errors::InitErrorReporting();

DESCRIPTION
	Deletes all the values if any stored in the vector of strings in an object of Errors class.
Returns
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/



void Errors::InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}


/**/
/*
Errors::RecordError(string &a_errMsg)
NAME
	Errors::RecordError(string &a_errMsg)
SYNOPSIS
	Errors::RecordError(string &a_errMsg)
	&a_errMsg -> The error message as a string

DESCRIPTION
	Pushes a string to the end of vector of strings containing error messages.
Returns
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/


void Errors::RecordError(string &a_errMsg) {
	m_ErrorMsgs.push_back(a_errMsg);
}


/**/
/*
Errors::DisplayErrors()
NAME
	Errors::DisplayErrors()
SYNOPSIS
	Errors::DisplayErrors();

DESCRIPTION
	Prints out all the error messages stored in the vector of strings.
Returns
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

void Errors::DisplayErrors() {
	for (auto const &out:m_ErrorMsgs) {
		cout << out << endl;
	}
}

/**/
/*
Errors::checkifEmpty()
NAME
	Errors::checkifEmpty()
SYNOPSIS
	Errors::checkifEmpty()
DESCRIPTION
	Checks if the vector has no elements.
Returns
	True if empty, false otherwise.
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

bool Errors::checkifEmpty() {
	if (m_ErrorMsgs.empty()) {
		return true; // Return true if no elements;
	}
	else { return false; };
}