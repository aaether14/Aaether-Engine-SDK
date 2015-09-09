#ifndef MESH_SHADER_HPP
#define MESH_SHADER_HPP





#include <stdafx.h>








class MeshShader : public Shader
{


#define MAX_BONES 128


    Light *m_light;



public:


    /**
    Calls basic Shader() and Init()
    */
    inline MeshShader() : Shader()
    {
        Init();
    }
    /**
    Initializes uniforms and light
    */
    void Init();
    /**
    Cleans data and shader
    */
    void Clean();


    /**
    Place the model in space
    */
    void Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 NormalMatrix);
    /**
    Place the model in space
    */
    inline void Space(glm::mat4 ModelMatrix, View * view)
    {
        Space(ModelMatrix, view->getViewMatrix(), view->getProjectionMatrix(), glm::transpose(glm::inverse(view->getViewMatrix() * ModelMatrix)));
    }






    /**
    Send specular values to shader
    */
    inline void SetSpecular(GLfloat specular_intensity, GLfloat specular_power)
    {
        Set("specular_intensity", specular_intensity);
        Set("specular_power", specular_power);
    }


    /**
    Get light pointer
    */
    inline Light*getLight()
    {
        return m_light;
    }



};









#endif








