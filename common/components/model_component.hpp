#ifndef MODEL_COMPONENT_HPP
#define MODEL_COMPONENT_HPP





#include <stdafx.h>




/**


Model component implementation
Used to load any type of model that has Render, Load and Clean functions defined


*/
class ModelComponent : public AComponent
{

	/**
	Pointer to model data, any class filling the AModel interface can be referenced
	*/
	AModel * model;


public:


	/**
	Provide definition for pure virtual function
	*/
	bool isValid(char * extension);
	/**
	Provide definition for pure virtual function
	*/
	void Load(char * path, char * extension);


	/**
	Get pointer to model data
	*/
	inline AModel*GetModel(){ return model; }



};




#endif