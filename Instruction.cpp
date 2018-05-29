#include "stdafx.h"
#include "Instruction.h"
#include <string>
#include <sstream>

/**/
/*
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
	NAME
		ParseInstruction(string &a_buff)
	SYNOPSIS
		Instruction::InstructionType Instruction::ParseInstruction(string &a_buff);
		a_buff	->	The original instruction to be parsed
	DESCRIPTION
		This function identifies the label, opcode and operand. It also determines the numerical value
		of the opCode, Operand and Label
	RETURNS
		Returns the type of instruction( ST_NULL, ST_MachineLanguage, ST_AssemblerInstr, ST_Comment or ST_End)
	AUTHOR
		Anuj Bastola
	DATE
		6:45 PM 09/05/2018
*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	clear();
	string ibuff;
	int count = 0;					// Number of columns in the line 
	bool isComment = false;
	m_instruction = a_buff;
	istringstream input(a_buff);
	istringstream temp(a_buff);


	for (; ;) {
		ibuff = "";
		temp >> ibuff;
		if (ibuff.size() == 0) {	// empty
			break;
		}
		else {
			if (ibuff.find_first_of(";") == string::npos) count++;
			else {
				if (ibuff[0] == ';') break;
				else {
					count++;
					break;
				}
			}
		}
	}

	int curr = 1;
	bool Label = true;
	if (count != 3) Label = false;

	for (; ; ) {
		ibuff = "";
		input >> ibuff;
		//	cout << "ibuff in Instruction.cpp is --> --> " << ibuff << endl;
		if (ibuff.size() == 0 || isComment == true) return m_type;

		string ibuffparse;
		string ibuffConvert;

		for (int i = 0; i < ibuff.length(); i++) {
			if (ibuff[i] == ';') {
				if (i == 0) {
					if (m_type == 0 && m_Label == "") {
						m_type = ST_Comment;
					}
					return m_type;
				}
				isComment = true;
				break;
			}
			ibuffparse += ibuff[i];
			ibuffConvert += tolower(ibuff[i]);
		}

		vector<string>::iterator itr;

		if ((m_OpCode.empty() && Label == false && find(vc_OpCode.begin(), vc_OpCode.end(), ibuffConvert) != vc_OpCode.end())) {
			itr = find(vc_OpCode.begin(), vc_OpCode.end(), ibuffConvert);
			m_OpCode = ibuffConvert;
			m_NumOpCode = distance(vc_OpCode.begin(), itr) + 1;
			m_type = ST_MachineLanguage;
			curr++;
		}
		else if ((m_OpCode.empty() && Label == false) && find(assembly_OpCode.begin(), assembly_OpCode.end(), ibuffConvert) != assembly_OpCode.end()) {
			m_OpCode = ibuffConvert;
			m_NumOpCode = 0;
			if (m_OpCode == "end") m_type = ST_End;
			else m_type = ST_AssemblerInstr;
			curr++;
		}
		else {
			if (m_OpCode.empty()) m_Label = ibuffparse;
			else {
				m_Operand = ibuffparse;
				//Searches the string for the first character that does not match any of the characters specified in its arguments.
				if (!m_Operand.empty() && m_Operand.find_first_not_of("0123456789") == string::npos) {
					m_IsNumericOperand = true;
					m_OperandValue = atoi(m_Operand.c_str());
				}
			}
			curr++;
		}
		if (curr != 1) Label = false;
	}
}/*Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)*/

/**/
/*
	int LocationNextInstruction(int a_loc)
	NAME
		LocationNextInstruction(int a_loc)
	SYNOPSIS
		int LocationNextInstruction(int a_loc)
		a_loc -> Current Location
	DESCRIPTION
		Determines next Location
	RETURNS
		Location of next instruction
	AUTHOR
		Anuj Bastola
	DATE
		6:48 PM 09/05/2018
*/
/**/
int Instruction::LocationNextInstruction(int a_loc) {
	if (m_OpCode == "ds" || m_OpCode == "org") return a_loc + m_OperandValue;
	return a_loc+1;
}

/**/
/*
	void Instruction::clear()
	NAME
		Instruction::clear()
	SYNOPSIS
		void Instruction::clear()
	DESCRIPTION
		Clears the values 
	RETURNS
		Void 
	AUTHOR
		Anuj Bastola
	DATE
		6:51 PM 09/05/2018
*/
/**/

void Instruction::clear() {
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = "";
	m_NumOpCode = -99;
	m_IsNumericOperand = false;
	m_OperandValue = -999999;
	m_type = ST_NULL;
}

