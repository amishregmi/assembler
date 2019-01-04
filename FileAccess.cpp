//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

// Don't forget to comment the function headers.



/**/
/*
FileAccess::FileAccess(int argc, char *argv[])
NAME
	FileAccess::FileAccess(int argc, char *argv[])
SYNOPSIS
	FileAccess::FileAccess(int argc, char *argv[]);
	argc	-->	Total number of arguments
	argv	-->	Array of the characters entered by the user
DESCRIPTION
	This is the constructor for FileAccess class that will help to open the file to read from.
Returns
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.  One might question if this is the best place to open the file.
	// One might also question whether we need a file access class.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
}

//Destructor.
FileAccess::~FileAccess()
{
	// Not that necessary in that the file will be closed when the program terminates.
	m_sfile.close();
}
// Get the next line from the file.


/**/
/*
FileAccess::GetNextLine(string &a_buff)

NAME
	FileAccess::GetNextLine(string &a_buff)
SYNOPSIS
	bool FileAccess::GetNextLine(string &a_buff)
	a_buff -> Contains the string in the line.
DESCRIPTION
	Reads the next line from the open file if it exists.
Returns
	True if next line is read, false otherwise.
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {

		return false;
	}
	getline(m_sfile, a_buff);
	
	return true;
}

/**/
/*
FileAccess::rewind()
NAME
	FileAccess::rewind()
SYNOPSIS
	FileAccess::rewind();
DESCRIPTION
	Rewind pointer to the start of the file.
Returns
	Void
AUTHOR
	Amish Regmi
DATE
	8:207 PM 12/25/2018
*/
/**/

void FileAccess::rewind()
{
	// Clean all file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}


