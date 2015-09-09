#include <stdafx.h>




void ui_TransformTab::Init()
{


    //Provide callbacks to determine updates


    CEGUI::Window *Root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    FrameRoot = Root->getChild("Frame3");
    FrameRoot->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
                              CEGUI::Event::Subscriber(&ui_TransformTab::CloseWindow, this));




    static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::RadioPositionChanged, this));
    static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton2"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::RadioRotationChanged, this));
    static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton3"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::RadioScaleChanged, this));



    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::SpinnerXChanged, this));
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::SpinnerYChanged, this));
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
            CEGUI::Event::Subscriber(&ui_TransformTab::SpinnerZChanged, this));




    p_info = new PaletteInfo();
    p_info->Reset();


    update_id = 0;
    static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton"))->setSelected(true);


}




void ui_TransformTab::Clean()
{





}




void ui_TransformTab::UpdateData()
{

    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->setCurrentValue(p_info->trans[update_id].x);
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->setCurrentValue(p_info->trans[update_id].y);
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->setCurrentValue(p_info->trans[update_id].z);

}



void ui_TransformTab::UpdateStepData(GLfloat step_size)
{

    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->setStepSize(step_size);
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->setStepSize(step_size);
    static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->setStepSize(step_size);


}


bool ui_TransformTab::RadioPositionChanged(const CEGUI::EventArgs& e)
{

    update_id = 0;
    UpdateData();
    UpdateStepData(0.125f);
    return 1;

}



bool ui_TransformTab::RadioRotationChanged(const CEGUI::EventArgs& e)
{

    update_id = 1;
    UpdateData();
    UpdateStepData(0.125f);
    return 1;

}



bool ui_TransformTab::RadioScaleChanged(const CEGUI::EventArgs& e)
{

    update_id = 2;
    UpdateData();
    UpdateStepData(0.125f);
    return 1;

}




bool ui_TransformTab::SpinnerXChanged(const CEGUI::EventArgs& e)
{

    p_info->trans[update_id].x = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->getCurrentValue();
    return 1;
}



bool ui_TransformTab::SpinnerYChanged(const CEGUI::EventArgs& e)
{

    p_info->trans[update_id].y = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->getCurrentValue();
    return 1;
}



bool ui_TransformTab::SpinnerZChanged(const CEGUI::EventArgs& e)
{

    p_info->trans[update_id].z = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->getCurrentValue();
    return 1;
}


