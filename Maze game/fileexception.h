//===================================
//include guard
#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

//===================================
//included dependencies
#include <string>
using namespace std;

//an exception to be thrown when a file doesn't exist
class FileMissingEx
{
private:
	string message; //exception message
public:
	FileMissingEx(); //constructor - sets message
	const char* what() const; //returns the message of the exception
};

#endif