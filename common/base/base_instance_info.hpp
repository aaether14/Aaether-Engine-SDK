#ifndef BASE_INSTANCE_INFO_HPP
#define BASE_INSTANCE_INFO_HPP



#include <stdafx.h>



/**
Interface for entity instance info
*/
class AEntityInstanceInfo
{


public:


    /**
    Loading interface from xml
    */
    virtual void Load(boost::property_tree::ptree::value_type const& v, std::string info_name) = 0;
    /**
    Saving interface to xml
    */
    virtual boost::property_tree::ptree Save() = 0;




private:



protected:



};



#endif
