#include <stdafx.h>




namespace AString
{


std::string LoadFileToString(char * path)
{

    std::string result;
    std::ifstream FileStream(path, std::ios::in);

    if (FileStream.is_open())
    {


        std::string Line = "";
        while (getline(FileStream, Line))
            result += "\n" + Line;
        FileStream.close();


        return result;


    }
    else
    {
        printf("Impossible to open %s.\n", path);
        getchar();
        return "ERROR";
    }


}




char * char_to_str(std::string str)
{


    std::vector<char> writable(str.begin(), str.end());
    writable.push_back('\0');
    char*send = new char[writable.size()];
    strcpy(send, &writable[0]);
    return send;


}









}


#ifndef _MSC_VER



namespace std
{


float stof(std::string arg)
{

    return atof(arg.c_str());


}



template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}


}



#endif
