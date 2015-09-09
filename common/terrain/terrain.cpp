#include <stdafx.h>





void Terrain::Init()
{



}




void Terrain::Clean()
{



    glDeleteTextures(1, &colormap_tex);
    glDeleteTextures(1, &texture_array);
    glDeleteTextures(1, &normal_texture_array);


    delete heightField;




}



void Terrain::RenderQuad(Frustum * frustum, QuadNode * node)

{



    GLuint result = Math::SphereInFrustum(frustum, node->GetCenter(), node->GetRadius());




    if (!result)
    {


        node->SetVisible(false);
        return;


    }


    node->SetVisible(true);


    if (node->GetNodes().size() > 0)
        for (GLuint i = 0; i < 4; i++)
            RenderQuad(frustum, node->GetNodes()[i].get());

    else
        node->GetChunk()->Render(0);


}


void Terrain::Render(Frustum * frustum, bool wired)
{

    if (wired)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_PRIMITIVE_RESTART);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->colormap_tex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->texture_array);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->normal_texture_array);



    this->RenderQuad(frustum, q_tree->GetStartNode());


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    glDisable(GL_PRIMITIVE_RESTART);
    if (wired)glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}





void load_texture_set(char*path, GLuint &texture_array, GLfloat aniso)
{



    std::ifstream fin(path);
    GLuint n, i = 0;
    fin >> n;
    std::string tex_path;
    char ** textures = 0;
    textures = new char*[n];



    while (std::getline(fin, tex_path))
    {

        if (tex_path == "")continue;
        textures[i] = new char[strlen(tex_path.c_str())];
        strcpy(textures[i], tex_path.c_str());
        i++;
    }


    texture_array = TextureObject::create_texture_array(BASE_DIR, textures, n, aniso);
    fin.close();


}




void Terrain::LoadColorFiles(char*tile_path, char*texture_set_path, char *normal_set_path, char * texture_attributes_set)
{


    colormap_tex = TextureObject::load_texture(tile_path, GL_LINEAR, GL_LINEAR);
    load_texture_set(texture_set_path, this->texture_array, 8.0f);
    load_texture_set(normal_set_path, this->normal_texture_array, 1.0f);
    tex_data.reset(new TerrainShader::TextureAttributes[4]);
    LoadTextureAttributesSet(texture_attributes_set, tex_data.get());



}





GLfloat HeightAt(Terrain*terrain,GLfloat x, GLfloat z)
{

    x /= terrain->ScaleX();
    z /= terrain->ScaleZ();

    if (x < 0)
    {
        x = 0;
    }
    else if (x > terrain->Width() - 1)
    {
        x = terrain->Width() - 1;
    }
    if (z < 0)
    {
        z = 0;
    }
    else if (z > terrain->Height() - 1)
    {
        z = terrain->Height() - 1;
    }

    GLint leftX = (GLint)x;
    if (leftX == terrain->Width() - 1)
    {
        leftX--;
    }
    GLfloat fracX = x - leftX;

    GLint outZ = (GLint)z;
    if (outZ == terrain->Height() - 1)
    {
        outZ--;
    }
    GLfloat fracZ = z - outZ;

    GLfloat h11 = terrain->getHeight(leftX, outZ);
    GLfloat h12 = terrain->getHeight(leftX, outZ + 1);
    GLfloat h21 = terrain->getHeight(leftX + 1, outZ);
    GLfloat h22 = terrain->getHeight(leftX + 1, outZ + 1);

    return (1 - fracX) * ((1 - fracZ) * h11 + fracZ * h12) +
           fracX * ((1 - fracZ) * h21 + fracZ * h22);
}












