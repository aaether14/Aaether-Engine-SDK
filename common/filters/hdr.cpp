#include <stdafx.h>




void HdrImplementation::Init(GLuint width, GLuint height)
{



	bright_texture_temp = new TextureObject(1);
	bright_texture_temp->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_RGB, GL_RGBA,
		GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_EDGE);

	bright_texture = new TextureObject(1);
	bright_texture->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_RGB, GL_RGBA,
		GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_EDGE);



	this->bright_shader = new Shader();
	this->bright_shader->Add("data/shaders/bright_filter_vert.txt", GL_VERTEX_SHADER);
	this->bright_shader->Add("data/shaders/bright_filter_frag.txt", GL_FRAGMENT_SHADER);
	this->bright_shader->Link();



	this->bright_shader->AddVariable("texture");
	this->bright_shader->AddVariable("white_point");





}





void HdrImplementation::Clean()
{


	if (bright_shader)
	delete bright_shader;

	if (bright_texture)
	delete bright_texture;


	if (bright_texture_temp)
	delete bright_texture_temp;



}




void HdrImplementation::SetUniforms(GLfloat white_point)
{


	this->bright_shader->Set("white_point", white_point);


}