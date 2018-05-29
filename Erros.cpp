#include "stdafx.h"
#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

/**/
/*
	void Errors::InitErrorReporting()	
	NAME
		InitErrorReporting
	SYNOPSIS
		void Errors::InitErrorReporting();
	DESCRIPTION
		Initiate the Error Reporting. Erases the previous errros
	RETURNS
		void
	AUTHOR
		Anuj Bastola
	DATE
		07:05 PM 05/09/2018
*/
/**/


void Errors::InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}

/**/
/*
	void Errors::RecordError(string &a_errMsg)
	NAME
		RecordError
	SYNOPSIS
		void Errors::RecordError(string &a_errMsg)
		a_errMsg --> Error messages 
	DESCRIPTION
		Records the error messages found during translation
	RETURNS
		void
	AUTHOR
		Anuj Bastola
	DATE
		07:08 PM 05/09/2018
*/
/**/

void Errors::RecordError(string &a_errMsg) {
	m_ErrorMsgs.push_back(a_errMsg);
}

/**/
/*
	void Errors::DisplayErrors()
	NAME
		DisplayErrors
	SYNOPSIS
		void Errors::DisplayErrors();
	DESCRIPTION
		Displays the errors that have been recorded during the translation
	RETURNS
		void 
	AUTHOR
		Anuj Bastola
	DATE
		07:11 PM 05/09/2018
*/
/**/

void Errors::DisplayErrors() {
	for (auto const& a : m_ErrorMsgs) {
		cout << a << endl;
	}
}
