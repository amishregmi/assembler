#include "stdafx.h"
#include "Instruction.h"

/**/
/*
Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
NAME
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
SYNOPSIS
	Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
	a_buff -> String that contains a single line of the sentence that needs to be parsed.
DESCRIPTION
	The function extracts Opcode, operand and label by parsing the string.
Returns
	If it is an assembly or machine language, returns the instruction type.
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/



Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	settodefault();
	
	int numberofcolumns = 0; //Number of columns present in the line.
	bool checkifcomment = false;
	m_instruction = a_buff;
	istringstream input(a_buff);
	istringstream temp(a_buff);

	string instr_buff;

	for (;;) {
		instr_buff = "";
		temp >> instr_buff;

		if (instr_buff.size() == 0) {
			//If it is empty, break
			break;
		}
		else {
			//If not empty
			if (instr_buff.find_first_of(";") == string::npos) { //Find the first ; position to disregard everything after.
				numberofcolumns++; 
			}
			else {
				if (instr_buff[0] == ';') {
					//It's a comment
					break;
				}
				else {
					numberofcolumns++; // Not a comment
					break;
				}
			}

		}
	}
	
	int current = 1;
	bool has_label = true;

	if (numberofcolumns != 3) {
		//Needs to have 3 columns to have a label
		has_label = false;
	}

	for (;;) {
		instr_buff = "";
		input >> instr_buff;
		string buff_parse;
		string buff_convert;


		if (instr_buff.size() == 0 || checkifcomment == true) {
			return m_type;
		}


		for (int i = 0; i < instr_buff.length(); i++) {
			if (instr_buff[i] == ';') {
				if (i == 0) {
					if (m_type == 0 && m_Label == "") {
						//Comment found
						m_type = ST_Comment;
					}
					return m_type;
				}
				checkifcomment = true;
				break;
			}

			buff_parse += instr_buff[i];
			//Convert to lowercase.
			buff_convert += tolower(instr_buff[i]);
		}


		vector<string>::iterator it;

		if ((m_OpCode.empty() && has_label == false && find(opcode_vc.begin(), opcode_vc.end(), buff_convert) != opcode_vc.end())) {
			//Check if type MachineLanguage
			//Find the position in the vector.
			it = find(opcode_vc.begin(), opcode_vc.end(), buff_convert);
			m_OpCode = buff_convert;
			//Calculates number of elements between the first element of opcode_vc and buff_convert found in opcode_cv.
			m_NumOpCode = distance(opcode_vc.begin(), it) + 1;
			m_type = ST_MachineLanguage;
			current++;
		}

		else if ((m_OpCode.empty() && has_label == false) && find(opcode_assembly.begin(), opcode_assembly.end(), buff_convert) != opcode_assembly.end()) {

			m_OpCode = buff_convert;
			m_NumOpCode = 0;
			if (m_OpCode == "end") {
				m_type = ST_End;
			}
			else {
				m_type = ST_AssemblerInstr;

			}
			current++;

		}

		else {

			if (m_OpCode.empty()) {
				m_Label = buff_parse;
			}
			else {
				m_Operand = buff_parse;
				//Find the first character that does not match any of the characters specified "0123456789"
				if (!m_Operand.empty() && m_Operand.find_first_not_of("0123456789") == string::npos) {
					m_IsNumericOperand = true;
					m_OperandValue = atoi(m_Operand.c_str());
				}
			}
			current++;

		}
		
		if (current != 1) has_label = false;

	}
}


/**/
/*
Instruction::LocationNextInstruction(int a_loc)
NAME
	Instruction::LocationNextInstruction(int a_loc)
SYNOPSIS
	Instruction::LocationNextInstruction(int a_loc)
	a_loc -> The current location
DESCRIPTION
	Function finds the next location of the instruction.
Returns
	Returns the location of the next instruction
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/


int Instruction::LocationNextInstruction(int a_loc) {
	if (m_OpCode == "ds" || m_OpCode == "org")
	{
		return a_loc + m_OperandValue;
	}
	return a_loc + 1;
}

/**/
/*
Instruction::settodefault()
NAME
	Instruction::settodefault();
SYNOPSIS
	void Instruction::settodefault()
DESCRIPTION
	Sets the member variables of Instructions class to default values.
Returns
	void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/


void Instruction::settodefault() {
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = "";
	m_NumOpCode = -99;
	m_IsNumericOperand = false;
	m_OperandValue = -999999;
	m_type = ST_null;
}
