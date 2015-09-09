#include <stdafx.h>




void RootSettings::Init(ResourceLoader * res, CEGUI::Window * Root)
{


    is_inside_window = false;
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


    static_cast<CEGUI::FrameWindow*>(Root->getChild("Frame"))->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
            CEGUI::Event::Subscriber(&RootSettings::CloseWindow, this));


    Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("lighting.layout"));
    Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("ssao.layout"));
    Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("hdr.layout"));
    Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("fxaa.layout"));
    Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("dof.layout"));



    Root->getChild("Frame")->subscribeEvent(CEGUI::Window::EventMouseLeavesArea,
                                            CEGUI::Event::Subscriber(&RootSettings::MouseOutside, this));

    Root->getChild("Frame")->subscribeEvent(CEGUI::Window::EventMouseEntersArea,
                                            CEGUI::Event::Subscriber(&RootSettings::MouseInside, this));



    Environment * env = static_cast<Environment*>(res->Get("Environment"));
    FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));



    ui_lighting_root = new ui_LightingRoot(env, Root);
    ui_filter_root = new ui_FilterRoot(f_settings, Root);




}




void RootSettings::Clean()
{


    delete ui_lighting_root;
    delete ui_filter_root;


}




void RootSettings::Render(Controller * ctrl, CEGUI::Window * Root)
{


    if (!is_inside_window && ctrl->GetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
        Root->getChild("Frame")->deactivate();




    ui_lighting_root->SyncUI();
    ui_filter_root->SyncUI();


}

