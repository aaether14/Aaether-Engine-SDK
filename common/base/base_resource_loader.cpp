#include <stdafx.h>








void BaseResourceLoader::SaveChanges()
{


	try
	{

		std::map<std::string, AModule*>::iterator it;



		for (it = module_map.begin(); it != module_map.end(); it++)
			static_cast<AStateSaver*>(it->second)->Save();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}


}



void BaseResourceLoader::LoadChanges()
{




	try
	{

		std::map<std::string, AModule*>::iterator it;



		for (it = module_map.begin(); it != module_map.end(); it++)
			static_cast<AStateSaver*>(it->second)->Load();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}




}



void BaseResourceLoader::NoChanges()
{


	try
	{

		std::map<std::string, AModule*>::iterator it;



		for (it = module_map.begin(); it != module_map.end(); it++)
			static_cast<AStateSaver*>(it->second)->Reset();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}




}




void BaseResourceLoader::Init()
{



}




void BaseResourceLoader::Clean()
{



}




void BaseResourceLoader::Enable()
{



}




