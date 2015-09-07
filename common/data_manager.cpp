#include <stdafx.h>



void DataManager::Init()
{



	ControllerSource * controller_source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	GLuint window_width = controller_source->GetWindowWidth();
	GLuint window_height = controller_source->GetWindowHeight();







	GLuint dof_factor = 2;
	GLuint bright_factor = 2;
	Techniques * techniques = new Techniques();
    techniques->Create(window_width, window_height, ShadowMapWidth, ShadowMapHeight,
		window_width / dof_factor, window_height / dof_factor,
		window_width / bright_factor, window_height / bright_factor);



	Add("Techniques", techniques);
	Add("Resources", new ResourceLoader());








}




void DataManager::Enable()
{



	ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	ResourceLoader * res = static_cast<ResourceLoader*>(Get("Resources"));


	if (ctrl->GetDropFiles().size() > 0)
	{


	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


	scene_info->InsertNewEntity(ctrl->GetDropFiles()[0]);
	ctrl->ResetDropList();


	}


}


void DataManager::Clean()
{


	CleanModule();


}



