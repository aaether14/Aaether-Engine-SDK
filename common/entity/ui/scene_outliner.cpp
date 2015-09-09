#include <stdafx.h>




void ui_SceneOutliner::Init()
{




    CEGUI::Window *Root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    static_cast<CEGUI::FrameWindow*>(Root->getChild("Frame2"))->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
            CEGUI::Event::Subscriber(&ui_SceneOutliner::CloseWindow, this));



    Treebox = static_cast<CEGUI::Tree*>(Root->getChild("Frame2/SceneOutliner"));
    Treebox->initialise();
    Treebox->subscribeEvent(CEGUI::Tree::EventSelectionChanged,
                            CEGUI::Event::Subscriber(&ui_SceneOutliner::SelectionChanged, this));




    ClearItems();



}





bool ui_SceneOutliner::SelectionChanged(const CEGUI::EventArgs& e)
{



    return 1;


}




void ui_SceneOutliner::Clean()
{





}




void ui_SceneOutliner::AddItem(AEntityInstance * instance)
{








}




void ui_SceneOutliner::Update(AEntityInstance * instance)
{




}




void ui_SceneOutliner::ClearItems()
{





}
