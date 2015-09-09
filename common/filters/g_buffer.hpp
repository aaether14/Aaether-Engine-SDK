#ifndef G_BUFFER_HPP
#define G_BUFFER_HPP



#include <stdafx.h>






/**



GBuffer implementation for deffered rendering
Provides textures for simple WTT and ping pong techniques



*/
class GBuffer
{


    TextureObject * buffer;
    TextureObject * color_textures[2];


    GLuint texture_index;


public:


    /**
    Calls Init()
    */
    inline GBuffer(GLuint window_width, GLuint window_height)
    {
        this->Init(window_width, window_height);
    }
    /**
    Initialize GBuffer with screen size
    */
    void Init(GLuint window_width, GLuint window_height);


    /**
    Calls Clean()
    */
    inline ~GBuffer()
    {
        this->Clean();
    }
    /**
    Cleans data
    */
    void Clean();


    /**
    Get color texture array
    */
    inline TextureObject ** GetColorTextures()
    {
        return this->color_textures;
    }
    /**
    Get GBuffer pointer
    */
    inline TextureObject * GetBuffer()
    {
        return this->buffer;
    }
    /**
    Ping pong primary texture
    */
    inline TextureObject * GetTexture()
    {
        return color_textures[texture_index];
    }
    /**
    Ping pong secondary texture
    */
    inline TextureObject * GetOtherTexture()
    {
        return color_textures[!texture_index];
    }


    /**
    Reset ping pong counter
    */
    inline void Reset()
    {
        texture_index = 0;
    }
    /**
    Ping pong ( Switching active texture)
    */
    inline void Switch()
    {
        texture_index = !texture_index;
    }




};



#endif
