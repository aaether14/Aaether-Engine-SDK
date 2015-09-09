#ifndef TRANSFORM_INFO_HPP
#define TRANSFORM_INFO_HPP





#include <stdafx.h>




/**


Storing transform data for entity instancing


*/
class TransformInfo : public AEntityInstanceInfo
{



public:





    glm::mat4 matrix;


    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;




    /**
    Matching interface
    */
    void Load(boost::property_tree::ptree::value_type const& v, std::string info_name);
    /**
    Mathcing interface
    */
    boost::property_tree::ptree Save();




};

















#endif












