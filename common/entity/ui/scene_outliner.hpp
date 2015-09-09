#ifndef SCENE_OUTLINER_HPP
#define SCENE_OUTLINER_HPP




#include <stdafx.h>



/**


Scene outliner
WIP


*/
class ui_SceneOutliner
{


    CEGUI::Tree * Treebox;
    std::map<boost::shared_ptr<AEntityInstance>, boost::shared_ptr<CEGUI::TreeItem> > instance_map;
    boost::shared_ptr<AEntityInstance> selected_instance;





    /**
    Callback triggered EventSelectionChanged event
    */
    bool SelectionChanged(const CEGUI::EventArgs& e);


    /**
    Callback to process clicking 'X'
    */
    inline bool CloseWindow(const CEGUI::EventArgs& e)
    {
        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Frame2")->hide();
        return 1;
    }



public:


    /**
    Calls Init()
    */
    inline ui_SceneOutliner()
    {
        this->Init();
    }
    /**
    Initialize data
    */
    void Init();



    /**
    Calls Clean()
    */
    inline ~ui_SceneOutliner()
    {
        this->Clean();
    }
    /**
    Cleans data
    */
    void Clean();


    /**
    Add item to scene outliner (UI wise)
    */
    void AddItem(AEntityInstance * instance);



    /**
    Update scene outliner
    */
    void Update(AEntityInstance * instance);


    /**
    Clear scene outliner
    */
    void ClearItems();



};



#endif
