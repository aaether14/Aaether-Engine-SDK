#ifndef TERRAIN_SHADER_HPP
#define TERRAIN_SHADER_HPP





#include <stdafx.h>





class TerrainShader : public Shader
{


	Light *m_light;



public:



	/**
	Initialize light, shaders and uniforms
	*/
	void Init();
	/**
	Calls Init()
	*/
	inline TerrainShader() : Shader(){ Init(); }
	/**
	Cleans all data
	*/
	void Clean();



	/**
	Holding information required for splatting
	*/
	class TextureAttributes
	{

	public:

		GLfloat diffuse_scale;
		GLfloat detail_scale;
		GLfloat diffuse_intensity;

	};


	/**
	Place the terrain in Space
	*/
	void Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);
	/**
	Place the terrain in Space
	*/
	inline void Space(glm::mat4 ModelMatrix, View * view){ Space(ModelMatrix, view->getViewMatrix(), view->getProjectionMatrix()); }
	/**
	Send splatting information to shader
	*/
	void SendTextureAttributes(TextureAttributes*tex_attributes, GLuint n);
	/**
	Get light pointer
	*/
	inline Light*getLight(){ return m_light; }

};



/**
Load a texture attributes set from a file
*/
void LoadTextureAttributesSet(char * path, TerrainShader::TextureAttributes*tex_data);








#endif