#ifndef BASE_MODEL_LOADER_HPP
#define BASE_MODEL_LOADER_HPP






#include <stdafx.h>



/**


Base model loader implementation
Interface for adding any type of 3d model to an entity


*/
class AModel
{


public:



	/**
	Model loading
	*/
	virtual int Load(const char * path) = 0;
	/**
	Render to scene
	*/
	virtual void Render() = 0;
	/**
	Cleaning used resources
	*/
	virtual void Clean() = 0;


};




#endif