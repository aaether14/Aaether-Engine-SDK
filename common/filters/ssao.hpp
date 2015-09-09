#ifndef SSAO_HPP
#define SSAO_HPP




#include <stdafx.h>






/**



Hemispherical SSAO with noise texture and blur



*/
class SSAOImplementation
{


#define MAX_BONES 128


    //SSAO PASS

    const static GLuint KERNEL_SIZE = 128;


    Shader * ssao_shader;
    TextureObject * ssao_texture;
    TextureObject * ssao_temp_texture;
    TextureObject * geometry_pass_texture;


    GLuint noise_texture;
    GLuint window_width, window_height;
    void Init(GLuint width, GLuint height);
    void Clean();


    //SSAO BLUR

    Shader * ssao_blur;


    //SSAO Geometry Pass

    Shader * geometry_pass;
    GLboolean on_geometry_pass;





    /**
    Generate random kernels for ssao shader sampling
    */
    void GenKernel();
    /**
    Generate the noise texture for normal randomization
    */
    void GenerateNoiseTexture(GLuint size);




public:


    /**
    Calls Init()
    */
    inline SSAOImplementation(GLuint width, GLuint height)
    {
        this->Init(width, height);
    }
    /**
    Initializes textures with given size
    */
    inline ~SSAOImplementation()
    {
        this->Clean();
    }


    /**
    Get primary SSAO texture object
    */
    inline TextureObject * GetSSAOTexture()
    {
        return this->ssao_texture;
    }
    /**
    Get secondary SSAO texture object
    */
    inline TextureObject * GetSSAOTempTexture()
    {
        return this->ssao_temp_texture;
    }
    /**
    Get texture target for geometry pass
    */
    inline TextureObject * GetGeometryPassTexture()
    {
        return this->geometry_pass_texture;
    }
    /**
    Get noise texture reference
    */
    inline GLuint GetNoiseTexture()
    {
        return this->noise_texture;
    }


    /**
    Use shader program for ssao texture computation
    */
    inline void Use()
    {
        ssao_shader->Enable();
    }
    /**
    Use shader program for ssao blur
    */
    inline void UseBlur()
    {
        ssao_blur->Enable();
    }
    /**
    Use shader program for geometry pass
    */
    inline void UseGeometryPass()
    {
        geometry_pass->Enable();
    }

    /**
    Bind texture unit in ssao blur
    */
    inline void BindBlurTexture()
    {
        ssao_blur->Set("texture", 0);
    }




    /**
    Link required data to ssao shader uniforms
    */
    void SetUniforms(glm::mat4 proj, GLfloat radius, GLfloat aspect, GLfloat tan_fov, GLfloat power, GLint num_samples);
    /**
    Link required data to geometry pass uniforms
    */
    void SetGeometryPassUniforms(glm::mat4 MVP, glm::mat4 MV);
    /**
    Set if meshes are currently rendered
    */
    inline void SetOnMeshRender(GLfloat on_mesh_render)
    {
        this->geometry_pass->Set("on_mesh_render", on_mesh_render);
    }

    /**
    Query geometry pass
    */
    inline GLboolean OnGeometryPass()
    {
        return this->on_geometry_pass;
    }
    /**
    Set if on geometry pass
    */
    inline void SetGeometryPass(GLboolean on_geometry_pass)
    {
        this->on_geometry_pass = on_geometry_pass;
    }


    /**
    Set first texture unit (ssao shader)
    */
    inline void SetTex1()
    {
        this->ssao_shader->Set("gDepthMap", 0);
    }
    /**
    Set second texture unit (ssao shader)
    */
    inline void SetTex2()
    {
        this->ssao_shader->Set("gNormalMap", 1);
    }
    /**
    Set third texture unit (ssao shader)
    */
    inline void SetTex3()
    {
        this->ssao_shader->Set("gNoiseMap", 2);
    }


    /**
    Bind ssao textures required in shader
    */
    void BindSSAOTexture();

    /**
    Get width of ssao textures
    */
    inline GLuint GetWidth()
    {
        return this->window_width;
    }
    /**
    Get height of ssao textures
    */
    inline GLuint GetHeight()
    {
        return this->window_height;
    }


};




#endif
