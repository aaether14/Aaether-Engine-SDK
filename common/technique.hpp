#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP





#include <stdafx.h>






#define NULL_FILTER 11
#define DEPTH_SHADER 12
#define GAUS_BLUR_SHADER 13
#define GAUS_BLUR_SHADER2 14
#define BRIGHT_FILTER 15
#define SSAO_FILTER 16
#define SSAO_BLUR 17
#define GAMMA_CORRECTION_FILTER 18
#define GEOMETRY_PASS 19
#define FXAA_FILTER 20





class Techniques : public AModule
{




    BasicFilterImplementation * basic_filter_implementation;
    SSAOImplementation * ssao_implementation;
    ESMImplementation * esm_implementation;
    BlurImplementation * blur_implementation;
    DofImplementation * dof_implementation;
    HdrImplementation * hdr_implementation;
    FXAAImplementation * fxaa_implementation;
    GBuffer * g_buffer;




public:





    /**
    Initialize all techniques
    */
    bool Create(GLuint window_width, GLuint window_height,
                GLuint shadow_width, GLuint shadow_height,
                GLuint dof_width, GLuint dof_height,
                GLuint bright_width, GLuint bright_height);






    /**
    Cleans data used by techniques
    */
    void Clean();
    /**
    Initializes data
    */
    void Init();
    /**
    Enables module to affect scene
    */
    void Enable();



    /**
    Bind a certain texture object to be written to using the 'prog_target' shader
    */
    void Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height);
    /**
    Apply certian filter and transform 'tex_source' into 'tex_target'
    */
    void ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height);
    /**
    Unbind any binding done by the class
    */
    void Unbind();
    /**
    Run a certain shader program
    */
    void RunProgram(GLuint prog_target);





    inline BasicFilterImplementation * GetBasic()
    {
        return basic_filter_implementation;
    }
    inline SSAOImplementation * GetSSAO()
    {
        return ssao_implementation;
    }
    inline ESMImplementation * GetShadow()
    {
        return esm_implementation;
    }
    inline BlurImplementation * GetBlur()
    {
        return blur_implementation;
    }
    inline DofImplementation * GetDof()
    {
        return dof_implementation;
    }
    inline HdrImplementation * GetHdr()
    {
        return hdr_implementation;
    }
    inline FXAAImplementation * GetFXAA()
    {
        return fxaa_implementation;
    }
    inline GBuffer * GetGBuffer()
    {
        return g_buffer;
    }










};




#endif
