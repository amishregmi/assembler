#include "stdafx.h"
#include "Emulator.h"

/**/
/*
Assembler::insertMemory()
NAME
	emulator::insertMemory(int a_location, int a_contents)
SYNOPSIS
	emulator::insertMemory(int a_location, int a_contents)
	a_location -> Location specified to store content
	a_contents -> Content to be stored in the location

DESCRIPTION
	Stores the given content in the memory location
RETURNS
	True if stored successfully, false otherwise.
AUTHOR
	Amish Regmi
DATE
8:207 PM 12/25/2018
*/
/**/



bool emulator::insertMemory(int a_location, int a_contents) {
	// If the location to be stored in is greater than 10000, then, return false
	if (a_location >= MEMSZ) {
		return false;
	}

	m_memory[a_location] = a_contents;		// Add the data to the location

	return true;
} 

/**/
/*
emulator::runProgram()

NAME
	emulator::runProgram() - Run the emulator

SYNOPSIS
	emulator::runProgram()

DESCRIPTION
	Goes through each memory location and executes the instruction found.

RETURNS
	True if done, false if error encountered.
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

bool emulator::runProgram() {
	int opCode = 0;
	int userInput = 0;
	int address = 0;

	//Loop through the size of the memory of the VC3600

	for (int index = 0; index < MEMSZ; ++index) {
		if (m_memory[index] != 0) {

			//Something was stored.

			opCode = m_memory[index] / 10000;
			address = m_memory[index] % 10000;
			//cout << "Current: " << index << "\t" <<opCode << "   Location: " << address << endl;

			switch (opCode) { //Check value from 1 to 13

			case 1:
				// Add content of accumulator and of the memory location provided 
				accumulator = accumulator+ m_memory[address];
				break;

			case 2:
				// Substract the contents of accumulator and of the memory location provided
				accumulator = accumulator- m_memory[address];
				break;
			
			case 3:
				// Multiply the contents of accumulator and of the memory location provided
				
				accumulator = accumulator* m_memory[address];
				break;
			
			case 4:

				// Divide the contents of accumulator and of the memory location provided
			
				accumulator = accumulator / m_memory[address];
				break;
			
			case 5:
				// Load the content of the address into the accumulator
			
				accumulator = m_memory[address];
				break;
	
			case 6:
				// Store contents of accumulator in the address provided
			
				m_memory[address] = accumulator;
				break;
			
			case 7:
				// Read a line and place first 6 digits in the required address.
				cout << "?";
				cin >> userInput;
				userInput = userInput % 1000000;
				m_memory[address] = userInput;

				break;
			
			case 8:
				// Display the contents present in the given address.
				cout << m_memory[address] << endl;
				break;
			case 9:
				// Change the index to the given location.
				index = address;
				break;
			
			case 10:
				// If the content of the accumulator is negative, go to address-1;
				if (accumulator < 0)
				{
					index = address - 1;
				}
				
				break;
			case 11:
				// If c(ACC) = 0, go to address-1.

				if (accumulator == 0)
				{
					index = address - 1;
				}
				break;
			
			
			case 12:
				//If c(ACC) is positive, go to address-1. 
				if (accumulator > 0)
				{
					index = address - 1;
				}
				break;
			
			case 13:
				//Terminate execution of the emulator.
				index = 10000;
				break;
			}
		}
	}


	return false;
}