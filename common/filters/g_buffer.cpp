#include <stdafx.h>



void GBuffer::Init(GLuint window_width, GLuint window_height)
{


	Reset();


	buffer = new TextureObject(1);
	buffer->CreateTexture(G_TYPE,
		GL_TEXTURE_2D,
		window_width, window_height,
		GL_RGB16F,
		GL_RGBA,
		GL_FLOAT,
		0,
		GL_NEAREST,
		GL_CLAMP_TO_EDGE);
	buffer->CreateTexture(DEPTH_TYPE,
		GL_TEXTURE_2D,
		window_width,
		window_height,
		GL_DEPTH_COMPONENT,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		0,
		GL_NEAREST,
		GL_CLAMP_TO_EDGE);




	
	for (GLuint i = 0; i < 2; i++)
	{


		color_textures[i] = new TextureObject(1);
		color_textures[i]->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, window_width, window_height, GL_RGB16F, GL_RGBA,
			GL_FLOAT, 0, GL_NEAREST, GL_CLAMP_TO_EDGE);


	}





}




void GBuffer::Clean()
{


	if (buffer)
	delete buffer;


	for (GLuint i = 0; i < 2; i++)
		if (color_textures[i])
		delete color_textures[i];


}