//
//		Symbol table class.
//
#pragma once

/**/
/*
	NAME
		SymbolTable - Maintains a table of symbols and their addresses
	DESCRIPTION
		Maintains a table of symbols and their corresponding addresses
	AUTHOR
		Anuj Bastola
	DATE
		11:27 AM 05/10/2018
*/
/**/

// This class is our symbol table.
class SymbolTable {

public:
	// Get rid of constructor and destructor if you don't need them.
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol, int &a_loc);
	//	return true;

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;

};