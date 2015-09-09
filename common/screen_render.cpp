#include <stdafx.h>



void ScreenRender::Init()

{


    Add("data/shaders/2d_vert.txt", GL_VERTEX_SHADER);
    Add("data/shaders/2d_frag.txt", GL_FRAGMENT_SHADER);
    Link();

    AddVariable("texture");
    AddVariable("texture1");
    AddVariable("texture2");
    AddVariable("use_dof");
    AddVariable("white_point");




    this->quad = new Quad();


}




void ScreenRender::Clean()
{

    delete quad;

}




void ScreenRender::Render(GLuint texture,
                          GLuint texture1,
                          GLuint texture2,
                          GLfloat use_dof,
                          GLfloat white_point,
                          glm::ivec2 window_size)
{




    glViewport(0, 0, window_size.x, window_size.y);
    Shader::Enable();


    Set("use_dof", use_dof);
    Set("white_point", white_point);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    Set("texture", 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    Set("texture1", 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    Set("texture2", 2);


    quad->Render();
    Stop();


}




