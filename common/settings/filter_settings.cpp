#include <stdafx.h>




void FilterSettings::Reset()
{



    //SSAO

    SSAO.Enabled = false;
    SSAO.Radius = 1.5;
    SSAO.Power = 1.25;
    SSAO.NumSamples = 16;

    //Dof

    DoF.Enabled = false;



    //HDR


    //Bloom


    HDR.Bloom.Enabled = false;
    HDR.Bloom.Whitepoint = 1.0;



    //FXAA


    FXAA.Enabled = false;
    FXAA.span_max = 8.0;
    FXAA.reduce_min = 0.0078125;
    FXAA.reduce_mul = 0.125;



    SetShouldReset(false);




}


void FilterSettings::Init(char * path)
{

    SetPath(path);
    Reset();


}








void FilterSettings::Save()
{


    using boost::property_tree::ptree;
    ptree pt;
    ptree rootNode;



    ptree new_info;
    new_info.push_back(ptree::value_type("Enabled", ptree(std::to_string(SSAO.Enabled))));
    new_info.push_back(ptree::value_type("Radius", ptree(std::to_string(SSAO.Radius))));
    new_info.push_back(ptree::value_type("Power", ptree(std::to_string(SSAO.Power))));
    new_info.push_back(ptree::value_type("NumberOfSamples", ptree(std::to_string(SSAO.NumSamples))));
    rootNode.add_child("SSAO", new_info);



    new_info.clear();
    new_info.push_back(ptree::value_type("Enabled", ptree(std::to_string(DoF.Enabled))));
    rootNode.add_child("DoF", new_info);



    new_info.clear();
    new_info.push_back(ptree::value_type("BloomEnabled", ptree(std::to_string(HDR.Bloom.Enabled))));
    new_info.push_back(ptree::value_type("Whitepoint", ptree(std::to_string(HDR.Bloom.Whitepoint))));
    rootNode.add_child("HDR", new_info);


    new_info.clear();
    new_info.push_back(ptree::value_type("Enabled", ptree(std::to_string(FXAA.Enabled))));
    new_info.push_back(ptree::value_type("ReduceMul", ptree(std::to_string(FXAA.reduce_mul))));
    new_info.push_back(ptree::value_type("ReduceMin", ptree(std::to_string(FXAA.reduce_min))));
    new_info.push_back(ptree::value_type("SpanMax", ptree(std::to_string(FXAA.span_max))));
    rootNode.add_child("FXAA", new_info);





    pt.add_child("Scene", rootNode);
    boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
    write_xml(GetPath(), pt, std::locale(), settings);



}




void FilterSettings::Load()
{



    using boost::property_tree::ptree;
    ptree pt;
    read_xml(GetPath(), pt);




    BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
    {


        if (v.first == "SSAO")
        {


            SSAO.Enabled = v.second.get<GLboolean>("Enabled");
            SSAO.Radius = v.second.get<GLfloat>("Radius");
            SSAO.Power = v.second.get<GLfloat>("Power");
            SSAO.NumSamples = v.second.get<GLint>("NumberOfSamples");


        }
        else if (v.first == "DoF")
        {

            DoF.Enabled = v.second.get<GLboolean>("Enabled");

        }
        else if (v.first == "HDR")
        {

            HDR.Bloom.Enabled = v.second.get<GLboolean>("BloomEnabled");
            HDR.Bloom.Whitepoint = v.second.get<GLfloat>("Whitepoint");

        }
        else if (v.first == "FXAA")
        {

            FXAA.Enabled = v.second.get<GLboolean>("Enabled");
            FXAA.reduce_mul = v.second.get<GLfloat>("ReduceMul");
            FXAA.reduce_min = v.second.get<GLfloat>("ReduceMin");
            FXAA.span_max = v.second.get<GLfloat>("SpanMax");

        }




    }


    SetShouldReset(true);


}


