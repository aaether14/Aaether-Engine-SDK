#include <stdafx.h>







void Controller::Init()
{



	using boost::property_tree::ptree;
	ptree pt;
	read_xml("data/settings.xml", pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("GeneralInfo"))
	{




		if (v.first == "BaseInfo")
		{


			GLuint window_width = v.second.get<GLuint>("WindowWidth");
			GLuint window_height = v.second.get<GLuint>("WindowHeight");
			std::string window_title = v.second.get<std::string>("WindowTitle");
			GLboolean fullscreen = v.second.get<GLboolean>("Fullscreen");
			GLuint opengl_major_version = v.second.get<GLuint>("OpenGLMajorVersion");
			GLuint opengl_minor_version = v.second.get<GLuint>("OpenGLMinorVersion");
			project_name = v.second.get<std::string>("ProjectName");




			CreateWindowContext(window_width, window_height, fullscreen, AString::char_to_str(window_title), opengl_major_version, opengl_minor_version);
			Add("Camera", new Camera());






		}
		



	}





	

}





void Controller::Clean()
{

	
	CleanModule();
	ControllerSource::Clean();


}






void Controller::Enable()
{



	ControllerSource::Enable();
	Camera * camera = static_cast<Camera*>(Get("Camera"));

	camera->ProcessInput(this);
	camera->ComputeAngles(this);
	camera->SetFrustum(camera->GetView()->getCamera());




}
