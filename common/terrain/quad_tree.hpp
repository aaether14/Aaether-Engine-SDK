#ifndef QUAD_TREE
#define QUAD_TREE





#include <stdafx.h>





/**

Quad tree implementation


*/
class QuadNode
{


    glm::vec3 h_points[4];
    glm::vec3 center;



    GLfloat radius;
    GLuint ind;
    GLboolean visible;



    std::vector<boost::shared_ptr<QuadNode> > nodes;
    boost::shared_ptr < TerrainStrip > chunk;




public:


    /**
    Get center of node
    */
    inline glm::vec3 GetCenter()
    {
        return center;
    }
    /**
    Get radius of node
    */
    inline GLfloat GetRadius()
    {
        return radius;
    }
    /**
    Get index of node
    */
    inline GLuint GetInd()
    {
        return ind;
    }


    /**
    Set if quad node should be visible
    */
    inline void SetVisible(GLboolean visible)
    {
        this->visible = visible;
    }
    /**
    Query node visibility
    */
    inline GLboolean GetVisible()
    {
        return this->visible;
    }


    /**
    Get child nodes
    */
    inline std::vector<boost::shared_ptr<QuadNode> > GetNodes()
    {
        return nodes;
    }
    /**
    Pointer to node's TerrainStrip (if terminal node, otherwise NULL)
    */
    inline TerrainStrip *GetChunk()
    {
        return chunk.get();
    }




    /**
    Create out of 4 points and chunk_height and chunk_width to see where to stop splitting
    */
    void Create(glm::ivec2 sq_points[4], GLuint chunk_height, GLuint chunk_width,
                GLuint width,
                glm::vec3 *heightData);



    /**
    Save quad node to file
    */
    void Save(std::ofstream *fout, GLuint width, GLuint chunk_height, GLuint chunk_width,
              glm::vec3 *heightData,
              glm::vec2 *uvData,
              glm::vec3 *normalData,
              glm::vec3 *tangentData,
              GLfloat min_x,
              GLfloat min_z);




    /**
    Load quad node from file
    */
    void Load(std::ifstream *fin,
              GLuint chunk_width, GLuint chunk_height,
              glm::vec3 * heightData,
              glm::vec2 * uvData,
              glm::vec3 * normalData,
              glm::vec3 * tangentData,
              GLuint *index_buffer,
              GLuint index_size,
              GLuint *mip_start_buffer,
              GLuint *mip_count_buffer,
              GLuint mipmaps,
              GLfloat min_x,
              GLfloat min_z);






};


class QuadTree
{




    boost::shared_ptr<QuadNode> start_node;



    GLuint tree_width, tree_height;
    GLfloat min_x, min_z;




public:


    /**
    Get width of a chunk
    */
    inline GLfloat GetMinX()
    {
        return this->min_x;
    }
    /**
    Get height of a chunk
    */
    inline GLfloat GetMinZ()
    {
        return this->min_z;
    }


    /**
    Pointer to starting node
    */
    inline QuadNode* GetStartNode()
    {
        return start_node.get();
    }


    /**
    Get width (number of chunks)
    */
    inline GLuint GetWidth()
    {
        return this->tree_width;
    }
    /**
    Get height (number of chunks)
    */
    inline GLuint GetHeight()
    {
        return this->tree_height;
    }



    /**
    Initialize starting node
    */
    inline QuadTree()
    {
        start_node.reset(new QuadNode);
    }





    /**
    Create tree
    */
    void Create(GLuint quad_height, GLuint quad_width,
                GLuint chunk_height, GLuint chunk_width,
                GLuint width,
                glm::vec3 *heightData);




    /**
    Save tree to file*/
    void Save(std::ofstream *fout,GLuint width,GLuint chunk_height,GLuint chunk_width,
              glm::vec3 *heightData,
              glm::vec2 *uvData,
              glm::vec3 *normalData,
              glm::vec3 *tangentData,
              GLfloat min_x,
              GLfloat min_z);



    /**
    Load tree from file
    */
    void Load(std::ifstream *fin,
              GLuint chunk_width, GLuint chunk_height,
              glm::vec3 * heightData,
              glm::vec2 * uvData,
              glm::vec3 * normalData,
              glm::vec3 * tangentData,
              GLuint *index_buffer,
              GLuint index_size,
              GLuint *mip_start_buffer,
              GLuint *mip_count_buffer,
              GLuint mipmaps,
              GLfloat min_x,
              GLfloat min_z);


};





#endif