void Terrain::SaveChunks(char * path,
                         BYTE*bits,
                         GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
                         GLuint chunk_height, GLuint chunk_width,
                         GLuint height, GLuint width,
                         GLuint mipmaps
                        )
{

    glm::vec3 *heightData = new glm::vec3[height*width];
    glm::vec2 *uvData = new glm::vec2[height*width];
    glm::vec3 *normalData2 = new glm::vec3[height*width];
    glm::vec3 *normalData = new glm::vec3[height*width];
    glm::vec3 * tangentData = new glm::vec3[height*width];

    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {

            GLuint current_index = z*width + x;

            heightData[current_index] = glm::vec3(
                                            x / GLfloat(width - 1)*fSizeX,
                                            (bits[current_index*2 + 0] + bits[current_index*2 + 1]*255) / 65025.0f*fSizeY1,
                                            z / GLfloat(height - 1)*fSizeZ
                                        );


            uvData[current_index] = glm::vec2(x / GLfloat(width), z / GLfloat(height));


        }

    }




    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            glm::vec3 sum(0.0f, 0.0f, 0.0f);

            glm::vec3 out;
            if (z > 0)
            {
                out = glm::vec3(0.0f, heightData[(z - 1)*width + x].y - heightData[z*width + x].y, -1.0f);
            }
            glm::vec3 in;
            if (z < height - 1)
            {
                in = glm::vec3(0.0f, heightData[(z + 1)*width + x].y - heightData[z*width + x].y, 1.0f);
            }
            glm::vec3 left;
            if (x > 0)
            {
                left = glm::vec3(-1.0f, heightData[z*width + (x - 1)].y - heightData[z*width + x].y, 0.0f);
            }
            glm::vec3 right;
            if (x < width - 1)
            {
                right = glm::vec3(1.0f, heightData[z*width + (x + 1)].y - heightData[z*width + x].y, 0.0f);
            }

            if (x > 0 && z > 0)
            {
                sum += glm::normalize(glm::cross(out, left));
            }
            if (x > 0 && z < height - 1)
            {
                sum += glm::normalize(glm::cross(left, in));
            }
            if (x < width - 1 && z < height - 1)
            {
                sum += sum += glm::normalize(glm::cross(in, right));
            }
            if (x < width - 1 && z > 0)
            {
                sum += glm::normalize(glm::cross(right, out));
            }

            normalData2[z*width + x] = sum;
        }
    }

    const float FALLOUT_RATIO = 0.5f;


    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {



            glm::vec3 sum = normalData2[z*width + x];

            if (x > 0)
            {
                sum += normalData2[z*width + (x - 1)] * FALLOUT_RATIO;
            }
            if (x < width - 1)
            {
                sum += normalData2[z*width + (x + 1)] * FALLOUT_RATIO;
            }
            if (z > 0)
            {
                sum += normalData2[(z - 1)*width + x] * FALLOUT_RATIO;
            }
            if (z < 0)
            {
                sum += normalData2[(z + 1)*width + x] * FALLOUT_RATIO;
            }

            if (glm::length(sum) == 0)
            {
                sum = glm::vec3(0.0f, 1.0f, 0.0f);
            }
            normalData[z*width + x] = sum;


        }
    }



    GLuint index_size = (width * 2 + 1)*(height - 1);
    GLuint *index_buffer = new GLuint[index_size];

    for (GLuint i = 0; i < height - 1; i++)
    {
        GLuint start = i*width;
        for (GLuint j = 0; j < width; j++)
        {
            index_buffer[i*(2 * width + 1) + j * 2] = start + j;
            index_buffer[i*(2 * width + 1) + j * 2 + 1] = start + width + j;
        }
        index_buffer[(i + 1)*(2 * width + 1) - 1] = width*height;
    }




    for (GLuint i = 0; i < GLint(index_size / 3) * 3 - 1; i++)

    {

        glm::vec3 v0, v1, v2;
        glm::vec2 t0, t1, t2;
        GLuint i1, i2, i3;

        if (index_buffer[i] == width*height)
        {
            i1 = i + 1;
            i2 = i + 2;
            i3 = i + 3;
        }
        else if (index_buffer[i + 1] == width*height)
        {
            i1 = i;
            i2 = i + 2;
            i3 = i + 3;
        }
        else if (index_buffer[i + 2] == width*height)
        {
            i1 = i;
            i2 = i + 1;
            i3 = i + 3;
        }
        else
        {
            i1 = i;
            i2 = i + 1;
            i3 = i + 2;
        }

        v0 = heightData[index_buffer[i1]];
        v1 = heightData[index_buffer[i2]];
        v2 = heightData[index_buffer[i2]];

        t0 = uvData[index_buffer[i1]];
        t1 = uvData[index_buffer[i2]];
        t2 = uvData[index_buffer[i3]];

        glm::vec3 Edge1 = v1 - v0;
        glm::vec3 Edge2 = v2 - v0;

        GLfloat DeltaU1 = t1.x - t0.x;
        GLfloat DeltaV1 = t1.y - t0.y;
        GLfloat DeltaU2 = t2.x - t0.x;
        GLfloat DeltaV2 = t2.y - t0.y;

        GLfloat f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

        glm::vec3 Tangent;

        Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
        Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
        Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

        tangentData[index_buffer[i1]] += Tangent;
        tangentData[index_buffer[i2]] += Tangent;
        tangentData[index_buffer[i3]] += Tangent;

    }

    for (GLuint i = 0; i < height*width; i++)
        glm::normalize(tangentData[i]);

    std::ofstream os(path, std::ios::binary);

    GLint num_chunks = ((width - 1) / (chunk_width - 1))*((height - 1) / (chunk_height - 1));
    os.write((const char*)&(num_chunks), sizeof(GLint));

    os.write((const char*)&(height), sizeof(GLint));
    os.write((const char*)&(width), sizeof(GLint));

    os.write((const char*)&(chunk_height), sizeof(GLint));
    os.write((const char*)&(chunk_width), sizeof(GLint));

    os.write((const char*)&(fSizeZ), sizeof(GLfloat));
    os.write((const char*)&(fSizeX), sizeof(GLfloat));
    os.write((const char*)&(fSizeY1), sizeof(GLfloat));

    os.write((const char*)&heightField[0], height*width*sizeof(GLfloat));



    GLuint t_width, t_height;
    index_size = 0;

    GLuint *mip_start_buffer = new GLuint[mipmaps];
    GLuint *mip_count_buffer = new GLuint[mipmaps];


    for (GLuint i = 0; i < mipmaps; i++)
    {

        mip_start_buffer[i] = index_size;

        t_width = (chunk_width - 1) / pow(2, i) + 1;
        t_height = (chunk_height - 1) / pow(2, i) + 1;

        index_size += (t_width * 2 + 1)*(t_height - 1);

        mip_count_buffer[i] = index_size - mip_start_buffer[i];

    }


    index_buffer = new GLuint[index_size];

    GLuint offset = 0;

    for (GLuint k = 0; k < mipmaps; k++)
    {
        t_width = (chunk_width - 1) / pow(2, k) + 1;
        t_height = (chunk_height - 1) / pow(2, k) + 1;


        for (GLuint i = 0; i < t_height - 1; i++)
        {
            GLuint start = i*chunk_width;
            for (GLuint j = 0; j < t_width; j++)
            {
                index_buffer[offset+i*(2 * t_width + 1) + j * 2] = pow(2,k)*(start + j);
                index_buffer[offset+i*(2 * t_width + 1) + j * 2 + 1] = pow(2,k)*(start + chunk_width + j);
            }
            index_buffer[offset+(i + 1)*(2 * t_width + 1) - 1] = chunk_width*chunk_height;
        }


        offset += (t_width * 2 + 1)*(t_height - 1);


    }

    os.write((const char*)&index_size, sizeof(GLuint));
    os.write((const char*)&index_buffer[0], index_size*sizeof(GLuint));


    os.write((const char*)&mipmaps, sizeof(GLuint));
    os.write((const char*)&mip_start_buffer[0], mipmaps*sizeof(GLuint));
    os.write((const char*)&mip_count_buffer[0], mipmaps*sizeof(GLuint));



    QuadTree*tree = new QuadTree();


    tree->Create((height - 1) / (chunk_height - 1) + 1, (width - 1) / (chunk_width - 1) + 1,
                 chunk_height,chunk_width,
                 width,
                 heightData);


    tree->Save(&os,
               width,
               chunk_height,
               chunk_width,
               heightData,
               uvData,
               normalData,
               tangentData,
               (chunk_width - 1)*this->fSizeX,
               (chunk_height - 1)*this->fSizeZ);


    os.close();

    delete[] heightData;
    delete[] uvData;
    delete[] normalData;
    delete[] normalData2;
    delete[] tangentData;
    delete[] index_buffer;

}








