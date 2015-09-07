#include <stdafx.h>






void SceneInfo::CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, Entity * new_entity)
{

	std::string class_name = typeid(*new_component).name();


#ifdef _MSC_VER
	class_name = class_name.substr(class_name.find_first_of(" ") + 1);
#endif





	if (new_component->isValid(AString::char_to_str(boost::filesystem::extension(iterator->path()))))
	{
		new_component->Load(AString::char_to_str(iterator->path().string()),
			AString::char_to_str(boost::filesystem::extension(iterator->path())));
		new_entity->AddComponent(class_name, new_component);
	}
	else if (new_component)
		delete new_component;





}






void SceneInfo::AddComponentsToEntity(char * path, Entity * new_entity)
{






	boost::filesystem::directory_iterator iterator(path);
	for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
	{




		if (boost::filesystem::is_regular_file(iterator->path()))
		{



			CreateComponentInstance(iterator, new ModelComponent(), new_entity);
			CreateComponentInstance(iterator, new InfoComponent(), new_entity);





		}



	}


}




void SceneInfo::AddEntity(Entity * new_entity)
{

	if (new_entity)
		if (!new_entity->GetComponentsSize())
			delete new_entity;
		else
		{
			if (new_entity->GetComponent("InfoComponent"))
			{
				InfoComponent * ic = static_cast<InfoComponent*>(new_entity->GetComponent("InfoComponent"));
				if (!entity_map.count(ic->GetInfo()->entity_name))
					entity_map[ic->GetInfo()->entity_name].reset(new_entity);
				else
				{
					GLuint number_sufix = 2;
					while (entity_map.count(ic->GetInfo()->entity_name + std::to_string(number_sufix)))
						number_sufix++;
					ic->GetInfo()->entity_name = ic->GetInfo()->entity_name + std::to_string(number_sufix);
					entity_map[ic->GetInfo()->entity_name].reset(new_entity);

				}
			}
			else
			{
				const std::string &ex("No info component found");
				printf("%s\n", ex.c_str());
			}
		}


}





void SceneInfo::Load()
{



	//reading components



	Reset();



		boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
		{



			Entity * new_entity = new Entity();
			AddComponentsToEntity(AString::char_to_str(iterator->path().string()), new_entity);
			AddEntity(new_entity);



		}





	//Reading infos






	using boost::property_tree::ptree;
	ptree pt;
	read_xml(GetPath(), pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
	{




        if (v.first == "EntityInstance")
		{



			std::string instance_name = v.second.get<std::string>("Name");



			EntityInstance * new_instance = new EntityInstance();
			new_instance->SetEntityName(v.second.get<std::string>("EntityName"));
			new_instance->AddInformation("TransformInfo", new TransformInfo());




			BOOST_FOREACH(ptree::value_type const& instance_info_index, v.second)
				new_instance->GetInformation("TransformInfo")->Load(instance_info_index, "TransformInfo");




			if (entity_map.count(new_instance->GetEntityName()))
				AddInstance(instance_name, new_instance);





		}



	}



	SetShouldReset(true);


}




void SceneInfo::Save()
{





	using boost::property_tree::ptree;
	ptree pt;
	ptree rootNode;







	std::map<std::string, boost::shared_ptr<EntityInstance> >::iterator it;



	for (it = instance_map.begin(); it != instance_map.end(); it++)
	{


		EntityInstance * instance = it->second.get();



			ptree new_info;
			new_info.push_back(ptree::value_type("EntityName", ptree(instance->GetEntityName())));
			new_info.push_back(ptree::value_type("Name", ptree(it->first)));
			new_info.add_child("TransformInfo", instance->GetInformation("TransformInfo")->Save());
			rootNode.add_child("EntityInstance", new_info);

	}





	pt.add_child("Scene", rootNode);
	boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
	write_xml(GetPath(), pt, std::locale(), settings);




}




void SceneInfo::Reset()
{


	ClearInstances();
	ClearEntities();


}




void SceneInfo::InsertNewEntity(std::string path)
{



	std::vector<std::string> extensions;
	extensions.push_back(".obj");
	extensions.push_back(".3ds");
	extensions.push_back(".blend");
	extensions.push_back(".ms3d");
	extensions.push_back(".dae");




	if (AFile::GetFileWithExtensionList(path, extensions).compare(STRING_ERROR) != 0)
	{


		std::string copied_folder_path = "data\\objects\\";
		std::string entity_name = path.substr(path.find_last_of("\\") + 1);
		copied_folder_path += entity_name;


		if (AFile::copyDir(boost::filesystem::path(path),
			boost::filesystem::path(copied_folder_path)))
		{

			InfoComponent * ic = new InfoComponent();
			ic->GetInfo()->base_rot = glm::vec3(0.0);
			ic->GetInfo()->base_scale = glm::vec3(1.0);
			ic->GetInfo()->entity_name = entity_name;
			ic->GetInfo()->cull = 1;
			ic->GetInfo()->affected_by_ssao = 1;
			ic->GetInfo()->radius = 12.5;



			boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
			boost::property_tree::write_xml(AString::char_to_str(std::string(copied_folder_path + "\\general_info.ainfo"))
				, ic->GetInfo()->GetPtree(), std::locale(), settings);


			delete ic;


				AssimpConverter * ac = new AssimpConverter();
				ac->ConvertModel(AFile::GetFileWithExtensionList(copied_folder_path, extensions));
				delete ac;



				Entity * new_entity = new Entity();
				AddComponentsToEntity(AString::char_to_str(copied_folder_path), new_entity);
				AddEntity(new_entity);




		}
		else
		{
			const std::string &ex("Could not create entity - most likely there's another entity with the same name!");
			printf("%s\n", ex.c_str());
		}


	}
	else
	{
		const std::string &ex("No model file detected!");
		printf("%s\n", ex.c_str());
	}




}

