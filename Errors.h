//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//

/**/
/*
	NAME
		Class Errors --> Manages errors found while translation
	DESCRIPTION
		All members are static so we can access them anywhere
	AUTHOR
		Anuj Bastola
	DATE
		07:41 PM 05/09/2018
*/
/**/

#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	// Returns true if no error
	static bool IsNoErrors() { return m_ErrorMsgs.empty(); }

private:

	static vector<string> m_ErrorMsgs;
};
#endif