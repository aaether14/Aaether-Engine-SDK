#ifndef GENERAL_ENTITY_INFO_COMPONENT
#define GENERAL_ENTITY_INFO_COMPONENT





#include <stdafx.h>




/**


Info component implementation
Affects entity


*/
class InfoComponent : public AComponent
{



	/**
	Actual info for an entity
	*/
	class GeneralEntityInfo
	{


	public:


		std::string entity_name;
		glm::vec3 base_rot;
		glm::vec3 base_scale;
		GLfloat radius;
		GLboolean affected_by_ssao;
		GLboolean cull;


		/**
		Read general information regarding the entity from a file
		*/
		void Read(std:: string path);
		/**
		Create a boost::property_tree::ptree from the data
		*/
		boost::property_tree::ptree GetPtree();
		



	}*info;
	


public:


	/**
	Call Init()
	*/
	inline InfoComponent(){ Init(); }
	/**
	Initialize data
	*/
	void Init();


	/**
	Provide definition for pure virtual function
	*/
	bool isValid(char * extension);
	/**
	Provide definition for pure virtual function
	*/
	void Load(char * path, char * extension);


	/**
	Get pointer to entity information
	*/
	GeneralEntityInfo * GetInfo(){ return info; }



};





#endif