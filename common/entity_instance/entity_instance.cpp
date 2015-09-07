#include <stdafx.h>




void EntityInstance::Enable(AModule * manager)
{


	SceneInfo * scene_info = static_cast<SceneInfo*>(manager->Get("DataManager")->Get("Resources")->Get("Entities"));
	scene_info->GetEntity(GetEntityName())->Render(manager, this);


}


