#include "fileexception.h"

FileMissingEx::FileMissingEx()
{
	message = "File non-existant";
}

const char* FileMissingEx::what() const
{ 
	return message.c_str(); 
}