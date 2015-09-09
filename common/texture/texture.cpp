#include <stdafx.h>




#define ANISO 16.0f





FIBITMAP * TextureObject::get_dib(char* file)
{



    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *dib(0);
    fif = FreeImage_GetFileType(file, 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(file);
    if (fif == FIF_UNKNOWN)
        return NULL;
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, file);
    if (!dib)
        return NULL;
    FreeImage_FlipVertical(dib);
    return dib;



}







GLuint TextureObject::load_texture(char* file, GLint param_min, GLint param_max)
{



    BYTE* bits(0);
    unsigned int width(0), height(0);
    GLuint gl_texID;
    FIBITMAP *dib = get_dib(file);
    if (!dib)
        return -1;
    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    if ((bits == 0) || (width == 0) || (height == 0))
        return -1;
    glGenTextures(1, &gl_texID);
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    if (FreeImage_GetBPP(dib) == 24)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    }
    else if (FreeImage_GetBPP(dib) == 32)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_max);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ANISO);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    FreeImage_Unload(dib);
    return gl_texID;




}






GLuint TextureObject::create_texture_from_color(GLfloat r, GLfloat g, GLfloat b)
{


    GLuint gl_texID;
    BYTE * bits = new BYTE[3];
    bits[0] = (r * 255);
    bits[1] = (g * 255);
    bits[2] = (b * 255);
    glGenTextures(1, &gl_texID);
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
    glBindTexture(GL_TEXTURE, 0);
    delete bits;
    return gl_texID;




}





GLuint TextureObject::load_cube_texture(const char *Directory,
                                        const char *PosXFilename,
                                        const char *NegXFilename,
                                        const char *PosYFilename,
                                        const char *NegYFilename,
                                        const char *PosZFilename,
                                        const char *NegZFilename)
{



    std::string files[6];
    files[0] += Directory;
    files[0] += PosXFilename;
    files[1] += Directory;
    files[1] += NegXFilename;
    files[2] += Directory;
    files[2] += PosYFilename;
    files[3] += Directory;
    files[3] += NegYFilename;
    files[4] += Directory;
    files[4] += PosZFilename;
    files[5] += Directory;
    files[5] += NegZFilename;




    FIBITMAP * dib(0);
    BYTE* bits(0);
    unsigned int width(0), height(0);
    GLuint gl_texID;




    glGenTextures(1, &gl_texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gl_texID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (int i = 0; i<6; i++)
    {


        dib = get_dib(AString::char_to_str(files[i]));
        bits = FreeImage_GetBits(dib);
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);





        if ((bits == 0) || (width == 0) || (height == 0))
            return -1;
        if (FreeImage_GetBPP(dib) == 24)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, 0, GL_SRGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
        else if (FreeImage_GetBPP(dib) == 32)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);



        FreeImage_Unload(dib);
    }




    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return gl_texID;



}







GLuint TextureObject::create_texture_array(char *Directory, char ** textures, GLuint num, GLfloat aniso)
{



    GLuint gl_texID(0), width(0), height(0);
    FIBITMAP ** dibs = 0;
    BYTE ** bits = 0;
    dibs = new FIBITMAP*[num];
    bits = new BYTE*[num];
    for (GLuint i = 0; i < num; i++)
    {


        std::string file_path = std::string(std::string(Directory) + std::string(textures[i]));
        dibs[i] = get_dib(AString::char_to_str(file_path));
        assert(dibs[i]);
        bits[i] = FreeImage_GetBits(dibs[i]);


    }

    width = FreeImage_GetWidth(dibs[0]);
    height = FreeImage_GetHeight(dibs[0]);


    glGenTextures(1, &gl_texID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, gl_texID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);


    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, num, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);


    for (GLuint i = 0; i < num; i++)
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_BGRA, GL_UNSIGNED_BYTE, bits[i]);


    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    for (GLuint i = 0; i < num; i++)
        FreeImage_Unload(dibs[i]);

    return gl_texID;





}


