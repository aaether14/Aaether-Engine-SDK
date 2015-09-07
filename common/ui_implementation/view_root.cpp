#include <stdafx.h>





void ui_ViewRoot::Init(CEGUI::Window * Root)
{



	this->Root = Root;




	Root->getChild("Menubar/MenuItem2/PopupMenu/MenuItem")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ViewRoot::ViewSettings, this));


	Root->getChild("Menubar/MenuItem2/PopupMenu/MenuItem2")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ViewRoot::ViewSceneOutliner, this));


	Root->getChild("Menubar/MenuItem2/PopupMenu/MenuItem3")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ViewRoot::ViewTransform, this));





}




void ui_ViewRoot::Clean()
{




}




void ui_ViewRoot::SyncUI()
{




}

