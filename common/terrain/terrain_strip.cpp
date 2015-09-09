#include <stdafx.h>








void TerrainStrip::Init()
{
    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
}





void TerrainStrip::Clear()
{
    glDeleteVertexArrays(1, &this->m_VAO);
    glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
}






void TerrainStrip::Render(GLuint lod)
{


    lod = std::min(lod, this->mipmaps - 1);


    glBindVertexArray(this->m_VAO);


    glDrawElements(GL_TRIANGLE_STRIP,
                   this->mip_count_buffer[lod],
                   GL_UNSIGNED_INT,
                   (GLvoid*)(sizeof(GLuint)*this->mip_start_buffer[lod]));



    glBindVertexArray(0);
}

void TerrainStrip::Create(GLuint strip_width, GLuint strip_height,
                          glm::vec3 * heightData,
                          glm::vec2 * uvData,
                          glm::vec3 * normalData,
                          glm::vec3 * tangentData,
                          GLuint *index_buffer,
                          GLuint index_size,
                          GLuint *mip_start_buffer,
                          GLuint *mip_count_buffer,
                          GLuint mipmaps
                         )
{

    this->mipmaps = mipmaps;
    this->mip_start_buffer = new GLuint[this->mipmaps];
    memcpy(this->mip_start_buffer, mip_start_buffer, sizeof(GLuint)*this->mipmaps);
    this->mip_count_buffer = new GLuint[this->mipmaps];
    memcpy(this->mip_count_buffer, mip_count_buffer, sizeof(GLuint)*this->mipmaps);



    this->height = strip_height;
    this->width = strip_width;



    glBindVertexArray(this->m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*width*height, heightData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * width*height, uvData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*width*height, normalData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TANGENT_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*width*height, tangentData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(TANGENT_LOCATION);
    glVertexAttribPointer(TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*index_size, index_buffer, GL_STATIC_DRAW);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(width*height);

    glBindVertexArray(0);

}

