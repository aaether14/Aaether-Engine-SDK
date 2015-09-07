#ifndef SIMPLE_2D_HPP
#define SIMPLE_2D_HPP





#include <stdafx.h>




/*


Class for combining all textures from deffered process


*/
class ScreenRender : public Shader
{



	Quad * quad;




public:



	/**
	Initializes shader and quad
	*/
	void Init();


	/**
	Calls Clean()
	*/
	inline ~ScreenRender(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();
	/**
	Empty Enable() to ensure it can access the interface
	*/
	inline void Enable(){}


	/**
	Combines textures and renders to screen
	*/
	void Render(GLuint texture,
		GLuint texture1,
		GLuint texture2,
		GLfloat use_dof,
		GLfloat white_point,
		glm::ivec2 window_size);




};



#endif