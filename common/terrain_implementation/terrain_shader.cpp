#include <stdafx.h>





void TerrainShader::Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix)
{

    Set("M", ModelMatrix);
    Set("V", ViewMatrix);
    Set("P", ProjectionMatrix);

}



void TerrainShader::Init()
{


    Add("data/shaders/terrain_vert.txt", GL_VERTEX_SHADER);
    Add("data/shaders/terrain_frag.txt", GL_FRAGMENT_SHADER);
    Link();



    AddVariable("LightMatrix");
    AddVariable("M");
    AddVariable("V");
    AddVariable("P");
    AddVariable("myTextureSampler");
    AddVariable("myTextureSampler2");
    AddVariable("myTextureSampler3");
    AddVariable("shadow_map");


    for (GLuint i = 0; i < 4; i++)
    {


        char name[128];
        sprintf(name, "attributes[%d].diffuse_scale", i);
        AddVariable(name);
        sprintf(name, "attributes[%d].detail_scale", i);
        AddVariable(name);
        sprintf(name, "attributes[%d].diffuse_intensity", i);
        AddVariable(name);


    }



    m_light = new Light(this);



}



void TerrainShader::SendTextureAttributes(TextureAttributes*tex_attributes, GLuint n)
{


    for (GLuint i = 0; i < 4; i++)
    {


        char name[128];
        sprintf(name, "attributes[%d].diffuse_scale", i);
        Set(name, tex_attributes[i].diffuse_scale);
        sprintf(name, "attributes[%d].detail_scale", i);
        Set(name, tex_attributes[i].detail_scale);
        sprintf(name, "attributes[%d].diffuse_intensity", i);
        Set(name, tex_attributes[i].diffuse_intensity);


    }


}




void TerrainShader::Clean()
{

    Shader::Clean();


    if (m_light)
        delete m_light;


}



void LoadTextureAttributesSet(char * path, TerrainShader::TextureAttributes*tex_data)
{

    GLuint n;

    std::ifstream fin(path);


    fin >> n;


    for (GLuint i = 0; i < n; i++)
        fin >> tex_data[i].diffuse_scale >> tex_data[i].detail_scale >> tex_data[i].diffuse_intensity;


    fin.close();


}
