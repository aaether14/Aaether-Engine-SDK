#ifndef DOF_HPP
#define DOF_HPP




#include <stdafx.h>





/**


Attempt to create Depth of Field
WIP


*/
class DofImplementation
{



	TextureObject * dof_texture;
	TextureObject * dof_temp_texture;



public:



	/**
	Calls Init()
	*/
	inline DofImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	/**
	Inits textures with given size
	*/
	void Init(GLuint width, GLuint height);



	/**
	Calls Clean()
	*/
	inline ~DofImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Get pointer to primary texture
	*/
	inline TextureObject * GetDofTexture(){ return this->dof_texture; }
	/**
	Get pointer to secondary texture
	*/
	inline TextureObject * GetDofTempTexture(){ return this->dof_temp_texture; }



};








#endif