//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Instruction.h"
#include <iomanip>

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler()
{
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.

/**/
/*
	Assembler::PassI()
	NAME
		PassI - establishes the location of the labels
	SYNOPSIS
		Assembler::PassI();
	DESCRIPTION
		Parses the assembly code and establishes the location of the labels,
		and adds the symbols with their respective addresses to the symbol table
	RETURNS
		Void
	AUTHOR
		Anuj Bastola
	DATE
		11:50 AM 05/10/2018
*/
/**/

void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated
	int labelLookup;
	for (; ; ) {

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		if (m_inst.isLabel()) {
			if (m_symtab.LookupSymbol(m_inst.GetLabel(), labelLookup)) {
				string errMsg = "END is not the last statement.";
				Errors::RecordError(errMsg);
			}

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}/*void Assembler::PassI();*/

void Assembler::PassII() {
	m_facc.rewind();			// Back to the beginning of file;
	int loc = 0;				// location of the instruction
	cout << "\n\n";

	// Header format for Translation
	cout << "Translation of Program" << endl;
	cout << endl;
	cout << left << setw(10) << "Location" << setw(14) << "Contents" << "Original Statement" << endl;
	string errMsg;			// to store errors
	for (; ;) {
		string buff;		// Get the next line for .txt 

		// If there are no more lines, we are missing an end statement.
		if (!m_facc.GetNextLine(buff)) {
			//m_error.RecordError("Missing END statement");
			errMsg = "Missing END statement";
			Errors::RecordError(errMsg);
			break;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) {
			if (m_facc.GetNextLine(buff)) {
				errMsg = "END is not the last statement.";
				Errors::RecordError(errMsg);
				break;
			}
			// If END is the last statement, then DONE
			cout <<right<< setw(34) << m_inst.GetInstruction() << endl;
			break;
		}

		// Check of label is between 1-20 character
		if (m_inst.GetLabel().length() > 10) {
			errMsg = m_inst.GetLabel() + ": Label too Long";
			Errors::RecordError(errMsg);
		}
		// Check of the Label starts with a integer value
		else {
			if (m_inst.GetLabel()[0] >= '0' && m_inst.GetLabel()[0] <= '9') {
				errMsg = m_inst.GetLabel() + ": Label can't start with Number";
				Errors::RecordError(errMsg);
			}
		}
		// Illegal Opcode
		if (st == Instruction::ST_Illegal) {
			errMsg = m_inst.GetOpCode() + " : Illegal opCode!";
		}

		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr) {
			cout << "\t \t \t" << m_inst.GetInstruction() << endl;
			continue;
		}

		//Calculate Content Based on Opcodevalue
		int value = 10000 * m_inst.GetNumOpCode();
		//Check Assembly language
		if (st == Instruction::ST_AssemblerInstr) {
			if (m_inst.GetOpCode() == "dc") {
				value += m_inst.GetOperandValue();
			}
			if (m_inst.GetOpCode() != "end") {
				if (m_inst.GetOperand().empty()) {
					string Error_Msg = m_inst.GetOpCode() + ": Operand for Opcode Empty";
					Errors::RecordError(Error_Msg);
				}
				else if (!m_inst.isNumericOperand()) {
					string Error_Msg = m_inst.GetOpCode() + ": No numeric value or Opcode";
					Errors::RecordError(Error_Msg);
				}
				if (m_inst.GetOpCode() != "org" && m_inst.GetLabel().empty()) {
					string Error_Msg = m_inst.GetOpCode() + ": No Label Provided";
					Errors::RecordError(Error_Msg);
				}
			}
		}
		// if operand is numeric, get value, if not, add location to value
		else {

			if (m_inst.GetOperand().empty() && m_inst.GetNumOpCode() != 13) {
				string Error_Msg = m_inst.GetOpCode() + ": Operand not Defined or Missing in Opcode";
				Errors::RecordError(Error_Msg);
			}
			else if (!m_inst.isNumericOperand() && !m_inst.GetOperand().empty()) {
				int tempLoc = 0;
				if (!m_symtab.LookupSymbol(m_inst.GetOperand(), tempLoc)) {
					string Error_Msg = m_inst.GetOperand() + ": Symbol Not found";
					Errors::RecordError(Error_Msg);
					tempLoc = 9999;
				}
				//add the location to the value
				value += tempLoc;
			}
		}
		cout << setfill(' ') << setw(5) << loc << "\t";			// Display location during translation
		string temp;
		if (value != 0) {
			temp = string(6 - to_string(value).length(), '0') + to_string(value);
			cout << "  " << temp;;								// Display Contents during transaltion 
		}
		else {
			cout << " \t";
		}
		cout << "\t" << m_inst.GetInstruction() << endl;				// Display original statements during transaltion

		//Get next Instruction
		loc = m_inst.LocationNextInstruction(loc);

		
	}
	// Display erros 
	Errors::DisplayErrors();
}/*void Assembler::PassII();*/
