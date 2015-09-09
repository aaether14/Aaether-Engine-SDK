#ifndef AAETHER_LOADER
#define AAETHER_LOADER





#include <stdafx.h>




#define INVALID_MATERIAL 0xFFFFFFFF





/**


Own model format implementation
Using Assimp to convert from other formats into binary data
for faster acces


*/
class Aa_model : public AModel
{


    /**
    In order to allocate OpenGL memory for vertex data
    */
    enum VB_TYPES
    {
        INDEX_BUFFER,
        POS_VB,
        NORMAL_VB,
        TEXCOORD_VB,
        BONE_VB,
        NUM_VBs
    };


    GLuint m_VAO;
    GLuint m_Buffers[NUM_VBs];



    /**
    Mesh entry of a 3d model
    */
    struct Aa_entry
    {
        Aa_entry()
        {
            NumIndices = 0;
            BaseVertex = 0;
            BaseIndex = 0;
            MaterialIndex = INVALID_MATERIAL;
        }

        GLuint NumIndices;
        GLuint BaseVertex;
        GLuint BaseIndex;
        GLuint MaterialIndex;
    };


    std::vector<Aa_entry> m_Entries;
    std::vector<GLuint> m_Textures;


public:


    /**
    Initializes data
    */
    Aa_model();
    /**
    Calls Clean()
    */
    ~Aa_model();
    /**
    Cleans data
    */
    void Clean();


    /**
    Loads a .aao
    */
    int Load(const char*path);
    /**
    Renders model
    */
    void Render();



};

#endif
