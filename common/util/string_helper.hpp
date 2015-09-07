#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP



#include <stdafx.h>





/**
Useful functions regarding strings
*/
namespace AString
{


	/**
	Load a file to a string
	*/
	std::string LoadFileToString(char * path);
	/**
	Succesfully converts std::string to char*
	*/
	char * char_to_str(std::string str);








}




#endif
