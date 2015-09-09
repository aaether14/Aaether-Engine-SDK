#include <stdafx.h>





void DofImplementation::Init(GLuint width, GLuint height)
{



    this->dof_texture = new TextureObject(1);
    this->dof_texture->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_RGB, GL_RGBA,
                                     GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_EDGE);

    this->dof_temp_texture = new TextureObject(1);
    this->dof_temp_texture->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_RGB, GL_RGBA,
                                          GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_EDGE);




}




void DofImplementation::Clean()
{


    if (dof_texture)
        delete dof_texture;


    if (dof_temp_texture)
        delete dof_temp_texture;



}
