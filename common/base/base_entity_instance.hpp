#ifndef BASE_ENTITY_INSTANCE_HPP
#define BASE_ENTITY_INSTANCE_HPP




#include <stdafx.h>




/**
Interface for entity instance
*/
class AEntityInstance
{


public:


	/**
	Every instance should have a way to affect scene
	*/
	virtual void Enable(AModule * manager) = 0;



	/**
	Get vector of child nodes
	*/
	inline AEntityInstance* GetChildNode(GLuint i){ return child_nodes[i].get(); }
	/**
	Get number of childs
	*/
	inline GLuint GetNumberOfChilds(){ return child_nodes.size(); }
	/**
	Add child node
	*/
	inline void AddChildNode(AEntityInstance* new_child){ child_nodes.push_back(boost::shared_ptr<AEntityInstance>(new_child)); }
	/**
	Add info to entity instance
	*/




	inline void AddInformation(std::string name, AEntityInstanceInfo * info)
	{
		infos.insert(std::pair<std::string, boost::shared_ptr<AEntityInstanceInfo> >(name, boost::shared_ptr<AEntityInstanceInfo>(info)));
	}
	/**
	Get information from entity instance
	*/
	inline AEntityInstanceInfo * GetInformation(std::string name){ return infos[name].get(); }





	/**
	Get entity name
	*/
	inline std::string GetEntityName(){ return entity_name; }
	/**
	Set entity name
	*/
	inline void SetEntityName(std::string name){ entity_name = name; }



private:



	std::vector<boost::shared_ptr<AEntityInstance> > child_nodes;
	std::map<std::string, boost::shared_ptr<AEntityInstanceInfo> > infos;


	std::string entity_name;




protected:




};



#endif
