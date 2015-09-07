#ifndef PIPELINE
#define PIPELINE





#include <stdafx.h>






class Pipeline : public AModule
{


	/**
	Initialize data
	*/
	void Init();



	/**
	Pass that colors the screen
	*/
	void LightPass();
	/**
	Pass that computes shadow map
	*/
	void ShadowPass();
	/**
	Geometry information needed for SSAO map computation
	*/
	void GeometryPass();




	/**
	Ping pong technique for bluring textures
	*/
	void ApplyGausBlur(GLuint type,
		TextureObject * tex_source, TextureObject * tex_target,
		GLuint width, GLuint height,
		GLfloat blur_amount);



	/**
	Handle depth of field
	*/
	void HandleDoF();
	/**
	Handle HDR bloom
	*/
	void HandleBloom();
	/**
	Handle screen space ambient occlusion
	*/
	void HandleSSAO();
	/**
	Handle fast aproximate anti aliasing
	*/
	void HandleFXAA();




public:



	/**
	Enable pipeline
	*/
	void Enable();
	/**
	Clean data
	*/
	void Clean();


};

#endif