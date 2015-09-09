#include <stdafx.h>




void Environment::Reset()
{


    sun_dir = glm::vec3(
                  sin(M_PI / 180 * 25),
                  -cos(M_PI / 180 * 25),
                  0.0f
              );


    sun_color = glm::vec3(1.0f, 1.0f, 1.0f);


    model_ambient = 0.5f;
    terrain_ambient = 0.5f;
    model_diffuse = 1.0f;
    terrain_diffuse = 1.5f;


    terrain_bright = 1.0f;
    model_bright = 1.3f;




    fog_color = glm::vec3(0.964f, 0.913f, 0.705f);
    fog_density = 0.00175f;



    SetShouldReset(false);


}



void Environment::Save()
{





    using boost::property_tree::ptree;
    ptree pt;
    ptree rootNode;



    ptree new_info;
    new_info.push_back(ptree::value_type("SunDirection", ptree(Math::GetStringFromVec(sun_dir))));
    new_info.push_back(ptree::value_type("SunColour", ptree(Math::GetStringFromVec(sun_color))));
    new_info.push_back(ptree::value_type("FogColour", ptree(Math::GetStringFromVec(fog_color))));
    new_info.push_back(ptree::value_type("FogDensity", ptree(std::to_string(fog_density))));
    new_info.push_back(ptree::value_type("ModelAmbient", ptree(std::to_string(model_ambient))));
    new_info.push_back(ptree::value_type("ModelDiffuse", ptree(std::to_string(model_diffuse))));
    new_info.push_back(ptree::value_type("TerrainAmbient", ptree(std::to_string(terrain_ambient))));
    new_info.push_back(ptree::value_type("TerrainDiffuse", ptree(std::to_string(terrain_diffuse))));
    rootNode.add_child("EnvironmentInfo", new_info);






    pt.add_child("Scene", rootNode);
    boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
    write_xml(GetPath(), pt, std::locale(), settings);





}



void Environment::Load()
{



    using boost::property_tree::ptree;
    ptree pt;
    read_xml(GetPath(), pt);




    BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
    {


        if (v.first == "EnvironmentInfo")
        {



            std::string sun_color_str;
            std::string sun_direction_str;
            std::string fog_color_str;



            sun_color_str = v.second.get<std::string>("SunColour");
            sun_direction_str = v.second.get<std::string>("SunDirection");
            fog_color_str = v.second.get<std::string>("FogColour");
            fog_density = v.second.get<GLfloat>("FogDensity");
            model_ambient = v.second.get<GLfloat>("ModelAmbient");
            model_diffuse = v.second.get<GLfloat>("ModelDiffuse");
            terrain_ambient = v.second.get<GLfloat>("TerrainAmbient");
            terrain_diffuse = v.second.get<GLfloat>("TerrainDiffuse");



            sun_color = Math::GetVecFromString(sun_color_str);
            sun_dir = Math::GetVecFromString(sun_direction_str);
            fog_color = Math::GetVecFromString(fog_color_str);


        }


        break;

    }


    SetShouldReset(true);


}






void Environment::Init(char * path)
{

    SetPath(path);
    this->Reset();


}



