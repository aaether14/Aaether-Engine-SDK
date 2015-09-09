#include <stdafx.h>





bool InfoComponent::isValid(char * extension)
{


    //See if valid extension


    if (!std::string(extension).compare(".ainfo"))
        return true;
    return false;


}




void InfoComponent::Load(char * path, char* extension)
{

    //Read if valid file

    info->Read(AString::char_to_str(path));



}




void InfoComponent::Init()
{


    info = new GeneralEntityInfo();


}




void InfoComponent::GeneralEntityInfo::Read(std::string path)
{


    //read xml using boost


    using boost::property_tree::ptree;
    ptree pt;
    read_xml(path, pt);




    BOOST_FOREACH(ptree::value_type const& v, pt.get_child("GeneralInfo"))
    {


        if (v.first == "BaseInfo")
        {



            std::string base_rot;
            std::string base_scale;


            base_rot = v.second.get<std::string>("Rotation");
            base_scale = v.second.get<std::string>("Scale");
            affected_by_ssao = v.second.get<GLboolean>("SSAO");
            cull = v.second.get<GLboolean>("Cull");
            radius = v.second.get<GLfloat>("Radius");
            entity_name = v.second.get<std::string>("EntityName");



            this->base_rot = Math::GetVecFromString(base_rot);
            this->base_scale = Math::GetVecFromString(base_scale);


        }


        break;

    }

}




boost::property_tree::ptree InfoComponent::GeneralEntityInfo::GetPtree()
{

    using boost::property_tree::ptree;
    ptree pt;
    ptree rootNode;




    ptree new_info;
    new_info.push_back(ptree::value_type("EntityName", ptree(entity_name)));
    new_info.push_back(ptree::value_type("Rotation", ptree(Math::GetStringFromVec(base_rot))));
    new_info.push_back(ptree::value_type("Scale", ptree(Math::GetStringFromVec(base_scale))));
    new_info.push_back(ptree::value_type("Radius", ptree(std::to_string(radius))));
    new_info.push_back(ptree::value_type("SSAO", ptree(std::to_string(affected_by_ssao))));
    new_info.push_back(ptree::value_type("Cull", ptree(std::to_string(cull))));
    rootNode.add_child("BaseInfo", new_info);



    pt.add_child("GeneralInfo", rootNode);


    return pt;

}
