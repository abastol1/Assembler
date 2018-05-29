//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME
	AddSymbol - adds a new symbol to the symbol table.
SYNOPSIS
	void AddSymbol( char *a_symbol, int a_loc );
	a_symbol --> symbol 
	a_loc	 --> location
DESCRIPTION
	This function will place the symbol "a_symbol" and its location "a_loc"
	in the symbol table.
Return 
	Void 
Author 
	Anuj Bastola 
Date 
	11:45 AM 05/10/2018

*/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
	void SymbolTable::DisplaySymbolTable()
	NAME
		SymbolTable::DisplaySymbolTable()
	SYNOPSIS
		void SymbolTable::DisplaySymbolTable()
	DESCRIPTION
		Displays the symbol table on the console in below format:
			Symbol#		Symbol		Location
	RETURNS
		VOID
	AUTHOR
		Anuj Bastola
	DATE
		6:16 PM 09/05/2018
*/
/**/

void SymbolTable::DisplaySymbolTable() {
	int index = 0;
	cout << "Symbol#    Symbol    Location" << endl;
	for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
		cout << "   " << index++ << "\t    " << it->first << "\t      " << it->second << endl;
	}
}

	/**/
	/*
	bool SymbolTable::LookupSymbol(string &a_symbol)
		NAME
			LookupSymbol - Looks up if a symbol exists in SymbolTable

		SYNOPSIS
			bool SymbolTable::LookupSymbol(string &a_symbol);
			a_symbol	->	The Symbol to look up
			a_loc		->	If symbol is found place the location in a_loc
		DESCRIPTION
			Looks up if a symbol exists in the SymbolTable
	RETURNS
		True if found, false if not found
	AUTHOR
		Anuj Bastola
	DATE
		6:20 PM 09/05/2018
	*/
	/**/

bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc) {
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end()) {
		return false;
	}
	a_loc = m_symbolTable[a_symbol];
	return true;
}
