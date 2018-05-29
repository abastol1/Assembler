/*
* Assembler main program.
*/

/**/
/*
	NAME
		Assem -Entry Point
	SYNOPSIS
		Runs the Assembler Pass I and PassII
	DESCRIPTION
	Compiles and executes the assembly code.
		Initializes the Assembler class & parses the assembly code received from file
		Creates a symbol table, calculates and inserts machine instructions into memory.
		Displays error messages if any
	RETURNS
		0
	AUTHOR
		Anuj Bastola
	DATE
		11:21 AM 05/10/2018
*/
/**/
#include "stdafx.h"     // This must be present if you use precompiled headers which you will use.
#include <stdio.h>

#include "Assembler.h"
#include "Instruction.h"

int main(int argc, char *argv[])
{
	Assembler assem(argc, argv);

	// Establish the location of the labels:
	assem.PassI();

	// Display the symbol table.
	assem.DisplaySymbolTable();

	// Output the symbol table and the translation.
	assem.PassII();

	// Run the emulator on the VC3600 program that was generated in Pass II.
	//assem.RunEmulator();

	// Terminate indicating all is well.  If there is an unrecoverable error, the 
	// program will terminate at the point that it occurred with an exit(1) call.
	return 0;
}