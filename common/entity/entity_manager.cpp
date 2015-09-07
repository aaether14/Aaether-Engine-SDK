#include <stdafx.h>





void EntityManager::Init()
{




}








void EntityManager::Enable()
{



	SceneInfo * scene_info = static_cast<SceneInfo*>(GetManager()->Get("DataManager")->Get("Resources")->Get("Entities"));
	std::map<std::string, boost::shared_ptr<EntityInstance> >::iterator it;
	for (it = scene_info->GetFirstInstance(); it != scene_info->GetLastInstance(); it++)
		it->second.get()->Enable(GetManager());


}







void EntityManager::Clean()
{


	CleanModule();


}





