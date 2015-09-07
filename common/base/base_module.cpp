#include <stdafx.h>




void AModule::SetManager(AModule * module)
{

	manager = module;

}



void AModule::CleanModule()
{


	std::map<std::string, AModule*>::iterator it;
	for (it = module_map.begin(); it != module_map.end(); it++)
		it->second->Clean();
	
	module_map.clear();


}



void AModule::Add(std::string key, AModule * module)
{

	module_map[key] = module;
	module->SetManager(GetManager());
	module->Init();


}





AModule * AModule::Get(std::string key)
{

	return module_map[key];

}




AModule * AModule::GetManager()
{

	return manager;

}