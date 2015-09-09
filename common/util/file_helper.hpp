#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP




#include <stdafx.h>







/**


Using Templates for easier binary data storing/loading
Also provides tools for directory copying


*/
namespace AFile
{



#define STRING_ERROR "_$#$_STRING_ERROR"


template <class T>
/**
Writes anytype of data to binary file
*/
inline void WriteToFile(std::ofstream& os, const T& obj)
{
    os.write((const char*)&(obj), sizeof(T));
}
template <class T>
/**
Reads anytype of data from binary file
*/
inline void ReadFromFile(std::ifstream& is, const T& obj)
{
    is.read((char*)&(obj), sizeof(T));
}


/**
Copy folder from a location to another. Returns true if succesful
*/
bool copyDir(
    boost::filesystem::path const & source,
    boost::filesystem::path const & destination
);


/**
If in the folder specified by 'path' exists a file that has 'extension' return path of that file. Returns NULL otherwise
*/
std::string GetFileWithExtension(std::string path, std::string extension);
/**
Same as GetFileWithExtension but for multiple extensions
*/
std::string GetFileWithExtensionList(std::string path, std::vector<std::string>extensions);


/**
Return size of file
*/
long GetFileSize(const char* filePath);
/**
Read file content into memory and return pointer
*/
unsigned char * ReadFile(const char * filePath);
/**
Encrypt file from 'path' using Blowfish algorithm
*/
void BlowfishEncryptFile(const char * path);
/**
Get decrytpted file from 'path' to string using Blowfish algorithm
*/
std::string BlowfishDecryptFile(const char * path);


}




#endif
