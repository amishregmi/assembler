//
//      Implementation of the Assembler class.
//


#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Instruction.h"

/**/
/*
Assembler::Assembler(int argc, char *argv[])
NAME
	Assembler::Assembler(int argc, char *argv[]) - Constructor of the assembler that takes in the file name as its arguments
SYNOPSIS
	Assembler::Assembler(int argc, char *argv[])
	argc		-->			Total number of arguments in the command line
	argv		-->			Array of strings that are input by user
DESCRIPTION
	Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
RETURNS
	
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/


Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
Assembler::~Assembler()
{
}

/**/
/*
Assembler::PassI()
NAME
	Assembler::PassI() - Constructor of the assembler that takes in the file name as its arguments
SYNOPSIS
	Assembler::PassI()
DESCRIPTION
	// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
RETURNS

AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/


void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

						// Successively process each line of source code.
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

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}


/**/
/*
Assembler::PassII()
NAME
	Assembler::PassII() - Translates the assembler code and records errors.
SYNOPSIS
	Assembler::PassII();
DESCRIPTION
	Reads the text file specified by the command line. Generates machine language by going through the text file line by line and reading contents.
RETURNS

AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

void Assembler::PassII() {

	string errormessages;
	//First we need to go to the beginning of the file. 
	m_facc.rewind();
	int loc = 0; // Tracks the location of the instructions to be generated.
	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	cout << "TRANSLATION OF THE PROGRAM:" << endl << endl << endl; //Output Title
																   //Output Headers:
	cout << left << setw(8) << "LOCATION" << "     " << setw(10) << "CONTENTS" << setw(25) << " ORIGINAL STATEMENT" << endl;

	//string errormessages;

	for (; ;) {
		//To read the next line from the file specified.
		string next_buff;

		if (!m_facc.GetNextLine(next_buff)) {
			//If there is no next line, we don't have an end statement. Record error!

			errormessages = "Missing an END statement";
			Errors::RecordError(errormessages);
			break;
		}

		//Parse the line by calling ParseInstruction. Returns instruction type, if any.

		Instruction::InstructionType st = m_inst.ParseInstruction(next_buff);

		// Check if the operand label and opcode are in a valid format.


		if (st == Instruction::ST_End) {
			//If there is another line after end statement, end is not the last statement. Error.
			if (m_facc.GetNextLine(next_buff)) {
				errormessages = "End not the last statement or END not present";
				Errors::RecordError(errormessages);
				cout << endl << "------------------" << endl;
				return;
			}

			//Otherwise, end is the last statement. Break;
			else {
				cout << right << setw(35) << m_inst.GetInstruction() << endl;
				break;
			}
		}


		//Check the number of characters of the label. 

		if (m_inst.GetLabel().length() > 10) {
			//If it's too long, record the error.
			errormessages = m_inst.GetLabel() + " -> This label is too long";
			Errors::RecordError(errormessages);
			break;
		}

		else {
			//The label is of the appropriate length. Check if it starts with a number .
			char checklabel = m_inst.GetLabel()[0];
			if (checklabel >= '0' && checklabel <= '9') {
				//If yes, record the error.
				errormessages = m_inst.GetLabel() + " This label starts with a number. Erorr";
				Errors::RecordError(errormessages);
				break;
			}
		}

		//If not machine language and assembler instruction, then call GetInstruction() which returns the original instruction.

		if (st != Instruction::ST_MachineLanguage) {
			
			if (st != Instruction::ST_AssemblerInstr) {
				cout << "\t \t \t" << m_inst.GetInstruction() << endl;
				//Continue to next iteration.
				continue;
			}
		}

		//Calculate the present value from OpCode value.

		int values = 10000 * m_inst.GetOpCodeVal();

		//If assembler instruction, check which one.
		if (st == Instruction::ST_AssemblerInstr) {
			if (m_inst.GetOpCodeStr() == "dc") {
				//Define Constant in operand field.
				values += m_inst.GetOperandValue();
			}


			//check if empty without finding end statement.

			if (m_inst.GetOpCodeStr() != "end" && m_inst.GetOperand().empty()) {

				errormessages = m_inst.GetOpCodeVal() + "EMPTY ";
				Errors::RecordError(errormessages);
			}

			//Check if the label is missing
			else if (m_inst.GetLabel().empty()) {
				//If label missing, then should define origin. Otherwise, record error.
				if (m_inst.GetOpCodeStr() != "org") {
					errormessages = m_inst.GetOpCodeStr() + " label missing";
					Errors::RecordError(errormessages);
				}
			//	else {
			//		continue;
			//	}
			}
		}

		//Check if operand is numeric.
		else {
			//Check if operand is present and defined.
			if (m_inst.GetOperand().empty() && m_inst.GetOpCodeVal() != 13) {
				errormessages = m_inst.GetOpCodeStr() + " Is either not defined or missing";
				Errors::RecordError(errormessages);
			}

			//If numeric operand, lookup in symtable.
			else {
				if (!m_inst.checkifnumericOperand() && !m_inst.GetOperand().empty()) {

					int temporarylocation;
					//If numeric get value.
					//Else, add location to value.
					//Check if found in SymTab
					if (!m_symtab.LookupSymbol(m_inst.GetOperand(), temporarylocation)) {
						errormessages = m_inst.GetOperand() + " Symbol is not found";
						Errors::RecordError(errormessages);
						temporarylocation = 9999;
					}
					//Else add value to the temporary location.
					else
					{ 
						values += temporarylocation;
					}
				}
			}
		}

		//cout << "LOC IS " << loc << endl;
		//cout << "CONTENTS IS " << contents << endl;

		//Insertion Here.

		m_emul.insertMemory(loc, values);


		cout << setfill(' ') << setw(5) << loc << "\t";

		if (values != 0) {
			string temp = string(6 - to_string(values).length(), '0') + to_string(values);
			//Display contents of translation.
			cout << "    " << temp;

		}
		else {
			cout << " \t";
		}
		//Original statements.
		cout << "\t " << m_inst.GetInstruction() << endl;

		//Get location of the next instruction.

		loc = m_inst.LocationNextInstruction(loc);

	}
	//Call the DisplayErrors() function. 
	Errors::DisplayErrors();
}

/**/
/*
Assembler::runEmulator()
NAME
	Assembler::runEmulator()
SYNOPSIS
	Assembler::runEmulator(); 
DESCRIPTION
	If there are no errors, emulator is run by calling this function.
RETURNS

AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

void Assembler::runEmulator() {
	//cout << "INSIDE RUN EMULATOR" << endl;
	if (!Errors::checkifEmpty()) {
		//cout << "ERRORS YES" << endl;
		//	m_emul.runProgram();
		cout << "EMULATOR CANNOT START UNTIL THE LIST CONTAINING ERRORS IS EMPTY" << endl;
	}
	else {
		//cout << "ERRORS NO" << endl;
		m_emul.runProgram();
	}
	cout << endl;
	cout << "END OF EMULATION" << endl;
}
