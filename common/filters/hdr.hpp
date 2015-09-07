#ifndef HDR_HPP
#define HDR_HPP




#include <stdafx.h>






/**


High Dynamic Range including Bloom, Tone mapping, white points and basic exposure
WIP


*/
class HdrImplementation
{



	Shader * bright_shader;
	TextureObject * bright_texture;
	TextureObject * bright_texture_temp;




public:




	/**
	Calls Init()
	*/
	inline HdrImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	/**
	Initializes textures with given size
	*/
	void Init(GLuint width, GLuint height);



	/**
	Calls Clean()
	*/
	inline ~HdrImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Get primary bloom texture
	*/
	inline TextureObject * GetBrightTexture(){ return this->bright_texture; }
	/**
	Get secondary bloom texture
	*/
	inline TextureObject * GetBrightTextureTemp(){ return this->bright_texture_temp; }


	/**
	Get pointer to bloom shader
	*/
	inline Shader * GetBrightShader(){ return this->bright_shader; }
	/**
	Bind texture unit for bloom shader
	*/
	inline void BindBrightTexture(){ this->bright_shader->Set("texture", 0); }

	/**
	Sets uniforms for bloom shader
	*/
	void SetUniforms(GLfloat white_point);




};





#endif