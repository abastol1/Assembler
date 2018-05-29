//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

/**/
/*
	NAME
		class Assembler
	DESCRIPTION
		This class contains all the necessary function to make the assembler. 
		Pass I --> Establishes the location of the symbols
		Pass II --> Generates the transaltion 
		Display Table --> Displays the symbol in a table
		Displays Error messages if any 
	AUTHOR
		Anuj Bastola
	DATE
		07:32 PM 05/09/2018
*/
/**/

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"


class Assembler {

public:
	Assembler(int argc, char *argv[]);
	~Assembler();

	// Pass I - establish the locations of the symbols
	void PassI();


	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

private:

	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab; // Symbol table object
	Instruction m_inst;	    // Instruction object
	//emulator m_emul;        // Emulator object
	Errors m_error;			// Error Object
};