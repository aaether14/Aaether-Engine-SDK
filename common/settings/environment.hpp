#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP





#include <stdafx.h>







/**


Storing lighting state
WIP


*/
class Environment : public AStateSaver
{




public:




    glm::vec3 sun_dir;
    glm::vec3 sun_color;
    glm::vec3 fog_color;


    GLfloat model_ambient;
    GLfloat terrain_ambient;
    GLfloat model_diffuse;
    GLfloat terrain_diffuse;
    GLfloat model_bright;
    GLfloat terrain_bright;
    GLfloat fog_density;



    /**
    Calls Init()
    */
    inline Environment(char * path)
    {
        this->Init(path);
    }
    /**
    Initialize state saver with the path of the file it will affect
    */
    void Init(char * path);


    /**
    Reset data
    */
    void Reset();
    /**
    Save data to file
    */
    void Save();
    /**
    Load data from file
    */
    void Load();


};



#endif
