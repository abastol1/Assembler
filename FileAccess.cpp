//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"


/**/
/*
	FileAccess::FileAccess(int argc, char *argv[])
	NAME
		Opens the source file for reading
	SYNOPSIS
		FileAccess(int argc, char *argv[]);
		argc	--> the number of command line arguments
		argv	--> all the given command line arguments
	DESCRIPTION
		This constructor will open the file passed as command line argument for reading.
		Error message will be thrown and program terminates if the file can't be found.
	RETURNS
		Nothing
	AUTHOR
		Anuj Bastola
	DATE
		06:54 PM 09/05/2018
*/
/**/
// Don't forget to comment the function headers.
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
	else {
		cout << "File successfully opened" << endl;
	}
}/*FileAccess::FileAccess(int argc, char *argv[])*/

FileAccess::~FileAccess()
{
	// Not that necessary in that the file will be closed when the program terminates.
	m_sfile.close();
}

/**/
/*
	bool FileAccess::GetNextLine(string &a_buff)
	NAME
		FileAccess GetNextLine - Reads the next line from source file
	SYNOPSIS
		bool FileAccess::GetNextLine(string &a_buff);
		a_buff	-> string that will contain data read.
	DESCRIPTION
		It reads the next line from file and returns a true boolean value
		if it is successful.
	RETURNS
		Returns true if read is successful. False otherwise.
	AUTHOR
		Anuj Bastola
	DATE
		2:32 PM 05/10/2018
*/
/**/

// Get the next line from the file.
bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {
		return false;
	}
	getline(m_sfile, a_buff);
	//cout << "Next line is " << a_buff << endl;

	// Return indicating success.
	return true;
}/*bool FileAccess::GetNextLine(string &a_buff)*/

void FileAccess::rewind()
{
	// Clean all file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}