bool TextureObject::readRawFile(char* path, BYTE*bits)
{

    std::ifstream inputFile(path, std::ios::binary);

    int size = getRawSize(path);

    for (int j = size - 1; j >= 0; j--)
    {


        for (int i = 0; i < size; i++)

        {

            int current_index = j*size + i;
            int current_index2 = (size - 1 - j)*size + i;

            inputFile.seekg(current_index * 2 + 0, std::ios::beg);
            bits[current_index2 * 2 + 0] = inputFile.get();
            inputFile.seekg(current_index*2 + 1, std::ios::beg);
            bits[current_index2*2 + 1] = inputFile.get();

        }

    }

    inputFile.close();


    return true;
}





int TextureObject::getRawSize(char * path)
{

    std::ifstream inputFile(path, std::ios::binary);


    int size;


    inputFile.seekg(0, std::ios::end);

    if (!POWER_OF_TWO(int(sqrt((long)inputFile.tellg()))-1))
        size = sqrt((long)inputFile.tellg() / 2);
    else
        size = sqrt((long)inputFile.tellg());

    inputFile.close();

    return size;



}


GLuint TextureObject::create_texture(GLenum target, GLsizei width, GLsizei height,
                                     GLint internalFormat, GLint format, GLenum type, GLvoid * pixels,
                                     GLint f_param, GLint c_param, glm::vec4 b_color)
{


    GLuint tex_id;

    glGenTextures(1, &tex_id);
    glBindTexture(target, tex_id);
    glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, pixels);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, f_param);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, f_param);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, c_param);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, c_param);
    glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, ANISO);
    if (c_param == GL_CLAMP_TO_BORDER)
        glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, &b_color[0]);
    glBindTexture(target, 0);


    return tex_id;



}




bool TextureObject::CheckStatus(GLuint fbo)
{


    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

    switch (status)
    {

    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        DebugMsg("OpenGL framebuffer format not supported.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        DebugMsg("OpenGL framebuffer missing attachment.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        DebugMsg("OpenGL framebuffer attached images must have same dimensions.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        DebugMsg("OpenGL framebuffer attached images must have same format.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        DebugMsg("OpenGL framebuffer missing draw buffer.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        DebugMsg("OpenGL framebuffer missing read buffer.\n");
        return false;
    case GL_FRAMEBUFFER_COMPLETE_EXT:
        DebugMsg("FBO working!\n");
        return true;
    default:
        return true;
    }

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);





}






void TextureObject::CreateTexture(GLuint tex_type,
                                  GLenum target,
                                  GLsizei width, GLsizei height,
                                  GLint internalFormat, GLint format,
                                  GLenum type, GLvoid
                                  * pixels,
                                  GLint f_param,
                                  GLint c_param,
                                  glm::vec4 b_color)
{



    this->width = width;
    this->height = height;




    if (this->m_FBO)
    {



        glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);



        if (tex_type == COLOR_TYPE)
        {

            this->texture = new GLuint[this->num_tex];
            this->texture[0] = create_texture(target, width, height, internalFormat,
                                              format,
                                              type,
                                              pixels, f_param, c_param, b_color);


            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture[0], 0);
            GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(1, DrawBuffers);



        }
        else if (tex_type == DEPTH_TYPE)
        {

            this->depth = create_texture(target, width, height, internalFormat,
                                         format,
                                         type,
                                         pixels, f_param, c_param, b_color);



            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);


        }
        else if (tex_type == G_TYPE)
        {


            this->texture = new GLuint[this->num_tex];
            for (GLuint i = 0; i < this->num_tex; i++)
            {

                this->texture[i] = create_texture(target, width, height, internalFormat,
                                                  format,
                                                  type,
                                                  pixels, f_param, c_param, b_color);


                glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, this->texture[i], 0);
            }



            GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(this->num_tex, DrawBuffers);


        }



        CheckStatus(this->m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

}

void TextureObject::WriteTexture(GLuint width, GLuint height)
{


    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
