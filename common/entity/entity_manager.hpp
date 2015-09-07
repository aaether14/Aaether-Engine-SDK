#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP






#include <stdafx.h>







/**


Entity manager implementation to determine how each visible entity affects the scene
Also stores the entity palette
It uses the terrain quad tree for frustum culling


*/
class EntityManager : public AModule


{








public:




	/**
	Initialize data
	*/
	void Init();




	/**
	Clean data
	*/
	void Clean();


	/**
	Try to render entities
	*/
	void Enable();
	

};





#endif