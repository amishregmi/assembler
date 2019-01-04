//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once
#include "stdafx.h"

// The elements of an instruction.
class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,          // Comment or blank line
		ST_End, // end instruction.
		ST_null //Null
	};
	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline string &GetLabel() {

		return m_Label;
	};
	// To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};

	void settodefault();
	
	//Some Get Functions

	inline string GetInstruction() { return m_instruction; }
	inline int &GetOpCodeVal() { return m_NumOpCode; }
	inline string &GetOpCodeStr() { return m_OpCode; }
	inline int &GetOperandValue() { return m_OperandValue; }
	inline string &GetOperand() { return m_Operand; }
	inline bool checkifnumericOperand() { return m_IsNumericOperand; }

private:


	// The elemements of a instruction
	string m_Label;            // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.


	string m_instruction;    // The original instruction.

							 // Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.

	vector<string> opcode_vc = { "add", "sub", "mult", "div", "load", "store", "read", "write", "b", "bm", "bz", "bp", "halt" };
	vector<string> opcode_assembly = { "dc", "ds", "org", "end" };
};

