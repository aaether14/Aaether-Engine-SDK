#ifndef FXAA_HPP
#define FXAA_HPP




#include <stdafx.h>




/**


Fast aporXimate Anti Aliasing


*/
class FXAAImplementation
{


	Shader * fxaa_shader;



public:



	/**
	Calls Init()
	*/
	inline FXAAImplementation(){ this->Init(); }
	/**
	Initializes data
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~FXAAImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Get pointer to FXAA shader
	*/
	inline Shader * GetFxaaFilter(){ return this->fxaa_shader; }
	/**
	Binds FXAA texture unit
	*/
	inline void BindFxaaTexture(){ this->fxaa_shader->Set("R_filterTexture", 0); }

	/**
	Link data to uniforms
	*/
	void SetUniforms(GLfloat span_max, GLfloat reduce_min, GLfloat reduce_mul);



};




#endif 