# assembler
Assembler and emulator for the VC3600 computer.

Final Project for Software Design class. 

Description of VC3600 Computer: 

#The VC-3600 Computer

The VC-3600 is a decimal computer with 10,000 words of memory. Each word consists of 6 decimal digits. There is an additional word of memory called the accumulator. The machine language instructions for the VC-3600 is of the following form:

                         |2 digits       | 4 digits       | 
                         |operation code | address portion|
A machine language program is a sequence of machine language instructions stored in memory. The computer executes a machine language program by obeying the commands specified by a sequence of instructions stored in successive memory locations. The first instruction of a program is assumed to be at location 100. The following are the machine language instructions for the VC-3600.

NAME OP. CODE MEANING
ADD 01 ACC <-- c(ACC) + c(ADDR) 
SUBTRACT 02 ACC <-- c(ACC) - c(ADDR) 
MULTIPLY 03 ACC <-- c(ACC) * c(ADDR) 
DIVIDE 04 ACC <-- c(ACC) / c(ADDR) 
LOAD 05 ACC <-- c(ADDR) 
STORE 06 ADDR <-- c(ACC) 
READ 07 A line is read and its first 6 digits are placed in the specified address. 
WRITE 08 c(ADDR) is displayed 
BRANCH 09 go to ADDR for next instruction
BRANCH MINUS 10 go to ADDR if c(ACC) < 0
BRANCH ZERO 11 go to ADDR if c(ACC) = 0
BRANCH POSITIVE 12 go to ADDR if c(ACC) > 0
HALT 13 terminate execution

Project divided into two stages:

Pass I : 
Parse the text file to determine whether a line contains a label, machine language or assembly language code, operand, and/or a comment.

Pass II:

Translate the text lines into location, and operation code and operand location. Upon success it will begin the emulation process, PassII is responsible for handling any errors in the code itself.

Full project requirements description can be found here: https://pages.ramapo.edu/~vmiller/SoftwareDesign/AssemblerNotes.html
