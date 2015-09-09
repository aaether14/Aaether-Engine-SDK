#ifndef TERRAIN_WRAPPER
#define TERRAIN_WRAPPER




#include <stdafx.h>



class TerrainWrapper : public TerrainShader
{


    /**
    Terrain data
    */
    Terrain* terra;



    /**
    Manage collision between player and terrain
    */
    void ManagePlayerCollision(Controller*ctrl, bool null_gravity);



public:



    /**
    Initialize module
    */
    void Init();
    /**
    Clean module data
    */
    void Clean();
    /**
    Enable module
    */
    void Enable();


    /**
    Render module information
    */
    void Render();






};


#endif
