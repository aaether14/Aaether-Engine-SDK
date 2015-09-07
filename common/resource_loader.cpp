#include <stdafx.h>






void ResourceLoader::LoadResourcePaths(char *path)
{


	int i = 0;

	std::ifstream fin(path);
	std::string temp_str;

	std::string files[8];


	while (std::getline(fin,temp_str))
	{
		if (temp_str == "")continue;
		files[i] = temp_str;
		i++;
	}


	terrain_file = files[0];
	color_file = files[1];
	t_file = files[2];
	n_file = files[3];
	a_file = files[4];


	env_file = files[5];
    fsettings_file = files[6];
	scene_file = files[7];


	fin.close();

}



void ResourceLoader::Init()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));


	LoadResourcePaths(AString::char_to_str(ctrl->GetProjectName()));
	Add("Environment", new Environment(GetEnvFile()));
	Add("FilterSettings", new FilterSettings(GetFSettingsFile()));
	Add("Entities", new SceneInfo(AString::char_to_str(GetSceneFile())));
	LoadChanges();


}




void ResourceLoader::Clean()
{


	CleanModule();


}
