//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

This function will place the symbol "a_symbol" and its location "a_loc"
in the symbol table.
*/
void
SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
SymbolTable::DisplaySymbolTable()

NAME
	SymbolTable::DisplaySymbolTable() - Print the symbol table

SYNOPSIS
	SymbolTable::DisplaySymbolTable()

DESCRIPTION
	Prints the symbol table
RETURNS
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

void SymbolTable::DisplaySymbolTable() {
	int start = 0;
	//cout << "--------------------------------------------------------" << endl;
	cout << endl << endl;
	cout << "OUTPUT FROM TEST PROGRAM: " << endl << endl;;
	cout << "Symbol Table: " << endl;

	cout << "Symbol#"<<"\t"<<"Symbol"<<"\t"<<"Location"<< endl;
	map<string, int>::iterator it;

	for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++) {
		cout << "    " << start++ << "\t" << it->first << "\t" << it->second << endl;
	}

}

/**/
/*
SymbolTable::LookupSymbol(string &a_sym, int &a_loc)

NAME
	SymbolTable::LookupSymbol(string &a_sym, int &a_loc)

SYNOPSIS
	bool SymbolTable::LookupSymbol(string &a_sym, int &a_loc);

DESCRIPTION
	Check if a symbol exists in the symbol table. 
RETURNS
	True if found, false otherwise.
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/



bool SymbolTable::LookupSymbol(string &a_sym, int &a_loc) {
	if (m_symbolTable.find(a_sym) != m_symbolTable.end()) {
		a_loc = m_symbolTable[a_sym];
		return true;
	}
	return false;
}