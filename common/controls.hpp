#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <stdafx.h>







/**
Derives from controller source in order to hold engine data like camera, filters and scene resources
*/
class Controller : public ControllerSource
{


    std::string project_name;



public:




    /**
    Enable controller source and camera computations
    */
    void Enable();


    /**
    Clean engine's data
    */
    void Clean();
    /**
    Calls Clean()
    */
    inline  ~Controller()
    {
        this->Clean();
    }



    /**
    Calls ControllerSource constructor
    */
    inline Controller() : ControllerSource() {}


    /**
    Initializes Controller Source, camera and game object
    */
    void Init();
    /**
    Get project name
    */
    std::string GetProjectName()
    {
        return project_name;
    }


};




#endif
