#ifndef TEXTURE_HPP
#define TEXTURE_HPP






#include <stdafx.h>







#define DebugMsg(str){printf("%s\n",str);}
#define POWER_OF_TWO(x) ( (x > 0) && ((x & (x - 1)) == 0) )
#define COLOR_TYPE 0x256
#define DEPTH_TYPE 0x257
#define G_TYPE 0x258






/**


Class for managing OpenGL textures and also WTT(write to texture) support
Using FreeImage for loading


*/
class TextureObject
{



    GLuint m_FBO;


    GLuint *texture;
    GLuint depth;


    GLuint num_tex;
    GLuint width;
    GLuint height;



public:


    /**
    Reserve a number of texture targets
    */
    inline TextureObject(GLuint num_tex)
    {
        this->Init(num_tex);
    }
    /**
    Create a number - 'num_tex'
    */
    inline void Init(GLuint num_tex)
    {
        glGenFramebuffers(1, &this->m_FBO);
        this->num_tex = num_tex;
    }


    /**
    Calls Clean()
    */
    inline ~TextureObject()
    {
        this->Clean();
    }
    /**
    Cleans textures
    */
    inline void Clean()
    {
        glDeleteFramebuffers(1, &m_FBO);
        glDeleteTextures(num_tex, texture);
        glDeleteTextures(1, &depth);
    }



    /**
    Bind the texture with 'id' to a 'tex_unit'
    */
    inline void BindTexture(GLuint id, GLuint tex_unit)
    {
        glActiveTexture(tex_unit);
        glBindTexture(GL_TEXTURE_2D, this->texture[id]);
    }
    /**
    Reset active texture unit
    */
    inline void ResetTextureState()
    {
        glActiveTexture(GL_TEXTURE0);
    }


    /**
    Get array of OpenGL texture references
    */
    inline GLuint *GetTexture()
    {
        return this->texture;
    }
    /**
    Get OpenGL texture reference of depth texture
    */
    inline GLuint GetDepth()
    {
        return this->depth;
    }


    /**
    Write to texture on given size
    */
    void WriteTexture(GLuint width, GLuint height);



    /**
    Create texture out of parameters
    */
    void CreateTexture(GLuint tex_type,
                       GLenum target,
                       GLsizei width, GLsizei height,
                       GLint internalFormat, GLint format,
                       GLenum type, GLvoid
                       * pixels,
                       GLint f_param,
                       GLint c_param,
                       glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));



    /**
    Get texture width
    */
    inline GLuint GetWidth()
    {
        return this->width;
    }
    /**
    Get texture height
    */
    inline GLuint GetHeight()
    {
        return this->height;
    }
    /**
    Set a certain viewport
    */
    inline void SetViewport()
    {
        glViewport(0, 0, this->width, this->height);
    }



    /**
    Load texture from file to OpenGL memory
    */
    static GLuint load_texture(char* file, GLint param_min, GLint param_max);
    /**
    Load cube map from files to OpenGL memory
    */
    static GLuint load_cube_texture(const char *Directory,
                                    const char *PosXFilename,
                                    const char *NegXFilename,
                                    const char *PosYFilename,
                                    const char *NegYFilename,
                                    const char *PosZFilename,
                                    const char *NegZFilename);
    /**
    Load textures to texture array in OpenGL memory
    */
    static GLuint create_texture_array(char *Directory, char ** textures, GLuint num, GLfloat aniso);
    /**
    Create a texture from a given color
    */
    static GLuint create_texture_from_color(GLfloat r, GLfloat y, GLfloat z);
    /**
    Fill FIBITMAP data from image file
    */
    static FIBITMAP *get_dib(char* file);
    /**
    read a .raw file
    */
    static bool readRawFile(char*path, BYTE * bits);
    /**
    Get size of a .raw file
    */
    static int getRawSize(char*path);
    /**
    Create a texture in memory
    */
    static GLuint create_texture(GLenum target, GLsizei width, GLsizei height, GLint internalFormat, GLint format, GLenum type, GLvoid * pixels,
                                 GLint f_param, GLint c_param, glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    /**
    Check if OpenGL is ok with what you're doing
    */
    static bool CheckStatus(GLuint fbo);





};






#endif