void Terrain::LoadChunks(char *path)
{

    GLdouble time = glfwGetTime();
    printf("Loaded terrain in: ");

    GLint num_chunks,
          height, width,
          chunk_height, chunk_width;


    GLfloat fSizeZ, fSizeX,fSizeY1;

    std::ifstream is(path, std::ios::binary);

    is.read((char*)&num_chunks, sizeof(GLint));
    this->num_chunks = num_chunks;


    is.read((char*)&height, sizeof(GLint));
    is.read((char*)&width, sizeof(GLint));
    this->HEIGHT = height;
    this->WIDTH = width;

    is.read((char*)&chunk_height, sizeof(GLint));
    is.read((char*)&chunk_width, sizeof(GLint));
    this->chunk_rows = (height - 1) / (chunk_height - 1);
    this->chunk_cols = (width - 1) / (chunk_width - 1);



    is.read((char*)&fSizeZ, sizeof(GLfloat));
    is.read((char*)&fSizeX, sizeof(GLfloat));
    is.read((char*)&fSizeY1, sizeof(GLfloat));
    this->fSizeX = fSizeX / GLfloat(WIDTH - 1);
    this->fSizeZ = fSizeZ / GLfloat(HEIGHT - 1);

    this->heightField = new GLfloat[height*width];
    is.read((char*)&heightField[0], height*width*sizeof(GLfloat));


    GLuint index_size;
    is.read((char*)&index_size, sizeof(GLuint));
    GLuint *index_buffer = new GLuint[index_size];
    is.read((char*)&index_buffer[0], index_size*sizeof(GLuint));


    GLuint mipmaps;
    is.read((char*)&mipmaps, sizeof(GLuint));
    this->max_mips = mipmaps;

    GLuint *mip_start_buffer = new GLuint[mipmaps];
    is.read((char*)&mip_start_buffer[0], mipmaps*sizeof(GLuint));


    GLuint *mip_count_buffer = new GLuint[mipmaps];
    is.read((char*)&mip_count_buffer[0], mipmaps*sizeof(GLuint));



    glm::vec3 *heightData = new glm::vec3[chunk_height*chunk_width];
    glm::vec2 *uvData = new glm::vec2[chunk_height*chunk_width];
    glm::vec3 *normalData = new glm::vec3[chunk_height*chunk_width];
    glm::vec3 * tangentData = new glm::vec3[chunk_height*chunk_width];





    q_tree.reset(new QuadTree);
    q_tree->Load(&is,
                 chunk_width,
                 chunk_height,
                 heightData,
                 uvData,
                 normalData,
                 tangentData,
                 index_buffer,
                 index_size,
                 mip_start_buffer,
                 mip_count_buffer,
                 mipmaps,
                 (chunk_width - 1)*this->fSizeX,
                 (chunk_height - 1)*this->fSizeZ);



    is.close();
    printf("%1.5f seconds\n\n", glfwGetTime() - time);

}


