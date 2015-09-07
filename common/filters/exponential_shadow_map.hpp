#ifndef SHADOW_HPP
#define SHADOW_HPP




#include <stdafx.h>





#define ShadowMapWidth 1024
#define ShadowMapHeight 1024




/**



Exponential shadow mapping



*/
class ESMImplementation
{


	Shader * shadow_shader;
	TextureObject * shadow_map;
	TextureObject * temp_shadow_map;


	GLuint width, height;
	GLboolean on_shadow_pass;
	GLfloat shadow_size;


public:


	/**
	Calls Init()
	*/
	inline ESMImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	/**
	Initializes shadow map with given size
	*/
	void Init(GLuint width, GLuint height);


	/**
	Calls Clean()
	*/
	inline ~ESMImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Use shadow shader program
	*/
	inline void Use(){ this->shadow_shader->Enable(); }
	/**
	Get primary shadow map
	*/
	inline TextureObject * GetShadowMap(){ return this->shadow_map; }
	/**
	Get secondary shadow map
	*/
	inline TextureObject * GetTempShadowMap(){ return this->temp_shadow_map; }


	/**
	Query shadow pass
	*/
	inline GLboolean OnShadowPass(){ return this->on_shadow_pass; }
	/**
	Set if on shadow pass
	*/
	inline void SetShadowPass(GLboolean on_shadow_pass){ this->on_shadow_pass = on_shadow_pass; }

	/**
	Provide ModelViewProjection to the shader that computes shadow map
	*/
	inline void UniformMVP(glm::mat4 MVP){ this->shadow_shader->Set("depthMVP", MVP); }


	/**
	Create ortographic projection from light direction, shadow size and ViewInfo (position and view direction)
	*/
	glm::mat4 GetDirectionalShadow(Environment * env, ViewInfo * info, View * view);



};


#endif