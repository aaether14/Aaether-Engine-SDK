#ifndef STATIC_BUILDER_HPP
#define STATIC_BUILDER_HPP





#include <stdafx.h>





/**


entity palette implementation
also stores information affecting scene outliner and transform tab from ui


*/
class EntityPalette : public AModule
{


    //UI data

    ui_SceneOutliner * ui_scene_outliner;
    ui_TransformTab * ui_transform_tab;



    GLboolean visible;
    Entity * current_entity;
    EntityInstance * current_instance;
    GLuint entity_counter;




    /**
    Compute Model matrix from entity information
    */
    glm::mat4 GetMatrix(Entity * entity);
    /**
    Find an appropriate name for the new instance
    */
    std::string GetInstanceName(SceneInfo * scene_info);




public:


    /**
    Get pointer to scene outliner
    */
    inline ui_SceneOutliner * GetSceneOutliner()
    {
        return ui_scene_outliner;
    }



    /**
    Initialize data*/
    void Init();
    /**
    Cleans data
    */
    void Clean();
    /**
    Render the currently selected entity
    */
    void Enable();
    /**
    Manage input
    */
    void ManagePaletteInput();
    /**
    Entity placement
    */
    void ManageEntityPlacing();
    /**
    Manage filling of scene outliner with information
    */
    void ManageSceneOutliner();




};


#endif