void Terrain::CreateTerra(char*path,
                          char*ch1,
                          GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
                          GLuint chunk_height, GLuint chunk_width,
                          GLuint mipmaps)

{


    WIDTH  = TextureObject::getRawSize(ch1);
    HEIGHT = TextureObject::getRawSize(ch1);



    assert(chunk_height <= HEIGHT || chunk_width <= WIDTH);
    assert(chunk_height >= chunk_width);
    assert(chunk_height >= 17 && chunk_width >= 17);
    assert(POWER_OF_TWO(chunk_height - 1) && POWER_OF_TWO(chunk_width - 1));



    this->fSizeX = fSizeX / GLfloat(WIDTH - 1);
    this->fSizeZ = fSizeZ / GLfloat(HEIGHT - 1);
    heightField = new GLfloat[WIDTH * HEIGHT];



    BYTE * bits = new BYTE[WIDTH*HEIGHT*2];
    TextureObject::readRawFile(ch1, bits);



    for (int z = 0; z < HEIGHT; z++)
    {
        for (int x = 0; x < WIDTH; x++)
        {


            GLuint current_index = z*WIDTH + x;
            heightField[current_index] = (bits[current_index * 2 + 0] + bits[current_index * 2 + 1] * 255) / 65025.0f*fSizeY1;

        }

    }


    SaveChunks(path,
               bits,
               fSizeX, fSizeZ, fSizeY1,
               chunk_height, chunk_width,
               HEIGHT, WIDTH,
               mipmaps);


}

