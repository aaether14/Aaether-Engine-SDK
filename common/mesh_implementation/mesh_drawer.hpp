#ifndef MESH_DRAWER
#define MESH_DRAWER




#include <stdafx.h>




#define MAX_BONES 128





/**
Holds entity manager
*/
class MeshDrawer : public AModule
{





public:



    /**
    Initialize entity manager
    */
    void Init();
    /**
    Cleans data
    */
    void Clean();
    /**
    Enables entity manager
    */
    void Enable();
    /**
    Renders entities
    */
    void Render();



};

#endif
