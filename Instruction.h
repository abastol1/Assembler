//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//

/**/
/*
	NAME
		Instruction Class - Parses and provides information about instructions
	DESCRIPTION
		Parses the instruction and provides information on them.
		Consists information on opcodes, labels and instruction type
	AUTHOR
		Anuj Bastola
	DATE
		11:26 AM 05/10/2018
*/
/**/


#include <vector>
#pragma once

// The elements of an instruction.
class Instruction {

public:

	Instruction() { 
		m_NumOpCode = -99;
		m_IsNumericOperand = false;
		m_OperandValue = 0;
		m_type = ST_NULL;

	};
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,          // Comment or blank line
		ST_End,              // end instruction.
		ST_NULL,
		ST_Illegal
	};
	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// Clear all the elements of Instruction
	void clear();

	// To access the label
	inline string &GetLabel() {

		return m_Label;
	};
	// To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};

	// To access the number value of OpCode 
	inline int &GetNumOpCode() { return m_NumOpCode; }

	// To access the symbolic OpCode 
	inline string &GetOpCode() { return m_OpCode; }

	// To access the numerical value of operand 
	inline int &GetOperandValue() { return m_OperandValue; }

	// To access the operand 
	inline string &GetOperand() { return m_Operand; }

	// To determine if a operand is numerical value or variable 
	inline bool isNumericOperand() { return m_IsNumericOperand; }

	inline string GetInstruction() { return m_instruction; }


private:


	// The elemements of a instruction
	string m_Label;				  // The label.
	string m_OpCode;			  // The symbolic op code.
	string m_Operand;			 // The operand.


	string m_instruction;		 // The original instruction.

								// Derived values.
	int m_NumOpCode;			// The numerical value of the op code.
	InstructionType m_type;		// The type of instruction.

	bool m_IsNumericOperand;	// == true if the operand is numeric.
	int m_OperandValue;			// The value of the operand if it is numeric.

	vector<string> vc_OpCode = { "add", "sub", "mult", "div", "load", "store", "read", "write", "b", "bm", "bz", "bp", "halt" };
	vector<string> assembly_OpCode = { "dc", "ds", "org", "end" };
};